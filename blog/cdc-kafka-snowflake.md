---
layout: default
title: "CDC with Debezium, Kafka & Snowflake"
permalink: /blog/cdc-kafka-snowflake
---
# CDC with Debezium, Kafka & Snowflake

**Role focus:** Data Engineering · Streaming · Change Data Capture

This case demonstrates the architecture **PostgreSQL WAL → Debezium → Kafka → Snowflake RAW → dbt incremental models**. The repository includes a Docker Compose environment for PostgreSQL, Kafka and Debezium plus a connector definition for customer/order CDC.

It demonstrates inserts, updates and deletes as events rather than repeated full-table batch extraction.

**Technologies:** PostgreSQL · Debezium · Apache Kafka · Docker Compose · CDC · Snowflake · dbt.

[View implementation](https://github.com/oleglihvoinen/oleglihvoinen.github.io/tree/main/projects/cdc-kafka-snowflake)
