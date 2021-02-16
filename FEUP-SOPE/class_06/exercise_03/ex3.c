// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10


void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *)threadnum);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int *thrarg[NUM_THREADS]; 
    int t;
    for (t = 0; t < NUM_THREADS; t++)
    {
        thrarg[t] = (int*)malloc(sizeof(int)); 
        *thrarg[t] = t; 
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, PrintHello, (void *)thrarg[t]);
    }
    exit(0);    //the program gets first to exit and so the threads do not have time to finish 
}
