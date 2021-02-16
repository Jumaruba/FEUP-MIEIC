#include <stdlib.h>
#include <stdio.h>

void hello_1();
void hello_2(); 

int main(){
	printf("Main done!\n"); 
	atexit(hello_2);
	atexit(hello_1); 
	return 0;
}

void hello_1(){
	printf("Executing exit handler 1\n");
}

void hello_2(){
	printf("Executing exit handler 2\n");
}
