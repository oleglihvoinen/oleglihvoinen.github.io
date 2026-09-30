---
layout: default
title: "HaeSiivooja AI Marketplace Intelligence Platform"
permalink: /blog/haesiivooja-ai-marketplace-intelligence
---
# HaeSiivooja AI Marketplace Intelligence Platform

**Role focus:** Data Engineering · Applied AI · Marketplace Analytics · Data Products · SaaS Architecture

## Architecture

![HaeSiivooja AI Marketplace Intelligence architecture](https://raw.githubusercontent.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence/main/docs/architecture.png)

[Open architecture PNG](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence/blob/main/docs/architecture.png)

## Summary

This case turns the operating model of **HaeSiivooja**, a web and mobile cleaning-services marketplace, into an end-to-end AI and data-engineering platform.

The core problem is broader than prediction. A two-sided marketplace must continuously balance **customer demand, cleaner supply, availability, price, quality, location and service compatibility**. The platform therefore combines transactional data engineering, governed metrics, temporal feature pipelines, forecasting, ranking and APIs that can return decisions to web/mobile applications.

The public implementation uses **synthetic/anonymized marketplace data only**. No production customer identities, exact addresses, phone numbers, emails, Stripe IDs or payment credentials are published.

## Real product domain

The HaeSiivooja backend already contains the business objects needed for a meaningful marketplace-intelligence platform: cleaners, bookings, recurring and blocked availability, services, apartment size, location, price/duration, booking status, ratings and Stripe-connected payment flows.

Rather than exposing production records, this case reproduces those analytical shapes with deterministic synthetic data. That makes the project public, reproducible and privacy-safe while preserving the real business complexity.

## Data engineering architecture

The operational SaaS remains the system of record. A production architecture would capture booking and availability changes incrementally and create an analytical event history.

**Web/mobile SaaS → MySQL transactional data → CDC/events → Bronze history → standardized marketplace entities → Gold metrics & feature tables → AI models → FastAPI decision services**

The same logical design maps to either:

- **Debezium / Kafka → Snowflake → dbt**, or
- **Microsoft Fabric → OneLake/Lakehouse → PySpark/Delta**

The repository keeps the public implementation local and reproducible so no cloud credentials are required.

## Governed data products

The pipeline builds two primary analytical products.

### Marketplace demand features

Daily city/service grain containing booking volume, completions, cancellations, booked minutes, gross marketplace value, calendar features and cancellation rate.

### Cleaner features

Per-cleaner quality and capacity signals including rating, reliability, historical completion rate, booked minutes, utilization proxy, relative price and historical marketplace value.

A separate semantic specification defines governed metrics including **Booking GMV, Completed Bookings, Cancellation Rate and Supply Utilization**, with explicit grain and ownership.

## AI capability 1 — Demand forecasting

A gradient-boosted regression pipeline forecasts booking demand by city, service and date.

The training workflow uses a **chronological holdout**, avoiding a random split that would leak future temporal structure into model validation.

Potential marketplace actions include:

- identify cities/services where demand is likely to exceed available cleaner capacity
- nudge existing cleaners to open more availability
- prioritize cleaner acquisition by location
- plan campaigns around expected low-demand periods
- expose supply-demand signals in operations dashboards

The deterministic synthetic dataset currently produces a holdout MAE of approximately **1.55 bookings/day**. This validates the public pipeline only; it is not a claim about production HaeSiivooja forecast accuracy.

## AI capability 2 — Cleaner ranking

The second model ranks already-eligible cleaners using:

- distance/travel proxy
- relative price
- customer rating
- reliability
- historical completion rate
- utilization

Availability and service compatibility are treated as **hard business constraints**. AI ranks only candidates who are eligible for the requested booking.

The public synthetic ranking workflow produces ROC-AUC of approximately **0.75**. Because labels are synthetic, this metric demonstrates model/training integration rather than marketplace performance.

The ranking API also combines model probability with a quality guardrail so the final score is not based on the classifier alone.

## Decision API

FastAPI exposes model capabilities through stable application contracts:

- `GET /health`
- `POST /api/v1/demand-forecast`
- `POST /api/v1/match`

This is important architecturally: models are not embedded directly in mobile/web clients. They are deployed behind governed APIs so model changes can be versioned independently from customer-facing applications.

## Privacy and governance

The public project deliberately excludes:

- real customer or cleaner names
- email and phone data
- exact cleaning addresses
- Stripe account/customer/payment identifiers
- payment methods or credentials

A production implementation should pseudonymize analytical identities, separate PII from behavioral/transactional data, enforce role-based access, define retention rules and support GDPR data-subject workflows.

**Technologies:** Python · Pandas · scikit-learn · FastAPI · Pydantic · demand forecasting · ranking · feature engineering · semantic metrics · marketplace analytics · CI/CD · MySQL CDC · Debezium/Kafka · Snowflake/dbt · Microsoft Fabric/OneLake architecture.

[View the implementation on GitHub](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence)
