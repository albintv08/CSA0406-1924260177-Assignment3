#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s RAID_LEVEL drive_count\n", argv[0]);
        fprintf(stderr, "RAID_LEVEL: 0, 1, 5, 6, or 10\n");
        return 2;
    }
    char *end = NULL;
    long n = strtol(argv[2], &end, 10);
    if (*end != '\0' || n < 2 || n > 64) {
        fprintf(stderr, "Drive count must be between 2 and 64\n");
        return 2;
    }
    double drive_gb = 1000.0;
    double usable = 0.0;
    if (strcmp(argv[1], "0") == 0) usable = n * drive_gb;
    else if (strcmp(argv[1], "1") == 0 && n == 2) usable = drive_gb;
    else if (strcmp(argv[1], "5") == 0 && n >= 3) usable = (n - 1) * drive_gb;
    else if (strcmp(argv[1], "6") == 0 && n >= 4) usable = (n - 2) * drive_gb;
    else if (strcmp(argv[1], "10") == 0 && n >= 4 && n % 2 == 0) usable = (n / 2) * drive_gb;
    else {
        fprintf(stderr, "Unsupported drive count for RAID %s\n", argv[1]);
        return 2;
    }
    printf("RAID %s with %ld x %.0f GB drives\n", argv[1], n, drive_gb);
    printf("Nominal usable capacity: %.0f GB\n", usable);
    puts("Assumes equal-size drives; excludes filesystem and metadata overhead.");
    return 0;
}
