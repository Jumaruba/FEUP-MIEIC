#include "jogo.h"
#include <sstream>
#include <cmath>


//a alterar
ostream &operator << (ostream &os, Circulo &c1)
{
	return os;
}


//verificar com o professor
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo = Inicial(0, niv, pontos, estados);
}
BinaryTree<Circulo> Jogo::Inicial(int pos, int nivel, vector<int> &pontos, vector<bool> &estados){
    Circulo c(pontos[pos], estados[pos]);
    if (nivel == 0) return BinaryTree<Circulo>(c);
    BinaryTree<Circulo> esq = Inicial(2*pos+1, nivel-1, pontos, estados);
    BinaryTree<Circulo> dir = Inicial(2*pos+2, nivel-1, pontos, estados);
    return BinaryTree<Circulo> (c, esq, dir);
}
//a alterar
string Jogo::escreveJogo()
{
    string s;
    BTItrLevel<Circulo> it(jogo);
    while(!it.isAtEnd()){
        s+= to_string(it.retrieve().getPontuacao()) + "-";
        s+= it.retrieve().getEstado()? "true-": "false-";
        s+= to_string(it.retrieve().getNVisitas()) + "\n";
        it.advance();
    }
	return s;
}

//a alterar
int Jogo::jogada()
{
    BTItrLevel<Circulo> it(jogo);
    Circulo &root = it.retrieve();
    int pos = 0;
    int pos_anterior;
    int caminho = root.getEstado() ? 2: 1;
    int pontuacao = root.getPontuacao();
    root.mudaEstado();
    root.incVisitas();
    while(!it.isAtEnd()){
        pos_anterior = pos;
        pos = 2*pos + caminho;
        for (int i = 0; i < pos-pos_anterior; i++) {
            it.advance();
            if (it.isAtEnd()) return pontuacao;
        }
        Circulo & c = it.retrieve();
        caminho = c.getEstado() ? 2: 1;
        c.incVisitas();
        c.mudaEstado();
        pontuacao = c.getPontuacao();

    }
	return pontuacao;
}


//a alterar
int Jogo::maisVisitado()
{
    int visitas = -1;
    BTItrLevel<Circulo> it(jogo);
    it.advance();                       //nao queremos contar com a root
    while (!it.isAtEnd()){
        Circulo &c = it.retrieve();
        visitas = visitas > c.getNVisitas() ? visitas: c.getNVisitas();
        it.advance();
    }
	return visitas;
}

