#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap)
{
    this->apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const
{
    int total = 0;
	for (auto it = apostas.begin(); it != apostas.end(); it++){
        auto iterator = it->getNumeros().find(num);
        total+= iterator != it->getNumeros().end() ? 1 : 0;
	}
	return total;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
	for (auto it = apostas.begin(); it != apostas.end(); it++){ //apostas da pessoa
	    int total = it->calculaCertos(sorteio);
	    if (total > 3) money.insert(*it);
	}
	return money;
}
