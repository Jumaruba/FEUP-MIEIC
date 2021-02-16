#include <unistd.h> 
#include <stdio.h>

int main(){

	if (fork() > 0){	//father
        printf("Hello");

	}else{
        printf(" world\n"); //son
    }
}