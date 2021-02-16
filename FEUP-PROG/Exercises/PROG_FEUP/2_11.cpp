#include <iostream>
#include <iomanip>

using namespace std;


int main() { //letter a
    int n, counter = 1, x;
    float soma = 0, fracao = 1;
    cout << fixed << setprecision(3);
    cout << "Let's find out the pi value! To do this, type a number: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        if (i%2 == 0)
            soma += (float) 4 / counter;
        else
            soma-= (float) 4 / counter;
        counter += 2;
    }
    cout << "Here it is: " << soma << endl;
    cout << "Now, let's find out the value of e! To do this, type a number and a x number: "; //letter b
    cin >> n >> x;
    soma = 1;
    for (int i = 1; i< n+1; i++){
        fracao = x*fracao/i;
        soma+= fracao;
    }
    cout << "Here it it: " << soma << endl;

    cout << "Now, let's find out the value of e^-x! To do this, type a number and a x: "; //letter c
    cin >> n >> x;
    soma = 1;
    for (int i = 1; i< n+1; i++){
        fracao = x*fracao/i;
        if (i %2 == 1)
            soma+= fracao;
        else 
            soma-= fracao;
    }
    cout << "Here it it: " << soma << endl;


}
