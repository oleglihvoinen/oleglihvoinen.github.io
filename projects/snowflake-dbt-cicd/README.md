# Snowflake + dbt CI/CD

A compact reference implementation for testing and deploying dbt changes against Snowflake with GitHub Actions.

## Workflow
Feature branch -> pull request -> dbt dependency install -> compile -> build/test -> review -> merge -> production deployment.

## Production concerns demonstrated
- Credentials supplied through repository secrets
- Separate CI target
- Automated dbt build
- Fail-fast data tests
- Repeatable dependency installation
- Deployment workflow kept in source control

Required secrets: SNOWFLAKE_ACCOUNT, SNOWFLAKE_USER, SNOWFLAKE_PASSWORD, SNOWFLAKE_ROLE, SNOWFLAKE_WAREHOUSE, SNOWFLAKE_DATABASE and SNOWFLAKE_SCHEMA.
