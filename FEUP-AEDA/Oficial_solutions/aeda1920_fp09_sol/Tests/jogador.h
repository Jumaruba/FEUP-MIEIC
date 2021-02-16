#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "aposta.h"
#include <string>

using namespace std;

struct apostaHash
{
	int operator() (const Aposta & ap) const
	{
		return ap.somaNumeros();
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
		if ( ap1.tamanho() != ap2.tamanho() )
			return false;
			
		unsigned int n = ap1.calculaCertos(ap2.getNumeros());
		if ( n == ap1.tamanho() )
			return true;
		else
			return false;
	}
};



typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
