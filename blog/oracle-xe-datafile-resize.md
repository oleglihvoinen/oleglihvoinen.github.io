---
layout: default
title: "Oracle XE 10g Size Limit and Datafile Resizing – Solving ORA-03297"
date: 2025-11-10
description: "A detailed walkthrough of how to resolve ORA-03297: file contains used data beyond requested RESIZE value in Oracle Database 10g XE after hitting the 5GB limit."
---

# 🧱 Oracle 10g XE: Resizing Datafiles and Solving ORA-03297

When Oracle XE hits the hard 5 GB user-data limit you can encounter failures across the instance — the APEX web UI may stop working and background operations can fail. A common symptom is the resize error:

```sql
ORA-03297: file contains used data beyond requested RESIZE value
```

This guide explains why that happens and shows a safe, repeatable approach to compacting a datafile by moving segments (tables, indexes, LOBs) away from the end of the file so Oracle will accept a RESIZE.

---

## 🚨 Why ORA-03297 Happens

Oracle stores data in blocks. If any block near the end of a datafile is occupied, RESIZE cannot shrink past that block. Even when the file reports much free space, occupied high-block segments prevent shrinking.

---

## 🔍 Initial checks

Find the datafile(s) and their file_id(s):

```sql
-- List datafiles and sizes
SELECT file_id, tablespace_name, file_name, bytes/1024/1024 AS MB
FROM dba_data_files
ORDER BY 1;
```

Check the highest allocated block in a file:

```sql
SELECT MAX(block_id) AS max_block_id
FROM dba_extents
WHERE file_id = :file_id;
```

Identify segments that live near the end of the file:

```sql
SELECT owner, segment_name, segment_type, block_id, bytes/1024/1024 AS MB
FROM dba_extents
WHERE file_id = :file_id
ORDER BY block_id DESC;
```

Replace :file_id with the numeric file_id from the first query. These queries let you see which segments prevent resizing.

---

## 🧰 Preparatory cleanup (APEX-specific tips)

If APEX or EPG is down, freeing SYSAUX space can restore web access:

```sql
-- Drop old/unused APEX schemas (example, check names carefully first)
-- DROP USER FLOWS_030000 CASCADE;

-- Remove obsolete APEX images from the filesystem (if applicable)
-- rm -rf /path/to/apex/images/*
```

Clean APEX file-storage objects (run as appropriate owner or as SYS where needed):

```sql
-- Example: delete old flows_files objects (USE WITH CAUTION)
DELETE FROM FLOWS_FILES.WWV_FLOW_FILE_OBJECTS$ WHERE <your_filter>;
COMMIT;
```

Always verify what you delete; back up if uncertain.

---

## ⚠️ Why DBMS_SPACE shrink may not help

You can call database-level shrink APIs:

```plsql
BEGIN
  dbms_space.database_level_shrink;
END;
/
```

However, on many XE installs these run without error but do not actually reduce file size. The reliable approach is to move the segments that sit near the file end.

---

## ✅ The reliable approach: move segments and resize

The approach:

1. Identify the datafile and its file_name and file_id.
2. Find the highest block_id used in that file.
3. Move (or rebuild) segments that occupy high block positions:
   - ALTER TABLE ... MOVE
   - ALTER INDEX ... REBUILD
   - ALTER TABLE ... MOVE LOB(...)
4. Attempt ALTER DATABASE DATAFILE ... RESIZE after moving those segments.
5. Repeat until RESIZE succeeds.

Run these steps as SYS. Below is a tested PL/SQL helper script that automates scanning the highest blocks, moving objects found there, then attempting a RESIZE. Update l_file_id to match the target datafile.

```plsql
-- Run as SYS. CHANGE l_file_id to your USERS tablespace file_id.
SET SERVEROUTPUT ON SIZE 1000000

DECLARE
  l_orig_file_size_bytes NUMBER := 1;
  l_new_file_size_bytes  NUMBER := 0;
  l_block_size           NUMBER;
  l_file_id              NUMBER := 4;  -- << change this to your file_id
  l_block_id             NUMBER;
  l_tablespace_name      VARCHAR2(1000);
  l_file_name            VARCHAR2(1000);
  l_size_kb              NUMBER;
BEGIN
  SELECT tablespace_name, file_name
    INTO l_tablespace_name, l_file_name
    FROM dba_data_files
   WHERE file_id = l_file_id;

  SELECT block_size
    INTO l_block_size
    FROM dba_tablespaces
   WHERE tablespace_name = l_tablespace_name;

  WHILE l_orig_file_size_bytes > l_new_file_size_bytes LOOP
    -- refresh file size and highest block used
    SELECT bytes INTO l_orig_file_size_bytes FROM dba_data_files WHERE file_id = l_file_id;
    SELECT NVL(MAX(block_id), 0) INTO l_block_id FROM dba_extents WHERE file_id = l_file_id;
    SELECT l_block_size * l_block_id INTO l_new_file_size_bytes FROM dual;

    FOR i IN (
      SELECT segment_name, owner, segment_type
        FROM dba_extents
       WHERE file_id = l_file_id
         AND block_id = l_block_id
    ) LOOP
      dbms_output.put_line(i.owner || '.' || i.segment_name || ' found and will be moved/rebuilt, type ' || i.segment_type);

      IF i.segment_type = 'TABLE' THEN
        EXECUTE IMMEDIATE 'ALTER TABLE "' || i.owner || '"."' || i.segment_name || '" MOVE TABLESPACE "' || l_tablespace_name || '"';
      ELSIF i.segment_type = 'INDEX' THEN
        EXECUTE IMMEDIATE 'ALTER INDEX "' || i.owner || '"."' || i.segment_name || '" REBUILD TABLESPACE "' || l_tablespace_name || '"';
      ELSIF i.segment_type IN ('LOBSEGMENT','LOBINDEX') THEN
        FOR j IN (
          SELECT table_name, owner, column_name
            FROM dba_lobs
           WHERE index_name = i.segment_name
              OR segment_name = i.segment_name
        ) LOOP
          EXECUTE IMMEDIATE
            'ALTER TABLE "' || j.owner || '"."' || j.table_name ||
            '" MOVE LOB("' || j.column_name || '") STORE AS (TABLESPACE "' || l_tablespace_name || '")';
        END LOOP;
      ELSE
        dbms_output.put_line(i.owner || '.' || i.segment_name || ' needs manual handling, type ' || i.segment_type);
        -- Exit or continue based on your choice:
        -- EXIT;
      END IF;
    END LOOP;

    l_size_kb := ROUND(l_new_file_size_bytes / 1024, -1);
    BEGIN
      EXECUTE IMMEDIATE 'ALTER DATABASE DATAFILE ''' || l_file_name || ''' RESIZE ' || l_size_kb || 'K';
      dbms_output.put_line('Resized ' || l_file_name || ' to ' || l_size_kb || ' KBytes');
    EXCEPTION
      WHEN OTHERS THEN
        dbms_output.put_line('Resize failed: ' || SQLERRM);
    END;
  END LOOP;
EXCEPTION
  WHEN OTHERS THEN
    dbms_output.put_line('Script error: ' || SQLERRM);
END;
/
```

Notes:
- Use SET SERVEROUTPUT ON with a sufficiently large buffer to capture messages.
- The script prints moves and resize attempts; a buffer overflow in DBMS_OUTPUT is harmless to the process but you may miss some output — use logging if needed.
- Always test in a non-production environment first and have backups.

---

## 🔄 Rebuild unusable indexes

After moving segments you may need to rebuild unusable indexes:

```sql
SELECT 'ALTER INDEX ' || owner || '.' || index_name ||
       ' REBUILD TABLESPACE ' || tablespace_name || ';' AS ddl
FROM dba_indexes
WHERE status = 'UNUSABLE'
  AND tablespace_name = 'USERS';
```

Run the printed DDL statements as SYS or the appropriate owner.

---

## 📊 Helpful monitoring queries

Tablespace usage:

```sql
SELECT tablespace_name, ROUND(SUM(bytes)/1024/1024,2) AS MB_USED
FROM dba_segments
GROUP BY tablespace_name
ORDER BY MB_USED DESC;
```

Free space by tablespace (from DBA_FREE_SPACE):

```sql
SELECT tablespace_name, ROUND(SUM(bytes)/1024/1024,2) AS MB_FREE
FROM dba_free_space
GROUP BY tablespace_name
ORDER BY MB_FREE DESC;
```

---

## 💡 Lessons & Best Practices

- Oracle XE enforces the 5 GB user-data limit — plan for it.
- Regularly clean SYSAUX and application file stores (APEX FLOWS_FILES) to avoid sudden service disruptions.
- Shrink operations are not always supported — moving/rebuilding segments is the reliable method.
- Backup before major DDL operations.
- Monitor segments and tablespace usage proactively to avoid hitting the limit.

---

## ✅ Conclusion

ORA-03297 doesn't require a full reinstall. By cleaning SYSAUX/flows files, moving segments away from the file end, and then resizing, you can reclaim gigabytes and restore APEX and EPG functionality.

"Before rebuilding everything, try moving what’s already there — it may be all you need."
