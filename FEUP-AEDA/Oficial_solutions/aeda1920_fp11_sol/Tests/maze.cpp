#include "maze.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>

using namespace std;

DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const {
    cout << setw(3) << " ";
    for (int j=0; j<ncols; j++) {
        cout << setw(6) << "______";
    }
    for (int i=0; i<nrows; i++) {
        cout << endl;
        cout << setw(3) << "|";
        for (int j=0; j<ncols-1; j++) {
            int val = i*nrows+j;
            cout << setw(3) << val<<setw(3);
            if (noWalls.empty() ||
                    (find(noWalls.begin(),noWalls.end(),pair<int,int>(val,val+1)) == noWalls.end() &&
                            find(noWalls.begin(),noWalls.end(),pair<int,int>(val+1,val)) == noWalls.end())
                    )
                cout << "|";
            else
                cout <<" ";
        }
        int val = i*nrows+ncols-1;
        cout << setw(3) << val<<setw(3) << "|";
        cout <<endl;
        cout << setw(3) << " ";
        for (int j=0; j<ncols; j++) {
            int val = i*nrows+j;
            if (i<nrows-1) {
                if ( noWalls.empty() ||
                        (find(noWalls.begin(), noWalls.end(), pair<int, int>(val, val + ncols)) == noWalls.end()
                        && find(noWalls.begin(), noWalls.end(), pair<int, int>(val+ncols, val)) == noWalls.end())
                        )
                    cout << setw(6) << "______";
                else
                    cout << setw(6) << " ";
            } else
                cout << setw(6) << "______";
        }

    }
    cout <<endl << endl;
}



// a implementar

Maze::Maze(int rows, int cols): maze(rows*cols) {
    nrows=rows; ncols=cols;
    noWalls.clear();
}

vector<int> Maze::getNeighbours(int x) const {
    vector<int> res;
    if (x%ncols > 0)  // tem vizinho esquerdo
        res.push_back(x-1);
    if (x%ncols < (ncols-1))  // tem vizinho direito
        res.push_back(x+1);
    if (x>=ncols)           // tem vizinhao acima
        res.push_back(x-ncols);
    if ((x + ncols) < ncols*nrows )   // tem vizinhao abaixo
        res.push_back(x+ncols);
    return res;
}

void Maze::buildRandomMaze()
{
    noWalls.clear();
    srand(time(NULL));
    int size = nrows*ncols;
    while (maze.getNumberOfSets()!=1) {
        int x = rand()%size;
        vector<int> vizinhos = getNeighbours(x);
        int pos = rand()%vizinhos.size();
        int y = vizinhos[pos];
        int s1= maze.find(x);
        int s2 = maze.find(y);
        if (s1!=s2) {
            maze.unionSets(s1, s2);
            noWalls.push_back(pair<int,int>(x,y));
        }
    }
}

