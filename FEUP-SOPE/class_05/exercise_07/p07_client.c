#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    int n1 = 1;
    int n2 = 2;

    do
    {
        fd = open("/home/maruba/Documentos/SOPE/class_05/exercise_07/myfifoNumber", O_WRONLY);
        if (fd == -1)
            sleep(1);
    } while (fd < 0);
    printf("Writing...\n");
    write(fd, &n1, sizeof(n1));
    write(fd, &n2, sizeof(n2));
    sleep(5);
    close(fd);
    printf("Client second fifo\n");
    if (mkfifo("/home/maruba/Documentos/SOPE/class_05/exercise_07/myfifoResult", 0660) < 0)
        perror("mkfifo");
    if ((fd = open("/home/maruba/Documentos/SOPE/class_05/exercise_07/myfifoResult", O_RDONLY)) < 0)
    {
        perror("open");
        exit(1);
    }

    int sum, mult;
    read(fd, &sum, sizeof(int));
    read(fd, &mult, sizeof(int));

    printf("SUM: %d", sum);
    printf("MULT: %d", mult);

    close(fd);
    exit(0);
}