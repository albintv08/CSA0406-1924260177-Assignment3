# Q3 – Segmentation

## Programs
- `segments.c`: translates the eight (segment, offset) test cases and rejects offsets outside limits.
- `segment_experiments.c`: reproducible demonstration of holes left after loading/removing 20 variable-sized segments.
- `segfault_demo.c`: changes a mapped page to read-only and deliberately writes to it to demonstrate SIGSEGV.
- `show_process_maps.sh`: displays a process's Linux memory mappings.

## Build and run
```bash
gcc -std=c11 -Wall -Wextra segments.c -o segments && ./segments
gcc -std=c11 -Wall -Wextra segment_experiments.c -o segment_experiments && ./segment_experiments
gcc -std=c11 -Wall -Wextra segfault_demo.c -o segfault_demo
./segfault_demo
sh show_process_maps.sh
```
The segmentation-fault demo is expected to terminate abnormally; run it separately.

## Analysis
Explain code/data/stack segments, base-and-limit protection, sharing of read-only code and external fragmentation. Compare pure paging, pure segmentation and segmented paging. Discuss why modern general-purpose operating systems rely mainly on paging.
