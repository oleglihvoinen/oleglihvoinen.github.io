---
layout: default
title: "Snowflake + dbt Customer 360"
permalink: /blog/snowflake-dbt-customer360
---
# Snowflake + dbt Customer 360

**Role focus:** Data Engineering · MDM · REST API · Data Quality · Data Architecture

This portfolio case shows how fragmented customer records from CRM and ERP systems can be transformed into a governed Customer 360 model in Snowflake using dbt.

## Challenge
Enterprise customer data commonly contains duplicated identities, inconsistent formats and conflicting attributes. A useful analytical customer view therefore needs more than ingestion: it needs explicit standardization, matching, survivorship and quality rules.

## Solution
The pipeline separates raw source data from staging, identity resolution and the final golden customer dimension.

```text
CRM ─┐
     ├─> Snowflake RAW -> dbt staging -> identity resolution
ERP ─┘                                      |
                                             v
                                   survivorship rules
                                             |
                                             v
                                      DIM_CUSTOMER
                                             |
                                      BI / AI / APIs
```

The staging layer normalizes customer names, email addresses, phone numbers and country codes. The intermediate model builds a cross-source identity key and ranks competing records using explicit source precedence and recency. The mart publishes one governed customer record per resolved identity.

## Engineering decisions
The implementation keeps source-specific cleanup in staging and business identity logic in the intermediate layer. This makes lineage easier to inspect and lets matching rules evolve without coupling them to source ingestion. dbt tests protect the published customer key from nulls and duplicates.

In a production implementation I would extend this baseline with probabilistic matching where appropriate, SCD2 history, exception queues, stewardship workflows, source freshness SLAs and richer observability.

## REST data-product layer

A **Python FastAPI** service now exposes the governed Snowflake customer mart through versioned REST endpoints for customer lookup, search and record-level quality status. FastAPI provides the OpenAPI contract, while a Dockerfile packages the service for repeatable deployment. Warehouse credentials stay in environment variables rather than source control.

This demonstrates how a dbt/Snowflake model can become a reusable **data product** consumed by applications or AI services without exposing physical warehouse tables directly.

## Technologies
**Snowflake · dbt · SQL · Python · FastAPI · REST API · OpenAPI · Docker · MDM · dimensional modeling · data quality · Git**

[View the public source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-customer360)
