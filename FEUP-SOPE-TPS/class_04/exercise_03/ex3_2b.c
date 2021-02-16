//
// Created by maruba on 13/03/20.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

int variable = 1;

void handler(int signo) {
    if (signo == SIGUSR1) variable = abs(variable);
    if (signo == SIGUSR2) variable = -abs(variable);
}

int main(void) {
    pid_t pid;
    int counter = 0, status, choice;
    if ((pid = fork()) > 0) {
        srand(time(NULL));
        while (1) {
            sleep(1);
            choice = rand() % 2 + 1 == 0 ? SIGUSR1 : SIGUSR2;            //choose the option
            kill(pid, choice);                                           //send signal to the child
            waitpid(pid, &status, WNOHANG);
            if (WIFEXITED(status)) exit(0);
        }
    } else if (pid == 0) {
        //handle signals
        struct sigaction sig;
        sig.sa_handler = handler;
        sigemptyset(&sig.sa_mask);
        if (sigaction(SIGUSR1, &sig, NULL) < 0) {
            fprintf(stderr, "Not possible to handle SIGUSR1\n");
            exit(2);
        }
        if (sigaction(SIGUSR2, &sig, NULL) < 0) {
            fprintf(stderr, "Not possible to handle SIGUSR2\n");
            exit(3);
        }

        //child loop
        for (int i = 0; i < 10; i++) {
            sleep(1);
            counter += variable;
            printf("Value %d\n", counter);
        }
        exit(0);
    } else {   //err
        fprintf(stderr, "Not possible to fork\n");
        exit(1);
    }

}