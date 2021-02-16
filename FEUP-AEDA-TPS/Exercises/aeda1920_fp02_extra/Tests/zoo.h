#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	int numAnimais() const;
	int numVeterinarios() const;
    void adicionaAnimal(Animal *a1);
    string getInformacao() const;
    bool animalJovem(string nomeA);
    void alocaVeterinarios(istream &isV);
    bool operator < (Zoo& zoo2) const;
    bool removeVeterinario (string nomeV);
	//completar
};


#endif /* ZOO_H_ */
