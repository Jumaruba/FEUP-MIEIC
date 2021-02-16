#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <termios.h>
#define MAX_SIZE 256
int main(){
	int nr, desc;
	char ch; 
	struct termios oldterm, term; 
	char buffer[MAX_SIZE]; 
	if ((desc = open("students", O_WRONLY)) == 0){
		perror("error");
		exit(1);
	}	
	write(STDOUT_FILENO,"Write students names and grades: ",32); 
	dup2(desc, STDOUT_FILENO);
	int i = 0;
	while ( i < MAX_SIZE && read(STDOUT_FILENO, &ch, 1) && ch != '\n'){
		write(STDOUT_FILENO, &ch, 1); 
		printf("%c",ch);
		if (sizeof(ch) != 0) i++;
	}


	close(desc);
	exit(0);

}
