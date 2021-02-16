// let's find out if the number is a prime

#include <iostream>
#include <cmath>

using namespace std;

int primo(int numero){
    if (numero%2 == 0 && numero!= 2)
        return 0;
    for (int i = 2; i < sqrt(numero); i+= 2)
        if (numero % i == 0)
            return 0;
    return 1;
}

int main(){
    int number;

    cin >> number;
    cout << "0 if not a prime, 1 if it's a prime: " << primo(number) << endl;  //this is letter a

    for (int i = 2; i < 100; i++)  //this is letter b
        cout << "0 if not a prime, 1 if it's a prime: " << primo(i) << endl;

    for (int i = 2; i < 1000; i++)  //this is letter c
        cout << "0 if not a prime, 1 if it's a prime: " << primo(i) << endl;
    return 0;
} 
