// PROGRAMA p06_reader.c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 

int readline(int fd, char *str);
int main(void)
{
    int fd, r;
    char str[100];
    mkfifo("/tmp/myfifo", 0660);
    fd = open("/tmp/myfifo", O_RDONLY);
    printf("fd: %d", fd);
    while ((r= readline(fd, str))) printf("%s", str);
    close(fd);
    printf("r: %d\n", r); 
    return 0;
}

int readline(int fd, char *str){
    int n;
    do{
        n = read(fd, str, 1);
    }while (n > 0 && *str++ != '\0');
    
    return (n > 0);
}
