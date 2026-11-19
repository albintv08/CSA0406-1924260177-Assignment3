# Q3 – Segmentation

Build and run:
```bash
gcc -std=c11 -Wall -Wextra segments.c -o segments
./segments
```

A segment-table entry stores base and limit. Reject an address when offset >= limit; otherwise physical address = base + offset. Discuss variable-sized segment external fragmentation, logical program regions, protection and segmentation with paging. Capture all output. For process mappings, inspect `/proc/<pid>/maps` while the process is alive.
