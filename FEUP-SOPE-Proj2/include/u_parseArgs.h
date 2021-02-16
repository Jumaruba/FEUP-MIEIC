#pragma once
#pragma once

#include "../include/common_utils.h"

typedef struct info_u{
    int secs; 
    char fifoname[MAX_FIFONAME]; 
}Info_u; 

int parseArgs(int argc, char *argv[], Info_u * info);
