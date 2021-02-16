//
// Created by maruba on 12/03/20.
//

//
// Created by maruba on 12/03/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int variable = 1;

void handler_usr(int signo) {
    if (signo == SIGUSR1) {
        printf("Increasing value\n");
        variable = abs(variable);
    } else {
        printf("Decreasing value\n");
        variable = -abs(variable);
    }
}

//dont use waitpid for handling signals, because it will terminate
int main(void) {
    pid_t pid;
    int counter = 0;
    struct sigaction sig;
    int n = 0;
    sigemptyset(&sig.sa_mask);
    sig.sa_handler = handler_usr;
    if (sigaction(SIGUSR1, &sig, NULL) < 0) {
        //never forget the difference between fprintf and printf
        fprintf(stderr, "Not possible to handle SIGUSR1\n");
        exit(1);
    }
    if (sigaction(SIGUSR2, &sig, NULL) < 0) {
        fprintf(stderr, "Not possible to handle SIGUSR2\n");
        exit(2);
    }

    if ((pid = fork()) > 0) {
        int status, signo, val;
        //generate random number [1,2]
        srand(time(NULL));
        for (int i = 0; i< 50; i++) {
            signo = rand() % 2 + 1 == 1 ? SIGUSR1 : SIGUSR2;
            kill(pid, signo);
            sleep(1);
        }
    } else {
        for (int i = 0; i < 50; i++) {
            sleep(1);
            printf("Value %d\n", n);
            n += variable;
            counter++;
        }
        exit(0);
    }
    exit(0);

}