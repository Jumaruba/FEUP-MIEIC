#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int i = 0;
	if (argc != 3){
		perror("struct: <program-name> <ceil> <target>");
		exit(1);	
	}
	int ceil = atoi(argv[1]); 
	int target = atoi(argv[2]);
       	int actual = -1; 
	while (actual != target){
		actual = rand()%ceil;
	       	printf("iter: %d || actual: %d\n", i, actual);	
		srand(i++);
		 
	}	
	return 0; 
}
