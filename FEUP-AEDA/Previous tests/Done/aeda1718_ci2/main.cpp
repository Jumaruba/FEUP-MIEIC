#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    list<int> p = {4,6,3,1,2,5,4,7};
    queue<int> q;
    q.push(9); q.push(4); q.push(3); q.push(1); q.push(6); q.push(8);
    /**
    for (int i = 0; i < q.size(); i++){
        if (q.front() == 1)
            break;
    }
     **/
    for (int i = 0; i< q.size(); i++){
        if (q.front() == 10) break;
        int front = q.front();
        q.pop();
        q.push(front);

    }
    /**
    p.sort([](int x1, int x2){return x1> x2; });
    for (auto it = p.begin(); it != p.end(); it++){
        if (*it == 1)
            it = p.erase(it);
    }
    for (auto x: p)
        cout << x << endl ;
       **/
    return 0;}