#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	vector<Objeto>::iterator it = objs.begin();
	while(it != objs.end()) {
		if( (*it).getPeso() <= capacidadeCaixas ) {
			objetos.push(*it);
			it = objs.erase(it);
		}
		else it++;
	}
	return objetos.size();
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	//estrutura temporaria para guardar caixas retiradas da fila
	vector<Caixa> temp;

	//procura caixa mais cheia, ainda com espaco para obj
	while ( !caixas.empty() )
	{
		Caixa cx = caixas.top();
		caixas.pop();
		if ( cx.getCargaLivre() >= obj.getPeso() ) {

			for (unsigned i=0; i<temp.size(); i++) //repoe na fila de caixas as caixas retiradas da frente.
		        caixas.push(temp[i]);
			return cx;
		}
		else temp.push_back(cx); //coloca as caixas nao utilizadas num vetor temporario
	}
	for (unsigned i=0; i<temp.size(); i++) //repoe as caixas nao utilizadas de volta, caso nenhuma sirva
		caixas.push(temp[i]);

    return Caixa(capacidadeCaixas); //e retorna uma nova caixa
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	while ( !objetos.empty() )
	{
		Objeto o1 = objetos.top();
		objetos.pop();
		Caixa c1 = procuraCaixa(o1);
		c1.addObjeto(o1);
		caixas.push(c1);
		cout << "Objeto de peso " << o1.getPeso() << " -> caixa " << c1.getID() << endl;
	}
	return caixas.size();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	stringstream ss;
	if( objetos.empty() ) ss << "Nao ha objetos!" << endl;
	else {
		HEAP_OBJS buffer = objetos;
		while( !buffer.empty() ) {
			Objeto obj = buffer.top();
			buffer.pop();
			ss << obj << endl;
		}
	}
	return ss.str();
}


Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	if( caixas.empty() ) throw MaquinaSemCaixas();
	else {
		HEAP_CAIXAS buffer = caixas;
		Caixa caixaMais = buffer.top();
		buffer.pop();
		while( !buffer.empty() ) {
			if( caixaMais.getSize() < buffer.top().getSize() ) caixaMais = buffer.top();
			buffer.pop();
		}
		return caixaMais;
	}
}



