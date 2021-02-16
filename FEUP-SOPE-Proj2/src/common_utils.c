#include "../include/common_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool is_num(char *s) {
    if (*s == '\0')
        return false;
    while (*s != '\0') {
        if (*s < '0' || *s > '9')
            return false;
        ++s;
    }
    return true;
}

struct timespec getTimespecIn(int seconds, int miliseconds) {
    time_t now = time(NULL);
    now += seconds;
    struct timespec ret = {now, miliseconds};
    return ret;
}

int parseInt(char *str, int *p)
{
    if (!is_num(str)) {
        fprintf(stderr, "Parameter must be an integer (given \"%s\")\n", str);
        return 1;
    }
    else
        *p = atoi(str);

    if (*p <= 0) {
        fprintf(stderr, "Argument must be an integer larger than 0\n");
        return 1;
    }

    return 0;
}

int parseFifoname(char *str, char *dest) {

    if (strnlen(str, MAX_FIFONAME - 5) >= MAX_FIFONAME - 6) {
        fprintf(stderr, "Fifo name too large\n");
        return 1;
    }

    strcpy(dest, "/tmp/");
    strncat(dest, str, MAX_FIFONAME - 6);
    return 0;
}
