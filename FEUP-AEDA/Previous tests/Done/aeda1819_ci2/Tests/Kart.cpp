#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <string>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

//Exercicio 1 a)
vector<CKart> CGrupo::ordenaKarts()
{

	vector<CKart> vord;
	for (int i = 0 ; i < pistasG.size(); i++ ){
	    for (int j = 0; j < pistasG[i].getFrotaActual().size(); j++){
	        vord.push_back(pistasG[i].getFrotaActual()[j]);
	    }
	}
	sort(vord.begin(), vord.end(), [](CKart x1, CKart x2){return x1.getNumero() < x2.getNumero();});

	return vord;

}

//Exercicio 1 b)
int CGrupo::numAvariados(int cilind)
{
    int total = 0;
    for (auto& pista: pistasG){
        for (auto& avariado: pista.getKartsAvariados()){
            if ((int)avariado.getCilindrada() == cilind) {
                total++;
            }
        }
    }
    return total;
}

//Exercicio 1 c)
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    int total = 0;
    for (CKart& karts : frotaKartsPista){
        if (cilind == (int)karts.getCilindrada() && !karts.getAvariado()) {
            kartsLinhaPartida.push(karts);
            total++;
        }
        if (total == numeroKarts) return true;
    }
    return false;
}

//Exercicio 1 d)
int CPista::inicioCorrida()
{
    int total = 0;
    while (!kartsLinhaPartida.empty()){
        CKart kart = kartsLinhaPartida.front();
        kartsEmProva.push_back(kart);
        kartsLinhaPartida.pop();
        total++;
    }
    return total;
}
