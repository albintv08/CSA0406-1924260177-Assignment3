#include <stdio.h>
#include <stdlib.h>
#define SEGMENTS 20
#define ARENA 100000
typedef struct { int start,size,active; } Block;
int main(void) {
    Block b[SEGMENTS]; int cursor=0, used=0, holes=0;
    srand(17);
    for(int i=0;i<SEGMENTS;i++) {
        b[i].start=cursor; b[i].size=500+rand()%3500; b[i].active=1;
        cursor+=b[i].size; used+=b[i].size;
    }
    for(int i=1;i<SEGMENTS;i+=2) { b[i].active=0; used-=b[i].size; holes+=b[i].size; }
    printf("Segments allocated: %d\n",SEGMENTS);
    printf("Active segments: %d\n",SEGMENTS/2);
    printf("Free space in released holes: %d bytes\n",holes);
    printf("Active payload: %d bytes\n",used);
    printf("Largest contiguous free hole is workload-dependent; released holes are not automatically coalesced across active segments.\n");
    printf("Total simulated arena consumed before releases: %d / %d bytes\n",cursor,ARENA);
    return 0;
}
