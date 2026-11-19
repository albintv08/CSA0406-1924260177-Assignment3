# Q6 – Disk Management and RAID

Discuss low-level initialization, partitioning, logical formatting, boot blocks, bad-block handling and swap placement. Never run destructive disk commands on your host drive; use a disposable virtual disk or simulator.

For N equal drives of capacity D:
- RAID 0: ND usable, no redundancy.
- Two-drive RAID 1: D usable, tolerates one drive failure.
- RAID 5: (N-1)D usable, tolerates one drive failure.
- RAID 6: (N-2)D usable, tolerates two drive failures.
- RAID 10: (N/2)D usable for even N, mirrored pairs striped.

These are nominal capacities before metadata overhead. RAID is not backup. If independent drive failure probability is p, RAID 0 survival is (1-p)^N; RAID 1 with two drives survives unless both fail, 1-p². Discuss correlated failures and rebuild risk when evaluating RAID 5/6.
