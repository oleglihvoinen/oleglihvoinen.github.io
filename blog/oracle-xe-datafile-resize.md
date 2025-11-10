---
layout: default
title: "Oracle XE 10g Size Limit and Datafile Resizing – Solving ORA-03297"
date: 2025-11-10
description: "A detailed walkthrough of how to resolve ORA-03297: file contains used data beyond requested RESIZE value in Oracle Database 10g XE after hitting the 5GB limit."
---

# 🧱 Oracle 10g XE Size Limit or Resizing Datafile When It Gives ORA-03297

Recently, I encountered a common but painful issue — the **Oracle Database 10g XE 5GB limit**.  
Oracle XE allows only up to **5GB of user data** across all tablespaces (SYSAUX, SYSTEM, UNDO, USERS).  
Once you reach that limit, everything stops working — including the **APEX Web interface**.

---

## 🚨 The Problem

When my Oracle XE instance reached 5GB:
- The **EPG (Embedded PL/SQL Gateway)** stopped because it couldn’t write to the **SYSAUX** tablespace.  
- The **APEX web interface** was down.  
- Attempts to shrink the datafile resulted in the error:

```sql
ORA-03297: file contains used data beyond requested RESIZE value

Even though there was plenty of free space in the file, Oracle refused to resize it.

🧠 Why This Happens

Oracle data is stored in blocks throughout the file.
If even a single data block near the end of a file is occupied, Oracle won’t allow a RESIZE operation past that point.

In my case:

USERS tablespace = 1960 MB total

Only ~400 MB used

But a few high-block objects prevented shrinking

🧩 First Recovery: Free Space in SYSAUX

Before resizing, I needed APEX and EPG running again.

Dropped old APEX/HTMLDB schemas

Removed obsolete APEX images

This freed ~400 MB in the SYSAUX tablespace — enough to get EPG and APEX working again.

🧹 Cleaning APEX FLOWS_FILES

To reclaim more space, I also cleaned up old file storage objects:

DELETE FROM FLOWS_FILES.WWV_FLOW_FILE_OBJECTS$ WHERE ...;
COMMIT;

This can be a significant space saver if your APEX app stores many uploaded files.

🧪 Failed Shrink Attempts

I tried both database-level and tablespace-level shrinking:

BEGIN
  dbms_space.database_level_shrink;
END;
/

Unfortunately, Oracle XE does not actually shrink datafiles with these commands —
they run without error but make no change.

⚙️ The Real Fix: Move Segments Manually

The only reliable way is to move segments (tables, indexes, and LOBs)
from the end of the datafile back to the beginning — effectively compacting the file.

Here’s the PL/SQL script I used (run as SYS):

DECLARE
  l_orig_file_size_bytes NUMBER := 1;
  l_new_file_size_bytes  NUMBER := 0;
  l_block_size           NUMBER;
  l_file_id              NUMBER := 4;  -- Change this to your USERS tablespace file ID
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
    SELECT bytes INTO l_orig_file_size_bytes FROM dba_data_files WHERE file_id = l_file_id;
    SELECT MAX(block_id) INTO l_block_id FROM dba_extents WHERE file_id = l_file_id;
    SELECT l_block_size * l_block_id INTO l_new_file_size_bytes FROM dual;

    FOR i IN (
      SELECT segment_name, owner, segment_type
        FROM dba_extents
       WHERE file_id = l_file_id
         AND block_id = l_block_id
    ) LOOP
      dbms_output.put_line(i.owner || '.' || i.segment_name || ' found and will be moved/rebuilt, type ' || i.segment_type);

      IF i.segment_type = 'TABLE' THEN
        EXECUTE IMMEDIATE 'ALTER TABLE ' || i.owner || '.' || i.segment_name || ' MOVE TABLESPACE ' || l_tablespace_name;
      ELSIF i.segment_type = 'INDEX' THEN
        EXECUTE IMMEDIATE 'ALTER INDEX ' || i.owner || '.' || i.segment_name || ' REBUILD TABLESPACE ' || l_tablespace_name;
      ELSIF i.segment_type IN ('LOBSEGMENT', 'LOBINDEX') THEN
        FOR j IN (
          SELECT table_name, owner, column_name
            FROM dba_lobs
           WHERE index_name = i.segment_name
              OR segment_name = i.segment_name
        ) LOOP
          EXECUTE IMMEDIATE
            'ALTER TABLE ' || j.owner || '.' || j.table_name ||
            ' MOVE LOB(' || j.column_name || ') STORE AS (TABLESPACE ' || l_tablespace_name || ')';
        END LOOP;
      ELSE
        dbms_output.put_line(i.owner || '.' || i.segment_name || ' found, move manually, type ' || i.segment_type);
        EXIT;
      END IF;
    END LOOP;

    l_size_kb := ROUND(l_new_file_size_bytes / 1024, -1);
    EXECUTE IMMEDIATE 'ALTER DATABASE DATAFILE ''' || l_file_name || ''' RESIZE ' || l_size_kb || 'K';
    dbms_output.put_line('Data file ' || l_file_name || ' resized to ' || l_size_kb || ' KBytes');
  END LOOP;
EXCEPTION
  WHEN OTHERS THEN
    dbms_output.put_line(SQLERRM);
END;
/

📉 Results

After running the script:

The USERS tablespace datafile shrank from 1960 MB → 761 MB

Tables, indexes, and LOBs were successfully reorganized

Oracle accepted the resize operation

⚠️ You might hit a “buffer overflow” in dbms_output if there are many objects.
It’s safe — the process continues working.

🔄 Rebuild Unusable Indexes

Once the move completes, rebuild unusable indexes:

SELECT 'ALTER INDEX ' || owner || '.' || index_name ||
       ' REBUILD TABLESPACE ' || tablespace_name || ';'
  FROM dba_indexes
 WHERE status = 'UNUSABLE'
   AND tablespace_name = 'USERS';

Run the generated commands in SQL*Plus as SYS.

🧮 Monitoring Space Usage

To check tablespace utilization and segment sizes:

SELECT tablespace_name, SUM(bytes)/1024/1024 AS MB_USED
  FROM dba_segments
 GROUP BY tablespace_name
 ORDER BY 2 DESC;

This gives you a clear picture of where your space goes before the next cleanup.

💡 Lessons Learned

Oracle XE’s 5GB limit is absolute — you can’t exceed it, but you can reclaim space.

Shrinking isn’t supported — you need to move segments manually.

Always clean SYSAUX and FLOWS_FILES regularly when using APEX.

Plan ahead: monitor segment sizes before hitting the limit.

✅ Conclusion

The ORA-03297 error doesn’t have to mean a full reinstall of Oracle XE.
With smart cleanup and the segment-move method, you can reclaim gigabytes of space and keep your APEX applications running without a full export/import cycle.

“Before rebuilding everything, try moving what’s already there — it may be all you need.”





