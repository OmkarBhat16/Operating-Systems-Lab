#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main(int strlen, char *strings[]){

	if(strlen == 1){
		printf("No cmd arguments\n");
		return 0;
	}
	int status;
	if(fork() == 0){
		for (int i = 1; i < strlen ; i++) {
        int min = i;
	        for (int j = i + 1; j < strlen; j++) {
	            if (strcmp(strings[min], strings[j]) > 0) {
	                min = j;
	            }
	        }
	        // Swap strings[i] and strings[min]
	        if (min != i) {
	            char *temp = strings[i];
	            strings[i] = strings[min];
	            strings[min] = temp;
	        }
    	}

		printf("Sorted string is : \n");
		for(int i = 1 ; i < strlen ; i++){
			printf("%s ",strings[i]);
		}			
		printf("\n");
	} else {
		int retval = wait(&status);
		printf("%d",retval);
		printf("\n");
		printf("Unsorted string is : \n");
		for(int i = 1 ; i < strlen ; i++){
			printf("%s ",strings[i]);
		}			
		printf("\n");
	}

	
	return 0;
}