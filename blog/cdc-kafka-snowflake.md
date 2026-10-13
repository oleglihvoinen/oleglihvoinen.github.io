---
layout: default
title: "CDC with Debezium, Kafka & Snowflake"
permalink: /blog/cdc-kafka-snowflake
---
# CDC with Debezium, Kafka & Snowflake

**Role focus:** Data Engineering · Streaming · CDC Correctness · Replay · Analytics Engineering

![CDC Kafka Snowflake architecture](/assets/architecture/cdc-kafka-snowflake-pipeline.png)

## Summary

This case implements PostgreSQL WAL → Debezium → Kafka → Snowflake/dbt CDC with an emphasis on **state correctness under duplicates, deletes, replay and out-of-order delivery**.

## Source capture and streaming

The Docker environment runs PostgreSQL with logical replication, Kafka and Debezium. Database inserts, updates and deletes become structured CDC events instead of periodic full-table extracts.

Kafka supplies durable event positions and replay.

## Source and transport lineage

The analytical event model retains:

- Debezium operation type
- source LSN
- event timestamp
- Kafka partition
- Kafka offset
- deterministic event ID

This lets the downstream model reason about source order rather than assuming arrival order is correct.

## Delete-aware staging

Debezium delete events have a null after-image. The staging model therefore resolves the order key and other trace fields from the before-image when necessary.

Without that handling, deletes can disappear during analytical reconstruction.

## Replay-safe current state

The incremental current-state model deliberately reprocesses a bounded overlap interval. Within each business key, events are ranked by source LSN, event time and Kafka offset.

A Python reducer independently models the same correctness rules and is tested for:

- duplicate events
- out-of-order events
- deletes
- replay
- deterministic transport/source identity

## Separation of history and state

Snowflake RAW retains event history and lineage. dbt derives consumer-facing current state from that immutable history. This preserves replay and investigation capability instead of overwriting the only copy of a change.

**Technologies:** PostgreSQL · WAL · Debezium · Apache Kafka · Docker Compose · Snowflake · dbt · Python · CDC · replay · idempotency · incremental ELT

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/cdc-kafka-snowflake-pipeline)
