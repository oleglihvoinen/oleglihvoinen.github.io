# Snowflake + dbt Customer 360

Portfolio implementation of a governed Customer 360 pipeline using Snowflake and dbt.

## Problem
Customer records arrive from CRM, ERP and digital channels with different identifiers, formats and quality. The pipeline standardizes source data, applies deterministic identity rules and publishes an analytics-ready golden customer model.

## Architecture
RAW source tables -> dbt staging -> standardized customer records -> identity resolution -> golden customer -> marts.

## Engineering highlights
- Source contracts and freshness checks
- Standardization of email, phone, country and business keys
- Deterministic cross-source matching
- Source-priority survivorship rules
- SCD-ready customer history
- dbt generic and singular data-quality tests
- Analytics-ready Customer 360 mart

## Run
Configure a Snowflake target in your local dbt profile, then run:

```bash
dbt deps
dbt build
```

This repository contains portfolio-safe synthetic logic and no employer or customer data.
