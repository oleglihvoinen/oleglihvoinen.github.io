import json
import os
import time
import uuid
from datetime import datetime, timezone
from confluent_kafka import Producer

producer = Producer({"bootstrap.servers": os.environ["KAFKA_BOOTSTRAP_SERVERS"]})

def publish_order(customer_id: str, amount: float):
    event = {
        "event_id": str(uuid.uuid4()),
        "event_type": "order.created",
        "event_version": 1,
        "occurred_at": datetime.now(timezone.utc).isoformat(),
        "customer_id": customer_id,
        "amount": amount,
        "currency": "EUR",
    }
    producer.produce("orders.v1", key=customer_id, value=json.dumps(event))
    producer.flush()

if __name__ == "__main__":
    publish_order("C001", 149.90)
