#include <stdio.h>
#include <stdlib.h>
#include "forky.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_processes> <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_processes = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (num_processes < 1 || num_processes > 256) {
        fprintf(stderr, "Error: Number of processes must be between 1 and 256.\n");
        exit(EXIT_FAILURE);
    }

    if (pattern == 1) {
        process_pattern1(num_processes);
    } else if (pattern == 2) {
        process_pattern2(num_processes);
    } else {
        fprintf(stderr, "Error: Invalid pattern number. Use 1 or 2.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
