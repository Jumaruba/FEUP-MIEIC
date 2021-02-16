#include <iostream> 
#include <cmath>
using namespace std;


double round(double x, unsigned n){
    return floor(x*pow(10,n-1) + 0.5)/pow(10,n-1);
}


int main(){
    double x, n;
    cout << "Insira o valor e o numero de casas decimais: ";
    cin >> x >> n;
    cout << round(x,n) << endl;
    return 0;
}