// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define STDERR 2
#define NUMITER 2


void * thrfunc(void * arg)
{
	int i; 
	for (i = 1; i <= NUMITER; i++) {
		printf("%d\n", *(int*)arg );
	}
	return NULL;
}


int main(){
	pthread_t ta, tb;
	
	int a = 1; 
	pthread_create(&ta, NULL, thrfunc, &a);	//the value of a is changed before the thread is executed 
	a = 2; 
	pthread_create(&tb, NULL, thrfunc, &a);


	pthread_join(ta, NULL);
	pthread_join(tb, NULL); 
	return 0;
}
