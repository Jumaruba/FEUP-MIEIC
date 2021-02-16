#include "veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m ,int a): marca(mc), mes(m), ano(a) {};

Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc, m,a), combustivel(c), cilindrada(cil) {};

Automovel::Automovel(string mc, int m, int a, string c, int cil): Motorizado(mc,m,a,c,cil){};

Camiao::Camiao(string mc, int m, int a, string c,int cil, int cm): Motorizado(mc,m,a,c,cil), carga_maxima(cm){};

Bicicleta::Bicicleta(string mc, int m, int a, string t): Veiculo(mc,m,a), tipo(t) {};

string Veiculo::getMarca() const {
    return marca;
}

string Motorizado::getCombustivel() const {
    return combustivel;
}

int Veiculo::getAno() const {
    return ano;
}

int Veiculo::info() const {
    cout << "Marca: " << marca << endl << "Mes: " << mes << endl << "Ano: " << ano << endl;
    return 3;
}

int Motorizado::info() const {
    Veiculo::info();
    cout << "Combustivel:" << combustivel << endl << "Cilindradada: " << cilindrada << endl;
    return 5;
}

int Automovel::info() const {
    Motorizado::info();
    return 5;
}

int Camiao::info() const {
    Motorizado::info();
    cout << "Tipo: " << carga_maxima << endl;
    return 6;
}

int Bicicleta::info() const {
    Veiculo::info();
    cout << "Tipo: " << tipo << endl;
    return 4;
}


float Motorizado::calcImposto() const {
    if (combustivel == "gasolina"){
        if (cilindrada <=1000){
            if (ano > 1995) return 14.56;
            return 8.10;
        }

        if (1000<cilindrada && cilindrada<=1300){
            if (ano > 1995) return 29.06;
            return 14.56;
        }

        if (1300<cilindrada && cilindrada<=1750){
            if (ano > 1995) return 45.15;
            return 22.65;
        }

        if (1750<cilindrada && cilindrada<=2600){
            if (ano> 1995) return 113.98;
            return 54.89;
        }

        if (2600<cilindrada && cilindrada<=3500){
            if (ano > 1995) return 181.17;
            return 87.13;
        }

        if (cilindrada > 3500){
            if (ano > 1995) return 320.89;
            return 148.37;
        }
    }
    else{
        if (cilindrada <=1500){
            if (ano > 1995) return 14.56;
            return 8.10;
        }

        if (1500<cilindrada && cilindrada<=2000){
            if (ano > 1995) return 29.06;
            return 14.56;
        }

        if (2000<cilindrada && cilindrada<=3000){
            if (ano > 1995) return 45.15;
            return 22.65;
        }

        if (cilindrada > 3000){
            if (ano> 1995) return 113.98;
            return 54.89;
        }
    }
}

float Bicicleta::calcImposto() const {
    return 0;
}