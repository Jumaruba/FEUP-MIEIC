#include <termios.h> 
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PASSWD_LEN 30

int main(void){
	struct termios oldterm, term;
	char passw[MAX_PASSWD_LEN+1]; 
	char ch, echo = '*';
	write(STDOUT_FILENO,"\nType the password: ", 20); 
	tcgetattr(STDIN_FILENO, &oldterm);	//get the information about the keyboard 
	term = oldterm;				//we gonna modify this  
	term.c_lflag &= ~(ECHO | ECHONL | ICANON); 
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); 
	int i = 0; 
	while(i < MAX_PASSWD_LEN && read(STDOUT_FILENO, &ch, 1) && ch != '\n'){
		passw[i++] = ch;		//store the passwd 
		write(STDOUT_FILENO, &echo, 1);  
	}
	passw[i] = 0; 				//last character
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm); 
	write(STDOUT_FILENO,"\nThe password is ", 17); 
	write(STDOUT_FILENO, passw, strlen(passw)); 
	write(STDOUT_FILENO, "\n", 1);
	exit(0); 
}
