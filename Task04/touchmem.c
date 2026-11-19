#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
static double secs(struct timespec a, struct timespec b) {
    return (double)(b.tv_sec-a.tv_sec) + (double)(b.tv_nsec-a.tv_nsec)/1e9;
}
int main(int argc, char **argv) {
    unsigned long mb=128;
    if (argc>1) {
        char *end=NULL; unsigned long v=strtoul(argv[1],&end,10);
        if (end==argv[1] || *end!='\0' || v==0 || v>4096) {
            fprintf(stderr,"Usage: %s [memory_MB: 1..4096]\n",argv[0]); return 2;
        }
        mb=v;
    }
    long ps=sysconf(_SC_PAGESIZE);
    if (ps<=0) { perror("sysconf"); return 1; }
    size_t bytes=(size_t)mb*1024U*1024U, pages=(bytes+(size_t)ps-1)/(size_t)ps;
    volatile unsigned char *p=malloc(bytes);
    if (!p) { perror("malloc"); return 1; }
    struct timespec a,b;
    clock_gettime(CLOCK_MONOTONIC,&a);
    for (size_t i=0;i<pages;i++) p[i*(size_t)ps]=(unsigned char)i;
    clock_gettime(CLOCK_MONOTONIC,&b);
    printf("Sequential: %.6f s (%zu pages)\n",secs(a,b),pages);
    unsigned int seed=12345;
    clock_gettime(CLOCK_MONOTONIC,&a);
    for (size_t i=0;i<pages;i++) { size_t k=(size_t)rand_r(&seed)%pages; p[k*(size_t)ps]++; }
    clock_gettime(CLOCK_MONOTONIC,&b);
    printf("Random: %.6f s\n",secs(a,b));
    free((void *)p); return 0;
}
