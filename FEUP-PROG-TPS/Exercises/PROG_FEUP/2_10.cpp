#include <iostream>
#include <string>

using namespace std;


int main(){
    string numero;
    bool capicua = true;
    cin >> numero;
    for (int i = 0; i< numero.size()/2 ; i++){
        if (numero[i] != numero[2*numero.size()/2 - i -1]){
            cout << "It's not a capicua!" << endl;
            capicua = false;
            break;
        }
    }
    if (capicua)
        cout << "It's a fucking capicua!!";

    return 0;

}