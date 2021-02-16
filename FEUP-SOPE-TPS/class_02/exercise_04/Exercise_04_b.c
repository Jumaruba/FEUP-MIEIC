#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


typedef struct{
	char name[50]; 
	int grade; 
}Student;


int main(){
	Student students[100]; 
	Student s; 
	int number;

	unsigned long SIZE = 50*sizeof(char); 

	//get the descriptor 
	int desc = open("students.txt",O_WRONLY); 
	char * buffer = s.name; 
	char * n; 
	unsigned long size_int = sizeof(int); 
	for (int i = 0; i < 100; i++){
		printf("Type the name: "); 
		getline(&buffer, &SIZE, stdin); 
		printf("Type the grade: ");
		getline(&n, &size_int, stdin); 
		s.grade = atoi(n);  
		students[i] = s; 
		printf("%s %d\n", s.name, s.grade); 
		if (s.grade == -1) break; 

	}

	write(desc, students, 100*sizeof(Student)); 


}