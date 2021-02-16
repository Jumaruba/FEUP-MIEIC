#ifndef SOPE_PROJ1_HANDLESIGNAL_H
#define SOPE_PROJ1_HANDLESIGNAL_H

#include "utils.h"
#include "handleLog.h" 
#include <unistd.h> 
#include <signal.h> 
#include <stdlib.h>
#include <stdio.h> 

Options *thisOpt;  

/**
 * @brief Set the signal if the process is the father 
 * 
 * @param opt Options struct 
 * @return int 0 upon sucess, 1 otherwise
 */
int setSignal(Options *opt); 



#endif 