# Q7 – Memory-Management Plan for a Real-Time Edge Device

## Programs
- `rt_memory.c`: attempts `mlockall()`, prefaults a bounded region and records the worst observed loop-body delay.
- `compare_locking.c`: compares observed loop timing before and after `mlock()`.
- `task_memory_sim.c`: simplified FIFO simulation of control, ML and logging working sets.

## Build and run
```bash
gcc -O2 -std=c11 -Wall -Wextra rt_memory.c -o rt_memory
gcc -O2 -std=c11 -Wall -Wextra compare_locking.c -o compare_locking
gcc -O2 -std=c11 -Wall -Wextra task_memory_sim.c -o task_memory_sim
ulimit -l
./rt_memory
./compare_locking
./task_memory_sim
```

## Design requirements
The real-time control task must have its working set resident and avoid page faults, dynamic allocation and blocking I/O in its critical path. ML and logging can tolerate controlled paging/queuing subject to memory budgets. With 2 GB RAM and a 1.5 GB ML task, reserve bounded memory for control, logging, kernel and safety margin; apply admission control before adding a fourth 500 MB task.

Capture actual timing under representative load. Observed maximum delay is not a certified worst-case execution-time guarantee. Compare Linux with locked/prefaulted memory to an RTOS using static allocation and bounded scheduling, including the trade-off in ML memory and future extensibility.
