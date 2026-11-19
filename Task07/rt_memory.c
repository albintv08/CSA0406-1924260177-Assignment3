#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#define BUFFER_MB 8
#define ITERATIONS 100000
static long long ns(struct timespec t){return (long long)t.tv_sec*1000000000LL+t.tv_nsec;}
int main(void){
 size_t bytes=BUFFER_MB*1024U*1024U;
 volatile unsigned char *p=malloc(bytes);if(!p){perror("malloc");return 1;}
 if(mlockall(MCL_CURRENT|MCL_FUTURE)==0)puts("mlockall: success");
 else printf("mlockall unavailable: %s\n",strerror(errno));
 long ps=sysconf(_SC_PAGESIZE);if(ps<=0){perror("sysconf");free((void*)p);return 1;}
 for(size_t i=0;i<bytes;i+=(size_t)ps)p[i]=0;
 long long worst=0;unsigned long sum=0;
 for(int i=0;i<ITERATIONS;i++){
  struct timespec a,b;size_t k=((size_t)i*4096U)%bytes;
  clock_gettime(CLOCK_MONOTONIC,&a);p[k]++;sum+=p[k];clock_gettime(CLOCK_MONOTONIC,&b);
  long long d=ns(b)-ns(a);if(d>worst)worst=d;
 }
 printf("Iterations: %d\nWorst observed loop body: %lld ns\nChecksum: %lu\n",ITERATIONS,worst,sum);
 puts("Observed maximum is not a formal worst-case execution-time guarantee.");
 (void)munlockall();free((void*)p);return 0;
}
