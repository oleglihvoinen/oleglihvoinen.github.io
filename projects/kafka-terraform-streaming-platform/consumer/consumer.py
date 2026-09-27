import json
import os
from confluent_kafka import Consumer

consumer = Consumer({
    "bootstrap.servers": os.environ["KAFKA_BOOTSTRAP_SERVERS"],
    "group.id": "snowflake-order-loader",
    "auto.offset.reset": "earliest",
    "enable.auto.commit": False,
})
consumer.subscribe(["orders.v1"])

def valid(event):
    required = {"event_id", "event_type", "occurred_at", "customer_id", "amount", "currency"}
    return required.issubset(event) and event["amount"] >= 0

while True:
    msg = consumer.poll(1.0)
    if msg is None:
        continue
    if msg.error():
        raise RuntimeError(msg.error())

    event = json.loads(msg.value())
    if valid(event):
        # Replace with Snowflake writer / connector in a deployed implementation.
        print(json.dumps({"status": "accepted", "event": event}))
        consumer.commit(message=msg)
    else:
        print(json.dumps({"status": "rejected", "event": event}))
