#include <stdlib.h>
#include <stdio.h> 
#include <sys/mman.h> 
#include <pthread.h> 
#include <fcntl.h> 
#include <semaphore.h>
sem_t* sem; 
int global = 0; 


void * printNumber(void * v){
	printf("im the process %d\n", *(int*)v); 
	sem_wait(sem); 
	
	int k = *(int *) v; 
	global ++; 
	printf("global: %d: process: %d\n", global,k); 

	sem_post(sem); 
	pthread_exit(0); 
} 
int main(){
	//creating pthreads 
	pthread_t threads[3]; 
	void * args[3]; 

	//craeting signal 

	sem = (sem_t*) malloc(sizeof(sem_t)) ; 
	sem = sem_open("/sem", O_CREAT| O_RDWR, 0777, 1); 
	
	if (sem == SEM_FAILED){
		perror("failed opening semaphore"); 
		exit(1); 

	}
	if (sem_unlink("/sem") != 0){
		printf("semaphore not unliked\n"); 
       		exit(1); 		
	}
	for (int i = 0; i < 3; i++){
		args[i] = malloc(sizeof(int)); 
		*(int*)args[i] = i; 
		pthread_create(&threads[i], NULL, &printNumber,args[i]); 
		pthread_join(threads[i], NULL); 
	}

	sem_close(sem);

} 
