#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int cmp(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

int main(int strlen, char *strings[]) {
  if (strlen == 1) {
    printf("No cmd arguments\n");
    return 0;
  }
  int status;
  if (fork() == 0) {
    qsort(strings + 1, strlen - 1, sizeof(char *), cmp);
    printf("Sorted string is : \n");
    for (int i = 1; i < strlen; i++) {
      printf("%s ", strings[i]);
    }
    printf("\n");
  } else {
    int retval = wait(&status);
    printf("%d", retval);
    printf("\n");
    printf("Unsorted string is : \n");
    for (int i = 1; i < strlen; i++) {
      printf("%s ", strings[i]);
    }
    printf("\n");
  }

  return 0;
}
