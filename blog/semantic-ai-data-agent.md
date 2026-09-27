---
layout: default
title: "Governed Semantic Layer + AI Data Agent"
permalink: /blog/semantic-ai-data-agent
---
# Governed Semantic Layer + AI Data Agent

**Role focus:** Data Architecture · Semantic Modeling · AI Engineering · Governance

![Governed Semantic AI Data Agent architecture](/assets/architecture/semantic-ai-data-agent.png)

## Goal

This project demonstrates a governed pattern for analytical AI. Instead of giving a language model unrestricted access to warehouse tables, an **approved semantic layer** defines which business metrics and dimensions exist, how they are calculated, who owns them and which combinations are allowed.

The semantic API becomes the contract between natural-language/agent experiences and physical data platforms such as Snowflake/dbt or Microsoft Fabric.

## Semantic contracts

Metrics are stored in machine-readable YAML. The current examples define **Net Revenue** and **Active Customers**, including description, aggregation, expression, time dimension, allowed dimensions and business owner. This makes a metric more than a column name: it becomes an explicit governed business concept.

## API and governance boundary

A FastAPI service exposes the approved metric catalogue and a query-plan endpoint. Requests are validated against the semantic contract; an unapproved metric or dimension is rejected before it reaches a warehouse execution layer. Responses include provenance back to the semantic specification.

That pattern is important for AI systems because the model is not treated as the authority on metric definitions. The model can interpret user intent and call tools, but the semantic/governance layer decides what is valid.

## Trust and production evolution

The current repository focuses on the **contract and validation boundary**. A production implementation would add identity-aware RBAC, row-level security, Snowflake/Fabric adapters, query compilation, ambiguity handling, LLM tool calling, caching, audit logs, observability and golden-question evaluation sets.

This architecture also creates a practical place to manage provenance and escalation: if the user's question cannot be mapped confidently to an approved metric, the agent can ask for clarification instead of silently inventing business logic.

**Technologies:** Python · FastAPI · REST · Pydantic · YAML semantic contracts · Snowflake/dbt-ready metrics · Microsoft Fabric-ready semantics · LLM grounding · provenance · governance · Docker · CI.

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/semantic-ai-data-agent)
