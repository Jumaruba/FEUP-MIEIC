
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */

Animal::Animal(string nome, int idade): nome(nome), idade(idade){
    if (maisJovem == -1) maisJovem = idade;
    else if(maisJovem > idade) maisJovem = idade;
}

Cao::Cao(string nome, int idade, string raca): Animal(nome,idade), raca(raca){}

Voador::Voador(int vmax, int amax): velocidade_max(vmax), altura_max(amax) {}

Morcego::Morcego(string nome, int idade, int vmax, int amax): Animal(nome,idade), Voador(vmax,amax) {}

string Animal::getNome() const {
	return nome;
}

int Animal::maisJovem = -1;

int Animal::getMaisJovem(){
    return maisJovem;
}

bool Cao::eJovem() const {
    return idade < 5;
}

bool Morcego::eJovem() const {
    return idade < 4;
}

string Animal::getInformacao() const {
    ostringstream os;

    os << nome << ", " << idade << vet->getInformacao();
    return os.str();
}

string Cao::getInformacao() const {
    ostringstream os;

    os << Animal::getInformacao() << ", " << raca;
    return os.str();
}

string Voador::getInformacao() const {
    ostringstream os;

    os << velocidade_max << ", " << altura_max;
    return os.str();
}

string Morcego::getInformacao() const {
    ostringstream os;

    os << Animal::getInformacao() << ", " << Voador::getInformacao();
    return os.str();
}

int Animal::getIdade() const {
    return idade;
}

void Animal::setVet(Veterinario *veter) {
    vet = veter;
}

int Animal::getVetCod() const {
    return vet->getCod();
}