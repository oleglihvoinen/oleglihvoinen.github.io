---
layout: default
title: "Custom Error Page in Oracle APEX"
date: 2025-11-11
description: "How to build a user-friendly custom error page in Oracle APEX that preserves application look, logs errors to a custom table, and displays friendly messages."
permalink: /blog/custom-error-page-apex
---

# 🚨 Custom Error Page in Oracle APEX

When the Application Express runtime raises an error, APEX renders a minimal, out-of-theme error page that often confuses end users. This guide shows a pragmatic approach to replace the default APEX error page with a custom, branded page that:

- Preserves the look and feel of your application,
- Logs errors to a custom table for later investigation,
- Allows showing custom, friendlier error messages.

Overview of the approach
- Create an application page with alias ERROR to display errors.
- Create an application item to carry the error message (ERRMSG).
- Create a copy of your page template (an Error Page Template) that includes a small script to call an On-Demand process to log the error and then redirect to the ERROR page.
- Wire the new template into your theme as the Error page.
- Create database objects (sequence, table, trigger) and an On-Demand process (LOGERROR) that inserts the error record.

---

## 1) Create error page and region

1. In Application Builder create a new page and set the Page Alias to: `ERROR`.  
2. Add a Region of type "HTML" (or "Static Content") named `Error`. Example HTML for the region:

```html
<p>The following error occurred:</p>
<h3 class="ErrorPageMessage">&ERRMSG.</h3>
```

- The region uses substitution `&ERRMSG.` which will be populated when redirecting to the error page.
- You can extend this region with links, styling or a "Report this problem" button.

---

## 2) Create application item for the error message

Create an application item named `ERRMSG`. This item will hold the user-friendly message shown on the error page. Populate it during redirect so `&ERRMSG.` renders correctly.

---

## 3) Create the Error Page Template

Make a copy of your current application page template and name it something like `Error Page Template`. This ensures your error page uses the same header/footer and styling as the rest of the app.

In the Error Page Template:

- Add the error content placeholder where you want the message displayed (for example, in the content region):

```html
<pre style="font-weight:bold">#MESSAGE#</pre>
<a href="#BACK_LINK#" class="free"><b>#RETURN_TO_APPLICATION#</b></a>
<script type="text/javascript">
var gErrMesg = '#MESSAGE#';
</script>
```

- `#MESSAGE#` is replaced by APEX with the error message. The script assigns it to `gErrMesg` (used below).

---

## 4) Header script — call On-Demand process and redirect

In the Header section of your Error Page Template insert a small script that:

- Loads jQuery (APEX versions may already have jQuery — check your environment),
- Calls an On-Demand process named `LOGERROR` to persist the error,
- Redirects the user to the application ERROR page so the message is shown as a normal page.

Important: If you use Google Loader in your environment, sign up for an API key and create an Application Substitution String `APIKEY` with its value. If not needed, adapt the loading method to your APEX version.

Example header script (adapt quoting to your template engine):

```html
<script src="https://www.google.com/jsapi?key=&APIKEY."></script>
<script type="text/javascript">
google.load("jquery", "1.4.4");  // adapt/remove for modern APEX which already includes jQuery
google.setOnLoadCallback(function() {
  $(document).ready(function(){
    // send the message to an on-demand process LOGERROR and then redirect to the ERROR page
    var ajaxRequest = new htmldb_Get(null, $v('pFlowId'), 'APPLICATION_PROCESS=LOGERROR', $v('pFlowStepId'));
    ajaxRequest.addParam('x01', $('.ErrorPageMessage').text()); // original/textual message
    ajaxRequest.addParam('x02', gErrMesg);                     // defined/translated message
    var ajaxResult = ajaxRequest.get();
    ajaxRequest = null;
    // remove the visible message placeholder (to avoid duplicate info) and redirect
    $('.ErrorPageMessage').remove();
    window.location = "f?p=&APP_ID.:ERROR:&SESSION.";
  });
});
</script>
```

Notes:
- Adjust `htmldb_Get` usage to the APEX version; in some APEX releases the API names differ (htmldb_Get / apex.server.process). Update to `apex.server.process('LOGERROR', {x01:..., x02:...}, {async: false})` for modern APEX.
- Use synchronous/asynchronous behavior as needed; the script above attempts to log then redirect.

---

## 5) Wire the Error Page Template into your theme

Go to:
Home → Application Builder → [Your Application] → Shared Components → Themes → (Edit Theme)

Find the "Error Page" select list (or equivalent setting) and assign the new "Error Page Template" you created. This ensures APEX uses your template when errors occur.

---

## 6) Database objects (DDL)

Create a sequence and a table to store error events. Example DDL:

```sql
-- Sequence
CREATE SEQUENCE ERROR_SEQ
  MINVALUE 1
  MAXVALUE 999999999999999999999999999
  INCREMENT BY 1
  START WITH 1
  CACHE 20
  NOORDER
  NOCYCLE;
```

```sql
-- Error log table
CREATE TABLE ERROR_LOG (
  ID             NUMBER        NOT NULL,
  SESSION_ID     VARCHAR2(100),
  APPLICATION_ID NUMBER        NOT NULL,
  PAGE_ID        NUMBER        NOT NULL,
  APP_USER       VARCHAR2(255),
  ERR_MESSAGE    VARCHAR2(4000),
  DEFINED_MESSAGE VARCHAR2(4000),
  ERR_DATE       DATE          NOT NULL,
  CONSTRAINT ERROR_LOG_PK PRIMARY KEY (ID)
);
```

Notes:
- SESSION_ID is stored as VARCHAR2 here to avoid issues with varying session formats; adapt to NUMBER if you prefer.
- Increase column sizes and types to suit your needs.

Trigger to populate defaults and stamps:

```sql
CREATE OR REPLACE TRIGGER ERROR_LOG_TRG
BEFORE INSERT ON ERROR_LOG
FOR EACH ROW
BEGIN
  IF :NEW.ID IS NULL THEN
    SELECT ERROR_SEQ.NEXTVAL INTO :NEW.ID FROM DUAL;
  END IF;

  :NEW.SESSION_ID := v('SESSION');       -- session
  :NEW.APPLICATION_ID := v('APP_ID');    -- app id
  :NEW.PAGE_ID := v('APP_PAGE_ID');      -- page id
  :NEW.APP_USER := v('APP_USER');        -- apex user
  :NEW.ERR_DATE := SYSDATE;
END;
/
```

---

## 7) On-Demand Process: LOGERROR

Create an Application On-Demand Process named `LOGERROR` (process name must match what the client script calls).

Example PL/SQL body:

```plsql
BEGIN
  INSERT INTO ERROR_LOG (err_message, defined_message)
  VALUES (APEX_APPLICATION.G_X01, APEX_APPLICATION.G_X02);

  -- optionally return a friendly message to the client:
  :ERRMSG := APEX_APPLICATION.G_X02;
EXCEPTION
  WHEN OTHERS THEN
    -- swallow/log internal errors to avoid secondary failures
    NULL;
END;
```

Notes:
- In newer APEX versions you may use `apex_application.g_x01` or use `apex.server.process` on the client and `apex_application.g_x01` on the server; check your APEX version.
- Consider adding more columns (component, stack, call_id) if you want richer diagnostics.

---

## 8) Optional: Custom error mapping

You can map common APEX/ORA errors to friendlier messages. Example strategy:

- On error, capture ORA code or APEX code.
- Translate common codes into `DEFINED_MESSAGE` (e.g., "Missing required data", "Permission denied", "Service temporarily unavailable").
- Insert both raw and defined messages into ERROR_LOG.
- Show `DEFINED_MESSAGE` to the user and keep `ERR_MESSAGE` for diagnostics.

Implement mapping inside the LOGERROR process or in a PL/SQL package used by it.

---

## 9) Testing the flow

1. Force an error (temporary stray RAISE_APPLICATION_ERROR or invalid SQL) in a safe sandbox page.
2. Confirm:
   - User is redirected to the themed ERROR page (same header/footer).
   - `ERROR_LOG` contains a new row with raw and defined messages, session, page and user info.
   - The displayed message is friendly and helpful.
3. Verify that repeated/logged errors do not expose sensitive data.

---

## 10) Security and operational notes

- Never show raw DB stack traces or sensitive data to end users.
- Sanitize messages that may contain user input.
- Ensure access controls restrict who can query ERROR_LOG if it contains sensitive diagnostic information.
- Avoid logging very large payloads into VARCHAR2(4000) without truncation logic.
- Test in a development environment before deploying to production.

---

## 11) Variations for modern APEX

For APEX 18.x+ and modern releases:
- Use `apex.server.process('LOGERROR', {x01:..., x02:...}, {dataType:'text', async:false})` instead of `htmldb_Get`.
- Use `apex_error` framework to catch and control APEX errors where appropriate.
- Consider using `APEX_DEBUG` or APEX activity logs together with your custom table.

---

## Example: modern AJAX client call (APEX 19+)

```javascript
apex.server.process('LOGERROR',
  { x01: $('.ErrorPageMessage').text(), x02: gErrMesg },
  {
    dataType: 'text',
    success: function(pData) {
      $('.ErrorPageMessage').remove();
      location.assign('f?p=' + $v('pFlowId') + ':ERROR:' + $v('pInstance'));
    }
  }
);
```

---

## Conclusion

With a small template change, an on-demand logging process, and a lightweight DB table, you can replace the default APEX error screen with a branded, user-friendly error page that also captures diagnostic information for troubleshooting. This greatly improves the user experience and helps developers investigate issues without forcing exports, reinstallations, or confusing end users.

---

References & tips
- Adapt client calls to your APEX version (htmldb_Get vs apex.server.process).
- Provide an application substitution string `APIKEY` only if you rely on Google Loader; otherwise, use the APEX-bundled jQuery.
- Keep logged error data for a reasonable retention window and consider adding purging jobs.
