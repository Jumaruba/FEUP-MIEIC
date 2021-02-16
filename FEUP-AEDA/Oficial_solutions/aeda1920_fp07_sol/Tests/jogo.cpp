#include "jogo.h"
#include <sstream>


ostream &operator << (ostream &os, Circulo &c1)
{
	string estadoStr;
	if (c1.estado) estadoStr="true"; else estadoStr="false";
	os << c1.pontuacao << "-" << estadoStr  << "-" << c1.nVisitas << endl;
	return os;
}


BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados)
{
	Circulo c1(pontos[pos],estados[pos]);
	if (niv==0) return BinaryTree<Circulo>(c1);
	BinaryTree<Circulo> filhoEsq=iniciaJogo(2 * pos + 1, niv - 1, pontos, estados);
	BinaryTree<Circulo> filhoDir=iniciaJogo(2 * pos + 2, niv - 1, pontos, estados);
	return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}


Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
	jogo=iniciaJogo(0,niv,pontos,estados);
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(jogo);
	stringstream jogoStr("");
	while (!it.isAtEnd()) {
		jogoStr << it.retrieve();
		it.advance();
	}
	return jogoStr.str();
}


int Jogo::jogada()
{
	int pos=1; int pontos=-1;
	BTItrLevel<Circulo> it(jogo);
	if (it.isAtEnd()) return pontos;
	while (true) {
		Circulo &c1=it.retrieve();
		bool estado=c1.getEstado();
		int n;
		if (estado==false) n=pos;
		else n=pos+1;
		c1.mudaEstado();
		c1.incNVisitas();
		pontos=c1.getPontuacao();
		int i=0;
		while(i<n && !it.isAtEnd()) {
			it.advance();        // avanca p/ filho esquerdo ou direito
			i++;
		}
		if (!it.isAtEnd()) pos+=n;
		else break;
	}
	return pontos;
}



int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(jogo);
	if (it.isAtEnd()) return -1;
	int maisV=-1;
	it.advance();
	while (!it.isAtEnd()) {
		Circulo c1=it.retrieve();
		int nV=c1.getNVisitas();
		if (nV>maisV) maisV=nV;
		it.advance();
	}
	return maisV;
}

