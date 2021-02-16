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
  	if (argc != 2){
		perror("Format <program> <file1>\n"); 
		exit(1);
	}
	
	int desc = open(argv[1], O_RDONLY); 
	fstat(desc, &buf);
       	long int size = buf.st_size;	
	nr = read(desc, &buffer,size);
	write(STDOUT_FILENO, &buffer, size);
	close(desc);
	return 0;
}

