#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{

    return (numeros.find(num) != numeros.end());
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    int total = 0;
    auto it = valores.begin();
    while (total <n){
        if (numeros.find(*it) == numeros.end()) {
            numeros.insert(*it);
            total++;
        }
        it++;
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    int total = 0;
    for (auto it = sorteio.begin(); it != sorteio.end(); it++){
        if (this->contem(*it)) total++;
    }
    return total;
}





