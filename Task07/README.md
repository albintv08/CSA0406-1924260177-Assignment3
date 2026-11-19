# Q7 – Memory Plan for a Real-Time Edge Device

## Design
For the 2 GB device, reserve and lock the control-loop working set, prefault/touch pages during initialization, and avoid allocation, blocking I/O and page faults in the critical loop. Bound ML and logging buffers, apply admission control, and measure worst observed latency under representative load. A measured maximum is not a formal hard-real-time guarantee.

## Build and run
```bash
gcc -O2 -Wall -Wextra rt_memory.c -o rt_memory
ulimit -l
./rt_memory
```

The demo attempts `mlockall()`; this may fail under the process memory-lock limit. Capture the actual result and latency on the target. Discuss the effect of adding a fourth 500 MB task and compare Linux with locked/prefaulted memory against an RTOS using static allocation and bounded scheduling.
