#include "forky.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void process_pattern1(int num_processes) {
  // Fork all processes before waiting
  for (int ix= 0; ix< num_processes; ix++) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork failed");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Child process
      printf("Pattern 1 - Child %d created (PID: %d)\n", ix+ 1, getpid());
      exit(EXIT_SUCCESS); // Child exits
    }
  }
  // Parent waits for all children
  for (int ix= 0; ix< num_processes; ix++) {
    wait(NULL);
  }
}

void process_pattern2(int num_processes) {
  for (int ix= 0; ix< num_processes; ix++) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork failed");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      // Child process
      printf("Pattern 2 - Child %d created (PID: %d, Parent PID: %d)\n", ix+ 1,
             getpid(), getppid());
      if (ix== num_processes - 1) {
        exit(EXIT_SUCCESS);
      }
    } else {
      wait(NULL);
      // Parent exits immediately after waiting
      exit(EXIT_SUCCESS);
    }
  }
}