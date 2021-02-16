#include <stdlib.h>     //exit
#include <sys/wait.h>   //wait
#include <sys/types.h>
#include <unistd.h>     //fork
#include <stdio.h>      //printf

int main(int argc, char* argv[]){
    int status;
    pid_t pid = fork();
    if (pid > 0 ){
        waitpid(pid, &status, WUNTRACED);   //father waits for the child.
        printf("This is the termination code of the child: %d\n", WEXITSTATUS(status));
    }
    if (pid == 0){
        execl("/bin/ls", "ls", "-laR", argv[1], NULL);
        printf("Error execve\n");
        exit(1);
    }

    exit(0);
}