#include <stdio.h>
#include <math.h>

int main(void)
{
    const int drives = 6;
    const double drive_capacity = 4.0;
    const double p = 0.02;

    double raid0 = drives * drive_capacity;
    double raid1 = drive_capacity;
    double raid5 = (drives - 1) * drive_capacity;
    double raid10 = (drives / 2) * drive_capacity;

    double raid1_loss = pow(p, drives);
    double raid5_loss = 1.0 - pow(1.0 - p, drives)
                        - drives * p * pow(1.0 - p, drives - 1);

    printf("SIX-DISK RAID CAPACITY COMPARISON\n");
    printf("--------------------------------\n");
    printf("Number of drives: %d\n", drives);
    printf("Capacity per drive: %.0f TB\n\n", drive_capacity);

    printf("RAID 0  usable capacity: %.0f TB\n", raid0);
    printf("RAID 1  usable capacity: %.0f TB (six-way mirror)\n", raid1);
    printf("RAID 5  usable capacity: %.0f TB\n", raid5);
    printf("RAID 10 usable capacity: %.0f TB\n\n", raid10);

    printf("DISK FAILURE PROBABILITY ANALYSIS\n");
    printf("---------------------------------\n");
    printf("Assumed independent drive failure probability: %.2f%%\n\n",
           p * 100);

    printf("RAID 1 data-loss probability (all six drives fail):\n");
    printf("%.12e (%.12e%%)\n\n", raid1_loss, raid1_loss * 100);

    printf("RAID 5 data-loss probability (two or more drives fail):\n");
    printf("%.12e (%.6f%%)\n", raid5_loss, raid5_loss * 100);

    printf("\nNote: RAID is not a substitute for backup.\n");

    return 0;
}
