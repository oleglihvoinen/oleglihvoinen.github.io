---
layout: default
title: "CDC with Debezium, Kafka & Snowflake"
permalink: /blog/cdc-kafka-snowflake
---
# CDC with Debezium, Kafka & Snowflake

**Role focus:** Data Engineering · Streaming · Change Data Capture · Analytics Engineering

![CDC Kafka Snowflake architecture](/assets/architecture/cdc-kafka-snowflake-pipeline.png)

## Executive summary

This architecture implements **change data capture** from PostgreSQL into an analytical platform without recurring full-table extraction. The end-to-end flow is:

**PostgreSQL WAL → Debezium → Kafka → Snowflake RAW → dbt staging/current-state models**

The design separates operational change capture, durable event transport, immutable raw storage and analytical state reconstruction.

## Source capture

The Docker Compose environment starts PostgreSQL, Kafka and Debezium. PostgreSQL runs with logical replication enabled and includes operational customer and order tables.

A Debezium PostgreSQL connector consumes the write-ahead log and converts insert, update and delete operations into structured change events. This approach moves extraction from scheduled table scans to transaction-log-driven event capture.

## Streaming and lineage

Kafka provides the durable event layer through topics, partitions, offsets and replay. The Snowflake RAW design retains Kafka topic, partition and offset metadata alongside the event payload.

That metadata creates a strong operational lineage model for troubleshooting, replay analysis, deduplication and idempotent ingestion.

## dbt transformation layer

The staging model extracts typed fields from the Debezium envelope. An incremental current-state model then resolves the latest event for each order while respecting delete operations.

This preserves an important architectural distinction: **RAW retains change history; dbt derives consumer-facing state**.

## Reliability and enterprise controls

A production deployment would add managed Snowflake ingestion or Kafka Connect configuration, Schema Registry, SASL/TLS, secret management, connector observability, dead-letter handling, source schema-evolution policy, freshness SLAs, idempotency controls and end-to-end operational monitoring.

## Repository scope

The PostgreSQL, Kafka and Debezium components are directly runnable through Docker Compose. Snowflake integration is represented through table design and dbt models and requires environment-specific credentials and services.

**Technologies:** PostgreSQL · WAL · Debezium · Apache Kafka · Docker Compose · Snowflake · dbt · SQL · CDC · incremental ELT.

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/cdc-kafka-snowflake-pipeline)
