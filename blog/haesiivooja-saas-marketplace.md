---
layout: default
title: "HaeSiivooja — SaaS Marketplace, Mobile Apps & AI Cleaning Company Search"
permalink: /blog/haesiivooja-saas-marketplace
---
# HaeSiivooja — SaaS Marketplace, Mobile Apps & AI Cleaning Company Search

**Role focus:** SaaS Product Engineering · Web & Mobile · Backend/API Integration · AI Search · Data & AI Platform

## Summary

**HaeSiivooja** is a Finnish cleaning-services product ecosystem combining a customer-facing SaaS marketplace, cleaner-facing marketplace capabilities, native mobile applications and an AI-powered cleaning-company search experience.

The same product domain also provides the operational foundation for a separate **Real-Time Marketplace Intelligence & AI Decision Platform**, connecting marketplace activity to streaming data engineering, governed metrics, forecasting, ranking and controlled AI-assisted operational decisions.

This creates one end-to-end portfolio story:

**customer-facing product → web/mobile SaaS → operational data → AI search → real-time data platform → governed AI decisions**

## Product ecosystem

### HaeSiivooja marketplace

The main service connects customers and cleaning professionals through a digital marketplace.

Customers can discover cleaning professionals, compare service information and pricing, and arrange bookings. Cleaning professionals can maintain their marketplace presence, availability and pricing and receive work opportunities.

[Visit HaeSiivooja](https://haesiivooja.fi/)

### AI-powered cleaning company search

HaeSiivooja also includes an **AI-powered cleaning company search for Finland**, providing a focused search experience for discovering cleaning companies through the HaeSiivooja ecosystem.

[Open the AI-powered cleaning company search](https://app.haesiivooja.fi/)

### Native mobile applications

The marketplace extends beyond the web experience with native mobile applications:

- **Android:** Kotlin
- **iOS:** Swift

The mobile applications form part of the same marketplace domain and support service discovery and marketplace interaction across web and mobile channels.

## Product and data architecture

```text
Customers / Cleaning Professionals
              |
       +------+------+
       |             |
       v             v
    Web SaaS     Android / iOS
       |             |
       +------+------+
              |
              v
       Marketplace APIs
              |
              v
      Operational MySQL
       /      |       \
      /       |        \
     v        v         v
Bookings  Availability  Services / Ratings / Pricing
     |
     +--------------------------+
     |                          |
     v                          v
AI-powered company search   Real-Time Marketplace
                            Intelligence & AI
                            Decision Platform
```

## Companion data & AI platform

The **HaeSiivooja Real-Time Marketplace Intelligence & AI Decision Platform** takes the same marketplace domain into a production-oriented data-engineering architecture:

**MySQL → Debezium CDC → Kafka → Bronze/Silver/Gold → forecasting and ranking → governed decision API → policy/human approval → marketplace outcomes**

The public implementation uses deterministic synthetic/anonymized data while preserving the business structure of the marketplace.

[Read the Real-Time Marketplace Intelligence & AI Decision Platform case](/blog/haesiivooja-ai-marketplace-intelligence)

[View the data & AI platform source on GitHub](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence)

## Engineering range demonstrated

The combined HaeSiivooja case demonstrates:

- customer-facing SaaS marketplace
- cleaner/provider marketplace workflows
- database-backed web applications and APIs
- Android development with Kotlin
- iOS development with Swift
- AI-powered company search
- operational MySQL data
- real-time CDC and Kafka architecture
- governed marketplace metrics and features
- demand forecasting and cleaner ranking
- recommendation-only AI decisions with human approval controls
- CI/CD and testable data/decision logic

## Live links

**Marketplace:** [haesiivooja.fi](https://haesiivooja.fi/)  
**AI-powered company search:** [app.haesiivooja.fi](https://app.haesiivooja.fi/)  
**Real-time data & AI case:** [Marketplace Intelligence & AI Decision Platform](/blog/haesiivooja-ai-marketplace-intelligence)  
**Public data/AI source:** [GitHub repository](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence)

**Technologies across the ecosystem:** Web SaaS · MySQL · APIs · Kotlin · Swift · Python · FastAPI · Debezium CDC · Apache Kafka · Pandas · scikit-learn · semantic governance · CI/CD
