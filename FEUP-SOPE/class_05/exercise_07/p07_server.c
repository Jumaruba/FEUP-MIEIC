#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    int fd;
    int n1, n2;

    if (mkfifo("/home/maruba/Documentos/SOPE/class_05/exercise_07/myfifoNumber", 0660) < 0)
        perror("mkfifo");

    fd = open("/home/maruba/Documentos/SOPE/class_05/exercise_07/myfifoNumber", O_RDONLY); 

    printf("fd: %d\n", fd);
    //get numbers
    printf("Reading...\n");
    read(fd, &n1, sizeof(int));
    read(fd, &n2, sizeof(int));
    
    close(fd);
    printf("Server sencond fifo\n");
    int sum = n1 + n2;
    int mult = n1 * n2;

    do
    {
        fd = open("/home/maruba/Documentos/SOPE/class_05/exercise_07/myfifoResult", O_WRONLY);
        if (fd == -1)
            sleep(1);
        printf("waiting...\n");
    } while (fd == -1);

    write(fd, &sum, sizeof(sum));
    write(fd, &mult, sizeof(mult));
    sleep(5);
    close(fd);
    exit(0);
}