#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#define MB (1024*1024)
static void report(const char *label) {
    struct rusage r;
    if(getrusage(RUSAGE_SELF,&r)==0)
        printf("%s: max RSS reported by getrusage = %ld KB\n",label,r.ru_maxrss);
}
int main(void) {
    size_t bytes=64*MB;
    volatile char *p=malloc(bytes);
    if(!p){perror("malloc");return 1;}
    for(size_t i=0;i<bytes;i+=4096)p[i]=1;
    report("Parent before fork");
    pid_t pid=fork();
    if(pid<0){perror("fork");free((void*)p);return 1;}
    if(pid==0){
        for(size_t i=0;i<bytes;i+=4096)p[i]=2;
        report("Child after writing copy-on-write pages");
        _exit(0);
    }
    waitpid(pid,NULL,0);
    report("Parent after child exit");
    free((void*)p);
    return 0;
}
