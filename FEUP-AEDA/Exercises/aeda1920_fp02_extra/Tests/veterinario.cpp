
#include "veterinario.h"
#include <sstream>
using namespace std;

Veterinario::Veterinario(string nome, int cod): nome(nome), codOrdem(cod) {}

string Veterinario::getNome() const {
	return nome;
}

string Veterinario::getInformacao() const {
    ostringstream os;
    if (this != NULL)
        os << ", " <<nome << ", " << codOrdem;

    return os.str();

}

int Veterinario::getCod() const {
    return codOrdem;
}