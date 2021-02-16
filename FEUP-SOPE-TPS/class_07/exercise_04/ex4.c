// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <semaphore.h>
#include <sys/mman.h> 
#include <wait.h> 
#include <string.h> 


#define MAXELEMS 100000 // nr. max de posicoes
#define MAXTHREADS 100
#define min(a, b) (a) < (b) ? (a) : (b)
int npos;
     
// variaveis partilhadas
sem_t *sem, *s; 
char * shm;             //usable address 
int shmd;
char SHM_NAME[] = "/shm"; 
char SEM_NAME[] = "/sem"; 


typedef struct{
    int pos; 
    int val; 
    int buffer[MAXTHREADS]; 
}Info; 


//deve-se por números grandes, a fim de permitir que seja a vez de outras threads 
void fill(int k )
{
    printf("im alive %d\n", k); 
    while (1){
        sem_wait(sem);                  //decrements and waits until semaphore value is greater than zero 
 
 	//loads the struct 
        if (((Info*)shm)->pos >= npos)
        {
            sem_post(sem);              //increments and proceed    
            sem_close(sem);
            return;
        }
 	//writting back to the memory 
        ((Info*)shm)->pos++;
        ((Info*)shm)->val++;
        ((Info*)shm)->buffer[((Info*)shm)->pos] = ((Info*)shm)->val; 
        printf("f1.pos %d, process %d\n", ((Info*)shm)->pos, k); 


        sem_post(sem); 
	}   
}

int main(int argc, char *argv[])
{
    int k, nthr, count[MAXTHREADS];
    pid_t pid; 
    int status = 0; 
    // array para contagens

    if (argc != 3)
    {
        printf("Usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
        return 1;
    }

    npos = min(atoi(argv[1]), MAXELEMS);
    nthr = min(atoi(argv[2]), MAXTHREADS);
    
    //creating shared memory 
    shmd = shm_open(SHM_NAME, O_CREAT| O_RDWR, 0660); 

    //allocating space for the memory 
    ftruncate(shmd, sizeof(Info)); 

    //attach this region to a virtual memory. The shm is the value of the started area for the address mapped. We usually let the first parammeter be 0
    //to let the system choose what is the address. 
    shm = (char*)malloc(sizeof(char)*255);
    shm = (char*)mmap(0, sizeof(Info), PROT_READ|PROT_WRITE, MAP_SHARED, shmd, 0); 

    //create semaphore
    sem = sem_open(SEM_NAME, O_CREAT|O_RDWR, 0660, 1); 

    if (sem ==SEM_FAILED){
        printf("%s:%d\n", __FILE__, __LINE__);
    }


    //writing this struct into memory 
    ((Info *)shm)->pos = 0 ;
    ((Info*)shm)-> val = 0; 

    for (k = 0; k < nthr; k++)
    {
        count[k] = 0;
        if (fork() == 0){    //child process calls function 
            fill(k);
            return 0; 
        }
    }

    //waits all processes to end 
    while((pid = wait(&status)) > 0){} 

    //checking for errors 
    for (int i = 0; i < nthr; i++){
        if (i != ((Info*)shm)->buffer[i]){
            printf("error, how beautiful!! pos %d: buffer %d\n", i, ((Info*)shm)->buffer[i]);

        }
    }

    // espera thread 'verify'*/
    sem_close(sem); 
    sem_unlink(SEM_NAME); 
    
    if (munmap(shm, sizeof(Info)) < 0){
	   perror("Not possible to unmap"); 
	   exit(1); 
    }
    if (shm_unlink(SHM_NAME) < 0){
	    perror("Not possible to unlink shm"); 
	    exit(1); 
    } 
    return 0;
}