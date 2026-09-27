# CDC: PostgreSQL -> Debezium -> Kafka -> Snowflake

Reference architecture for change-data-capture ingestion.

PostgreSQL WAL changes are captured by Debezium and published to Kafka. Downstream processing can persist immutable raw events to Snowflake before dbt incremental transformations build analytical models.

**Technologies:** PostgreSQL · CDC · Debezium · Apache Kafka · Docker Compose · Snowflake · dbt · event streaming

The local Compose configuration demonstrates the PostgreSQL/Kafka/Debezium side. Snowflake loading is an architectural integration point and requires external credentials/services.
