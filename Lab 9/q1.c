#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
  int size, ptr;
  int processes[100];
} Holes;

typedef struct {
  int mem, allocated, hole;
} Processes;

// Global variable to track if we can proceed
volatile sig_atomic_t proceed = 0;

// Signal handler
void signal_handler(int signum) { proceed = 1; }

void firstFit(Holes holes[], int n, Processes processes[], int m) {
  printf("\nFirst Fit Algorithm (PID: %d):\n", getpid());
  for (int i = 0; i < m; i++) {
    processes[i].allocated = 0;
    int size = processes[i].mem;
    int allocated = 0;

    for (int j = 0; j < n; j++) {
      if (holes[j].size >= size) {
        holes[j].size -= size;
        holes[j].processes[holes[j].ptr++] = i;
        processes[i].allocated = 1;
        processes[i].hole = j;
        printf("Process %d allocated to hole %d\n", i, j);
        allocated = 1;
        break;
      }
    }
    if (!allocated) {
      printf("Process %d could not be allocated\n", i);
    }
  }
  printf("First Fit completed\n\n");
}

void bestFit(Holes holes[], int n, Processes processes[], int m) {
  printf("\nBest Fit Algorithm (PID: %d):\n", getpid());
  for (int i = 0; i < m; i++) {
    processes[i].allocated = 0;
    int size = processes[i].mem;
    int bestIdx = -1;
    int bestFit = __INT_MAX__;

    for (int j = 0; j < n; j++) {
      if (holes[j].size >= size) {
        if (holes[j].size - size < bestFit) {
          bestFit = holes[j].size - size;
          bestIdx = j;
        }
      }
    }

    if (bestIdx != -1) {
      holes[bestIdx].size -= size;
      holes[bestIdx].processes[holes[bestIdx].ptr++] = i;
      processes[i].allocated = 1;
      processes[i].hole = bestIdx;
      printf("Process %d allocated to hole %d\n", i, bestIdx);
    } else {
      printf("Process %d could not be allocated\n", i);
    }
  }
  printf("Best Fit completed\n\n");
}

void worstFit(Holes holes[], int n, Processes processes[], int m) {
  printf("\nWorst Fit Algorithm (PID: %d):\n", getpid());
  for (int i = 0; i < m; i++) {
    processes[i].allocated = 0;
    int size = processes[i].mem;
    int worstIdx = -1;
    int worstFit = -1;

    for (int j = 0; j < n; j++) {
      if (holes[j].size >= size) {
        if (holes[j].size - size > worstFit) {
          worstFit = holes[j].size - size;
          worstIdx = j;
        }
      }
    }

    if (worstIdx != -1) {
      holes[worstIdx].size -= size;
      holes[worstIdx].processes[holes[worstIdx].ptr++] = i;
      processes[i].allocated = 1;
      processes[i].hole = worstIdx;
      printf("Process %d allocated to hole %d\n", i, worstIdx);
    } else {
      printf("Process %d could not be allocated\n", i);
    }
  }
  printf("Worst Fit completed\n\n");
}

int main() {
  int m, n;
  printf("Enter number of holes and processes: (n, m) ");
  scanf("%d %d", &n, &m);

  // Allocate memory for arrays
  Holes *holes = malloc(n * sizeof(Holes));
  Processes *processes = malloc(m * sizeof(Processes));

  // Initialize holes
  for (int i = 0; i < n; i++) {
    printf("Enter size for hole %d: ", i);
    scanf("%d", &holes[i].size);
    holes[i].ptr = 0;
  }

  // Initialize processes
  for (int i = 0; i < m; i++) {
    printf("Enter required memory for process %d: ", i);
    scanf("%d", &processes[i].mem);
    processes[i].allocated = 0;
  }

  // Set up signal handler
  signal(SIGUSR1, signal_handler);

  pid_t pid1, pid2;
  pid_t parent_pid = getpid();

  pid1 = fork();
  if (pid1 == 0) {
    // First child - First Fit
    // Wait for signal from parent
    while (!proceed) {
      pause();
    }
    firstFit(holes, n, processes, m);
    kill(parent_pid, SIGUSR1); // Signal parent
    free(holes);
    free(processes);
    exit(0);
  } else {
    pid2 = fork();
    if (pid2 == 0) {
      // Second child - Best Fit
      // Wait for signal from parent
      while (!proceed) {
        pause();
      }
      bestFit(holes, n, processes, m);
      kill(parent_pid, SIGUSR1); // Signal parent
      free(holes);
      free(processes);
      exit(0);
    } else {
      // Parent process
      printf("\nStarting sequential execution of algorithms...\n");

      // Run First Fit
      proceed = 0;
      kill(pid1, SIGUSR1); // Signal first child to start
      while (!proceed) {
        pause();
      }

      // Run Best Fit
      proceed = 0;
      kill(pid2, SIGUSR1); // Signal second child to start
      while (!proceed) {
        pause();
      }

      // Run Worst Fit
      worstFit(holes, n, processes, m);

      // Wait for children to complete
      waitpid(pid1, NULL, 0);
      waitpid(pid2, NULL, 0);

      printf("All algorithms completed\n");
    }
  }

  free(holes);
  free(processes);
  return 0;
}

// Enter number of holes and processes: (n, m) 4 5
// Enter size for hole 0: 100
// Enter size for hole 1: 200
// Enter size for hole 2: 500
// Enter size for hole 3: 50
// Enter required memory for process 0: 101
// Enter required memory for process 1: 40
// Enter required memory for process 2: 230
// Enter required memory for process 3: 250
// Enter required memory for process 4: 10
