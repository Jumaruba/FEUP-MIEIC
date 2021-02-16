#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    float n,q,j, total;

    cout << "Digite os ANOS, a QUANTIA e a TAXA DE JUROS (em porcentagem): ";
    cin >> n >> q >> j;
    total = q;
    for(int i = 0; i< n; i++) {
        q = q*j/100;
    }
   
    cout << "Ao fim, serão retirados £ " << total+q << "euros!" << endl;

    return 0;
}
