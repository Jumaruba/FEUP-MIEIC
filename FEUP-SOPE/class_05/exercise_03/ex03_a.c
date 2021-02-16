#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <limits.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>



 #define MAX_NAME       7000
 #define READ_PIPE      0 
 #define WRITE_PIPE     1 

 int compare(const void * ca, const void *cb){      //pass to char ** and allocate 
     return strcmp(*(char **)ca,*(char**) cb); 
 }

int main(int argc, char* argv[]){
    int p[2]; 
    char c[MAX_NAME]; 
    char *n = (char *)calloc(MAX_NAME, sizeof(char)); 
    pid_t pid; 

    if (pipe(p) < 0){
        perror("pipe"); 
        exit(1); 
    } 

    pid = fork(); 
    
    if (pid > 0){   //father
        close(p[READ_PIPE]);
        dup2(p[WRITE_PIPE], STDOUT_FILENO); 
        if (argc != 2) return 1;
        int fd = open(argv[1], O_RDONLY);

        if ((read(fd, &c, MAX_NAME)) <0){
            perror("Error reading file"); 
            exit(1); 
        }
        n = strtok(c, "\n"); 
        while (n != NULL){
            printf("%s\n", n); 
            n = strtok(NULL, "\n"); 
        }
        
         

    }
    else if (pid == 0){
        close(p[WRITE_PIPE]); 
        dup2(p[READ_PIPE], STDIN_FILENO);                                   //if you do dup2, you must use fgets

        char *name = (char*)calloc(MAX_NAME, sizeof(char));                 //always alloc a size
        char *names[MAX_NAME];                                              //many names

        int counter = 0; 
        while(fgets(name, MAX_NAME, stdin)){
            names[counter] = (char*)calloc(strlen(name), sizeof(char));                 //each position o names is not allocated, we must do it
            strcpy(names[counter], name);                                               //so that we can make strcpy
            counter ++; 
        }
        
        close(p[READ_PIPE]);
        qsort(names, counter, sizeof(char*), compare);                      //very important
        for (int i = 0; i< counter; i++){
            printf("%s", names[i]);
        }

    }

    
}