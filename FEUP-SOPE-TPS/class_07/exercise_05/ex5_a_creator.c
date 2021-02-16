#include <stdlib.h> 
#include <stdio.h> 
#include <semaphore.h> 
#include <pthread.h> 
#include <sys/mman.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <fcntl.h> 

char SHM_NAME[] = "/shm"; 
char SEM_FULL[] = "/sem_full"; 
char SEM_EMPTY[] = "/sem_empty"; 

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

#define MAX_ITEMS 10 
#define ERROR(message) 		error(message, __FILE__, __LINE__) 

static inline void error(char * message, char* file, int line){
		printf("%s:%d %s\n", file, line, message); 
	   exit(1); 
} 


//this is the problem for the productor and consumer 
//this is the code for the producer
int main(){

		//creating the shared memory 
		int shmid = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0660); 

		//allocating memory for the memory 
		ftruncate(shmid, sizeof(int)*MAX_ITEMS); 
		
		//associating this shared memory to mapped virtual memory 
		char * shm = (char*) mmap(0, sizeof(int)*MAX_ITEMS, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0); 
		//creating the 2 necessary semaphores to solve the problem 
		sem_t* full = sem_open(SEM_FULL, O_CREAT | O_RDWR, 0660, MAX_ITEMS); 
		sem_t* empty = sem_open (SEM_EMPTY, O_CREAT | O_RDWR, 0660, 0);

		if (full == SEM_FAILED) ERROR("sem failed"); 
		if (empty == SEM_FAILED) ERROR("sem failed for empty"); 
		

		
		int actual_pos = 0; 
		while(actual_pos < 12){		//just gonna make 12 iterations 
			sem_wait(full); 			//can start producing 
			pthread_mutex_lock(&mut); 

			*(shm + sizeof(int)*(actual_pos%MAX_ITEMS)) = actual_pos;	
		   	printf("i've produced the number %d\n", actual_pos); 	
			actual_pos++;

			pthread_mutex_unlock(&mut); 
			sem_post(empty); 

		} 
		
		sem_close(full); 
		sem_close(empty); 

		sem_unlink(SEM_FULL); 
		sem_unlink(SEM_EMPTY); 
		if(munmap(shm, sizeof(int)*MAX_ITEMS) < 0) ERROR("error mumap"); 
		if (shm_unlink(SHM_NAME) < 0) ERROR ("shm_unlink"); 
}





