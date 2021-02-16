/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

Jogo::Jogo()
{
	this->criancas.clear();
}

Jogo::Jogo(list<Crianca>& lc2)
{
	this->criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
 	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return this->criancas;
}


string Jogo::escreve() const
{
	stringstream oss;
	list<Crianca>::const_iterator it = criancas.begin();
	list<Crianca>::const_iterator ite = criancas.end();
	while ( it != ite )
	{
		oss << it->escreve() << endl;
		it++;
	}
	return oss.str();
}


Crianca& Jogo::perdeJogo(string frase)
{
	int npal = numPalavras(frase)-1;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator ite = criancas.end();
	while (criancas.size()>1)
	{
		int nc = criancas.size();
		int p = npal%nc;
		for (int i=1; i<=p ; i++) {
			it ++;
			if (it == ite ) it =criancas.begin();
		}
		cout << "sai: " << it->escreve() << endl;
		it = criancas.erase(it);
		if (it == ite ) it =criancas.begin();
	}
	return *it;
}


list<Crianca>& Jogo::inverte()
{
	/*
	list<Crianca> l1;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator ite = criancas.end();
	while ( it != ite )
	{
		Crianca *c=new Crianca(*it);
		l1.push_front(*c);
		it ++;
	}
	criancas = l1;
	*/
	criancas.reverse();
	return this->criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> l1;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator ite = criancas.end();
	while ( it != ite )
	{
		if ( it->getIdade() > id )
		{
			l1.push_back(*it);
			it=criancas.erase(it);
		}
		else
			it++;
	}
	return l1;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	this->criancas = l1;
}


bool Jogo::operator==(Jogo& j2)
{
	if( this->criancas.size() != j2.criancas.size() ) return false;

	list<Crianca>::iterator ita = this->criancas.begin();
	list<Crianca>::iterator ite = this->criancas.end();
	list<Crianca>::iterator itb = j2.criancas.begin();

	for(; ita != ite; ita++, itb++){
		if( !((*ita) == (*itb)) ) return false;
	}
	return true;
}


list<Crianca> Jogo::baralha() const
{
	list<Crianca> buffer = this->criancas;
	list<Crianca> nova;

	int rPos;

	/* initialize random seed: */
	srand(time(NULL) );

	while( !buffer.empty() ){
		/* generate a random position: */
		rPos = rand() % buffer.size();
		list<Crianca>::iterator it = buffer.begin();
		for(int i = 0; i < rPos; i++, it++);
		nova.push_back(*it);
		buffer.erase(it);
	}

	return nova;
}
