# Q4 – Virtual Memory and Demand Paging

## Programs
- `touchmem.c`: touches pages sequentially and randomly.
- `page_fault_touch.c`: allocates and touches a configurable amount of memory for page-fault measurement.
- `cow_demo.c`: forks a process, writes to inherited pages and reports RSS from `/proc/PID/status`.

## Build and run
```bash
gcc -O2 -Wall -Wextra touchmem.c -o touchmem
gcc -O2 -Wall -Wextra page_fault_touch.c -o page_fault_touch
gcc -O2 -Wall -Wextra cow_demo.c -o cow_demo
/usr/bin/time -v ./touchmem 256
/usr/bin/time -v ./page_fault_touch 256
./cow_demo
```
Use a safe memory size and, for controlled pressure, a disposable VM or memory-limited container. Do not exhaust memory on a shared host.

## EAT calculation
With 100 ns memory access and 8 ms fault service, EAT = (1-p)×100 + p×8,000,000 ns. Evaluate p = 1/1,000, 1/100,000 and 1/1,000,000. For a 10% slowdown, solve EAT = 110 ns. Record your actual elapsed time, RSS and minor/major page faults.

Explain demand paging, page-fault handling, COW, working sets, equal/proportional frame allocation and thrashing. Plot page faults against frame count using your own reference-string results.
