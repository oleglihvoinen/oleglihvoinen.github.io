---
layout: default
title: "Snowflake + dbt Release Engineering"
permalink: /blog/snowflake-dbt-cicd
---
# Snowflake + dbt Release Engineering

**Role focus:** Data Engineering · DevOps · Data Platform Engineering · Release Governance

## Summary

This case treats dbt delivery as a governed software release. The repository now separates **static policy, warehouse validation, artifacts, approval and exact-SHA production promotion** rather than reducing CI/CD to one `dbt build` step.

## Delivery flow

```text
commit
   |
pull request
   +-> SQL policy-as-code
   +-> policy unit tests
   +-> dbt parse/build
   +-> manifest/run artifacts
   |
 review / merge
   |
 approved Git SHA
   |
 protected production environment
   |
 production dbt build
   |
 retained release artifacts
```

## Policy-as-code

A Python SQL policy scanner rejects several risky patterns before a warehouse build starts:

- broad `select *`
- hard-coded `PROD` / `PRODUCTION` relations
- destructive `DROP` / `TRUNCATE` DDL in dbt model SQL

The policy itself is unit-tested.

## Pull-request gate

CI runs the local policy gate first, then parses/builds the dbt project against the CI target. dbt artifacts such as `manifest.json` and `run_results.json` are retained for inspection.

## Production promotion

Production deployment is a separate manually dispatched workflow bound to the GitHub **production environment**. The operator must supply the exact approved Git SHA, and the workflow verifies that SHA before running dbt.

This creates a traceable path from reviewed code to the version actually promoted.

For larger projects the same design can be extended with dbt state/defer and slim CI.

**Technologies:** Snowflake · dbt · GitHub Actions · Python · SQL policy-as-code · CI/CD · release governance · DevOps

[View the public source and workflows on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-cicd)
