/*
 * Change.cpp
 */

#include "Change.h"
#include <iostream>
using namespace std;
string calcChange(int m, int numCoins, int *coinValues)
{
    if (m == 0) return "";
    string coins[m+1] = {""};
    int best[m+1] = {0};
    //selecting just two coins
    for (int i = 0; i < numCoins; i++){
        for (int j = coinValues[i]; j < m+1; j++){
            if ((best[j-coinValues[i]]+1 < best[j]) || (best[j-coinValues[i]] != 0 && best[j] == 0)){
                best[j] = best[j-coinValues[i]]+1;
                coins[j] = to_string(coinValues[i])+ ";" + coins[j-coinValues[i]];
            }
            if (j == coinValues[i]){
                best[j] = 1;
                coins[j] = to_string(coinValues[i]) + ";";
            }
        }
    }
    if (best[m] == 0) return "-";
    return coins[m];
}


