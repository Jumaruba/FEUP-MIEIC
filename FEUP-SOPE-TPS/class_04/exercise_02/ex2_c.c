//
// Created by maruba on 12/03/20.
//

//
// Created by maruba on 11/03/20.
//

// PROGRAMA p02a.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo)
{
    printf("Entering SIGINT handler ...\n");
    sleep(10);
    printf("Exiting SIGINT handler ...\n");
}

int main(void)
{
    //this program when executing the handler, if it receives another signal during the execution (one or more),
    // it will just compute the same signal one time.
    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGINT,&action,NULL) < 0)
    {
        fprintf(stderr,"Unable to install SIGINT handler\n");
        exit(1);
    }

    if (sigaction(SIGTERM, &action, NULL) < 0){
        fprintf(stderr, "Error with SIGTERM\n");
        exit(2);
    }

    printf("Try me with CTRL-C ...\n");
    while(1) pause();
    //pause will only stop when the non-ignored signal has a handler
    exit(0);
}
//now, to really kill the process read the specification of the process with ps u
//then use the command kill -s SIGKILL pid