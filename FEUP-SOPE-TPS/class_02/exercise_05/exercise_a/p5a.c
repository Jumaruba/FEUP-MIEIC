#include <fcntl.h>  //open file
#include <unistd.h> //use the write


int main(void)
{
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";

  fd = open("f1.txt",O_CREAT|O_TRUNC|O_EXCL|O_WRONLY|O_SYNC,0600);
  write(fd,text1,4);
  write(fd,text2,5);
  close(fd);
  return 0;
}

