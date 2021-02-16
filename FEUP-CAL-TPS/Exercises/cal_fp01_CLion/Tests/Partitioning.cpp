/*
 * Partioning.cpp
 */

#include "Partitioning.h"

int s_recursive(int n,int k)
{
    if (k == 1 || k == n) return 1;

   return s_recursive(n-1, k-1) + k*s_recursive(n-1,k);
}

int s_dynamic(int n,int k)
{
    vector<int> ant(k+1,0);
    vector<int> now(k+1,0);
    int soma;
    for (int i = 1; i< n+1; i++){
        soma = 0;
        for (int j = 1; j<k +1; j++){
            now[j] = (j == 1 || j == i)? 1: ant[j-1] + j*ant[j];
            if (i<=k)
                soma += now[j];
            else soma = now[j];
        }
        ant = now;
    }
	return soma;
}


int b_recursive(int n)
{
	return 0;
}

int b_dynamic(int n)
{
	return 0;
}


