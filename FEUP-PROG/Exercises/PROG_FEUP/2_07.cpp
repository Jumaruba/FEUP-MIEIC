// this is letter a

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    float incremento, gama_begin, gama_end;

    cout << "Digite o incremento: ";
    cin >> incremento;
    cout << "Digite o VALOR INICIAL  e o VALOR FINAL: ";
    cin >> gama_begin >> gama_end;

    
    
    cout << setw(3)<<"ang"<< setw(10) << "sen"<< setw(10) <<  setw(10) << "cos" << setw(10) <<  "tan" << endl;
    for (int i = gama_begin; i <= gama_end; i+= incremento){
        cout << fixed  <<setprecision(6) << setw(3)<< i <<setw(10) << sin(i*M_PI/180) <<setw(10) << cos((i*M_PI/180))<<setw(10) << tan(i*M_PI/180)<< endl;
    }
return 0;
}
