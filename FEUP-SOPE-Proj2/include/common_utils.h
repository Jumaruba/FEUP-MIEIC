#pragma once

#include <stdbool.h>
#include <time.h>
#include "stdbool.h"

#define MICRO_MILI(n)       n/1000              /**Microseconds to miliseconds*/
#define MILI_MICRO(n)       n*1000              /**Miliseconds to microseconds*/

#define MAX_FIFONAME 255

bool is_num(char *s);

struct timespec getTimespecIn(int seconds, int miliseconds);

int parseInt(char *str, int *p);

int parseFifoname(char *str, char *dest);