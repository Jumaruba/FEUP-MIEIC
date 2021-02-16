// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#define BUF_LENGTH 256

extern int errno; 

int main(void)
{

	//to print the error associated to errno, we need to import the errno. 
 	FILE *src, *dst;
 	char buf[BUF_LENGTH];
 	if ( ( src = fopen( "infile.txt", "r" ) ) == NULL )
 	{
		int errnum = errno; 
		printf("Erro %d", errnum); 
		//perror("The following error occurred"); 
 		exit(1); 
	}
	if ( ( dst = fopen( "outfile.txt", "w" ) ) == NULL )
 	{
		perror("The following error occurred"); 
 		exit(2);
 	}
 	while( ( fgets( buf, BUF_LENGTH, src ) ) == NULL )
 	{
 		fputs( buf, dst );
 	}
 	fclose( src );
 	fclose( dst );
 	exit(0); // zero é geralmente indicativo de "sucesso"
} 
