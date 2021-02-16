#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define STDERR 2
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; 

int n = 100; 


void *thrfunc(void *arg)
{
    int total = 0; 
    void * v = malloc(sizeof(int)); 
    while (1){
        pthread_mutex_lock(&mut); 
        if ( n == 0){
            *(int*) v = total; 
            pthread_mutex_unlock(&mut);
            pthread_exit(v); 
        }
        write(STDERR, arg, 1); 
        n--; 
        total++; 
        pthread_mutex_unlock(&mut); 
    }
    
    pthread_exit(v); 
}
int main()
{
    pthread_t ta, tb;
    void * v1 = malloc(sizeof(int));
    void * v2 = malloc(sizeof(int));
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, &v1);
    pthread_join(tb, &v2);
    printf("\nvalue of thread1 %d\n", *(int*) v1); 
    printf("value of thread2 %d\n", *(int*) v2);
    return 0;
}
