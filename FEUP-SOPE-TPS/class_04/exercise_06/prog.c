//Escreva um programa (prog) que apresente no écran,
//de 5 em 5 segundos, a mensagem indicada por prog_arg1 (ex: I'm alive!)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i;
    if (argc < 2){
        fprintf(stderr, "This program needs at least 2 arguments\n");
        exit(1);
    }
    for (i = 0; i < 100; i++){
        printf("%s\n", argv[1]);
        sleep(5);
    }

    exit(0);

}