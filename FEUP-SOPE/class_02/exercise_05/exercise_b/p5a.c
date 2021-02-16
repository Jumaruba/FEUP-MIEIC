#include <fcntl.h>  //open file
#include <unistd.h> //use the write
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";

  if ((fd = open("f1.txt",O_CREAT|O_WRONLY|O_SYNC,0600)) < 0){
    perror("The file already exists");
    exit(1);
  }
  write(fd,text1,5);
  write(fd,text2,5);
  close(fd);
  return 0;
}

