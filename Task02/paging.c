#include <stdio.h>
#define PAGE_SIZE 1024
#define PAGES 8
static const int page_table[PAGES] = {5, 2, -1, 7, 0, -1, 3, -1};
int main(void) {
    const unsigned logical[] = {0, 1500, 3100, 6200, 9000, 2049};
    for (size_t i = 0; i < sizeof logical / sizeof logical[0]; ++i) {
        unsigned a = logical[i], p = a / PAGE_SIZE, d = a % PAGE_SIZE;
        printf("%u -> page %u offset %u: ", a, p, d);
        if (p >= PAGES) puts("invalid address");
        else if (page_table[p] < 0) puts("page fault (not present)");
        else printf("physical address %u\n", (unsigned)page_table[p] * PAGE_SIZE + d);
    }
    return 0;
}
