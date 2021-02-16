#include <iostream>

using namespace std;

int main(){
    int numero, i = 2;

    cout << "Type a number to find out it's divisors: ";
    cin >> numero;

    while (i < numero/2+1){
        if (numero % i == 0) {
            cout << i << " ";
            numero = numero/i;
            i = 2;

        }
        else
            i++;

    }
    cout << numero;
    return 0;
}
