#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

void bubble_sort(int strlen,char* strings[]){
	for (int i = 1; i < strlen ; i++) {
        for (int j = i; j < strlen; j++) {
            if (strcmp(strings[j], strings[j+1]) > 0) {
                char *temp = strings[j];
            	strings[j] = strings[j+1];
            	strings[j+1] = temp;
            }
        }
	}
}

void selection_sort(int strlen,char* strings[]){
	for (int i = 1; i < strlen ; i++) {
        int min = i;
        for (int j = i + 1; j < strlen; j++) {
            if (strcmp(strings[min], strings[j]) > 0) {
                min = j;
            }
        }
        if (min != i) {
            char *temp = strings[i];
            strings[i] = strings[min];
            strings[min] = temp;
        }
	}			
}

int main(){
	if(strlen == 1){
		printf("No cmdline args\n");
		return 0;
	}

	printf("Enter number of inputs strings : \n");
	int n;
	scanf("%d",&n);

	char* strings[n];

	printf("Enter input strings : \n");
	for(int i = 0 ; i < n ; i++){
		scanf("%s",strings[i]);
	}

	printf("given input strings are: \n");
	for(int i = 0 ; i < n ; i++){
		printf("%s ",strings[i]);
	}

	int status1 ; 

	pid_t pid = fork();
	if(pid == -1){
		printf("Forking failed \n");
		return -1;
	} else if( pid == 0){
		bubble_sort(strlen, strings);
	} else {
		if(wait)
		int status2;
	}




	return 0;
}