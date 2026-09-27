#include <librdkafka/rdkafka.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const char *brokers=getenv("KAFKA_BOOTSTRAP_SERVERS");
    if(!brokers){ fprintf(stderr,"KAFKA_BOOTSTRAP_SERVERS is required\n"); return 1; }
    char err[512]; rd_kafka_conf_t *conf=rd_kafka_conf_new();
    if(rd_kafka_conf_set(conf,"bootstrap.servers",brokers,err,sizeof(err))!=RD_KAFKA_CONF_OK){
        fprintf(stderr,"%s\n",err); return 1;
    }
    rd_kafka_t *rk=rd_kafka_new(RD_KAFKA_PRODUCER,conf,err,sizeof(err));
    if(!rk){ fprintf(stderr,"%s\n",err); return 1; }
    char payload[256];
    snprintf(payload,sizeof(payload),
      "{\"machine_id\":\"M-001\",\"timestamp\":%ld,\"temperature\":72.4,\"rpm\":1480,\"status\":\"RUNNING\"}",
      (long)time(NULL));
    rd_kafka_producev(rk,RD_KAFKA_V_TOPIC("machine.telemetry.v1"),
      RD_KAFKA_V_KEY("M-001",5),RD_KAFKA_V_VALUE(payload,strlen(payload)),RD_KAFKA_V_END);
    rd_kafka_flush(rk,5000); rd_kafka_destroy(rk); return 0;
}
