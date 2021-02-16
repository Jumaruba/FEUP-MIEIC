#include <iostream>

using namespace std;

int mdc(int n1, int n2) {  //finding the mdc to do the reduction

    if (n1 % n2 == 0)
        return n2;
    else
        return mdc(n2, n1 % n2);
}

int main() {
    int n1, n2;
    cout << "Digite o maior número e o menor número: ";
    cin >> n1 >> n2;
    cout << mdc(n1, n2);

    return 0;
}