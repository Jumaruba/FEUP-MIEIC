#include <bits/stdc++.h>
using namespace std;

#define LIM_DEPTH   20
class State {

public:
    int b1, b2;
    State(int b1, int b2) : b1(b1), b2(b2) {}

    bool operator==(const State& s1) const {
        return s1.b1 == this->b1 && s1.b2 == this->b2;
    }

    friend ostream& operator<<(ostream& os, const State& s) {
        os << "b1: " << s.b1 << "|| b2: " << s.b2 << endl;
    }
    // Empty b1.
    State eb1() {
        State ns = *this;
        ns.b1 = 0;
        return ns;
    }

    State eb2() {
        State ns = *this;
        ns.b2 = 0;
        return ns;
    }

    State fb1() {
        State ns = *this;
        ns.b1 = 4;
        return ns;
    }

    State fb2() {
        State ns = *this;
        ns.b2 = 3;
        return ns;
    }

    State fe() {
        State ns = *this;
        ns.b1 += min(4 - ns.b1, ns.b2);
        ns.b2 -= (ns.b1 - this->b1);
        return ns;
    }

    State ef() {
        State ns = *this;
        ns.b2 += min(3 - ns.b2, ns.b1);
        ns.b1 -= (ns.b2 - this->b2);
        return ns;
    }

};

int isEndState(vector<State> goals, State currState) {
    if (count(goals.begin(), goals.end(), currState)) return 1;
    return 0;
}


State solveBFS(State init, vector<State> goals, int& cost) {
    queue<State> q;
    q.push(init);

    while (!q.empty()) {
        State currState = q.front();
        q.pop(); 

        // Abort operation. 
        if (cost > 10000) break; 

        // Check for end. 
        if (isEndState(goals, currState)) return currState;

        // Add states to the tree. 
        if (currState.b1 != 0) q.push(currState.eb1());
        if (currState.b2 != 0) q.push(currState.eb2());
        if (currState.b1 != 4) q.push(currState.fb1());
        if (currState.b2 != 3) q.push(currState.fb2());
        if (currState.b1 != 0 && currState.b2 != 3) q.push(currState.ef());
        if (currState.b1 != 4 && currState.b2 != 0) q.push(currState.fe());
        cost++;
    }

    return State(0, 0);
}

int solveDFS(State currState, vector<State> goals, int depth, int& solveCost) {
    solveCost++;
    if (isEndState(goals, currState))  return depth + 1;
    if (depth > LIM_DEPTH) return -1;

    int newCost = -1;
    if (currState.b1 != 0) newCost = solveDFS(currState.eb1(), goals, depth + 1, solveCost);
    if (newCost != -1) return newCost;

    if (currState.b2 != 0) newCost = solveDFS(currState.eb2(), goals, depth + 1, solveCost);
    if (newCost != -1) return newCost;

    if (currState.b1 != 4) newCost = solveDFS(currState.fb1(), goals, depth + 1, solveCost);
    if (newCost != -1) return newCost;

    if (currState.b2 != 3) newCost = solveDFS(currState.fb2(), goals, depth + 1, solveCost);
    if (newCost != -1) return newCost;

    if (currState.b1 != 0 && currState.b2 != 3) newCost = solveDFS(currState.ef(), goals, depth + 1, solveCost);
    if (newCost != -1) return newCost;

    if (currState.b1 != 4 && currState.b2 != 0) newCost = solveDFS(currState.fe(), goals, depth + 1, solveCost);
    if (newCost != -1) return newCost;

    return -1;

}

int main() {
    State init(0, 0);
    int cost = 0;

    vector<State> goals = { State(2, 0), State(2,1), State(2,2), State(2,3) };

    int solveCost = -1;
    int solutionCost = solveDFS(init, goals, -1, solveCost);
    cout << "Cost to go from init to goal (number of nodes between those two) \t ::" << solutionCost << endl; 
    cout << "Cost to process solution (number of nodes visited) \t\t\t ::" << solveCost << endl; 
    cout << "Total cost :: " << solveCost + solutionCost << endl;
    
    solveCost = 0; 
    solveBFS(init, goals, solveCost);  
    cout << "Cost to process solution (number of nodes visited) \t\t\t ::" << solveCost << endl;  

}
