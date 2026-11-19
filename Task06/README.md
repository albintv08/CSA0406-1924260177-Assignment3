# Q6 – Disk Management

## Programs and scripts
- `raid_calculator.c`: calculates nominal capacity for six 4 TB drives and RAID 1/5 data-loss probabilities under an explicit independent-drive failure assumption.
- `system_storage_info.sh`: read-only display of partitions and active swap using `lsblk`, `fdisk -l` and `/proc/swaps`.
- `read_speed_test.sh`: times a file read from a specified test disk.

## Build and run
```bash
gcc -std=c11 -Wall -Wextra raid_calculator.c -lm -o raid_calculator
./raid_calculator
sh system_storage_info.sh
sh read_speed_test.sh /path/to/a/large/test-file
```

Never run formatting or partition-changing commands on your system disk. Use read-only inspection and disposable virtual disks only.

## Six-disk RAID comparison
With six equal 4 TB drives: RAID 0 = 24 TB, RAID 1 as a six-way mirror = 4 TB, RAID 5 = 20 TB, and RAID 10 as three mirrored pairs = 12 TB nominal usable capacity. RAID 0 tolerates no disk failure; RAID 1 tolerates up to five; RAID 5 tolerates one; RAID 10 tolerates one failure in each mirror pair (but not every possible two-drive failure combination).

The probability program assumes independent equal per-drive failure probability p=0.02 over the same selected interval. Six-way RAID 1 loses data only if all six drives fail; RAID 5 loses data if two or more fail. Correlated failures and rebuild risk make real arrays more complex. RAID is not backup.

Explain low-level/logical formatting, partitioning, boot block, bad-block remapping and swap placement. Compare swap partition versus swap file and justify a storage configuration for hospital records.
