---
layout: default
title: "C & Linux Systems Engineering"
permalink: /blog/c-linux-systems-engineering
---
# C & Linux Systems Engineering

**Role focus:** Systems Engineering · Data Engineering · Linux · Event Streaming

This section demonstrates systems-level engineering beneath modern data platforms: Linux kernel interfaces, native C services, Kafka event production and storage-engine fundamentals. Each implementation is built around explicit operational boundaries, versioned interfaces and automation rather than isolated code samples.

---

## Linux System Metrics Agent

![Linux System Metrics Agent architecture](/assets/architecture/linux-system-metrics-agent.png)

The **Linux System Metrics Agent** is a native C service that collects CPU, memory, network and filesystem telemetry directly from Linux kernel interfaces. CPU activity is derived from `/proc/stat`, memory from `/proc/meminfo`, network counters from `/proc/net/dev`, and filesystem utilization through `statvfs()`.

The agent emits newline-delimited JSON, keeping the telemetry format simple and machine-readable for downstream ingestion. The architecture deliberately separates **metric collection from transport**: the collector owns accurate host sampling, while Kafka, OpenTelemetry, Fluent Bit or another backend can be introduced as a separate delivery layer.

A hardened `systemd` unit defines restart behavior, restricted privileges and service lifecycle management. GitHub Actions validates compilation and basic runtime output on Ubuntu.

**Engineering themes:** Linux kernel interfaces, low-overhead telemetry, service lifecycle, structured output, operational hardening, CI.

**Technologies:** C · Linux · POSIX · /proc · statvfs · systemd · JSON · GCC · GitHub Actions.

[View source on GitHub](https://github.com/oleglihvoinen/linux-system-metrics-agent)

---

## C Kafka Telemetry Producer

![C Kafka Telemetry Producer architecture](/assets/architecture/c-kafka-telemetry-producer.png)

The **C Kafka Telemetry Producer** models an edge or industrial integration where machine events are published directly into an event-streaming platform. The native application uses **librdkafka** to publish versioned telemetry records to Kafka.

Machine ID is used as the message key, providing deterministic partition selection and preserving per-machine ordering within a partition. A standalone JSON Schema defines the telemetry contract independently from producer code, which improves compatibility management and schema governance.

The implementation includes delivery callbacks, explicit flush semantics and environment-based broker configuration. The operational design can be extended with SASL/TLS, idempotent producer settings, Schema Registry, Avro/Protobuf, batching, producer metrics and dead-letter handling.

**Engineering themes:** producer semantics, partitioning strategy, event contracts, acknowledgement handling, edge-to-platform integration.

**Technologies:** C · Linux · librdkafka · Apache Kafka · JSON Schema · event streaming · GitHub Actions.

[View source on GitHub](https://github.com/oleglihvoinen/c-kafka-telemetry-producer)

---

## C Mini Database Engine

![C Mini Database Engine architecture](/assets/architecture/c-mini-database-engine.png)

The **C Mini Database Engine** exposes storage behavior below the SQL abstraction layer. Records use a fixed binary representation and are persisted directly to a data file. The CLI supports `INSERT`, `SELECT`, `DELETE` and `LIST`, with duplicate-ID validation and logical deletion through tombstone state.

The design makes record layout, file positions, sequential lookup and persistence semantics explicit. Automated smoke tests verify insert, lookup and deletion behavior in CI.

The architecture roadmap extends naturally toward page management, memory-resident indexes, B-tree/B+tree structures, free-page tracking, checksums, write-ahead logging and crash recovery.

**Engineering themes:** record layout, binary persistence, storage access, logical deletion, database internals, transactional architecture.

**Technologies:** C · Linux · binary files · persistence · storage-engine architecture · Make · GitHub Actions.

[View source on GitHub](https://github.com/oleglihvoinen/c-mini-database-engine)
