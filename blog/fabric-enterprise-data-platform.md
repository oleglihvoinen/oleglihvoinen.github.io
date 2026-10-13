---
layout: default
title: "Microsoft Fabric Enterprise Data Platform"
permalink: /blog/fabric-enterprise-data-platform
---
# Microsoft Fabric Enterprise Data Platform

**Role focus:** Data Engineering · Lakehouse Architecture · Pipeline Reliability · Governance

![Microsoft Fabric Enterprise Data Platform architecture](/assets/architecture/fabric-enterprise-data-platform.png)

## Summary

This case defines a governed Microsoft Fabric lakehouse from source ingestion through semantic consumption, with an added **incremental pipeline control plane** for durable watermarks, retry, quarantine and run audit.

## Platform architecture

ERP, CRM, API and file sources enter through **Fabric Data Factory** and land in OneLake/Lakehouse Bronze. PySpark and Delta produce standardized Silver models; Gold exposes business-ready facts, dimensions and aggregates; a semantic boundary supports Power BI, APIs and governed AI.

## Incremental control plane

The critical reliability rule is:

> **A durable source watermark advances only after all required pipeline stages and quality gates succeed.**

When a run begins, the next source position is only a *candidate* watermark. If Bronze ingestion, Silver validation, Gold publication or a required quality check fails, durable state remains unchanged so the interval can be replayed.

## Run state and row accounting

The repository includes:

- durable pipeline state
- per-run audit records
- candidate and committed watermarks
- source / accepted / rejected row counts
- last successful run ID
- data-quality quarantine records
- Git SHA field for release traceability

## Quarantine

Invalid records retain the original payload, business key, rule ID, run ID and timestamp. They are not silently dropped from the pipeline.

## Locally testable reliability logic

A Python module models the state transitions outside the Fabric runtime. Unit tests verify:

- failed runs do not advance watermarks
- successful runs advance only after completion
- source counts reconcile to accepted + rejected
- high reject ratios can trigger retry/escalation
- quarantine preserves failure context

The pattern maps directly to Fabric Data Factory activities, notebook parameters and Delta MERGE processing.

**Technologies:** Microsoft Fabric · OneLake · Lakehouse · Data Factory · PySpark · Delta · SQL · watermarks · quarantine · pipeline audit · Power BI · CI/CD

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/fabric-enterprise-data-platform)
