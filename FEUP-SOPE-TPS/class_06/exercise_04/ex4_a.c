#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h>
#define NUM_THREADS 10

void* routine(void * number){
    printf("Im the process %d\n", *((int*)number));
    sleep(1);
    return number;   
}
int main(){
    pthread_t threads[NUM_THREADS];         //init the number of threads
    int* args[NUM_THREADS];                 //arguments
    for (int i = 1; i< NUM_THREADS+1; i++){
        void* param; 
        args[i-1] = (int*)malloc(sizeof(int)); 
        *args[i-1] = i; 
        pthread_create(&threads[i-1], NULL, routine, (void*)args[i-1]); 
        pthread_join(threads[i-1], &param); 
        int number = *(int*)(param); 
        printf("%d\n", number); 
        free(param); 
    }

    pthread_exit(NULL); 
}