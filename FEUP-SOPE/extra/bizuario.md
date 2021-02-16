# Resume for operational systems in C

## Threads


\#include <pthread.h> 

- `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void* (*start_routine) (void *), void* arg); `  
 

- `pthread_exit(void * param);`  

If main function call pthread\_exit(NULL), even if the main is finished the threads will still be running.   

- `pthread_join(pthread_t thread, void **retval);`

Pthread join waits for the *thread* to finish and the *retval* is the value returned by the thread

### Example of usage 

```
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
	       
```

## Sleep 

```
#include <unistd.h>

unsigned int sleep(unsigned int seconds); 

```


## Exec 

```
#include <unistd.h>

extern char **environ;

int execl(const char *pathname, const char *arg, ...
                       /* (char  *) NULL */);
int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
int execle(const char *pathname, const char *arg, ...
                       /*, (char *) NULL, char *const envp[] */);
int execv(const char *pathname, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);
```
