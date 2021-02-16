#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int main(int argc, char* argv[], char* envp[]){

	int i = 0; 
	while (strstr(envp[i], "USER=") == NULL){
		i++; 
	}
	printf("%s\n", envp[i]); 
} 
