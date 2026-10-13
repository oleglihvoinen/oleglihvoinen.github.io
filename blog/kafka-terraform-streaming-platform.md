---
layout: default
title: "Kafka + Terraform Streaming Data Platform"
permalink: /blog/kafka-terraform-streaming-platform
---
# Kafka + Terraform Streaming Data Platform

**Role focus:** Data Engineering · Streaming · Infrastructure as Code · Reliability

## Summary

This case is now a standalone event-streaming platform rather than a minimal producer/consumer example. It focuses on the operational guarantees that make Kafka useful in a data platform: event contracts, partitioning, producer acknowledgements, manual offset commits, replay safety, dead-letter handling and infrastructure policy.

## Architecture

```text
Order/API producers
        |
        v
    orders.v1
        |
        +----> validated consumer group ----> Snowflake / Fabric sink
        |                 |
        |                 +----> orders.dlq.v1
        |
        +----> independent operational / fraud consumers

Terraform -> topic contract, partitions, retention and environment configuration
```

## Event contract

A versioned JSON Schema defines the `orders.v1` payload. Unknown fields are rejected so accidental schema expansion does not silently become part of the contract.

The producer validates the event before publish and uses the business order ID as the Kafka key, supporting stable per-order partitioning and ordering.

## Delivery and replay behavior

The producer enables Kafka idempotence and `acks=all`.

The consumer disables automatic commits. A message is committed only after one of two controlled outcomes:

- successful processing, or
- successful publication of a dead-letter envelope for an invalid record.

The transport identity `topic:partition:offset` is used as an idempotency key so replay decisions are explicit.

## Dead-letter handling

Invalid JSON or contract violations produce a DLQ record that preserves:

- source topic
- partition
- offset
- idempotency key
- validation error
- original payload

That makes failures diagnosable and replayable instead of disappearing in logs.

## Terraform

Terraform defines a provider-neutral topic contract for the main and DLQ topics, including partition count, retention and minimum in-sync replica expectations. Environment-specific modules can map the same contract to Confluent Cloud, AWS MSK or another managed Kafka service.

## CI

GitHub Actions validates:

- Python behavior with pytest
- event contract logic
- Terraform formatting
- Terraform configuration validity

**Technologies:** Apache Kafka · confluent-kafka · Python · Terraform · JSON Schema · DLQ · idempotency · manual commits · CI/CD · Snowflake/Fabric-ready streaming

[View the standalone implementation on GitHub](https://github.com/oleglihvoinen/kafka-terraform-streaming-platform)
