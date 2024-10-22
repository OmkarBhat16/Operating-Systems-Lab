#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int size;
  char process[100];
  int allocated;
} Hole;

typedef struct {
  int mem;
  int hole;
  int allocated;
} Process;

void firstFit(Hole holes[], int n, Process processes[], int m) {
  for (int i = 0; i < m; i++) {
    if (processes[i].allocated == 0) {
      int size = processes[i].mem;
      for (int j = 0; j < n; j++) {
        if (holes[j].size >= size) {
          char num[4]; // Assuming process ID won't exceed 999
          sprintf(num, "%d", i);
          strcat(holes[j].process, num);
          strcat(holes[j].process, " ");
          holes[j].size -= size;
          processes[i].hole = j;
          processes[i].allocated = 1;
        } else {
          // Handle insufficient space in the string buffer
          printf("Not enough space to add process %d to hole %d\n", i, j);
        }

        break;
      }
    }
  }

  printf("PROCESS ALLOCATION :: \n");
  for (int i = 0; i < m; i++) {
    printf("Process %d : \nAllocated Status: %s\n", i,
           processes[i].allocated == 1 ? "True" : "False");
    if (processes[i].allocated == 1)
      printf("Allocated Hole : %d\n", processes[i].hole);
  }

  printf("\nHOLE ALLOCATION :: \n");
  for (int i = 0; i < n; i++) {
    printf("Hole %d : \nLeftover space: %d\nAllocated Processes: %s\n", i,
           holes[i].size, holes[i].process);
  }
}

int main() {

  int n;
  printf("Enter number of holes :\n");
  scanf("%d", &n);

  Hole holes[n];

  for (int i = 0; i < n; i++) {
    printf("Enter size for hole %d : ", i);
    scanf("%d", &holes[i].size);
  }

  // for(int i = 0; i < n ; i++){
  // 	printf("Size of hole %d : %d",i,holes[i].size);
  // }

  int m;
  printf("Enter number of processes :\n");
  scanf("%d", &m);

  Process processes[m];

  for (int i = 0; i < m; i++) {
    printf("Enter size of process %d : ", i);
    scanf("%d", &processes[i].mem);
  }

  firstFit(holes, n, processes, m);

  return 0;
}
