//
// Created by julia on 15/04/2020.
//

#ifndef CAL_FP07_DISJOINTSET_H
#define CAL_FP07_DISJOINTSET_H

#include <vector>
#include <algorithm>


class DisjointSet {
private:
    std::vector<int> set;
public:
    DisjointSet();
    DisjointSet(int n);
    int find(int n) const;        //find the root of the set
    void unionSets(int root1, int root2);
    int getNumberOfSets() const;



};

#endif //CAL_FP07_DISJOINTSET_H
