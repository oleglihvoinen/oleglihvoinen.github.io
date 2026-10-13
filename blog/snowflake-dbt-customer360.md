---
layout: default
title: "Snowflake + dbt Customer 360"
permalink: /blog/snowflake-dbt-customer360
---
# Snowflake + dbt Customer 360

**Role focus:** Data Engineering · MDM · Entity Resolution · Data Quality · Data Products

## Summary

This case implements a governed Customer 360 pattern for fragmented CRM and ERP identities. It now goes beyond simple normalized joins: matching decisions are explainable, ambiguous identities can be routed to stewardship, survivorship happens at field level, and the source of each surviving attribute remains visible.

## Architecture

```text
CRM ─┐
     ├─> Snowflake RAW -> dbt staging -> match candidates
ERP ─┘                                      |
                                             +-> exact/fuzzy evidence
                                             +-> conflict rules
                                             +-> stewardship queue
                                             |
                                             v
                                    entity clusters
                                             |
                                    field survivorship
                                             |
                                             v
                                      DIM_CUSTOMER
                                             |
                                  BI / APIs / governed AI
```

## Entity resolution

The repository contains a Python entity-resolution engine alongside the dbt transformation layer.

It combines exact email/phone evidence with normalized name similarity and country agreement. Each comparison returns explicit reasons and one of three decisions:

- **match** — safe for automatic clustering
- **review** — ambiguous enough for stewardship
- **reject** — evidence is insufficient or strong identifiers conflict

Conflicting email **and** phone values prevent silent auto-merge even when names look similar.

## Field-level survivorship

Instead of selecting one entire source record as the winner, survivorship is evaluated per attribute. For example, the CRM may supply the surviving name while ERP supplies the surviving email.

The resulting golden record includes field provenance so downstream users can see where each value came from.

## Policy as code

`config/mdm_policy.yml` defines auto-match/review thresholds, strong identifiers, source priority, tie-breaking and expected outputs. This separates MDM policy from implementation code and makes changes reviewable.

## Stewardship and tests

Ambiguous candidates are exposed as a stewardship exception queue rather than being silently merged. Automated tests cover:

- exact cross-system matching
- strong-identifier conflicts
- stewardship review routing
- field-level survivorship
- transitive entity clustering

The dbt layer still provides source normalization, golden customer publishing, tests and history, while the FastAPI layer exposes the governed customer data product.

**Technologies:** Snowflake · dbt · SQL · Python · MDM · entity resolution · survivorship · stewardship · data quality · FastAPI · Docker · CI/CD

[View the public source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-customer360)
