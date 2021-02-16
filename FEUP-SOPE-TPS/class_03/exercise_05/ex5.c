#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h> 


int main(){
	int pid1, pid; 
	int status1; 
	if ((pid1 = fork()) > 0 ){
		waitpid(pid1, &status1, WUNTRACED); 
		printf("friends!\n"); 
	}else{
		if ((pid = fork()) > 0){
			int status; 
			printf("my ");
			waitpid(pid, &status, WUNTRACED); 
		}else{
			printf("Hello ");
		}
	}

} 
