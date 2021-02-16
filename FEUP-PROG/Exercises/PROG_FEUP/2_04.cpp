#include <iostream>
#include <cmath>

using namespace std;

int main(){
    float mercadoria;

    if (cin>> mercadoria) {
        if (mercadoria < 500)
            cout << "5 euros" << endl;
        else if (500 <= mercadoria <= 1000)
            cout << 5 + ceil((float) (mercadoria - 500) / 100) * 1.5 << " euros" << endl;
        else if (mercadoria > 1000)
            cout << 12.5 + ceil((float) (mercadoria - 500) / 250) * 5 << " euros" << endl;
    }
    return 0;

}