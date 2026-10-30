---
layout: default
title: "Senior Data Engineer · Web, Mobile & SaaS Products"
description: "Senior Data Engineer with 15+ years across enterprise data, MDM, cloud platforms and AI, plus hands-on development of web applications, mobile apps and SaaS products."
permalink: /
---

# Oleg Lihvoinen

## Senior Data Engineer | Data & AI Platforms | Web, Mobile & SaaS | C & Linux Systems

I bring **15+ years of enterprise data experience** across data engineering, master data management, analytics, integration and application development. My work combines **established Microsoft and Oracle platforms** with modern cloud data engineering, streaming, APIs, governance and AI-enabled data services, together with hands-on development of **web applications, Android and iOS mobile applications, and SaaS platforms for web and mobile**, as well as **C and Linux systems development**.

I design data solutions around clear contracts, reliable pipelines, governed business definitions and maintainable delivery practices. I also build **customer-facing SaaS products and platforms across web and mobile**, including database-backed web applications, APIs, marketplaces, Android applications and iOS applications. The portfolio below covers enterprise MDM, database applications, Snowflake/dbt, Microsoft Fabric, Kafka/CDC, Infrastructure as Code, REST data products, governed AI, full-stack SaaS product development for web and mobile, and **C/Linux systems engineering**, including POSIX services, systemd, native Kafka integration and storage-engine development. [View my repositories on GitHub](https://github.com/oleglihvoinen?tab=repositories).

**Based in Järvenpää, Finland** · [Contact me](mailto:lihvoinenoleg@gmail.com)

---

## Selected Work

### 📱 [HaeSiivooja — SaaS Marketplace, Mobile Apps & AI Search](/blog/haesiivooja-saas-marketplace)
A Finnish **cleaning-services SaaS product ecosystem** combining a customer/provider marketplace, native **Android (Kotlin) and iOS (Swift)** applications, and an **AI-powered cleaning company search in Finland** at [app.haesiivooja.fi](https://app.haesiivooja.fi/). The flagship case also links the product domain to the companion real-time marketplace intelligence and AI decision platform.

[Read the flagship case](/blog/haesiivooja-saas-marketplace) · [Visit HaeSiivooja](https://haesiivooja.fi/) · [Open AI search](https://app.haesiivooja.fi/)

### 🤖 [HaeSiivooja Real-Time Marketplace Intelligence & AI Decision Platform](/blog/haesiivooja-ai-marketplace-intelligence)
A **real-time data engineering and AI decision platform** built around the HaeSiivooja web/mobile SaaS domain. The architecture connects MySQL operational changes through Debezium CDC and Kafka to governed Bronze/Silver/Gold data products, forecasting, cleaner ranking, semantic metrics and recommendation-only operational decisions with policy and human-approval controls. Outcome events complete the feedback loop from marketplace activity back to measurable decision quality.

**Technologies:** Python, Pandas, scikit-learn, FastAPI, MySQL, Debezium CDC, Apache Kafka, Bronze/Silver/Gold data products, feature engineering, demand forecasting, ranking, decision intelligence, semantic governance, CI/CD, Snowflake/dbt, Microsoft Fabric.  
[Read the case study](/blog/haesiivooja-ai-marketplace-intelligence) · [View source on GitHub](https://github.com/oleglihvoinen/haesiivooja-ai-marketplace-intelligence)

### 🧭 [Master Data Management Tool](/blog/master-data-management)
A browser-based **MDM and data quality application** built with Oracle APEX. It combines CSV import and export, configurable business rules, validation runs, error dashboards, and record management to support data cleansing and harmonisation.

**Technologies:** Oracle APEX, Oracle Database, PL/SQL.  
[Explore the tool and demo](/blog/master-data-management)

---

## Database & Business Applications

### 🛠️ [Oracle DBA Tool](/blog/dba-tool)
An Oracle APEX application for database administration, bringing together session monitoring, performance analysis, schema exploration, health checks and user management in one interface.

**Technologies:** Oracle APEX, Oracle Database, PL/SQL.  
[Read the case study](/blog/dba-tool) · [Download the package](https://github.com/oleglihvoinen/oracle-apex_applications/blob/master/dba_tool.zip)

### 💾 [Data Import/Export Web Application](/blog/data-import-export-web-application)
A browser-based utility for moving CSV and XML data into and out of Oracle databases, supporting data cleansing, harmonisation and migration tasks.

**Technologies:** Oracle APEX, Oracle Database.  
[See details and demo](/blog/data-import-export-web-application)

### 💊 [Pharmacy Online](/blog/pharmacy-online)
An Oracle APEX web database connecting pharmacies, doctors, surgeries and patients. It brings prescription tracking, operational data and reporting together in one application.

[Watch the demo](https://www.youtube.com/watch?v=p366Onv_HGU)

### 🛍️ [Webshop](/blog/webshop)
An Oracle APEX e-commerce application with separate customer-facing and administration interfaces. It supports product and catalogue management, customer orders and order processing within a shared database-backed system.

[Explore the application](/blog/webshop) · [Download the package](https://github.com/oleglihvoinen/oracle-apex_applications/blob/master/webshop_v01.zip)

### 📝 [Oracle APEX Blogging Platform](/blog/oracle-apex-blogging-platform)
A web publishing application with a public blog reader and a separate administration interface. It provides article and comment management, file uploads, visitor statistics and a usage dashboard.

[Explore the platform](/blog/oracle-apex-blogging-platform) · [Download from SourceForge](https://sourceforge.net/projects/blogging-platform/)

### 🚗 [Car Dealer Web Application](/blog/car-dealer-web-application)
A database-backed vehicle marketplace built with Oracle APEX. Registered users can create and manage listings with technical specifications and multiple photos. Buyers can search by make, model, year, price and mileage. The application also supports a single-dealer setup for managing a business's own vehicle inventory.

**Technologies:** Oracle APEX, Oracle Database, HTML, CSS and JavaScript.  
[Explore the application and watch the demo](/blog/car-dealer-web-application)

---

## Data Engineering & Cloud Data Platforms

These cases show a broader **enterprise data-platform engineering** stack: Microsoft Fabric/OneLake, Snowflake and dbt, Kafka/CDC, Terraform Infrastructure as Code, MDM/data quality, semantic governance, APIs and production-oriented CI/CD controls.

### 🏢 [Microsoft Fabric Enterprise Data Platform](/blog/fabric-enterprise-data-platform)
An enterprise Fabric medallion/lakehouse platform with an explicit **incremental control plane**. Durable watermarks advance only after successful completion; failed intervals remain replayable; row accounting, quarantine, run audit and retry decisions are represented as testable pipeline state transitions.

**Technologies:** Microsoft Fabric, OneLake, Lakehouse, Data Factory, PySpark, Delta, SQL, watermarks, quarantine, pipeline audit, Power BI, CI/CD.  
[Read the case study](/blog/fabric-enterprise-data-platform) · [View source on GitHub](https://github.com/oleglihvoinen/fabric-enterprise-data-platform)

### ❄️ [Snowflake + dbt Customer 360](/blog/snowflake-dbt-customer360)
A governed **Customer 360 / MDM data product** with explainable entity resolution, match/review/reject evidence, conflict detection, transitive clustering, field-level survivorship, attribute provenance and a stewardship exception queue. dbt publishes the governed Snowflake customer model while Python tests validate identity and survivorship behavior.

**Technologies:** Snowflake, dbt, SQL, Python, MDM, entity resolution, survivorship, stewardship, data quality, FastAPI, Docker, CI/CD.  
[Read the case study](/blog/snowflake-dbt-customer360) · [View source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-customer360)

### 🌊 [Kafka + Terraform Streaming Data Platform](/blog/kafka-terraform-streaming-platform)
A standalone streaming platform with a **versioned JSON event contract, idempotent producer, manual-commit consumer, replay-safe transport identity and dead-letter handling**. Terraform defines provider-neutral topic policy for partitions, retention and minimum in-sync replicas, while CI validates Python behavior and Terraform configuration.

**Technologies:** Apache Kafka, confluent-kafka, Python, Terraform, JSON Schema, DLQ, idempotency, manual commits, CI/CD, Snowflake/Fabric-ready streaming.  
[Read the case study](/blog/kafka-terraform-streaming-platform) · [View source on GitHub](https://github.com/oleglihvoinen/kafka-terraform-streaming-platform)

### 🏔️ [Modern Snowflake + dbt ELT Analytics Platform](/blog/snowflake-dbt-analytics-platform)
A layered Snowflake/dbt ELT platform hardened for **late-arriving data, overlap replay, idempotent MERGE behavior and source/target reconciliation**. The case adds deterministic payload hashes, pipeline-run audit tables, data-quality exceptions and automated tests for watermark and state-management behavior.

**Technologies:** Snowflake, dbt, SQL, Python, incremental ELT, MERGE, watermarks, reconciliation, dimensional modeling, CI/CD.  
[Read the case study](/blog/snowflake-dbt-analytics-platform) · [View source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-analytics-platform)

### ⚙️ [Snowflake + dbt Release Engineering](/blog/snowflake-dbt-cicd)
A governed release pipeline for Snowflake/dbt with **SQL policy-as-code, policy unit tests, dbt PR validation, retained build artifacts and exact-SHA production promotion through a protected environment**. It demonstrates data-platform release controls rather than a single build command.

**Technologies:** Snowflake, dbt, GitHub Actions, Python, SQL policy-as-code, CI/CD, release governance, DevOps.  
[Read the case study](/blog/snowflake-dbt-cicd) · [View source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-cicd)

### 🔄 [CDC with Debezium, Kafka & Snowflake](/blog/cdc-kafka-snowflake)
A CDC platform focused on **correct state reconstruction under duplicates, deletes, replay and out-of-order delivery**. Debezium source LSN and Kafka positions are retained, delete before-images are handled explicitly, current state is derived from immutable history, and a production Snowflake MERGE pattern includes explicit DELETE behavior.

**Technologies:** PostgreSQL, WAL, Debezium, Apache Kafka, Docker Compose, Snowflake, dbt, Python, CDC, replay, idempotency, incremental ELT.  
[Read the case study](/blog/cdc-kafka-snowflake) · [View source on GitHub](https://github.com/oleglihvoinen/cdc-kafka-snowflake-pipeline)

### 🧠 [Governed Semantic Layer + AI Data Agent](/blog/semantic-ai-data-agent)
A governed analytical-AI boundary with **machine-readable semantic contracts, natural-language tool routing, ambiguity handling, allowed-dimension enforcement, golden-question evaluation and tamper-evident audit records**. The agent can prepare only approved semantic plans rather than inventing warehouse logic.

**Technologies:** Python, FastAPI, Pydantic, YAML semantic contracts, governed tool routing, evaluation, audit chain, Snowflake/dbt-ready semantics, Microsoft Fabric-ready semantics, Docker, CI.  
[Read the case study](/blog/semantic-ai-data-agent) · [View source on GitHub](https://github.com/oleglihvoinen/semantic-ai-data-agent)

---

## C & Linux Systems Engineering

These projects demonstrate systems-level engineering beneath the cloud/data stack: native Linux telemetry, C-based Kafka integration and storage-engine fundamentals.

### 🐧 [Linux System Metrics Agent](/blog/c-linux-systems-engineering)
A lightweight C/Linux observability agent that reads CPU, memory, filesystem and network telemetry directly from Linux interfaces such as `/proc` and `statvfs()`. It emits structured JSONL and includes a hardened systemd service, making the collection layer suitable for connection to Kafka, OpenTelemetry or another monitoring/data pipeline.

**Technologies:** C, Linux, POSIX, /proc, statvfs, systemd, JSON, GCC, GitHub Actions.  
[Read the case study](/blog/c-linux-systems-engineering) · [View source on GitHub](https://github.com/oleglihvoinen/linux-system-metrics-agent)

### ⚡ [C Kafka Telemetry Producer](/blog/c-linux-systems-engineering)
A native **librdkafka** producer for versioned industrial telemetry. Machine ID is used as the Kafka key to support deterministic partitioning and per-machine event ordering, while a JSON Schema defines the event contract independently from producer code.

**Technologies:** C, Linux, librdkafka, Apache Kafka, JSON Schema, event streaming, GCC, GitHub Actions.  
[Read the case study](/blog/c-linux-systems-engineering) · [View source on GitHub](https://github.com/oleglihvoinen/c-kafka-telemetry-producer)

### 🗄️ [C Mini Database Engine](/blog/c-linux-systems-engineering)
A compact storage-engine implementation exposing the mechanics beneath relational databases: fixed binary record layout, append persistence, duplicate-ID checks, sequential lookup, logical deletion and file-position updates. The design intentionally stays readable before evolving toward pages, indexes and write-ahead logging.

**Technologies:** C, Linux, binary files, persistence, storage-engine concepts, Make, GitHub Actions.  
[Read the case study](/blog/c-linux-systems-engineering) · [View source on GitHub](https://github.com/oleglihvoinen/c-mini-database-engine)

---

## AI & ML Projects

These projects explore practical AI application patterns including **RAG, embeddings, persistent memory, grounded web search, prompt-injection defenses, structured extraction, Pydantic validation, OpenAI/Anthropic APIs and Streamlit**.

- **[Product Lens — Product Page Extractor & AI Rewriter](https://github.com/hamk-ai-expert-2026/product_scrapper_oleglihvoinen):** A Streamlit application that extracts structured product data from public e-commerce pages using JSON-LD and HTML metadata fallbacks, validates the result with Pydantic, and optionally rewrites the extracted description with OpenAI. The implementation includes bounded downloads, URL/network protections, missing-field handling and explicit prompt-injection defenses for untrusted webpage content. **Technologies:** Python, Streamlit, Requests, Beautiful Soup, Pydantic, OpenAI Responses API.

- **[Current News Search & Summary](https://github.com/hamk-ai-expert-2026/news_search_app_oleglihvoinen):** A retrieval-and-summarization application that searches current web results through Tavily and sends only retrieved snippets to Claude for grounded summarization. The UI separates model interpretation, retrieved facts and source links, and includes result/session limits plus graceful handling of search or model failures. **Technologies:** Python, Streamlit, Tavily Search API, Anthropic Claude, grounded retrieval, source attribution.

- **[MemoryRAG Assistant](https://github.com/hamk-ai-expert-2026/rag_memory_assistant_oleglihvoinen):** A local RAG assistant combining persistent user preferences with document retrieval. Documents are chunked, embedded with OpenAI embeddings and stored in SQLite; cosine similarity retrieves relevant chunks, which are shown to the user before the grounded answer is generated. The assistant is explicitly constrained to retrieved content and treats documents as untrusted data. **Technologies:** Python, Streamlit, OpenAI, embeddings, SQLite, cosine similarity, RAG, persistent memory.

These projects apply retrieval, predictive modeling and language-model integration to concrete data and application scenarios.

- **[Local LLM RAG Chatbot](/blog/llm-rag):** Retrieval-augmented chat using Ollama, ChromaDB and FastAPI, with an optional Streamlit interface and support for local models or OpenAI.
- **[ChatBuddy-AI](/blog/chatbuddy-ai.html):** A full-stack chatbot using React, Node.js, MongoDB and local Ollama models, with authentication and chat sessions.
- **[Credit Card Fraud Detection](/blog/fraud.html):** XGBoost classification for imbalanced transaction data, evaluated with precision, recall and ROC-AUC.
- **[Loan Default Probability Prediction](/blog/loan-default-prediction.html):** A credit-risk modeling workflow with preprocessing, feature encoding and ROC-AUC evaluation.
- **[Bitcoin Price Prediction](/blog/bitcoin-price-prediction-ml.html):** Time-series experiments using LSTM and Random Forest models with technical indicators.
- **[Titanic Survival Prediction](/blog/titanic.html):** A Kaggle-based XGBoost project covering data cleaning, preprocessing, feature engineering and tabular classification.

---

## Industrial Data & AI

### 🔬 [FTIR Spectroscopy Integration with ERP Systems](/blog/integrating-ftir-spectroscopy-data-into-erp-workflows.html)
A data engineering and applied ML project connecting chemical spectroscopy analysis to ERP workflows for material verification. It covers spectral preprocessing, PCA visualization, anomaly detection and PASS/FAIL decisions exposed through a REST API for use in batch records.

**Technologies:** Python, NumPy, Pandas, SciPy, scikit-learn, FastAPI.  
[Read the project](/blog/integrating-ftir-spectroscopy-data-into-erp-workflows.html)

## About Me

My background combines **enterprise data engineering, Microsoft and Oracle platforms, analytics, AI, application development, and web/mobile SaaS product development**, together with **C/Linux systems development**. I work with **Oracle Database, Microsoft SQL Server, Snowflake and other database technologies**, choosing the right data platform for each problem. My broader toolkit includes **Microsoft Fabric, Azure, Google Cloud, AWS, dbt, DevOps and CI/CD**, alongside SQL, T-SQL, PL/SQL, Python, data quality and MDM, Oracle APEX, APIs and AI-assisted applications. I also build products that bring data into customer-facing web and mobile experiences, and I work with **C, Linux, POSIX services, systemd, native Kafka integration and storage-engine development**.

I am interested in **Senior Data Engineer, MDM and data architecture roles**, as well as opportunities to build **data-driven AI, web/mobile SaaS products, and C/Linux systems**.

[GitHub](https://github.com/oleglihvoinen?tab=repositories) · [Email me](mailto:lihvoinenoleg@gmail.com)

---

## Writing & Technical Notes

- [Master Data Management Tool](/blog/master-data-management)
- [Oracle DBA Tool](/blog/dba-tool)
- [Oracle XE 10g Size Limit and Datafile Resizing](/blog/oracle-xe-datafile-resize)
- [Custom Error Page in Oracle APEX](/blog/custom-error-page-apex)
- [Multiple Star Rating in APEX with jQuery](/blog/multiple-star-rating-apex)
- [Wanda the Fish — Fortunes in Oracle APEX](/blog/wanda-the-fish)
- [Oracle APEX Blogging Platform](/blog/oracle-apex-blogging-platform)

> From enterprise data to usable applications.
