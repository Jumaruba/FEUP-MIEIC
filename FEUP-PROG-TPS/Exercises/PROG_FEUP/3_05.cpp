#include <iostream>

using namespace std;

bool readFracc(int &numerator, int &denominator) {  //checking if the input is ok
    char division;
    cout << "Type the frac: ";
    if (cin >> numerator >> division >> denominator) {
        if (denominator == 0 || division != '/')
            return false;
        else return true;
    } else
        return false;
}

void writeFracc(int numerator, int denominator) {  //writing the frac
    cout << numerator << "/" << denominator << endl;
}


void operando(int n1, int n2, int &nr, int d1, int d2, int &dr, char operand) { //doing the operation
    if (operand == '+') {
        nr = (n1 * d2 + n2 * d1);
        dr = d1 * d2;
    } else if (operand == '-') {
        nr = n1 * d2 - n2 * d1;
        dr = d1 * d2;
    } else if (operand == '*') {
        nr = n1 * n2;
        dr = d1 * d2;
    } else if (operand == '/') {
        nr = n1 * d2;
        dr = n2 * d1;
    }

}


int mdc(int n1, int n2) {  //finding the mdc to do the reduction
    // recursive way

//     if (n1%n2 == 0)
//         return n2;
//     else
//         return mdc(n2, n1%n2);

    //non-recursive way

    for (int i = n2; i > 0; i--) {
        if (n1 % i == 0 && n2 % i == 0)
            return i;
    }
    return 1;
}

void reduceFracc(int &numerator, int &denominator) {  //reducing fraction
    int k;
    while (mdc(numerator, denominator) != 1) {
        k = mdc(numerator, denominator);
        numerator = numerator / k;
        denominator = denominator / k;
    }
}

int main() {
    int numerator1, denominator1, numerator2, denominator2;
    int dresult = 0, nresult = 0;
    char operand;
    bool frac;

    frac = readFracc(numerator1, denominator1);
    if (!frac) {
        numerator1 = denominator1 = 0;
        cout << "0/0" << endl;
    } else {
        reduceFracc(numerator1, denominator1);
        writeFracc(numerator1, denominator1);
    }

    cout << "If you dont wanna do an operation type 0, else type the operation ( + , - , * , / ):" << endl ;
    if (cin >> operand) {

        frac = readFracc(numerator2, denominator2);
        if (!frac) {
            numerator2 = denominator2 = 0;
            cout << "0/0" << endl;
        } else {
            reduceFracc(numerator2, denominator2);
            cout << "Reducing: ";
            writeFracc(numerator2, denominator2);
        }

        operando(numerator1, numerator2, nresult, denominator1, denominator2, dresult, operand);  //doing the operation;
        
        if (frac != 0) {
            reduceFracc(nresult, dresult);
            cout << "Result: ";
            writeFracc(nresult, dresult);
        } else
            cout << "Guess what..." << endl;
    }

    return 0;

}