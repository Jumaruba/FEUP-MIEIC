/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

string calcSum(int* sequence, int size)
{

    int pos, min = 0;
    string ans = "";
    vector<int> now(size+1, 0);
    vector<int> ant(size+1, 0);
    for (int i = 1; i < size+1; i++){
        for (int j = 0; j < size -i+1; j++){
            now[j] = sequence[j+i-1] + ant[j];
            if (j==0 || now[j] < min){
                min = now[j];
                pos = j;
            }
        }
        ant = now;

        ans += to_string(min) + "," + to_string(pos) + ";";
    }
    return ans;
}

void test_function(){
    int seq[1500+1];
    ofstream myfile;
    myfile.open("complexity.csv");
    for (int i = 10; i < 1500; i+=10){
        for (int j = 0; j < i; j++) seq[j] = rand()%1000 +1;
        auto start = std::chrono::high_resolution_clock::now();
        calcSum(seq, i);
        auto finish = std::chrono::high_resolution_clock::now();
        auto mili = chrono::duration_cast<chrono::milliseconds>(finish-start).count();
        myfile << mili << "," << i << "\n";
        //cout << "TIME OF EXECUTION: " << mili << endl;
    }
    myfile.close();
}

