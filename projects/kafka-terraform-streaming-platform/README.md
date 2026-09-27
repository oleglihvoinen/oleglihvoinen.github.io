# Kafka + Terraform Streaming Data Platform

Portfolio/reference implementation of an event-driven data engineering platform combining Apache Kafka, Python and Terraform.

## Use case
An order service publishes order events. Kafka decouples producers from downstream consumers. A Python consumer validates and transforms events for downstream analytical loading. Terraform defines the Kafka infrastructure as code.

## Architecture
```text
Order/API producer
       |
       v
 Kafka: orders.v1  ----> consumer group ----> validation/transformation ----> Snowflake RAW
       |
       +-----------> future consumers (fraud, notifications, operational analytics)

Terraform
   |
   +--> Kafka environment / cluster / topic / service accounts / ACL-ready infrastructure
```

## Technologies
**Apache Kafka · Terraform · Python · event streaming · Infrastructure as Code · Docker · Snowflake-ready integration · CI/CD**

This is a portfolio/reference implementation. Terraform is intentionally configured for Confluent Cloud as a practical managed-Kafka example; credentials are supplied through environment variables and are not committed.
