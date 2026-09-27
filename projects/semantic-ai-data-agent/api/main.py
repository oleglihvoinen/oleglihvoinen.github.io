from pathlib import Path
import yaml
from fastapi import FastAPI, HTTPException

app = FastAPI(title="Governed Semantic Metrics API", version="1.0")
metrics = {
    m["id"]: m
    for m in yaml.safe_load(Path("semantic/metrics.yml").read_text())["metrics"]
}

@app.get("/api/v1/metrics")
def list_metrics():
    return list(metrics.values())

@app.get("/api/v1/metrics/{metric_id}")
def metric(metric_id: str):
    if metric_id not in metrics:
        raise HTTPException(404, "Unknown or unapproved metric")
    return {"metric": metrics[metric_id], "provenance": "semantic/metrics.yml"}
