#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//precisa definir o operator para fazer a inserção
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return this->getPalavra() < ps1.getPalavra();
}

//a inserção ocorre na root, logo precisamos fazer um vector em ordem decrescente
void Dicionario::lerDicionario(ifstream &fich)
{
    string palavra, sign;
    while (!fich.eof()){
        getline(fich, palavra);
        getline(fich, sign);
        PalavraSignificado p (palavra,sign);
        palavras.insert(p);
    }
     return;
}

//a alterar
string Dicionario::consulta(string palavra) const
{

    BSTItrIn<PalavraSignificado> p(palavras);
    while(!p.isAtEnd()){
        if (p.retrieve().getPalavra() == palavra)
            return p.retrieve().getSignificado();
        p.advance();
    }

    throw PalavraNaoExiste(this->getPalavras(), palavra);
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    BSTItrIn<PalavraSignificado> p(palavras);
    while (!p.isAtEnd()){
        if (p.retrieve().getPalavra() == palavra) {
            PalavraSignificado m = p.retrieve();
            palavras.remove(p.retrieve());
            m.setSignificado(significado);
            palavras.insert(m);
            return true;
        }
        p.advance();
    }
    PalavraSignificado m(palavra, significado);
    palavras.insert(m);
    return false;
}

//usar o iterator
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    while (!it.isAtEnd()){
        cout << it.retrieve().getPalavra() << endl;
        cout << it.retrieve().getSignificado() << endl;
        it.advance();
    }
    return;
}

