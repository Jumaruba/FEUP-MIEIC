#include "caixa.h"
#include <sstream>
#include <vector>


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;

// a alterar
bool Objeto::operator<(const Objeto& o1) const {
    return this->getPeso() < o1.getPeso();
}
// a alterar
bool Caixa::operator<(const Caixa& c1) const {
	return this->getCargaLivre() > c1.getCargaLivre();
}

// a alterar
string Caixa::imprimeConteudo() const {
    ostringstream os;
    stack<Objeto> stk = objetos;
    //caso esteja vazia
    if(objetos.empty()) return "Caixa " + to_string(this->getID()) + " vazia!\n";
    //caso não esteja  vazia
    os << "C" << getID() << "[ ";
    while(!stk.empty()){
        os << stk.top() << " ";
        stk.pop();
    }
    os << "]";
	return os.str();
}



