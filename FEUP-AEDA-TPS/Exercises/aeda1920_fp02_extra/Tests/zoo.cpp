#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
    animais.push_back(a1);
}

string Zoo::getInformacao() const{
    ostringstream os;
    for (auto it = animais.begin(); it < animais.end(); it++){
        os << (*it)->getInformacao() << endl;
    }
    return os.str();
}

bool Zoo::animalJovem(string nomeA){
    for (auto it = animais.begin(); it < animais.end(); it++){
        if ((*it)->getNome() == nomeA && (*it)->eJovem())
            return true;
    }
    return false;
}

void Zoo::alocaVeterinarios(istream &isV){
    string nome;
    string codigo;
    int cod;

    //alocando veterinarios no vector veterinarios
    while (getline(isV, nome)){
        getline(isV, codigo);
        Veterinario* temp = new Veterinario(nome, stoi(codigo));
        veterinarios.push_back(temp);
    }

    //distribuir veterinarios uniformemente

    //numero de veterinarios
    size_t size = this->veterinarios.size();
    int vet_cont = 0;
    for (auto it = this->animais.begin(); it < this->animais.end(); it++){
        (*it)->setVet(veterinarios[vet_cont]);
        vet_cont ++;
        if (vet_cont >= size) vet_cont = 0;
    }

}

bool Zoo::operator < (Zoo& zoo2) const{
    int soma_1 = 0;
    int soma_2 = 0;

    for (auto it = this->animais.begin(); it < this->animais.end(); it++){
        soma_1 += (*it)->getIdade();
    }
    for (auto it = zoo2.animais.begin(); it < zoo2.animais.end(); it++){
        soma_2 += (*it)->getIdade();
    }

    return soma_1 < soma_2;
}

bool Zoo::removeVeterinario (string nomeV){
    //find veterinario position
    size_t position = -1;
    size_t f_position = -1;
    for (int i = 0; i< this->veterinarios.size(); i++){
        if (this->veterinarios[i]->getNome() == nomeV) {
            position = i;
            break;
        }
    }
    //se não tem veterinario com este nome
    if (position == -1) return false;

    if (position == this->numVeterinarios()-1) f_position = 0;
    else f_position = position+1;

    //any animal with this vet
    for (auto it = this->animais.begin(); it < this->animais.end(); it++){
        if ((*it)->getVetCod() == this->veterinarios[position]->getCod())
            (*it)->setVet(veterinarios[f_position]);
    }

    //erase vet
    veterinarios.erase(veterinarios.begin()+position, veterinarios.begin()+position+1);

    return true;
}