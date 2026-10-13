---
layout: default
title: "Governed Semantic Layer + AI Data Agent"
permalink: /blog/semantic-ai-data-agent
---
# Governed Semantic Layer + AI Data Agent

**Role focus:** Data Architecture · Semantic Modeling · AI Engineering · Evaluation · Governance

![Governed Semantic AI Data Agent architecture](/assets/architecture/semantic-ai-data-agent.png)

## Summary

This case creates a controlled semantic boundary between natural-language analytics and physical data models. It now includes not only metric contracts and query-plan validation, but also **governed intent routing, ambiguity handling, evaluation and tamper-evident auditability**.

## Architecture

```text
Business question
       |
       v
governed intent router
       |
       v
semantic policy / metric registry
       |
       +-> clarification / rejection
       |
       v
approved tool plan
       |
       v
Snowflake/dbt or Fabric adapter
       |
result + owner + provenance + audit
```

## Governed tool routing

The natural-language router maps recognized business language to approved metric IDs and dimensions. It can prepare a semantic tool call only when the requested metric is governed.

It does **not** generate arbitrary warehouse SQL.

When the question does not identify a metric safely, the result is `clarification_required` rather than a guessed business definition.

## Semantic enforcement

The FastAPI layer still validates requested dimensions against each metric contract. A dimension that exists generally but is not approved for a specific metric cannot pass the policy boundary.

The public `/api/v1/ask` endpoint returns a governed semantic plan with metric expression, aggregation, owner and provenance. Execution remains deliberately plan-only in the public repository.

## Evaluation

A golden-question harness evaluates whether representative business questions route to the expected metric/status. The output includes total cases, passes, pass rate and per-question results.

This makes agent behavior testable rather than relying on subjective prompt quality.

## Tamper-evident audit

The repository also includes a hash-chained audit record implementation. Each event incorporates the previous audit hash; modifying an earlier decision breaks chain verification.

## Enterprise boundary

A production deployment can attach Snowflake or Fabric execution adapters, SSO/RBAC, row-level security, policy services and an LLM orchestrator while leaving semantic authority outside the model.

**Technologies:** Python · FastAPI · Pydantic · YAML semantic contracts · governed tool routing · golden-question evaluation · audit chain · Snowflake/dbt-ready semantics · Microsoft Fabric-ready semantics · Docker · CI

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/semantic-ai-data-agent)
