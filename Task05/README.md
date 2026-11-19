# Q5 – Page-Replacement Techniques

## Programs
- `page_replacement.c`: completed assignment LRU TODO; includes FIFO, LRU, Optimal and Clock; uses the assignment's 20-reference string and Belady string.
- `benchmark.c`: generates 100,000 deterministic references and measures FIFO, LRU and Optimal for 3–10 frames.

## Build and run
```bash
gcc -std=c11 -Wall -Wextra page_replacement.c -o page_replacement
./page_replacement
gcc -O2 -std=c11 -Wall -Wextra benchmark.c -o benchmark
./benchmark
```

The required expected output is FIFO/LRU/Optimal = 15/12/9 faults for 3 frames and 10/8/8 for 4 frames; the Belady string gives FIFO 9 faults with 3 frames and 10 with 4. Confirm your run. Clock is a second-chance approximation to LRU using one reference bit per frame.

Generate additional locality-heavy and random workloads, plot faults against 3–10 frames, and hand-check one string. Discuss Optimal's future knowledge, LRU's stack property, Clock's lower bookkeeping cost, and Big-O time/space. Add measured results rather than fabricated values.
