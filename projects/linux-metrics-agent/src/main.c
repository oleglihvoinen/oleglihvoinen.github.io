#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <time.h>

static long mem_available_kb(void) {
    FILE *f=fopen("/proc/meminfo","r"); char k[64]; long v=0; char unit[16];
    if(!f) return -1;
    while(fscanf(f,"%63s %ld %15s",k,&v,unit)==3)
        if(strcmp(k,"MemAvailable:")==0){ fclose(f); return v; }
    fclose(f); return -1;
}
int main(void) {
    char host[256]="unknown"; gethostname(host,sizeof(host));
    struct statvfs fs; double disk=-1;
    if(statvfs("/",&fs)==0) disk=100.0*(1.0-(double)fs.f_bavail/fs.f_blocks);
    printf("{\"hostname\":\"%s\",\"timestamp\":%ld,\"mem_available_kb\":%ld,\"disk_used_pct\":%.2f}\n",
           host,(long)time(NULL),mem_available_kb(),disk);
    return 0;
}
