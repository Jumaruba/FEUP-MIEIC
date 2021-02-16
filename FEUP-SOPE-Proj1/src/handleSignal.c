#include "../include/handleSignal.h"


/**
 * @brief It handles the father SIGINT interrupt
 * 
 */
void handlerFather(int signo) {

    //STOP children
    log_sendSignal(thisOpt->child_pgid, "SIGSTOP");
    killpg(thisOpt->child_pgid, SIGSTOP);

    write(STDERR_FILENO, "\n____ Do you wish to terminate? ('y' to terminate) ____\n", 56);

    char str[MAXLINE+1];
    while (read(STDIN_FILENO, str, MAXLINE) < 0) {
        continue; // Cause some compilers are too smart
    }
    
    if (str[0] == 'y' || str[0] == 'Y') {
        // Terminate children
        log_sendSignal(getpid(), "SIGTERM");
        killpg(thisOpt->child_pgid, SIGTERM);
        thisOpt->sig_termed_childs = true;
        thisOpt->return_val = 1;
        exit(1);
    }
    else {
        // Continue children
        log_sendSignal(getpid(), "SIGCONT"); 
        killpg(thisOpt->child_pgid, SIGCONT);
        raise(SIGCONT);
    }

}

int setSignal(Options *opt){
    
    struct sigaction act; 
    thisOpt = opt; 

    if (sigemptyset(&act.sa_mask) < 0){
        perror("On sigempty %d"); 
        return 1; 
    }

    if (opt->original_process) {
        act.sa_handler = handlerFather;
        if (sigaction(SIGINT, &act, NULL) < 0){
            perror("Error set father interrupt signal"); 
            return 1; 
        }
    }

    return 0;
}

