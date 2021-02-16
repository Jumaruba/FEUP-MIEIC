//
// Created by maruba on 13/03/20.
//

//
// Created by maruba on 13/03/20.
//

// PROGRAMA p04a.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    //subscribing the handler
    struct sigaction act;
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGCHLD, &act, NULL)){
        fprintf(stderr, "Error sigaction\n");
        exit(1);
    }
    pid_t pid;
    int i, n, status;
    for (i = 1; i <= 3; i++) {
        pid = fork();
        if (pid == 0) {
            //1: 7s, 2: 14s, 3: 21s
            printf("CHILD no. %d (PID=%d) working ... \n", i, getpid());
            sleep(i * 7); // child working ...
            printf("CHILD no. %d (PID=%d) exiting ... \n", i, getpid());
            exit(0);
        }
    }
    for (i = 1; i <= 4; i++) {
        printf("PARENT: working hard (task no. %d) ...\n", i);
        n = 20;
        while ((n = sleep(n)) != 0);

    }
    exit(0);
}
