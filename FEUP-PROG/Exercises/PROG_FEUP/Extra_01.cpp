//Write a program that uses cin >> , cin.peek() and cin.ignore()
// to read the integer number contained in "#ABcdE12345$Esc", that is 12345,
// discarding all the remaining symbols.

#include <iostream>

using namespace std;

int main(){
    char palavra;
    int number = 0;
    cout << "Digite a palavra \n"; 

    palavra = cin.peek();

    while (palavra != '\n'){
        cout << palavra << endl;
        if (palavra >= '0' && palavra <= '9')
            number = 10* number + palavra - '0';
        cin.ignore(1);
        palavra = cin.peek();
    }
    cout << endl;

    cout << number << endl; 

}