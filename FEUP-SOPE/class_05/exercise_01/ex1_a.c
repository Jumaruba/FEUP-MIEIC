#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define READ    0
#define WRITE   1

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
        int n1, n2;
        fscanf(stdin,"%d %d", &n1, &n2);
        close(pd[READ]);
        write(pd[WRITE], &n1, sizeof(int));
        write(pd[WRITE], &n2, sizeof(int));
    }

    else{
        int n1, n2;
        close(pd[WRITE]);
        read(pd[READ], &n1, sizeof(int));
        read(pd[READ], &n2, sizeof(int));

        fprintf(stdout, "soma: %d\n", n1+n2);
        fprintf(stdout, "sub: %d\n", n1-n2);
        fprintf(stdout, "mult: %d\n", n1*n2);
        if (!n2) fprintf(stdout, "division not possible\n");
        else fprintf(stdout, "div: %d\n", n1/n2);

    }
}