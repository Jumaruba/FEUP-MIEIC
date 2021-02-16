#pragma once

#include "../include/common_utils.h"

#include <stdbool.h>

typedef struct q_singleton
{
    int nsecs, nplaces, nthreads;
    char request_fifo[MAX_FIFONAME];
    bool force;
    bool limited_capacity;
} q_singleton;

q_singleton* get_q_args();

void free_q_singleton();

int parse_args(int argc, char* argv[]);
