# Q2 – Paging

## Programs
- `paging.c`: completed assignment TODO 1, matching the supplied logical-address test list.
- `paging_experiments.c`: seeded 100-process internal-fragmentation simulation for 1 KB, 4 KB and 2 MB pages, plus TLB EAT for 80%, 95% and 99% hit ratios.
- `page_table_size.c`: single-level page-table size estimate for 32-bit and 48-bit spaces using 4 KB pages and an explicitly assumed 8-byte PTE.

## Build and run
```bash
gcc -std=c11 -Wall -Wextra paging.c -o paging
./paging
gcc -std=c11 -Wall -Wextra paging_experiments.c -o paging_experiments
./paging_experiments
gcc -std=c11 -Wall -Wextra page_table_size.c -o page_table_size
./page_table_size
getconf PAGESIZE
/usr/bin/time -v ./paging
```

## Concepts
For page size S: page number = logical address / S; offset = logical address % S. Physical address = frame × S + offset when resident. Paging removes external fragmentation but can leave internal fragmentation in the final page. Explain multi-level, hashed and inverted page tables, page permissions and shared read-only pages.

## Evidence
Run the same address test after changing PAGE_SIZE to 2048 and verify by hand. Record host page size and actual fault counts. The random experiment uses a fixed seed for repeatability; state its workload range and assumptions.
