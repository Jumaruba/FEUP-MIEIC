#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
 DIR *dirp;
 struct dirent *direntp;
 struct stat stat_buf;
 char *str;
 int erro; 

 if (argc != 2)
 {
  fprintf( stderr, "Usage: %s dir_name\n", argv[0]);
  exit(1);
 }

 if ((dirp = opendir( argv[1])) == NULL)
 {
  perror(argv[1]);
  exit(2);
 }

 while ((direntp = readdir( dirp)) != NULL)
 {
  if ((erro = lstat(direntp->d_name, &stat_buf))==-2)   // testar com stat()
  {
        printf("%d\n", erro); 
        perror("lstat ERROR");
        exit(3);
  }
  if (S_ISREG(stat_buf.st_mode)) str = "regular";
  else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
  else str = "other";
  printf("i-node number: %d", stat_buf.st_ino); 
  printf( "\t\t size: %d \t\t", stat_buf.st_size); 
  printf("%-25s - %s\n", direntp->d_name, str);
 }

 closedir(dirp);
 exit(0);
}

