#include <pthread.h>
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h> 

#define THREADS		10 


void * counter(void * param){

	int * m = (int*) param; 
	printf("hello, I'm thread number %d\n", *m);  
	
	pthread_exit(NULL); 
} 
int main(){

	pthread_t arrThread[THREADS]; 
	int* args[THREADS]; 
	for (int i = 0 ; i < THREADS ; i++) {
		args[i] = (int*) malloc(sizeof(int)); 
		*args[i] = i;  
		pthread_create(&arrThread[i], NULL, counter,(void*) args[i]); 
	} 

	//wait for the threads to finish 
	for (int i = 0 ; i < THREADS; i++) 
		pthread_join(arrThread[i], NULL); 

	pthread_exit(NULL); 
		
}
