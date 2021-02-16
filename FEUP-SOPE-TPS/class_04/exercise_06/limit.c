//
// Created by maruba on 13/03/20.
//

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t pid;
void handler(int signo){
    if (kill(pid, SIGKILL) != 0) fprintf(stderr, "Fail to kill process %d\n", pid);
    printf("Process %d killed\n", pid);
}
int main(void){
    int status;
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);

    if (sigaction(SIGALRM, &act, NULL) < 0){
        fprintf(stderr, "Fail to subscribe handler\n");
        exit(2);
    }
    if ((pid = fork()) > 0) {
        alarm(30);
        waitpid(pid, &status, WUNTRACED);
    }
    else if (pid == 0) execl("./prog", "./prog", "I'm alive!", NULL);

    else{
        fprintf(stderr,"Not possible to fork\n");
        exit(1);
    }
    exit(0);
}