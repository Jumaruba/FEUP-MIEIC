#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 


typedef struct number{
    int n1; 
    int n2; 
} Number; 

void * sum(void * v){
    printf("Calculating sum...\n"); 
    Number * n = (Number *)v; 
    int * sum = (int*)malloc(sizeof(int));
    *sum =  n->n1 + n->n2; 
    printf("Sum calculated!\n");
    return (void*)sum; 
}

void * subtraction(void *v){
    printf("Calculating subtraction\n"); 
    Number * n = (Number *)v; 
    int * sub = (int*)malloc(sizeof(int));
    * sub = n->n1 - n->n2; 
    printf("Subtraction calculated\n"); 
    return (void*)sub; 
}

void * multiplication(void *v){
    //..
}

void * division(void *v){
    //..
}

void * mainThread(void * v){

}
int main(){
    
    void* arr[4]; 
    Number * n = (Number *)malloc(sizeof(Number)); 
    pthread_t t1, t2,t3,t4;
    int *n1 = (int *)malloc(sizeof(int)); 
    int *n2 = (int *)malloc(sizeof(int)); 
    scanf("%d %d", n1, n2); 
    n -> n1 = *n1; 
    n -> n2 = *n2; 

    pthread_create(&t1, NULL, sum, (void *) n); 
    arr[0] = malloc(sizeof(int)); 
    pthread_join(t1, &(arr[0])); 
    printf("%d\n", *(int*)arr[0]); 

    pthread_create(&t2, NULL, subtraction, (void*) n); 
    arr[1] = malloc(sizeof(int)); 
    pthread_join(t2, &arr[1]); 
    printf("%d\n", *(int*)arr[1]); 


    free(n1);
    free(n2); 
    
}