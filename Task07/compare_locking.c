#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#define ITER 200000
#define BYTES (4*1024*1024)
static long long ns(struct timespec t){return (long long)t.tv_sec*1000000000LL+t.tv_nsec;}
static void run(const char *label,volatile unsigned char *p){
 long long worst=0;unsigned long sum=0;
 for(int i=0;i<ITER;i++){struct timespec a,b;size_t k=((size_t)i*4096U)%BYTES;
  clock_gettime(CLOCK_MONOTONIC,&a);p[k]++;sum+=p[k];clock_gettime(CLOCK_MONOTONIC,&b);
  long long d=ns(b)-ns(a);if(d>worst)worst=d;}
 printf("%s: worst observed loop-body delay=%lld ns checksum=%lu\n",label,worst,sum);
}
int main(void){
 volatile unsigned char *p=malloc(BYTES);if(!p){perror("malloc");return 1;}
 long ps=sysconf(_SC_PAGESIZE);if(ps<=0)return 1;
 for(size_t i=0;i<BYTES;i+=(size_t)ps)p[i]=0;
 run("Before mlock",p);
 if(mlock((const void *)p,BYTES)==0){run("After mlock",p);munlock((const void *)p,BYTES);}
 else printf("mlock failed: %s (check ulimit -l and permissions)\n",strerror(errno));
 free((void*)p);
 puts("These are observed maxima under this test, not certified WCET bounds.");
 return 0;
}
