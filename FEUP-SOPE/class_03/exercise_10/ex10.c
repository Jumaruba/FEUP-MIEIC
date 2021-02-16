#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[], char *envp[]){
    pid_t pid;
    if (argc >3){
        printf("usage: %s dirname optional\n", argv[0]);
        exit(1);
    }

    pid = fork();
    if (pid>0){ //father work
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
    }
    else if (pid == 0){
        if (argc == 3){
            int desc;
            if ((desc = open( argv[2], O_CREAT | O_TRUNC | O_WRONLY)) < 0){
                printf("impossible to create %s", strerror(errno));
            }
            dup2(desc, STDOUT_FILENO);
        }
        execlp("ls", "ls", "-laR", argv[1], NULL);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}

