# Operating Systems – Assignment 3 (CO3)

**Student:** Albin T V  
**Register number:** 1924260177  
**Repository:** https://github.com/albintv08/CSA0406-1924260177-Assignment3

This repository contains source code and execution instructions for all seven questions in Assignment 3.

## Task folders
| Question | Topic | Folder |
|---|---|---|
| Q1 | Linking, loading and address binding | [Task01](Task01/) |
| Q2 | Paging | [Task02](Task02/) |
| Q3 | Segmentation | [Task03](Task03/) |
| Q4 | Virtual memory and demand paging | [Task04](Task04/) |
| Q5 | Page-replacement techniques | [Task05](Task05/) |
| Q6 | Disk management and RAID | [Task06](Task06/) |
| Q7 | Memory-management plan | [Task07](Task07/) |

## Environment details – complete after checking your system
- Compiler: GCC (record exact version using `gcc --version`)
- Linux distribution/version: record using `cat /etc/os-release`
- Kernel: record using `uname -a`

## General requirements
Linux, GCC and standard system utilities. Some tasks use `/usr/bin/time`, `ldd`, `lsblk`, `fdisk` and `/proc`.

## Execution
Each task README lists its source files, exact compile commands and run instructions. Run every program yourself, compare completed TODO programs with the expected output in the assignment sheet, and save genuine command outputs/screenshots under the task's `outputs/` folder.

## Evidence and submission notes
The assignment requires at least one progressive commit per task, C source files, scripts, command outputs and screenshots. Update this README with your actual GCC version and Linux distribution. Record actual startup time, RSS, page-fault counts, memory timings, disk read speeds and latency values from your own system; do not submit invented measurements. Include the GitHub link on the report cover page and share the repository with faculty as instructed.

Some experiments intentionally trigger a segmentation fault or require a disposable VM. Run them separately and never use destructive disk commands on your host system.
