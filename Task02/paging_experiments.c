#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define PROCESS_COUNT 100
static unsigned long long random_size(unsigned long long max) {
    return 1ULL + (unsigned long long)rand() % max;
}
int main(void) {
    const unsigned long long sizes[] = {1024ULL, 4096ULL, 2ULL*1024*1024};
    const char *labels[] = {"1 KB","4 KB","2 MB"};
    srand(42);
    unsigned long long proc_sizes[PROCESS_COUNT];
    for (int i=0;i<PROCESS_COUNT;i++) proc_sizes[i]=random_size(32ULL*1024*1024);
    for (int p=0;p<3;p++) {
        unsigned long long total=0;
        for (int i=0;i<PROCESS_COUNT;i++) {
            unsigned long long rem=proc_sizes[i]%sizes[p];
            if(rem) total+=sizes[p]-rem;
        }
        printf("%s pages: total internal fragmentation = %llu bytes (%.2f KB)\n",
               labels[p],total,(double)total/1024.0);
    }
    const double memory_ns=100.0, tlb_ns=10.0;
    const double hit[]={0.80,0.95,0.99};
    puts("EAT with TLB (one memory access on hit, two on miss):");
    for(int i=0;i<3;i++) {
        double eat=hit[i]*(tlb_ns+memory_ns)+(1.0-hit[i])*(tlb_ns+2.0*memory_ns);
        printf("hit %.0f%%: %.2f ns\n",hit[i]*100.0,eat);
    }
    puts("Without TLB (one page-table access + one data access): 200 ns");
    return 0;
}
