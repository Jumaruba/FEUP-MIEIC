//
// Created by maruba on 12/03/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int variable = 1;

void handler_usr(int signo) {
    if (signo == SIGUSR1){
        printf("Increasing value\n");
        variable = abs(variable);
    }
    else {
        printf("Increasing value\n");
        variable = -abs(variable);
    }
}

int main(void) {
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
    while (1) {
        sleep(1);
        printf("Value %d\n", n);
        n += variable;
    }

    exit(0);

}
