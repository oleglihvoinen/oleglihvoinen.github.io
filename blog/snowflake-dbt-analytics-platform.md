---
layout: default
title: "Modern Snowflake + dbt ELT Analytics Platform"
permalink: /blog/snowflake-dbt-analytics-platform
---
# Modern Snowflake + dbt ELT Analytics Platform

**Role focus:** Data Engineering · Analytics Engineering · Incremental Processing · Reliability

## Summary

This case demonstrates a layered Snowflake/dbt platform with explicit controls for **late-arriving updates, idempotent replay, reconciliation and operational auditability**.

The goal is not simply to show RAW → staging → marts, but to show how incremental state remains correct when source records arrive late or the same extraction interval is replayed.

## Architecture

```text
Operational sources
       |
       v
 Snowflake RAW
       |
       v
 dbt staging
       |
       v
 incremental facts / dimensions
       |
       v
 dimensional marts
       |
 BI / semantic / AI

Control plane:
watermarks -> overlap replay -> reconciliation -> run audit -> DQ exceptions
```

## Late-arriving data

A strict filter such as `updated_at > max(updated_at)` can permanently miss delayed records.

The fact model therefore uses a bounded overlap window. Recent source changes are deliberately re-read, then Snowflake MERGE and deterministic payload hashes make reprocessing safe.

## Idempotent incremental control

The repository includes a locally testable Python control module representing the same rules:

- build a timezone-aware watermark window
- replay a configurable lookback interval
- preserve newer state when older changes arrive later
- apply deletes deterministically
- reprocess the same batch without changing the result

## Reconciliation

A source/target reconciliation function detects:

- missing business keys
- unexpected target keys
- payload/hash mismatches

This makes correctness measurable rather than assuming that a successful SQL statement means the pipeline is correct.

## Operational audit

Snowflake control tables capture run IDs, source and target row counts, watermarks, reject counts, reconciliation status and Git SHA. A separate exception table provides a destination for data-quality failures.

Automated tests cover watermark overlap, replay, late arrival, deletion and reconciliation drift.

**Technologies:** Snowflake · dbt · SQL · Python · incremental ELT · MERGE · watermarks · reconciliation · dimensional modeling · CI/CD

[View the public source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-analytics-platform)
