#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int main(int argc, char* argv[], char* envp[]){
	
	char * env = getenv("USER_NAME"); 
	printf("Say hello %s\n", env); 
	return 0; 
} 
