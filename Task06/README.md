# Q6 – Disk Management and RAID

Discuss low-level initialization, partitioning, logical formatting, boot blocks, bad-block handling and swap placement. Never run destructive disk commands on your host drive; use a disposable virtual disk or simulator.

Build the capacity calculator:
```bash
gcc -std=c11 -Wall -Wextra raid_capacity.c -o raid_capacity
./raid_capacity 5 4
./raid_capacity 6 4
```

For N equal drives of capacity D: RAID 0 = ND (no redundancy); two-drive RAID 1 = D; RAID 5 = (N-1)D; RAID 6 = (N-2)D; RAID 10 = (N/2)D for even N. RAID 5 tolerates one drive failure, RAID 6 two, and RAID 10 depends on which drives fail. These are nominal capacities before metadata overhead. RAID is not backup.

The calculator assumes 1,000 GB drives. If independent drive failure probability is p, RAID 0 survival is (1-p)^N; two-drive RAID 1 survives unless both fail, 1-p². Discuss correlated failures and rebuild risk.
