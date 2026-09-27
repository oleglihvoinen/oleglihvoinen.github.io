resource "confluent_environment" "portfolio" {
  display_name = "data-engineering-portfolio"
}

resource "confluent_kafka_cluster" "streaming" {
  display_name = "orders-streaming"
  availability = "SINGLE_ZONE"
  cloud        = var.cloud
  region       = var.region
  basic {}

  environment {
    id = confluent_environment.portfolio.id
  }
}

resource "confluent_kafka_topic" "orders" {
  kafka_cluster {
    id = confluent_kafka_cluster.streaming.id
  }
  topic_name       = "orders.v1"
  partitions_count = 3
  rest_endpoint    = confluent_kafka_cluster.streaming.rest_endpoint
}
