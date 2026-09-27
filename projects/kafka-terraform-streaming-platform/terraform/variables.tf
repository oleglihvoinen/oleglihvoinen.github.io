variable "cloud" {
  type        = string
  description = "Cloud hosting the managed Kafka cluster."
  default     = "AWS"
}

variable "region" {
  type        = string
  description = "Provider region for the portfolio cluster."
  default     = "eu-central-1"
}
