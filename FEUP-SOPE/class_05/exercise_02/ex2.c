#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define READ    0
#define WRITE   1


int isInteger(float n){
    if (n == (int)n) return 1;
    return 0;
}

void sendInfo(int *pd2, float *f){
    int integer = isInteger(*f);
    write(pd2[WRITE], &integer, sizeof(int));
    if (integer == 0)
        write(pd2[WRITE], f, sizeof(float));
    else {
        int buf = (int)*f;
        write(pd2[WRITE], &buf, sizeof(int));
    }
}

int main(){
    float n1,n2;
    pid_t pid;
    int pd[2], pd2[2];

    if (pipe(pd) < 0){
        fprintf(stderr, "Error shile creating pipe\n");
        exit(1);
    }
    if (pipe(pd2) < 0){
        fprintf(stderr, "Error while creating pipe2\n");
        exit(1);
    }

    if ((pid = fork())<0){
        fprintf(stderr, "Error while forking \n");
        exit(1);
    }
    if (pid > 0){
        int format, auxInt;
        float auxFloat;
        fscanf(stdin,"%f %f", &n1, &n2);
        close(pd[READ]);
        close(pd2[WRITE]);
        write(pd[WRITE], &n1, sizeof(float));
        write(pd[WRITE], &n2, sizeof(float));

        for (int i = 0; i < 4; i++){
            read(pd2[READ], &format, sizeof(int));
            if (format == 1){
                read(pd2[READ], &auxInt, sizeof(int));
                printf("The number is: %d\n", auxInt );
            }
            else if (format == 0){
                read(pd2[READ], &auxFloat, sizeof(int));
                printf("The number is %.2f", auxFloat);
            }
            else{
                printf("Invalid operation");
            }

        }
    }

    else{
        int invalid = 2;
        float f[4];
        close(pd[WRITE]);
        close(pd2[READ]);
        read(pd[READ], &n1, sizeof(float));
        read(pd[READ], &n2, sizeof(float));

        f[0] = n1 + n2;
        f[1] = n1- n2;
        f[2] = n1 * n2;
        for (int i = 0; i< 3; i++) sendInfo(pd2, &f[i]);
        if (!n2) write(pd2[WRITE], &invalid, sizeof(int));
        else{
            f[3] = n1/n2;
            sendInfo(pd2, &f[3]);
        }

    }
}