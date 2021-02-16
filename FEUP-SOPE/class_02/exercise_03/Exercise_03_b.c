//FOLHA 2 - p2b.c
//FILE COPY
//USAGE: copy source destination

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{	
	char buffer[BUFFER_SIZE];
	int nr;
	struct stat buf; 
  	if (argc != 3){
		perror("Format <program> <file1> <file2>\n"); 
		exit(1);
	}
	
	int desc = open(argv[1], O_RDONLY); 
	fstat(desc, &buf);
       	long int size = buf.st_size;	
	nr = read(desc, &buffer,size);
	//before writing on the screen we change the descriptors
	int desc_2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL,0644 ); 
	dup2(desc_2, STDOUT_FILENO);
	write(STDOUT_FILENO, &buffer, size);	//writing on the screen
	close(desc);
	close(desc_2);
	exit(0);
}

