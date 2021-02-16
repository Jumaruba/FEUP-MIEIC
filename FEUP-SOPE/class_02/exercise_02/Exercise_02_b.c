#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_SIZE 256
int main(int argc, char *argv[]){
	char buffer[MAX_SIZE];
	struct stat stat_read;
	if (argc != 3){
		printf("Format: <program> <file_read> <file_write>\n");
		exit(1);
	}
	int desc_read = open("file_read", O_RDONLY); 
	int desc_write = open("file_write", O_WRONLY);
	stat("file_read", &stat_read); 				//to get the size of the file
	read(desc_read, &buffer, stat_read.st_size); 
	write(desc_write, &buffer, stat_read.st_size); 
	close(desc_read);
	close(desc_write);
	exit(0);
}

