# Architecture

1. Data Factory pipelines ingest ERP/CRM/API/file sources into OneLake Bronze.
2. PySpark notebooks standardize, validate and deduplicate records into Silver Delta tables.
3. Gold models expose business-ready facts and dimensions.
4. A governed semantic model defines reusable measures and dimensions.
5. Power BI, APIs and AI/data-agent consumers use Gold/semantic assets rather than raw sources.

Production concerns include incremental loads, workspace/environment separation, deployment pipelines, RBAC, lineage, monitoring and data-quality gates.
