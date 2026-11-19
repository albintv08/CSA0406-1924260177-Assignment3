# Q4 – Virtual Memory and Demand Paging

Build and run with a safe memory size:
```bash
gcc -O2 -Wall -Wextra touchmem.c -o touchmem
/usr/bin/time -v ./touchmem 128
```

Explain page-fault handling, demand paging, copy-on-write, working sets and thrashing. Record elapsed time, maximum resident set size and minor/major faults from your own run. Results vary by machine and system load. Do not intentionally exhaust RAM on a shared or production system.

Simplified EAT model: EAT = (1-p) × 100 + p × 8,000,000 ns when memory access is 100 ns and the page-fault penalty is 8 ms.
