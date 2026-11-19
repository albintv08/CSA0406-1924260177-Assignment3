#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MB (1024*1024)
static void report(const char *s){
 char path[128];snprintf(path,sizeof path,"/proc/%ld/status",(long)getpid());
 FILE*f=fopen(path,"r");if(!f){perror("status");return;}
 char line[256];printf("%s\n",s);
 while(fgets(line,sizeof line,f))if(!strncmp(line,"VmRSS:",6)||!strncmp(line,"VmSize:",7))fputs(line,stdout);
 fclose(f);fflush(stdout);
}
int main(void){
 size_t bytes=64*MB;volatile char*p=malloc(bytes);if(!p){perror("malloc");return 1;}
 for(size_t i=0;i<bytes;i+=4096)p[i]=1;
 report("Parent before fork");
 pid_t pid=fork();if(pid<0){perror("fork");free((void*)p);return 1;}
 if(pid==0){for(size_t i=0;i<bytes;i+=4096)p[i]=2;report("Child after writing pages (copy-on-write)");_exit(0);}
 waitpid(pid,NULL,0);report("Parent after child exit");free((void*)p);return 0;
}
