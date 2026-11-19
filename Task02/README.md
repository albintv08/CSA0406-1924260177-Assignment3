# Q2 – Paging

Build and run:
```bash
gcc -std=c11 -Wall -Wextra paging.c -o paging
./paging
getconf PAGESIZE
/usr/bin/time -v ./paging
```

For page size S: page = logical address / S; offset = logical address % S. Physical address = frame × S + offset when the page is present. With TLB hit ratio h, lookup t and memory time m, assuming one page-table access on a miss: EAT = h(t+m) + (1-h)(t+2m). State assumptions for page-table entry size and address-space size. Capture actual host page size and page-fault counts.
