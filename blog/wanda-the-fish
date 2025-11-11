---
layout: default
title: "Wanda the Fish — Fortunes in APEX"
date: 2025-11-11
description: "Expose the Linux 'fortunes' files as external tables and show a random fortune in an Oracle APEX page."
permalink: /blog/wanda-the-fish
---

# 🐟 Wanda the Fish — Fortunes in Oracle APEX

"Wanda the fish" (the classic Linux `fortune`) is a small, fun app. You can surface those fortunes inside an Oracle APEX application by mapping the fortunes files as external tables and then showing a random line in a page region.

This guide shows a compact, safe way to:

- create an Oracle DIRECTORY to the fortunes folder,
- define external tables that read the fortunes files,
- populate an APEX item with a random fortune on page load,
- display the fortune in an HTML region.

---

## 1) Create the DIRECTORY and grant access

Run as a privileged user (e.g. SYS) to create a directory object that points to the OS location of the fortunes files:

```sql
-- Create DIRECTORY (run as SYS or a DBA)
CREATE OR REPLACE DIRECTORY WANDA AS '/usr/share/games/fortunes';

-- Grant read access on the directory to your parsing schema (replace MYSCHEMA)
GRANT READ ON DIRECTORY WANDA TO MYSCHEMA;
```

Make sure the OS path exists and the database user has OS-level read permission for those files.

---

## 2) External tables (map each fortunes file)

Create external tables that read the fortunes files. Adjust RECORDS / FIELDS parameters to match your files; the example uses `%` as record delimiter (classic fortune format).

```sql
CREATE TABLE WANDA_FORTUNES (
  msg VARCHAR2(4000)
)
ORGANIZATION EXTERNAL (
  TYPE ORACLE_LOADER
  DEFAULT DIRECTORY WANDA
  ACCESS PARAMETERS (
    RECORDS DELIMITED BY '%'
    NOBADFILE
    NODISCARDFILE
    NOLOGFILE
    FIELDS TERMINATED BY X'0A'
    MISSING FIELD VALUES ARE NULL
  )
  LOCATION ('fortunes')
)
REJECT LIMIT UNLIMITED;
```

```sql
CREATE TABLE WANDA_LITERATURE (
  msg VARCHAR2(4000)
)
ORGANIZATION EXTERNAL (
  TYPE ORACLE_LOADER
  DEFAULT DIRECTORY WANDA
  ACCESS PARAMETERS (
    RECORDS DELIMITED BY '%'
    NOBADFILE
    NODISCARDFILE
    NOLOGFILE
    FIELDS TERMINATED BY X'0A'
    MISSING FIELD VALUES ARE NULL
  )
  LOCATION ('literature')
)
REJECT LIMIT UNLIMITED;
```

```sql
CREATE TABLE WANDA_RIDDLES (
  msg VARCHAR2(4000)
)
ORGANIZATION EXTERNAL (
  TYPE ORACLE_LOADER
  DEFAULT DIRECTORY WANDA
  ACCESS PARAMETERS (
    RECORDS DELIMITED BY '%'
    NOBADFILE
    NODISCARDFILE
    NOLOGFILE
    FIELDS TERMINATED BY X'0A'
    MISSING FIELD VALUES ARE NULL
  )
  LOCATION ('riddles')
)
REJECT LIMIT UNLIMITED;
```

Notes:
- If your files or platform use different delimiters or encodings, adjust ACCESS PARAMETERS accordingly.
- `LOCATION ('fortunes')` refers to the filename in the directory object.

---

## 3) APEX setup

- Create (or use) an APEX application with parsing schema set to your schema (MYSCHEMA).
- Create an application item or page item P1_WANDA (or use a page item on the target page).
- On Page 1 (or whichever page will display the fortune) add an "On Load: Before Header" PL/SQL process that selects a random fortune and sets the APEX item.

Example PL/SQL for the On Load process (safe, picks the first row from a randomized result):

```plsql
DECLARE
  l_msg VARCHAR2(4000);
BEGIN
  SELECT msg
  INTO l_msg
  FROM (
    SELECT msg
    FROM (
      SELECT msg FROM wanda_fortunes
      UNION ALL
      SELECT msg FROM wanda_literature
      UNION ALL
      SELECT msg FROM wanda_riddles
    )
    WHERE msg IS NOT NULL
    ORDER BY dbms_random.value
  )
  WHERE rownum = 1;

  -- Set session state so the page item renders the fortune
  apex_util.set_session_state('P1_WANDA', l_msg);

EXCEPTION
  WHEN NO_DATA_FOUND THEN
    apex_util.set_session_state('P1_WANDA', 'No fortune available.');
  WHEN OTHERS THEN
    apex_util.set_session_state('P1_WANDA', 'Error fetching fortune.');
END;
```

Notes:
- Using `apex_util.set_session_state` ensures the item is populated reliably.
- The inner `UNION ALL` preserves all messages; `ORDER BY dbms_random.value` randomizes rows; `rownum = 1` picks one.
- For very large files consider performance and tuning.

---

## 4) Display the fortune in a region

Create an HTML (Static Content) region and show the APEX item:

```html
<pre>&P1_WANDA.</pre>
```

The `<pre>` tag preserves formatting and line breaks from the fortunes content.

---

## 5) Additional notes & tips

- If you create the MYSCHEMA user for APEX parsing schema, ensure it has SELECT privilege on the external tables (or owns them).
- External tables read the OS file each time — changes to the file on disk are seen by the DB on the next query.
- Validate file encoding (UTF-8 vs. system encoding) to avoid character issues.
- Consider caching a selected fortune in a small table if you want consistent content per user session.
- Use `UNION ALL` to preserve duplicates if the same fortune appears in multiple files; use `UNION` if you prefer de-duplicated results.

---

## ✅ Result

With the external tables, the directory set up and a small On Load process, your APEX app will display a random fortune (Wanda) on page load — bringing a little Linux charm into your Oracle application.

Enjoy!
