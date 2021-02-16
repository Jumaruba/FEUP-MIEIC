#pragma once

#include <sys/types.h>
#include <pthread.h>

typedef struct request {
    int i;
    pid_t pid;
    pthread_t tid;
    int dur;
    int pl;
} Request;
