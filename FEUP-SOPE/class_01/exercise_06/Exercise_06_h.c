// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#define BUF_LENGTH 256

extern int errno; 

int main(int argc, char* argv[])
{

	//to print the error associated to errno, we need to import the errno. 
 	FILE *src, *dst;
 	char buf[BUF_LENGTH];
	char *infile, *outfile; 
	if (argc >= 3){
		infile = argv[1]; 
		outfile = argv[2]; 
	}
	else {
		printf("usage: nome_do_executavel file1 file2\n"); 
	}

 	if ( ( src = fopen(infile, "r" ) ) == NULL )
 	{
		int errnum = errno; 
		printf("Erro %d", errnum); 
		//perror("The following error occurred"); 
 		exit(1); 
	}
	if ( ( dst = fopen( outfile, "w" ) ) == NULL )
 	{
		perror("The following error occurred"); 
 		exit(2);
 	}
 	while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL )
 	{
 		fputs( buf, dst );
 	}
 	fclose( src );
 	fclose( dst );
 	exit(0); // zero é geralmente indicativo de "sucesso"
} 
