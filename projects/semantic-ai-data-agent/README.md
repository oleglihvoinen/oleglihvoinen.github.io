# Governed Semantic Layer + AI Data Agent

Reference design for answering business questions through governed semantic definitions rather than giving an LLM unrestricted access to warehouse tables.

**Technologies:** Python · FastAPI · semantic layer · YAML contracts · Snowflake/dbt-ready metrics · LLM grounding · provenance · governance

The API resolves approved metric definitions and returns metric metadata/provenance. A production agent can use these contracts to generate constrained analytical queries with authorization, ambiguity handling and evaluation.
