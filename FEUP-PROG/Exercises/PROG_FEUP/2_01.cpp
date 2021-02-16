//exercise 2.1

#include <iostream>

using namespace std;

int main(){
    float a,b,c,d,e,f;

    cout << "Digite os numeros: ";
    if (cin >> a >> b >> c >> d >> e >> f) {
        if ((a * e - b * d) != 0) {
            float x = (float) (c * e - b * f) / (a * e - b * d);
            float y = (float) (a * f - c * d) / (a * e - d * b);
        }
        else
            cout << "sistema impossivel";
    }
    else
        cout << "sistema indeterminado";

    return 0;
}