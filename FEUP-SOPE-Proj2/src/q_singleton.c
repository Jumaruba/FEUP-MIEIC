#include "../include/q_singleton.h"

#include "../include/common_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

q_singleton* args = NULL;

int parse_args(int argc, char* argv[]) {

    get_q_args();

    // Default params
    args->nsecs = -1;
    args->nplaces = -1;
    args->nthreads = -1;
    args->request_fifo[0] = '\0';
    args->force = false;

    if (argc < 4) { // Minimum no of args
        return 1;
    }
    else {
        int cur_arg = 1;
        while (cur_arg < argc) {
            if (strcmp(argv[cur_arg], "-t") == 0) {
                ++cur_arg;
                if (cur_arg >= argc) {
                    fprintf(stderr, "Argument -t requires an additional integer argument\n");
                    return 1;
                }
                if (parseInt(argv[cur_arg], &args->nsecs)) {
                    fprintf(stderr, "Failed to parse number of threads\n");
                    return 1;
                }
            }
            else if (strcmp(argv[cur_arg], "-l") == 0) {
                ++cur_arg;
                if (cur_arg >= argc) {
                    fprintf(stderr, "Argument -l requires an additional integer argument\n");
                    return 1;
                }
                if (parseInt(argv[cur_arg], &args->nplaces)) {
                    fprintf(stderr, "Failed to parse number of bathrooms available\n");
                    return 1;
                }
            }
            else if (strcmp(argv[cur_arg], "-n") == 0) {
                ++cur_arg;
                if (cur_arg >= argc) {
                    fprintf(stderr, "Argument -n requires an additional integer argument\n");
                    return 1;
                }
                if (parseInt(argv[cur_arg], &args->nthreads)) {
                    fprintf(stderr, "Failed to parse number of threads\n");
                    return 1;
                }
            }
            else if (strcmp(argv[cur_arg], "-f") == 0) {
                args->force = true;
            }
            else {
                // Assume it's the directory path
                if (parseFifoname(argv[cur_arg], args->request_fifo)) {
                    return 1;
                }
            }

            ++cur_arg;
        }
    }

    if (args->nsecs == -1) {
        fprintf(stderr, "Number of seconds must be specified\n");
        return 1;
    }
    else if (args->nsecs < 0) {
        fprintf(stderr, "Must be active for 1 or more seconds\n");
        return 1;
    }
    else if(args->request_fifo[0] == '\0') {
        fprintf(stderr, "Fifoname must be specified\n");
        return 1;
    }

    if ((args->nplaces != -1 && args->nthreads == -1)
        || (args->nplaces == -1 && args->nthreads != -1)) {
            fprintf(stderr, "Either both of '-l' and '-n' or none of them must be specified\n");
            return 1;
    }
    else if (args->nplaces != -1) {
        // It's either both or none, so we only test one of them
        args->limited_capacity = true;
    }
    else {
        args->limited_capacity = false;
    }

    return 0;
}

q_singleton* get_q_args() {
    if (args == NULL) {
        args = (q_singleton*) calloc(1, sizeof(q_singleton));
    }
    return args;
}

void free_q_singleton() {
    free(args);
    args = NULL;
}
