#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	pid_t retval = fork();
	if( retval == -1){
		printf("Forking failed \n");
		exit(-1);
	} else if (retval == 0){
		printf("I am child process with pid %d \n", retval);
	} else if (retval > 0){
		printf("I am parent process with pid %d \n", retval);
	}
	return 0;
}