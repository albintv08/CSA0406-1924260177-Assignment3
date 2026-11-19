#!/bin/sh
set -eu
echo "Block devices and partitions:"
lsblk -o NAME,SIZE,TYPE,FSTYPE,MOUNTPOINTS
echo
echo "Partition table information (read-only):"
if command -v fdisk >/dev/null 2>&1; then sudo fdisk -l; else echo "fdisk is not installed"; fi
echo
echo "Active swap:"
cat /proc/swaps
