#include <stdlib.h>
#include <stdio.h>

void hello_1();
void hello_2(); 

int main(){
	printf("Main done!\n"); 
	//abort();		//if there is an abort the atexit will not be executed
	atexit(hello_2);
	atexit(hello_2);	//the same function can be subscribed multiple times
	atexit(hello_1); 
	return 0;
}

void hello_1(){
	printf("Executing exit handler 1\n");
	exit(0);		//it doesn't matter havign exit right now, because the program is already finished
}

void hello_2(){
	printf("Executing exit handler 2\n");
	exit(0);
}
