#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    char prog[20];
    sprintf(prog, "%s.c", argv[1]);     //program's name passed as argument
    execlp("gcc", "gcc", prog, "-Wall", "-o", argv[1], NULL);
    //gcc is the name of the program that the OS will search in the path
    //gcc is the name of the own program, since it's argv[0]
    //argv[1] is the name received by our program
    //the execl
    printf("Error message");
    exit(-1);
}