#include "maze.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <utility>
#include <algorithm>

using namespace std;

DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const
{
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

Maze::Maze(int rows, int cols) {
    nrows = rows;
    ncols = cols;
    noWalls.clear();
    DisjointSets temp(rows*cols);
    maze = temp;
}

vector<int> Maze::getNeighbours(int x) const {
    vector<int> res;
    if (x >= ncols) res.push_back(x-ncols);
    if (x/ncols+1 < nrows) res.push_back(x+ncols);
    if (x%ncols != 0) res.push_back(x-1);
    if (x%ncols != ncols-1) res.push_back(x+1);
    return res;

}

void Maze::buildRandomMaze() {
    noWalls.clear();
    int size = nrows*ncols;
    srand(time(NULL));
    while(maze.getNumberOfSets() != 1){
        int n = rand()%size;
        vector<int> tmp = getNeighbours(n);
        int pos = rand()%tmp.size();
        int c1 = maze.find(n);
        int c2 = maze.find(tmp[pos]);
        if (c1 != c2){
            maze.unionSets(c1,c2);
            noWalls.push_back(pair<int,int> (n, tmp[pos]));
        }
        printMaze();


    }
}


