#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int size, ptr;
  int processes[100];
} Holes;

typedef struct {
  int mem, allocated, hole;
} Processes;

// Helper function to create copies of arrays
void copyArrays(Holes dest_holes[], const Holes src_holes[], int n,
                Processes dest_proc[], const Processes src_proc[], int m) {
  memcpy(dest_holes, src_holes, n * sizeof(Holes));
  memcpy(dest_proc, src_proc, m * sizeof(Processes));
}

void firstFit(Holes holes[], int n, Processes processes[], int m) {
  printf("\nFirst Fit Algorithm:\n");
  for (int i = 0; i < m; i++) {
    processes[i].allocated = 0; // Reset allocation status
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
}

void bestFit(Holes holes[], int n, Processes processes[], int m) {
  printf("\nBest Fit Algorithm:\n");
  for (int i = 0; i < m; i++) {
    processes[i].allocated = 0; // Reset allocation status
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
}

void worstFit(Holes holes[], int n, Processes processes[], int m) {
  printf("\nWorst Fit Algorithm:\n");
  for (int i = 0; i < m; i++) {
    processes[i].allocated = 0; // Reset allocation status
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
}

int main() {
  int m, n;
  printf("Enter number of holes and processes: (n, m) ");
  scanf("%d %d", &n, &m);

  // Allocate memory for original arrays
  Holes *original_holes = malloc(n * sizeof(Holes));
  Processes *original_processes = malloc(m * sizeof(Processes));

  // Allocate memory for working copies
  Holes *working_holes = malloc(n * sizeof(Holes));
  Processes *working_processes = malloc(m * sizeof(Processes));

  // Initialize holes
  for (int i = 0; i < n; i++) {
    printf("Enter size for hole %d: ", i);
    scanf("%d", &original_holes[i].size);
    original_holes[i].ptr = 0;
  }

  // Initialize processes
  for (int i = 0; i < m; i++) {
    printf("Enter required memory for process %d: ", i);
    scanf("%d", &original_processes[i].mem);
    original_processes[i].allocated = 0;
  }

  // First Fit
  copyArrays(working_holes, original_holes, n, working_processes,
             original_processes, m);
  firstFit(working_holes, n, working_processes, m);

  // Best Fit
  copyArrays(working_holes, original_holes, n, working_processes,
             original_processes, m);
  bestFit(working_holes, n, working_processes, m);

  // Worst Fit
  copyArrays(working_holes, original_holes, n, working_processes,
             original_processes, m);
  worstFit(working_holes, n, working_processes, m);

  // Free allocated memory
  free(original_holes);
  free(original_processes);
  free(working_holes);
  free(working_processes);

  return 0;
}
