#include <unistd.h> 
#include <stdio.h>
#include <sys/wait.h>

int main(){
	int status; 
	pid_t pid = fork(); 
	if (pid > 0){	//father
		waitpid(pid, &status, WUNTRACED);  
		printf(" world\n"); 
		printf("%d", status); 
	}else{
		printf("Hello"); //son 
	}
}