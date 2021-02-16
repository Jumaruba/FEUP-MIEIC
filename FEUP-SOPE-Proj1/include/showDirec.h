#pragma once 

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/handleLog.h"

    
#define PATH_SIZE_MAX       540
#define PATH_MAX_CPY        180



/**
 * @brief This function handles the task of showing files information
 * 
 * @param opt Options given as parameters
 * @return int 0 if success and 1 upon error
 */
int showDirec(Options *opt);

/**
 * @brief Calculate the size to be shown to the user
 * 
 * @param size 
 * @param opt 
 * @return long int 
 */
long int calculate_size(long int size, Options *opt);
