---
layout: default
title: "Governed Semantic Layer + AI Data Agent"
permalink: /blog/semantic-ai-data-agent
---
# Governed Semantic Layer + AI Data Agent

**Role focus:** Data Architecture · Semantic Modeling · AI Engineering · Governance

![Governed Semantic AI Data Agent architecture](/assets/architecture/semantic-ai-data-agent.png)

## Executive summary

This architecture creates a controlled semantic boundary between natural-language analytics and physical data models. Instead of giving an LLM unrestricted access to warehouse tables, the platform exposes approved metrics, dimensions, ownership and provenance through a typed API.

The model can interpret intent and invoke tools, but the semantic layer remains authoritative for metric meaning and permitted analytical combinations.

## Semantic contracts

Metrics are defined in machine-readable YAML. Each contract includes business description, aggregation logic, expression, time dimension, allowed dimensions and business owner.

The current contracts include **Net Revenue** and **Active Customers**, showing how a metric becomes a governed business object rather than an informal column name or prompt convention.

## API and governance boundary

A FastAPI service exposes the metric catalogue and a query-plan endpoint. Requests are validated before reaching any warehouse execution layer.

Unknown metrics are rejected. Dimensions not approved for a metric are rejected. Approved query plans return provenance and ownership alongside the semantic expression.

This creates an explicit trust boundary between an AI agent and analytical data assets.

## Enterprise controls

A production implementation would add identity-aware RBAC, row-level security, Snowflake/Fabric adapters, governed query compilation, ambiguity resolution, LLM tool calling, caching, audit logging, observability and golden-question evaluation.

The same boundary also provides an escalation path: when intent cannot be mapped confidently to an approved metric, the agent can request clarification rather than inventing business logic.

## Repository scope

The implementation focuses on semantic contracts, API governance and query-plan validation. Warehouse execution is intentionally separated so the semantic boundary remains stable across Snowflake/dbt and Microsoft Fabric backends.

**Technologies:** Python · FastAPI · REST · Pydantic · YAML semantic contracts · Snowflake/dbt-ready metrics · Microsoft Fabric-ready semantics · LLM grounding · provenance · governance · Docker · CI.

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/semantic-ai-data-agent)
