#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char* argv[]){
	int i = 0, j;
	int times = atoi(argv[1]); 
	for (j = 0; j < times; j ++){
		printf("Hello");
		for (i = 2; i < argc; ++i) printf(" %s", argv[i]); 
		printf("\n");
}
	return 0; 
} 


