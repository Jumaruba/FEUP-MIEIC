#include <stdio.h>
#include <stdlib.h>

extern int max_word(char* vetor);


int main(){

	char vetor[] = "loucocuol0";
	int result;

	result = max_word(vetor);

	printf("resultado = %d", result);

	return 0;
}

