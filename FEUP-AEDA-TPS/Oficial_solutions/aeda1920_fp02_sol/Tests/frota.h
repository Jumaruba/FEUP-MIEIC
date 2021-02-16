#ifndef FROTA_H_
#define FROTA_H_

#include <vector>
#include "veiculo.h"
using namespace std;

class Frota {
	vector<Veiculo *> veiculos;
public:
	int numVeiculos() const;
	void adicionaVeiculo(Veiculo *v1);
	int menorAno() const;
	float totalImposto() const;
	vector<Veiculo *> operator() (int a) const;
	friend ostream & operator<<(ostream & o, const Frota & f);
};

#endif /*FROTA_H_*/
