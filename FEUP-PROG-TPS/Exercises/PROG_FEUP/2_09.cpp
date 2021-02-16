#include <iostream>
#include <iomanip>

using namespace std;

/*
int main() {  //letter a
    int x, contador = 0, maior, menor, soma = 0;

    cin >> x;
    maior = x;
    menor = x;
    while (x != 0) {
        contador++;
        soma += x;
        if (x > maior)
            maior = x;
        if (x < menor)
            menor = x;
        cin >> x;
    }
    cout << fixed << setprecision(3);
    cout << "Menor número: " << menor << endl;
    cout << "Maior número: " << maior << endl;
    cout << "Soma dos números: " << soma << endl;
    cout << "Média dos números: " << (float)(soma / contador) << endl;
}*/
/*

int main(){ //letter b
    int comp, x, maior, menor, soma;
    cout << "Digite o comprimento da sequência: ";
    cin >> comp;
    cout << "Digite os número: ";
    cin >> x;
    maior = x;
    menor = x;
    soma = x;
    for (int i = 1; i< comp; i++){
        cin >> x;
        soma += x;
        if (x > maior)
            maior = x;
        if (x < menor)
            menor = x;
    }

    cout << fixed << setprecision(2);
    cout << "Menor número: " << menor << endl;
    cout << "Maior número: " << maior << endl;
    cout << "Soma dos números: " << soma << endl;
    cout << "Média dos números: " << (float)soma/comp << endl;
}*/

int main(){
    int x, contador = 0, maior, menor, soma = 0;

    cin >> x;
    maior = x;
    menor = x;
    while(true){
        contador++;
        soma += x;
        if (x > maior)
            maior = x;
        if (x < menor)
            menor = x;
        cout << fixed << setprecision(3);
        cout << "----------------------------------" << endl;
        cout << "Menor número: " << menor << endl;
        cout << "Maior número: " << maior << endl;
        cout << "Soma dos números: " << soma << endl;
        cout << "Média dos números: " << (float)soma / contador << endl;
        cout << "----------------------------------" << endl;
        cout << "Pressione CTRL+Z para parar. Se não, digite o próximo número: ";
        cin >> x;
    }
}