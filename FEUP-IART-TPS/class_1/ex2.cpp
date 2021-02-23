#include <bits/stdc++.h>  
#include <fmt/ostream.h> 
using namespace std;
using fmt::print;


#define LIM_DEPTH   20 

// possible states = operations: -1,1; 1,1; -1,-1;
class State {
public:
    int miRight;        // Missionares on the right (initial) margin
    int caRight;        // Canibals on the right (initial) margin 
    int miLeft;         // Missionares on the left (end) margin
    int caLeft;         // Canibals on the left (end) margin 


    State() {
        int miRight = 3;
        int caRight = 3;
        int miLeft = 0;
        int caLeft = 0;
    }

    State(int miRight, int caRight, int miLeft, int caLeft) : miRight(miRight), caRight(caRight), miLeft(miLeft), caLeft(caLeft) {};

    // value -1 for canibals, 1 for missionares 
    State send(int value1, int value2) {
        State ns = *this;  
        ns.caLeft += (value1 == -1) + (value2 == -1); 
        ns.caRight -=  (value1 == -1) + (value2 == -1);   
        ns.miLeft += (value1 == 1) + (value2 == 1); 
        ns.miRight -= (value1 == 1) + (value2 == 1); 

        return ns;
    }

    bool canSend(int value1, int value2) {
        int miTrans = (value1 == 1) + (value2 == 1);
        int caTrans = (value1 == -1) + (value2 == -1);

        if (miTrans > miRight) return false;
        if (caTrans > caRight) return false;

        return ((miRight - miTrans) - (caRight - caTrans) >= 0 && (miLeft + miTrans) - (caLeft + caTrans) >= 0);
    } 

    bool operator==(const State& s) const {
        return (s.caLeft == this->caLeft && s.caRight == this->caRight
            && s.miLeft == this->miLeft && s.miRight == this->miRight);
    } 

    friend ostream& operator<<(ostream& os, const State& s) {
        cout << "M:-" << s.miLeft << " C:-" << s.caLeft << " <<<" << "+-+-+-+" <<  
                ">>> M:-" << s.miRight << " C:-" << s.caRight << endl; 
    }

};

int solveBFS(State init, State goal) {
    int cost = -1;
    queue<State> q;

    q.push(init);
    while (!q.empty()) {
        cost ++;  
        State currState = q.front();
        q.pop(); 
        cout << currState << endl; 
        if (currState == goal) return cost; 

        if (currState.canSend(1, 1)) q.push(currState.send(1, 1));
        if (currState.canSend(-1, 1)) q.push(currState.send(-1, 1));
        if (currState.canSend(-1, -1)) q.push(currState.send(-1, -1)); 
    }
}

int solveDFS(State currState, State goal, int depth){ 
    cout << currState << endl; 
    if (currState == goal) return depth; 
    if (depth > LIM_DEPTH) return -1; 

    int value = -1; 
    if (currState.canSend(1,1))  value = solveDFS(currState.send(1,1), goal, depth + 1); 
    if (value != -1) return value; 

    if (currState.canSend(1,-1)) value = solveDFS(currState.send(1,-1), goal, depth +1); 
    if (value != -1) return value; 

    if (currState.canSend(-1,-1)) value = solveDFS(currState.send(-1,-1), goal, depth +1); 
    if (value != -1) return value;  

}

int main() {
    State init(3,3,0,0);   
    State goal(0,0,3,3); 
    print("SOLVE BY BFS\n"); 
    cout << solveBFS(init, goal) << endl;  
    print("SOLVE BY DFS\n"); 
    cout << solveDFS(init, goal, 0) << endl;  
}
