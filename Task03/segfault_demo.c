#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
int main(void) {
    long page=sysconf(_SC_PAGESIZE);
    if(page<=0) return 1;
    char *p=mmap(NULL,(size_t)page,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
    if(p==MAP_FAILED){perror("mmap");return 1;}
    p[0]='A';
    if(mprotect(p,(size_t)page,PROT_READ)!=0){perror("mprotect");munmap(p,(size_t)page);return 1;}
    puts("Next write targets a read-only page; the OS should deliver SIGSEGV.");
    fflush(stdout);
    p[0]='B';
    munmap(p,(size_t)page);
    return 0;
}
