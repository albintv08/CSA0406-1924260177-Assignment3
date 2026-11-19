#include <stdio.h>
typedef struct { unsigned base, limit; } Segment;
static int translate(const Segment t[], int n, int s, unsigned off, unsigned *pa) {
    if (s < 0 || s >= n || off >= t[s].limit) return 0;
    *pa = t[s].base + off;
    return 1;
}
int main(void) {
    const Segment table[] = {{10000,4000},{20000,3000},{30000,2000}};
    const int seg[] = {0,1,2,1,3,0,2,1};
    const unsigned off[] = {120,2500,1999,3200,10,3999,2000,0};
    for (size_t i=0; i<sizeof seg/sizeof seg[0]; ++i) {
        unsigned pa=0;
        if (translate(table,3,seg[i],off[i],&pa)) printf("(%d,%u) -> %u\n",seg[i],off[i],pa);
        else printf("(%d,%u) -> invalid address / protection fault\n",seg[i],off[i]);
    }
    return 0;
}
