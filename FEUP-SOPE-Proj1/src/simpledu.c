#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "../include/utils.h"
#include "../include/showDirec.h"
#include "../include/handleLog.h" 


int main(int argc, char *argv[]) {
    Options *opt = calloc(1, sizeof(Options));             
    if (opt == NULL) {
        // If we exit here, we must've been pretty darn unlucky
        exit(1);
    }

    simpledu_startup(argc, argv, opt);
    log_create(argc, argv);

    if (showDirec(opt)){
        perror("Show directory error");
        opt->return_val = 1;
        exit(1); 
    }

    exit(opt->return_val);
}