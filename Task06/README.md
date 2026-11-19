# Q6 – Disk Management

## Programs and scripts
- `raid_calculator.c`: calculates nominal capacity for six 4 TB drives and approximate RAID 1/5 data-loss probabilities under an explicit independent-drive failure assumption.
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

## Evaluation
Compare RAID 0, 1, 5 and 10 for capacity, speed and reliability; select a configuration appropriate for hospital records. Explain low-level/logical formatting, partitioning, boot block, bad-block remapping and swap placement. RAID is not backup. The calculator assumes independent failures; correlated failures and rebuild risk make real arrays more complex. For RAID 6, six 4 TB drives provide 16 TB nominal capacity and tolerate any two drive failures.
