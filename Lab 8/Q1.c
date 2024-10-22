#include <stdio.h>

int isSafe(int avail[], int need[][3], int alloc[][3], int n) {
  int work[3], finish[5] = {0}, safeSeq[5], count = 0;
  for (int i = 0; i < 3; i++)
    work[i] = avail[i];

  while (count < n) {
    int found = 0;
    for (int i = 0; i < n; i++) {
      if (!finish[i]) {
        int j;
        for (j = 0; j < 3; j++)
          if (need[i][j] > work[j])
            break;

        if (j == 3) {
          for (j = 0; j < 3; j++)
            work[j] += alloc[i][j];
          safeSeq[count++] = i;
          finish[i] = 1;
          found = 1;
        }
      }
    }
    if (!found)
      return 0;
  }
  printf("Safe sequence: ");
  for (int i = 0; i < n; i++)
    printf("%d ", safeSeq[i]);
  printf("\n");
  return 1;
}

int main() {
  int avail[3] = {3, 3, 2};
  int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
  int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
  int need[5][3];

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 3; j++)
      need[i][j] = max[i][j] - alloc[i][j];

  while (1) {
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < 5; i++)
      printf("P%d: %d %d %d\n", i, need[i][0], need[i][1], need[i][2]);
    printf("Available: %d %d %d\n", avail[0], avail[1], avail[2]);

    if (!isSafe(avail, need, alloc, 5)) {
      printf("Unsafe state!\n");
      break;
    }

    printf("\nRequest? (1:Yes 0:No): ");
    int choice;
    scanf("%d", &choice);
    if (!choice)
      break;

    int pid, req[3];
    printf("Process ID (0-4): ");
    scanf("%d", &pid);
    printf("Request A B C: ");
    scanf("%d %d %d", &req[0], &req[1], &req[2]);

    int valid = 1;
    for (int i = 0; i < 3; i++) {
      if (req[i] > need[pid][i] || req[i] > avail[i]) {
        valid = 0;
        break;
      }
    }

    if (valid) {
      for (int i = 0; i < 3; i++) {
        avail[i] -= req[i];
        alloc[pid][i] += req[i];
        need[pid][i] -= req[i];
      }
      printf("Request granted!\n");
    } else {
      printf("Request denied!\n");
    }
  }
  return 0;
}
