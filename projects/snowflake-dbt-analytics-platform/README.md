# Snowflake + dbt Modern ELT Analytics Platform

A production-style ELT portfolio case that turns raw commerce data into governed dimensional marts in Snowflake.

## Architecture
Sources -> Snowflake RAW -> dbt staging -> intermediate transformations -> dimensional marts -> BI / semantic layer.

## Demonstrated patterns
- Layered dbt model design
- Source definitions and tests
- Incremental fact processing
- Dimensional modeling
- Reusable SQL transformations
- Documentation and lineage
- Warehouse-friendly transformations

The sample model uses synthetic commerce entities so the project can be reviewed publicly without exposing proprietary data.
