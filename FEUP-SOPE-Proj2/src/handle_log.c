#include "../include/handle_log.h"

#include <time.h>
#include <stdio.h>

void log_entry(Request *req, char *oper) {
    printf("%ld ; %d ; %d ; %lu ; %d ; %d ; %s\n",
        time(NULL), req->i, req->pid, req->tid, req->dur, req->pl, oper);
}
