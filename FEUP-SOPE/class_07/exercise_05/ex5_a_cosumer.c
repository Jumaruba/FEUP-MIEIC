#include <pthread.h> 
#include <fcntl.h> 
#include <semaphore.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <sys/mman.h> 
#include <unistd.h> 
char SHM_NAME[] = "/shm"; 
char SEM_FULL[] = "/sem_full"; 
char SEM_EMPTY[] = "/sem_empty"; 

#define MAX_ITEMS 	10

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
//this is the consumer 
int main(){
	//first I wanna open the semaphores initialized in the producer 
	sem_t *full = (sem_t*)malloc(sizeof(sem_t)); 
	sem_t *empty = (sem_t*)malloc(sizeof(sem_t)); 
	
	//waits the semaphores to open 
	while((full = sem_open(SEM_FULL, O_RDWR)) == SEM_FAILED) {} 
	while((empty = sem_open(SEM_EMPTY, O_RDWR)) == SEM_FAILED) {} 
	
	//now that we have oppened, we open the shared memory 
	int shmid = shm_open(SHM_NAME, O_RDWR, 0660); 
	
	//allocating memory 
	ftruncate(shmid, sizeof(int)*MAX_ITEMS); 

	//associating this shared memory to mapped virtual memory 
	char * shm = (char*) mmap(0, sizeof(int)*MAX_ITEMS, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0); 
	//read the values 
	int counter = 0; 		//get the position in the shared memory 
	while(counter != 12){
		
		sem_wait(empty); //the full must have something in there 
		pthread_mutex_lock(&mut); 
		//get the value in the memory 
		int number = *(int *)(shm + sizeof(int)*(counter%MAX_ITEMS)); 
		printf("value %d\n", number); 
		counter ++; 

		pthread_mutex_unlock(&mut); 
		sem_post(full); 

	}
	
	sem_close(full); 
	sem_close(empty); 

	sem_unlink(SEM_FULL);
	sem_unlink(SEM_EMPTY); 

	munmap(shm, sizeof(int)*MAX_ITEMS); 
	shm_unlink(SHM_NAME); 
	return 0; 
} 
