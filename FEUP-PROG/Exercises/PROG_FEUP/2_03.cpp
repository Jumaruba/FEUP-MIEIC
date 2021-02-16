#include <iostream>
#include <cctype>
using namespace std;

//we want to create a great calculator

int main(){
    double a, b;
    char operand, letter;
    bool fail;

    cout << "N1 OP N2 ? ";
    do {
        fail = false;
        if (cin >> a >> operand >> b) {
            switch (operand){
                case ('*'):
                    cout << (double)a*b << endl;
                    break;
                case ('+'):
                    cout << (double)(a+b) << endl;
                    break;
                case ('-'):
                    cout << (double)(a-b) << endl;
                    break;
                case ('/'):
                    cout << (double)(a/b) << endl;
                    break;
            }
            cout << "Do u wanna do it again? (Y|N): ";
            cin >> letter;
            if (toupper(letter) == 'Y') {
                fail = true;
                cout << "N1 OP N2 ? ";
            }
        } else {
            cout << "Try again, my friend..." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "N1 OP N2 ? ";
            fail = true;
        }
    } while (fail);
}