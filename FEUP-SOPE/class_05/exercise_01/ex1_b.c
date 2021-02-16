#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define READ    0
#define WRITE   1

typedef struct numbers{
    int n1;
    int n2;
} numbers;

int main(){
    pid_t pid;
    int pd[2];

    if (pipe(pd) < 0){
        fprintf(stderr, "Error shile creating pipe\n");
        exit(1);
    }

    if ((pid = fork())<0){
        fprintf(stderr, "Error while forking \n");
        exit(1);
    }
    if (pid > 0){
        numbers n;
        fscanf(stdin,"%d %d", &n.n1, &n.n2);
        close(pd[READ]);
        write(pd[WRITE], &n, sizeof(numbers));
    }

    else{

        numbers n;
        close(pd[WRITE]);
        read(pd[READ], &n, sizeof(numbers));

        fprintf(stdout, "soma: %d\n", n.n1+n.n2);
        fprintf(stdout, "sub: %d\n", n.n1-n.n2);
        fprintf(stdout, "mult: %d\n", n.n1*n.n2);
        if (!n.n2) fprintf(stdout, "division not possible\n");
        else fprintf(stdout, "div: %d\n", n.n1/n.n2);

    }
}