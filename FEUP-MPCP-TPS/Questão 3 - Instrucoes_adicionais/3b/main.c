#include <stdio.h>
#include <stdlib.h>

extern int max_word(char* vetor, char letra);


int main(){

	char vetor[] = "corrida maluca0";
	int result;

	result = max_word(vetor, 'r');

	printf("resultado = %d", result);

	return 0;
}

