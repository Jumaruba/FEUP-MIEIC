#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#define SIZE 60
int main(int argc, char * argv[]){
	FILE *fp;
       	char str[SIZE];
	fp = fopen("command.txt", "r"); 
	if (fp == NULL){
		perror("The file does not exist"); 
		exit(1);
	}
	if (fgets(str, SIZE,fp) == NULL){	//stores the string at str
		perror("Error to get the string");
		exit(2);
	}
	char *tokens = strtok(str," "); 
	while (tokens!= NULL){
	       	printf("%s\n", tokens); 
		tokens = strtok(NULL, " "); 	//each subsequence must be called using NULL 
	}
}
