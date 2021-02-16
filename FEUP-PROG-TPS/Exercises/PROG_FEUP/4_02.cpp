#include <iostream>

using namespace std;

bool sequenceSearch(string s, int nc, char c){
    int contador = 0;
    bool first = false;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == c){  // if its equal, sum 1;
            contador ++;
            first = true;
        }
        
        if (first && s[i] != c){ // if its different and first == true, reset;
            if (contador == nc)
                return true;
            else{
                contador = 0;
                first = false;
            }
        }

    }
    return false;
}

int main(){
    string s;
    int nc;
    char c;

    cout << "palavra quantidade letra ?" << endl;
    cin >> s >> nc >> c;
    cout << sequenceSearch(s, nc, c) << endl;
}