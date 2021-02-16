#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
int main(int argc, char * argv[]){
	char buffer[MAX_SIZE]; 
	FILE *fread, *fwrite;
	if (argc != 3){
		perror("<file_name> <source> <destination>");
		exit(1);
	}
	if ((fread = fopen(argv[1], "r")) == NULL){
		perror("The file does not exist");
		exit (3);
	}
	if ((fwrite = fopen(argv[2], "w")) == NULL){
		perror("The file does not exist");
		exit(4);
	}	
	while (fgets(buffer,MAX_SIZE, fread) != NULL){
	       	fputs(buffer, fwrite);
       		
 	}

	fclose(fread);
	fclose(fwrite);
		
	exit(0); 
}
