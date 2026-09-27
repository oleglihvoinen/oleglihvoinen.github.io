---
layout: default
title: "Governed Semantic Layer + AI Data Agent"
permalink: /blog/semantic-ai-data-agent
---
# Governed Semantic Layer + AI Data Agent

**Role focus:** Data Architecture · Semantic Modeling · AI Engineering · Governance

This reference implementation demonstrates a safer pattern for analytical AI: business questions are grounded in an approved **semantic layer** containing metric definitions, dimensions, ownership and calculation rules rather than exposing arbitrary warehouse tables directly to an LLM.

A FastAPI service exposes approved metrics and provenance. The architecture is designed for Snowflake/dbt or Fabric-backed implementations and can be extended with permissions, ambiguity handling, query generation, evaluation and audit trails.

**Technologies:** Python · FastAPI · REST · YAML semantic contracts · Snowflake/dbt-ready metrics · LLM grounding · provenance · governance.

[View implementation](https://github.com/oleglihvoinen/oleglihvoinen.github.io/tree/main/projects/semantic-ai-data-agent)
