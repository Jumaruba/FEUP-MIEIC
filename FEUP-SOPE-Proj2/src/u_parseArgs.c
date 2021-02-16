#include "../include/u_parseArgs.h"

#include "../include/common_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

// These extern are ugly, but it was this
// or converting Info_u into a singleton :upside_down:
extern int thread_interval;   /** Interval between threads creation in miliseconds */
extern int max_duration;     /** Max miliseconds a user can be at the bathroom */

int parseArgs(int argc, char *argv[], Info_u *info)
{
    info->secs = -1;
    info->fifoname[0] = '\0';

    if (argc < 4)
    {
        fprintf(stderr, "%s:%d  wrong number of args\n", __FILE__, __LINE__);
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

                if (parseInt(argv[cur_arg], &info->secs)) {
                    fprintf(stderr, "Failed to parse time\n");
                    return 1;
                }
            }
            if (strcmp(argv[cur_arg], "-d") == 0) {
                ++cur_arg;
                if (cur_arg >= argc) {
                    fprintf(stderr, "Argument -d requires an additional integer argument\n");
                    return 1;
                }

                if (parseInt(argv[cur_arg], &max_duration)) {
                    fprintf(stderr, "Failed to parse max bathroom ocupation time\n");
                    return 1;
                }
            }
            if (strcmp(argv[cur_arg], "-i") == 0) {
                ++cur_arg;
                if (cur_arg >= argc) {
                    fprintf(stderr, "Argument -i requires an additional integer argument\n");
                    return 1;
                }

                if (parseInt(argv[cur_arg], &thread_interval)) {
                    fprintf(stderr, "Failed to parse thread interval\n");
                    return 1;
                }
                else
                    thread_interval = MILI_MICRO(thread_interval);
            }
            else {
                if (parseFifoname(argv[cur_arg], info->fifoname) < 0) {
                    fprintf(stderr, "%s:%d  error parsing fifoName\n", __FILE__, __LINE__);
                    return 1;
                }
            }

            ++cur_arg;
        }
    }

    if (info->secs == -1) {
        fprintf(stderr, "Must specify program duration\n");
        return 1;
    }
    else if (info->fifoname[0] == '\0') {
        fprintf(stderr, "Must specify FIFO name\n");
        return 1;
    }

    return 0;
}
