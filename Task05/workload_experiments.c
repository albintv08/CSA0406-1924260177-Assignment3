
#include <stdio.h>
#include <stdlib.h>

#define N 100000
#define MAXF 10
#define PAGES 64

static unsigned next_random(unsigned *s)
{
    *s ^= *s << 13;
    *s ^= *s >> 17;
    *s ^= *s << 5;
    return *s;
}

static int find_page(const int f[], int n, int p)
{
    for (int i = 0; i < n; i++)
        if (f[i] == p) return i;
    return -1;
}

static int fifo(const int *r, int c)
{
    int f[MAXF], used = 0, head = 0, faults = 0;

    for (int i = 0; i < N; i++) {
        if (find_page(f, used, r[i]) < 0) {
            faults++;
            if (used < c)
                f[used++] = r[i];
            else {
                f[head] = r[i];
                head = (head + 1) % c;
            }
        }
    }
    return faults;
}

static int lru(const int *r, int c)
{
    int f[MAXF], t[MAXF], used = 0, faults = 0;

    for (int i = 0; i < N; i++) {
        int k = find_page(f, used, r[i]);

        if (k >= 0) {
            t[k] = i;
            continue;
        }

        faults++;
        if (used < c)
            k = used++;
        else {
            k = 0;
            for (int j = 1; j < used; j++)
                if (t[j] < t[k]) k = j;
        }

        f[k] = r[i];
        t[k] = i;
    }
    return faults;
}

static int optimal(const int *r, int c)
{
    int *next_at = malloc(N * sizeof(int));
    if (!next_at) return -1;

    int last[PAGES];
    for (int p = 0; p < PAGES; p++) last[p] = N;

    for (int i = N - 1; i >= 0; i--) {
        next_at[i] = last[r[i]];
        last[r[i]] = i;
    }

    int next_pos[PAGES];
    for (int p = 0; p < PAGES; p++) next_pos[p] = last[p];

    int f[MAXF], used = 0, faults = 0;

    for (int i = 0; i < N; i++) {
        if (find_page(f, used, r[i]) < 0) {
            faults++;

            if (used < c)
                f[used++] = r[i];
            else {
                int victim = 0, farthest = -1;

                for (int j = 0; j < used; j++) {
                    if (next_pos[f[j]] > farthest) {
                        farthest = next_pos[f[j]];
                        victim = j;
                    }
                }
                f[victim] = r[i];
            }
        }
        next_pos[r[i]] = next_at[i];
    }

    free(next_at);
    return faults;
}

static void generate_random(int *r, unsigned seed)
{
    for (int i = 0; i < N; i++)
        r[i] = next_random(&seed) % PAGES;
}

static void generate_locality(int *r, unsigned seed)
{
    for (int i = 0; i < N; i++) {
        unsigned x = next_random(&seed);

        if (x % 100 < 90)
            r[i] = (x >> 8) % 8;
        else
            r[i] = (x >> 8) % PAGES;
    }
}

static void run_experiment(const char *name, const int *r)
{
    for (int c = 3; c <= 10; c++) {
        printf("%s,%d,%d,%d,%d\n",
               name, c, fifo(r, c), lru(r, c), optimal(r, c));
    }
}

int main(void)
{
    int *r = malloc(N * sizeof(int));
    if (!r) return 1;

    printf("Workload,Frames,FIFO,LRU,Optimal\n");

    generate_random(r, 1234567U);
    run_experiment("Random", r);

    generate_locality(r, 7654321U);
    run_experiment("Locality", r);

    free(r);
    return 0;
}
