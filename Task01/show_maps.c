#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
    printf("PID: %ld\n", (long)getpid());
    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp) { perror("fopen /proc/self/maps"); return 1; }
    char line[512];
    puts("Process memory mappings:");
    while (fgets(line, sizeof line, fp)) fputs(line, stdout);
    fclose(fp);
    return 0;
}
