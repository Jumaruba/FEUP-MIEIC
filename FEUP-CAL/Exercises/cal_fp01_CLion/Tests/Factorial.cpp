/*
 * Factorial.cpp
 */

#include "Factorial.h"
#include <iostream>
int factorialRecurs(int n)
{
    if (n == 0 || n == 1) return 1;
    return  n*factorialRecurs(n-1);

}

int factorialDinam(int n)
{
    if (n == 0) return 1;
    int total = 1;
    for (int i = 1; i < n+1; i++){
        total = i*total;
    }
	return total;
}
