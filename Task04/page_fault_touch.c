#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int main(int argc,char **argv) {
    unsigned long mb=256;
    if(argc>1) mb=strtoul(argv[1],NULL,10);
    if(mb==0||mb>8192){fprintf(stderr,"Usage: %s [MB 1..8192]\n",argv[0]);return 2;}
    long ps=sysconf(_SC_PAGESIZE); if(ps<=0)return 1;
    size_t bytes=(size_t)mb*1024U*1024U, pages=(bytes+(size_t)ps-1)/(size_t)ps;
    volatile char *p=malloc(bytes); if(!p){perror("malloc");return 1;}
    for(size_t i=0;i<pages;i++)p[i*(size_t)ps]=1;
    printf("Touched %zu pages (%lu MB) using page size %ld bytes.\n",pages,mb,ps);
    free((void*)p);return 0;
}
