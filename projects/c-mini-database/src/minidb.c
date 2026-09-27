#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int id; char name[64]; double value; } Record;
static const char *DB="minidb.dat";

static void insert_record(Record r){
    FILE *f=fopen(DB,"ab"); if(!f){perror(DB); exit(1);}
    fwrite(&r,sizeof(r),1,f); fclose(f);
}
static int find_record(int id, Record *out){
    FILE *f=fopen(DB,"rb"); if(!f) return 0; Record r;
    while(fread(&r,sizeof(r),1,f)==1) if(r.id==id){*out=r; fclose(f); return 1;}
    fclose(f); return 0;
}
int main(void){
    char cmd[16]; puts("MiniDB: INSERT <id> <name> <value> | SELECT <id> | QUIT");
    while(scanf("%15s",cmd)==1){
        if(!strcmp(cmd,"INSERT")){ Record r; scanf("%d %63s %lf",&r.id,r.name,&r.value); insert_record(r); puts("OK"); }
        else if(!strcmp(cmd,"SELECT")){ int id; Record r; scanf("%d",&id); if(find_record(id,&r)) printf("%d %s %.2f\n",r.id,r.name,r.value); else puts("NOT FOUND"); }
        else if(!strcmp(cmd,"QUIT")) break;
        else puts("UNKNOWN COMMAND");
    } return 0;
}
