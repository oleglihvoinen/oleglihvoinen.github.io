---
layout: default
title: "CDC with Debezium, Kafka & Snowflake"
permalink: /blog/cdc-kafka-snowflake
---
# CDC with Debezium, Kafka & Snowflake

**Role focus:** Data Engineering · Streaming · Change Data Capture · Analytics Engineering

![CDC Kafka Snowflake architecture](/assets/architecture/cdc-kafka-snowflake-pipeline.png)

## Goal

This case demonstrates a **change-data-capture pipeline** that moves operational database changes into an analytical platform without repeatedly extracting complete source tables. It is designed around the flow **PostgreSQL WAL → Debezium → Kafka → Snowflake RAW → dbt models**.

## Source and capture

The local Docker Compose environment starts PostgreSQL, Kafka and Debezium. PostgreSQL is configured for logical replication and contains example customer and order tables. A Debezium PostgreSQL connector reads the write-ahead log and emits insert, update and delete operations as events.

This keeps the extraction logic close to the database transaction log and turns changes into a durable stream instead of a sequence of full refreshes.

## Streaming and raw ingestion

Kafka provides the durable event layer, including topics, partitions, offsets and replay. The Snowflake RAW design intentionally retains Kafka topic, partition and offset metadata together with the event payload. That metadata is useful for lineage, troubleshooting, deduplication and idempotent ingestion.

The public repository does not claim a live Snowflake connection: Snowflake is the defined downstream integration point and requires external credentials/infrastructure.

## dbt modeling

The included dbt staging model extracts the Debezium event envelope into typed analytical fields. An incremental current-state model uses the event sequence to keep the latest representation of an order while respecting CDC delete operations.

This demonstrates an important separation: the RAW layer preserves the change history, while dbt derives consumer-friendly state and business models.

## Production evolution

A production design would add Kafka Connect/Snowflake connector configuration, Schema Registry, secure SASL/TLS connections, connector monitoring, dead-letter handling, exactly-once/idempotency controls, source schema evolution, freshness SLAs, dbt CI and end-to-end observability.

**Technologies:** PostgreSQL · WAL · Debezium · Apache Kafka · Docker Compose · Snowflake · dbt · SQL · CDC · incremental ELT.

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/cdc-kafka-snowflake-pipeline)
