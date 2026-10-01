---
layout: default
title: "HaeSiivooja Real-Time Marketplace Intelligence & AI Decision Platform"
permalink: /blog/haesiivooja-ai-marketplace-intelligence
---
# HaeSiivooja Real-Time Marketplace Intelligence & AI Decision Platform

**Role focus:** Data Engineering · Real-Time Streaming · Applied AI · Decision Intelligence · Marketplace Data Products · SaaS Architecture

## Architecture

![HaeSiivooja Real-Time Marketplace Intelligence & AI Decision Platform architecture](https://raw.githubusercontent.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence/main/docs/architecture.png)

[Open architecture PNG](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence/blob/main/docs/architecture.png)

## Summary

This case evolves the HaeSiivooja marketplace domain into a **real-time data and AI decision platform** for a web, Android and iOS SaaS marketplace.

A two-sided marketplace must continuously balance **customer demand, cleaner supply, availability, service compatibility, price, quality and location**. The architecture therefore goes beyond reporting or isolated ML models. It connects operational events to governed data products, predictions, decision recommendations, policy controls and measurable outcomes.

The closed-loop operating model is:

**Observe → Predict → Recommend → Approve → Act → Measure → Improve**

The public repository uses deterministic synthetic/anonymized marketplace data and contains no production customer identities, exact addresses, Stripe IDs or payment credentials.

## Real product domain

The HaeSiivooja backend already contains the core business objects needed for the platform: cleaners, bookings, recurring and blocked availability, services, apartment sizes, location, pricing and duration, booking status, ratings and Stripe-connected payment flows.

The public case reproduces those analytical shapes without publishing operational records.

## Real-time data architecture

The production architecture is designed around continuous change capture:

**Web / Android / iOS SaaS → MySQL → Debezium CDC → Kafka → Bronze event history → Silver marketplace model → Gold metrics & feature tables → ML models → semantic/governance layer → AI decision service → policy & human approval → action APIs → applications**

Outcome events such as availability responses, conversions, completed bookings, cancellations and quality signals flow back into the platform so recommendations can be evaluated and improved.

The same governed data layers can map to either:

- **Snowflake + dbt**, or
- **Microsoft Fabric + OneLake/Lakehouse + PySpark/Delta**

## Implemented public components

The repository currently implements:

- deterministic synthetic HaeSiivooja-shaped marketplace data generation
- demand and cleaner feature pipelines
- gradient-boosted demand forecasting
- cleaner ranking with explicit quality guardrails
- governed semantic metric contracts
- FastAPI forecast and matching endpoints
- a marketplace decision endpoint that combines forecast demand with a public-case capacity proxy
- recommendation-only actions with human-approval flags
- automated tests and CI
- a Debezium MySQL connector example
- a versioned booking-event JSON Schema
- reproducible colored architecture generation

The public decision endpoint is intentionally **recommendation-only**. It does not autonomously execute campaigns, change pricing or move money.

## Governed data products

### Marketplace demand features

Daily city/service grain containing booking volume, completions, cancellations, booked minutes, gross marketplace value, calendar features and cancellation rate.

### Cleaner features

Per-cleaner signals including rating, reliability, completion rate, booked minutes, utilization proxy, relative price and historical marketplace value.

### Semantic metric contracts

Machine-readable definitions for **Booking GMV, Completed Bookings, Cancellation Rate and Supply Utilization**, including explicit grain and ownership.

## AI capability 1 — Demand forecasting

A gradient-boosted regression pipeline forecasts booking demand by city, service and date. Validation uses a **chronological holdout** rather than a random split.

The deterministic public dataset currently produces a holdout MAE of approximately **1.55 bookings/day**. This validates the synthetic pipeline only and is not a claim about production HaeSiivooja performance.

## AI capability 2 — Cleaner ranking

Eligible cleaners are ranked using:

- distance/travel proxy
- relative price
- customer rating
- reliability
- historical completion rate
- utilization

Availability and service compatibility remain **hard business constraints** outside the model.

The synthetic ranking workflow currently produces ROC-AUC of approximately **0.75**. Because labels are synthetic, this is a pipeline-validation metric rather than a production marketplace result.

## AI capability 3 — Marketplace decision intelligence

The decision layer combines predicted demand with supply/capacity signals and returns explainable operational recommendations.

Examples include:

- **availability campaign** when forecast demand exceeds estimated cleaner capacity
- **wider matching-radius evaluation** when local supply is insufficient
- **incentive simulation** for larger shortages
- **no intervention** when estimated capacity already covers expected demand

High-impact recommendations include an explicit human-approval requirement.

## Decision API

FastAPI exposes the current capabilities through stable contracts:

- `GET /health`
- `POST /api/v1/demand-forecast`
- `POST /api/v1/match`
- `POST /api/v1/marketplace-decision`

The API boundary lets the models and decision logic evolve independently from the customer-facing web, Android and iOS applications.

## Real-time event contracts

The repository includes:

- a **Debezium MySQL CDC connector configuration**
- a **versioned booking event JSON Schema**
- a documented Kafka/CDC boundary

These artifacts define how committed marketplace changes can enter a streaming platform before downstream transformation.

## Policy, guardrails and human approval

The architecture deliberately separates recommendation from execution. A production action boundary should evaluate model confidence, supply-demand gap, financial/customer impact, business rules, rate limits, approval requirements and audit metadata before any action is executed.

## Observability and reliability

A production deployment should monitor:

- source/event freshness
- Kafka consumer lag
- schema compatibility
- data-quality failures
- feature freshness
- model drift
- API latency
- decision volume and approval rate
- measured outcome
- end-to-end lineage

## Privacy and governance

The public project excludes real customer or cleaner names, phone/email data, exact cleaning addresses, Stripe account/customer/payment identifiers and payment methods.

A production implementation should use pseudonymous analytical identifiers, isolate PII, enforce role-based access and retention controls, support GDPR workflows, and audit decision/approval events.

**Technologies:** Python · Pandas · scikit-learn · FastAPI · Pydantic · MySQL · Debezium CDC · Apache Kafka · Bronze/Silver/Gold architecture · feature engineering · demand forecasting · ranking · decision intelligence · semantic metrics · CI/CD · Snowflake/dbt · Microsoft Fabric/OneLake.

[View the implementation on GitHub](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence)
