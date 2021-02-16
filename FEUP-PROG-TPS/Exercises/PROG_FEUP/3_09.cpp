#include <iostream>
#include <cmath>
using namespace std;

double funcao(double x){
    return pow(x, 2);
}

double integrateTR(double f(double), double a, double b, int n){
    float h = (b - a)/n;
    double soma = 0;
    for (int i = 0; i< n; i++){
        soma += (f(a + (i - 1)* h) + f(a + i*h))*(h/2);
    }
    return soma;
}

int main(){
    double a, b;
    int n ;
    cout << "a b n ?" << endl;

    cin >> a>> b >> n; 
    cout << integrateTR(funcao, a, b, n) << endl; 
    return 0;

}