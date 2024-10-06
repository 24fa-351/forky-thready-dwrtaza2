#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "forky.h"

void process_pattern1(int num_processes) {
    // Fork all processes before waiting
    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Pattern 1 - Child %d created (PID: %d)\n", i + 1, getpid());
            exit(EXIT_SUCCESS);  // Child exits
        }
    }
    // Parent waits for all children
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }
}

void process_pattern2(int num_processes) {
    // Fork one, and each child forks the next
    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Pattern 2 - Child %d created (PID: %d)\n", i + 1, getpid());
            if (i == num_processes - 1) {
                exit(EXIT_SUCCESS);  // Last child exits
            }
            continue;  // Child continues to fork the next one
        } else {
            wait(NULL);  // Parent waits for child to finish before forking next
            break;  // Parent exits the loop
        }
    }
}
