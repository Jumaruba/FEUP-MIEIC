#include "frota.h"
#include <string>

using namespace std;


int Frota::numVeiculos() const{
    return veiculos.size();
}

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::menorAno() const{
    int menor = 0;
    int numV = numVeiculos();
    if (numV!= 0) menor = veiculos[0]->getAno();
    for (int i = 1; i< numV; i++){
        menor = menor< veiculos[i]->getAno() ? menor: veiculos[i]->getAno();
    }
    return menor;
}

ostream & operator<<(ostream & o, const Frota & f){
    for (int i = 0; i < f.veiculos.size(); i++){
        f.veiculos[i]->info();
    }
    return o;
}

bool Veiculo::operator < (const Veiculo & v) const{
    if (this->ano < v.ano) return true;
    else if (this-> ano > v.ano) return false;
    else  return this->mes < v.mes;


}

vector<Veiculo *> Frota::operator()(int anoM) {
    vector <Veiculo *> temp;
    for (int i = 0 ; i< veiculos.size(); i++){
        if (veiculos[i]->getAno() == anoM) temp.push_back(veiculos[i]);
    }
    return temp;
}

float Frota::totalImposto() const{
    float soma = 0;
    for (int i = 0 ; i< veiculos.size(); i ++){
        soma+= veiculos[i]->calcImposto();
    }
    return soma;
}