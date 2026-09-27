---
layout: default
title: "C & Linux Systems Engineering"
permalink: /blog/c-linux-systems-engineering
---
# C & Linux Systems Engineering

**Role focus:** Systems Engineering · Data Engineering · Linux · Event Streaming

These projects show the lower-level engineering behind the data platforms in the rest of the portfolio. Rather than treating C and Linux as isolated programming exercises, each case connects systems concepts to telemetry, event streaming or database internals.

---

## Linux System Metrics Agent

![Linux System Metrics Agent architecture](/assets/architecture/linux-system-metrics-agent.png)

The **Linux System Metrics Agent** is a small C service that reads telemetry directly from Linux kernel interfaces. It samples CPU activity from `/proc/stat`, memory from `/proc/meminfo`, network counters from `/proc/net/dev`, and filesystem utilization through `statvfs()`. The output is newline-delimited JSON so it can be collected by a log/metrics pipeline or forwarded into Kafka.

The design deliberately keeps **collection separate from transport**. The C process is responsible for accurate host metrics; delivery to Kafka, OpenTelemetry, a warehouse or another observability backend can be attached as a downstream concern. A hardened systemd unit demonstrates how the collector could be run as a long-lived Linux service with restart behavior and restricted privileges.

**Engineering themes:** direct kernel interfaces, resource-efficient collection, service lifecycle, JSON telemetry, Linux hardening, CI compilation.

**Technologies:** C · Linux · POSIX · /proc · statvfs · systemd · JSON · GCC · GitHub Actions.

[View source on GitHub](https://github.com/oleglihvoinen/linux-system-metrics-agent)

---

## C Kafka Telemetry Producer

![C Kafka Telemetry Producer architecture](/assets/architecture/c-kafka-telemetry-producer.png)

The **C Kafka Telemetry Producer** represents an edge or industrial process publishing machine events into an event-driven data platform. The native C application uses **librdkafka** to send versioned JSON events to a Kafka topic. Machine ID is used as the message key, which gives a clear partitioning strategy and keeps events for the same machine ordered inside a partition.

The repository also contains a JSON Schema for the event contract. This separates the event definition from producer code and makes the interface easier to validate and evolve. The current implementation demonstrates delivery callbacks, explicit flushing and environment-based broker configuration; a production version would add SASL/TLS, idempotent producer settings, Schema Registry and operational metrics.

**Engineering themes:** producer semantics, keys and partitions, event versioning, data contracts, delivery acknowledgement, edge-to-platform integration.

**Technologies:** C · Linux · librdkafka · Apache Kafka · JSON Schema · event streaming · GitHub Actions.

[View source on GitHub](https://github.com/oleglihvoinen/c-kafka-telemetry-producer)

---

## C Mini Database Engine

![C Mini Database Engine architecture](/assets/architecture/c-mini-database-engine.png)

The **C Mini Database Engine** is intentionally small so the storage mechanics remain visible. Records have a fixed binary representation and are appended to a data file. The CLI supports `INSERT`, `SELECT`, `DELETE` and `LIST`; duplicate IDs are rejected and deletion uses a tombstone flag rather than physically rewriting the file.

This provides a useful bridge between application-level SQL knowledge and the lower-level concerns implemented by database engines: record layout, persistence, file offsets, scans and deletion semantics. The repository includes a smoke test and CI build. The natural next stage is a page abstraction followed by an in-memory or B+tree index, free-page management, checksums and write-ahead logging.

**Engineering themes:** storage representation, binary persistence, sequential access, logical deletion, database internals, incremental evolution toward indexed/transactional storage.

**Technologies:** C · Linux · binary files · persistence · storage-engine concepts · Make · GitHub Actions.

[View source on GitHub](https://github.com/oleglihvoinen/c-mini-database-engin)

---

These are **portfolio/reference implementations** intended to demonstrate the engineering approach and underlying concepts; they are not presented as production deployments.
