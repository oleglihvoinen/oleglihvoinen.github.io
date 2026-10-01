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

### 📱 [HaeSiivooja — Cleaning Services SaaS Marketplace](https://haesiivooja.fi/)
A Finnish **SaaS marketplace** connecting customers and cleaning professionals through a digital service. Customers can discover cleaners, view pricing and arrange bookings; cleaners can create profiles, set availability and prices, and receive work opportunities. The platform includes a web presence and **Android and iOS mobile apps developed with Kotlin and Swift**.

[Visit HaeSiivooja](https://haesiivooja.fi/)

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

These cases show a broader **enterprise data-platform engineering** stack: Snowflake and dbt ELT, Microsoft Fabric/OneLake lakehouse patterns, Python/FastAPI data products, Kafka streaming and CDC, Terraform Infrastructure as Code, GitHub Actions, Docker, MDM/data quality, semantic governance and AI-ready data services.

### ❄️ [Snowflake + dbt Customer 360](/blog/snowflake-dbt-customer360)
A governed **Customer 360 data product** that standardizes CRM and ERP customer data, resolves identities and publishes a golden customer dimension. A **Python FastAPI REST layer** exposes governed customer and data-quality endpoints from Snowflake, with OpenAPI documentation and Docker packaging. The implementation also includes synthetic data, dbt tests, snapshots, macros and architecture documentation.

**Technologies:** Snowflake, dbt, SQL, Python, FastAPI, REST API, OpenAPI, Docker, MDM, data quality, dimensional modeling.  
[Read the case study](/blog/snowflake-dbt-customer360) · [View source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-customer360)

### 🌊 [Kafka + Terraform Streaming Data Platform](/blog/kafka-terraform-streaming-platform)
An event-driven data pipeline using **Apache Kafka, Python and Terraform**, with a versioned order-event producer, consumer-group processing, explicit offset handling and Infrastructure as Code for managed Kafka resources. The architecture is designed for streaming ingestion into Snowflake and downstream dbt models.

**Technologies:** Apache Kafka, Terraform, Python, event streaming, Infrastructure as Code, Snowflake integration, Git, CI/CD.  
[Read the case study](/blog/kafka-terraform-streaming-platform) · [View source on GitHub](https://github.com/oleglihvoinen/oleglihvoinen.github.io/tree/main/projects/kafka-terraform-streaming-platform)

### 🏔️ [Modern Snowflake + dbt ELT Analytics Platform](/blog/snowflake-dbt-analytics-platform)
A layered **RAW → staging → intermediate → marts** architecture for turning operational data into analytics-ready Snowflake models, including incremental fact processing designed for scalable ELT workloads.

**Technologies:** Snowflake, dbt, SQL, ELT, dimensional modeling, incremental processing.  
[Read the case study](/blog/snowflake-dbt-analytics-platform) · [View source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-analytics-platform)

### ⚙️ [Snowflake + dbt CI/CD](/blog/snowflake-dbt-cicd)
A production-oriented delivery pattern for Snowflake transformations using **GitHub Actions and dbt**, with automated builds and data tests, secret-based credentials and a Git-based promotion workflow.

**Technologies:** Snowflake, dbt, GitHub Actions, CI/CD, SQL, DevOps.  
[Read the case study](/blog/snowflake-dbt-cicd) · [View source on GitHub](https://github.com/oleglihvoinen/snowflake-dbt-cicd)

### 🔬 [FTIR Spectroscopy Integration with ERP Systems](/blog/integrating-ftir-spectroscopy-data-into-erp-workflows.html)
A data engineering project connecting chemical spectroscopy analysis to ERP workflows for material verification. It covers spectral preprocessing, PCA visualization, anomaly detection and PASS/FAIL decisions exposed through a REST API for use in batch records.

**Technologies:** Python, NumPy, Pandas, SciPy, scikit-learn, FastAPI.  
[Read the project](/blog/integrating-ftir-spectroscopy-data-into-erp-workflows.html)

---

### 🏢 [Microsoft Fabric Enterprise Data Platform](/blog/fabric-enterprise-data-platform)
An enterprise **medallion/lakehouse platform** showing how ERP, CRM, APIs and files move through Data Factory into OneLake/Lakehouse Bronze, then through PySpark/Delta standardization and data-quality processing into Silver and governed Gold models. A semantic-consumption boundary is designed for Power BI, APIs and governed AI.

**Technologies:** Microsoft Fabric, OneLake, Lakehouse, Data Factory, PySpark, Delta, SQL, Power BI, semantic models, data quality, CI/CD.  
[Read the case study](/blog/fabric-enterprise-data-platform) · [View source on GitHub](https://github.com/oleglihvoinen/fabric-enterprise-data-platform)

### 🔄 [CDC with Debezium, Kafka & Snowflake](/blog/cdc-kafka-snowflake)
An end-to-end CDC architecture using **PostgreSQL WAL → Debezium → Kafka → Snowflake RAW → dbt**. The repository includes a runnable local PostgreSQL/Kafka/Debezium environment, sample operational tables, a connector definition, a Snowflake raw-event model retaining Kafka lineage metadata, and dbt models for typed staging and incremental current-state analytics.

**Technologies:** PostgreSQL, WAL, Debezium, Apache Kafka, Docker Compose, Snowflake, dbt, SQL, CDC, incremental ELT.  
[Read the case study](/blog/cdc-kafka-snowflake) · [View source on GitHub](https://github.com/oleglihvoinen/cdc-kafka-snowflake-pipeline)

### 🧠 [Governed Semantic Layer + AI Data Agent](/blog/semantic-ai-data-agent)
A governed analytical-AI pattern that places **approved metric and dimension contracts between natural-language questions and physical warehouse models**. The FastAPI layer publishes governed metrics, validates requested dimensions and returns ownership/provenance, creating a controlled boundary for future Snowflake/dbt or Fabric-backed AI agents instead of unrestricted LLM-to-database access.

**Technologies:** Python, FastAPI, REST, Pydantic, YAML semantic contracts, Snowflake/dbt-ready metrics, Microsoft Fabric-ready semantics, LLM grounding, provenance, governance, Docker, CI.  
[Read the case study](/blog/semantic-ai-data-agent) · [View source on GitHub](https://github.com/oleglihvoinen/semantic-ai-data-agent)

## C & Linux Systems Engineering

These projects demonstrate **systems-level engineering beneath the cloud and analytics stack**: direct Linux kernel interfaces, native C services, Kafka event publishing and database-storage fundamentals. Each case is implemented with source code, build automation and explicit operational considerations.

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
