#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

#define SIZE    100

int main(int argc, char *argv[]) {

    char *token[SIZE];
    char input[SIZE] = "";
    int i;
    pid_t pid;

    int status;
    while(strcmp(input, "quit") != 0){
        i = 0;

        printf("minish > ");
        scanf("%[^\n]s", input);
        getchar();
        if (strcmp("quit", input) == 0) exit(0);
        token[0] = strtok(input, " ");

        while(token[i] != NULL) {
            i++;
            token[i] = strtok(NULL, " ");
        }
        if ((pid = fork())> 0) waitpid(pid, &status, WUNTRACED);

        else{
            if (i == 1){
                execlp(token[0], token[0], NULL);
            }
            else if(strcmp(token[1], "-o") == 0 && i == 3){
                int desc = open(token[2], O_APPEND | O_CREAT | O_WRONLY);
                int saved_output = dup(STDOUT_FILENO);
                dup2(desc, STDOUT_FILENO);
                execlp(token[0], token[0], NULL);
                dup2(STDOUT_FILENO, saved_output);
                close(desc);
            }else{
                printf("Incorrect format\n");
                exit(0);
            }


        }
    }

    exit(0);
}