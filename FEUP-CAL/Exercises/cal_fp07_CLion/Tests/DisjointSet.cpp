#include "DisjointSet.h"

DisjointSet::DisjointSet()
{}

// create n disjoint sets (one for each item)
DisjointSet::DisjointSet(int n)
{
    for (int i=0 ; i<n; i++)
        set.push_back(-1);
}

// Find the root of the set in which element v belongs
int DisjointSet::find(int v) const
{
    if (set[v] <0)
        return v;
    return find(set[v]);
}

// Perform Union of two subsets
void DisjointSet::unionSets(int root1, int root2)
{
    set[root2] = root1;
}

//a implementar

int DisjointSet::getNumberOfSets() const
{
    return count(set.begin(), set.end(),-1);
}
