// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define STDERR 2
#define NUMITER 1000

int var = 1000; 

void * thrfunc(void * arg)
{
	int i;
    void *total;        
    int value = 0;  
	fprintf(stderr, "Starting thread %s\n", (char *) arg);
	for (i = 1; i <= NUMITER; i++) {
        write(STDERR,arg,1);
        var --; 
        value++; 
    }

    //memorize
    total = malloc(sizeof(int)); 
    *(int *) total = value; 
	return total;
}

int main(){
	pthread_t ta, tb;
    void * r; 
	pthread_create(&ta, NULL, thrfunc, "1");
	pthread_create(&tb, NULL, thrfunc, "2");
	pthread_join(ta, &r);
    printf("\n ta: %d", *(int *)r); 
	pthread_join(tb, &r); 
    printf("\n tb: %d", *(int *)r); 

    free(r);
	return 0;
}
