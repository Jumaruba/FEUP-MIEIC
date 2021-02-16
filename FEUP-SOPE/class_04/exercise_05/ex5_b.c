//
// Created by maruba on 13/03/20.
//

// PROGRAMA p04a.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int status;
void handler(int signo){
    wait(&status);
    printf("The child finished with the exit %d\n", WEXITSTATUS(status));
}

int main(void) {
    //subscribing the handler
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGCHLD, &act, NULL)){
        fprintf(stderr, "Error sigaction\n");
        exit(1);
    }
    pid_t pid;
    int i, n;
    for (i = 1; i <= 10; i++) {
        pid = fork();
        if (pid == 0) {
            printf("CHILD no. %d (PID=%d) working ... \n", i, getpid());
            sleep(15); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n", i, getpid());
            exit(0);
        }
    }

    printf("PARENT: working hard (task no. %d) ...\n", i);
    n = 20;
    while ((n = sleep(n)) != 0);


    exit(0);
}
