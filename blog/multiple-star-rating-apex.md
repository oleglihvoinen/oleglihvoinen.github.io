---
layout: default
title: "Multiple Star Rating in APEX with jQuery"
date: 2025-11-11
description: "Add multiple star rating controls to APEX pages using a jQuery star-rating plugin with AJAX-backed logging."
permalink: /blog/multiple-star-rating-apex
---

# ⭐ Multiple Star Rating in APEX with jQuery

If your application displays many items (articles, products, posts) you may want a per-item (multiple) star rating control. A common choice is a jQuery Star Rating plugin that turns radio buttons into visual stars and can submit ratings immediately via AJAX.

This article shows a simple, robust approach:
- render a radio-based star control per item,
- initialize a jQuery star plugin,
- send the selected rating to an On-Demand process (RATE_MULTIPLE),
- persist and aggregate ratings in a small table.

---

## 1. Include the plugin and styles

Download and host the plugin (or include via CDN). Example plugin file referenced historically:

- https://jquery-star-rating-plugin.googlecode.com/svn/trunk/jquery.rating.js

Prefer hosting the JS/CSS in your application static files or serve from a trusted CDN. Add the script and optional CSS to the page template or page header:

```html
<!-- Example: load jQuery (if not already included) and the star plugin -->
<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
<script src="/i/static/jquery.rating.js"></script>
<link rel="stylesheet" href="/i/static/jquery.rating.css" />
```

(APEX often already includes a supported jQuery — do not load duplicate versions.)

---

## 2. Render per-item rating controls (PL/SQL region)

A recommended approach is to output a radio input group per article, using a predictable class/data attributes so JavaScript can initialize each control and attach an AJAX handler. Place this code in a PL/SQL region where articles are rendered.

Example PL/SQL region (adjust column names and escaping per your schema):

```plsql
DECLARE
  l_rate NUMBER;
BEGIN
  FOR r IN (SELECT id, title, summary FROM articles ORDER BY created_date DESC) LOOP
    BEGIN
      SELECT rate INTO l_rate FROM article_rate WHERE article_id = r.id;
    EXCEPTION
      WHEN NO_DATA_FOUND THEN
        l_rate := NULL;
    END;

    -- Article container
    htp.p('<div class="article" id="article_'||r.id||'">');
    htp.p('<h3>'||htf.escape_sc(r.title)||'</h3>');
    htp.p('<p>'||htf.escape_sc(r.summary)||'</p>');

    -- Rating control: five radio buttons with a common name, data attribute for article id
    htp.p('<div class="star-rating" data-article="'||r.id||'">');
    FOR i IN 1..5 LOOP
      IF l_rate IS NOT NULL AND l_rate = i THEN
        htp.p('<input type="radio" name="rating_'||r.id||'" value="'||i||'" checked="checked" class="star" />');
      ELSE
        htp.p('<input type="radio" name="rating_'||r.id||'" value="'||i||'" class="star" />');
      END IF;
    END LOOP;
    htp.p('</div>'); -- .star-rating

    htp.p('</div>'); -- .article
  END LOOP;
END;
```

Notes:
- Use htf.escape_sc/escape_* helpers to avoid HTML injection.
- You can render APEX_ITEM HTML inputs instead of raw inputs; the key is each control contains the article id so JS can pass it on submit.

---

## 3. JavaScript: initialize plugin and submit rating via AJAX

After the page has rendered, initialize the plugin on each `.star-rating` container and send the chosen value to an On-Demand process called `RATE_MULTIPLE`. Use `apex.server.process` for modern APEX; fallback to `htmldb_Get` for older versions.

Example (modern APEX):

```javascript
$(function(){
  // Initialize the rating plugin on each container (plugin-specific init may vary)
  $('.star-rating').each(function(){
    var $container = $(this);
    // Plugin may turn radio inputs into stars automatically; if plugin requires init, call it here.
    // Example for jquery.rating plugin:
    $container.find('input.star').rating(); // plugin-specific

    // Attach change handler on radio inputs
    $container.find('input.star').on('change', function(){
      var value = $(this).val();
      var articleId = $container.data('article');

      // Call On-Demand process RATE_MULTIPLE
      apex.server.process('RATE_MULTIPLE',
        { x01: value, x02: articleId }, // x01 -> rating, x02 -> article id
        {
          dataType: 'json',
          success: function(pData) {
            // Optionally update UI (disable control, show new average, etc.)
            $container.find('input.star').prop('disabled', true);
          },
          error: function() {
            // handle error (show message)
            alert('Rating could not be saved. Please try again.');
          }
        }
      );
    });
  });
});
```

If you're on an older APEX version that uses htmldb_Get, adapt the AJAX call accordingly — but prefer apex.server.process when available.

---

## 4. On-Demand Application Process: RATE_MULTIPLE

Create an Application On-Demand Process named `RATE_MULTIPLE`. The process reads `APEX_APPLICATION.G_X01` (rating) and `APEX_APPLICATION.G_X02` (article id) and inserts or updates aggregate values.

Example PL/SQL body:

```plsql
BEGIN
  IF APEX_APPLICATION.G_X01 IS NOT NULL AND APEX_APPLICATION.G_X02 IS NOT NULL THEN
    BEGIN
      INSERT INTO article_rate (article_id, rate, clicks)
      VALUES (TO_NUMBER(APEX_APPLICATION.G_X02), TO_NUMBER(APEX_APPLICATION.G_X01), 1);
    EXCEPTION
      WHEN DUP_VAL_ON_INDEX THEN
        UPDATE article_rate
        SET rate = CEIL((rate * clicks + TO_NUMBER(APEX_APPLICATION.G_X01)) / (clicks + 1)),
            clicks = clicks + 1
        WHERE article_id = TO_NUMBER(APEX_APPLICATION.G_X02);
    END;
  END IF;
EXCEPTION
  WHEN OTHERS THEN
    -- optionally log or swallow; avoid raising to the client to prevent UX issues
    NULL;
END;
```

Notes:
- The aggregation strategy above uses a running average stored as integer (CEIL used to keep an integer rating). Adjust logic if you want a floating average.
- Consider storing separate total_score and count columns for exact averages.

---

## 5. Table DDL: article_rate

A simple table to hold per-article rating aggregates:

```sql
CREATE TABLE article_rate (
  article_id NUMBER PRIMARY KEY,
  rate       NUMBER,  -- aggregated rating (e.g. average or rounded value)
  clicks     NUMBER   -- number of ratings received
);
```

Or, for a more precise approach, store totals:

```sql
CREATE TABLE article_rate (
  article_id NUMBER PRIMARY KEY,
  total_score NUMBER DEFAULT 0,  -- sum of all ratings
  clicks      NUMBER DEFAULT 0   -- count of ratings
);
```

And update logic would set total_score = total_score + :new_rating; clicks = clicks + 1; and compute average for display as total_score / clicks.

---

## 6. Enhancements & tips

- Half-star support and split stars depend on the plugin: check plugin docs for half-star or fractional ratings.
- Consider preventing multiple votes per session/user (store user_id or cookie).
- When you store raw ratings per user (a ratings table), you can compute averages reliably and allow users to change their vote.
- Sanitize and validate incoming values in the On-Demand process (accept only 1..5 or plugin-defined range).
- Provide feedback after vote (disable inputs, show "Thanks" message, update average).
- Host plugin files in your APEX static application files or web server to avoid CDN issues.

---

## 7. Quick testing

1. Add the PL/SQL region to a test page and ensure articles render with star inputs.
2. Open browser console, check for JS errors.
3. Click a star — confirm network request to `wwv_flow.show?p_request=APPLICATION_PROCESS=RATE_MULTIPLE` (or apex.rpc equivalent) and verify DB updates.
4. Adjust UI behavior and aggregation logic as needed.

---

## Conclusion

This approach keeps the rendering on the server (PL/SQL region), provides predictable per-item markup, and relies on a small client-side initializer to make each radio group behave like a star control and post ratings via AJAX. It’s simple, easily adapted for user-based voting, and compatible with modern APEX using apex.server.process.

References: Star Rating jQuery plugin documentation (see plugin repo for features like half-stars and fractional values).
