#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <unistd.h> 	

int main(int argc, char* argv[]){
	struct tms t; 
	clock_t start = times(&t); 
	long ticks = sysconf(_SC_CLK_TCK); 
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
	clock_t end = times(&t);
       		
	printf("Real time: %4.2f\n", (double)(end-start)/ticks); 	
	printf("PC user time: %4.2f\n", (double)t.tms_utime); 
	printf("PC system time: %4.2f\n", (double)t.tms_stime);
	return 0; 
}
