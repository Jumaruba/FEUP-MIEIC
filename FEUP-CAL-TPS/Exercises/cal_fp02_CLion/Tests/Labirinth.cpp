/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>

using namespace std;


Labirinth::Labirinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            visited[i][j] = false;
}


void Labirinth::printLabirinth() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cout << labirinth[i][j] << " ";

        cout << endl;
    }
}


bool Labirinth::findGoal(int x, int y) {
    initializeVisited();
    return auxFindGoal(x, y);

}

bool Labirinth::auxFindGoal(int x, int y) {
    // checking for solution
    if (x+1 > 9 || x-1 < 0 || y+1 > 9 || y-1 < 0) return false;
    if (visited[x][y] || !labirinth[x][y] ) return false;
    if (labirinth[x][y] == 2) return true;
    visited[x][y] = true;

    if (auxFindGoal(x + 1, y)) return true;
    if (auxFindGoal(x, y + 1)) return true;
    if (auxFindGoal(x - 1, y)) return true;
    return auxFindGoal(x, y - 1);
}


