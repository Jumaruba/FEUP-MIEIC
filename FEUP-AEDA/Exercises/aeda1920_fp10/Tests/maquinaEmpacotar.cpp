#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas){}

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


// a alterar
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
    int total = 0;
    for (auto it = objs.begin(); it != objs.end(); it++){
        if (it->getPeso() <= capacidadeCaixas){
            objetos.push(*it);
            objs.erase(it);
            it --;
            total++;
        }
    }
	return total;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	vector <Caixa> c;
	Caixa cx;
	bool tem = false;

	while(!caixas.empty()){
	    cx = caixas.top();
	    if (obj.getPeso() <= cx.getCargaLivre()){
	        caixas.pop();
	        //tem = true;
	        //break;
            for (int i = 0; i < c.size(); i++){
                caixas.push(c[i]);
            }
            return cx;
	    }
	    c.push_back(cx);
	    caixas.pop();
	}
	for (int i = 0; i < c.size(); i++){
	    caixas.push(c[i]);
	}
    return Caixa(capacidadeCaixas);
}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {
     vector<Objeto> v_obj;
     vector<Caixa> v_cx;
     int total = 0;
    //coloca todos os objetos num vector
    while(!objetos.empty()){
        Objeto obj = objetos.top();
        v_obj.push_back(obj);
        objetos.pop();
    }
    for (int i = 0; i < v_obj.size(); i++){
        Caixa cx = procuraCaixa(v_obj[i]);      //acha a caixa
        cx.addObjeto(v_obj[i]);                 //adiciona objeto a caixa
        for (int j = 0; j < v_cx.size(); j++){
            if (cx.getID() == v_cx[j].getID()) {    //verifica se esta caixa ja foi usada
                total --;
                break;
            }
        }
        total ++;
        v_cx.push_back(cx);
        caixas.push(cx);                            //coloca caixa de volta no vector
    }
    return total;
}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    ostringstream os;
    vector<Objeto> v_obj;
    HEAP_OBJS priority_obj = getObjetos();
    if (priority_obj.empty()) return "Nao ha objetos!\n";
    while(!priority_obj.empty()){
        Objeto obj = priority_obj.top();
        v_obj.push_back(obj);
        os << "O" << obj.getID() << ": " << obj.getPeso() << "\n";
        priority_obj.pop();
    }
	return os.str();
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa cx;
	unsigned int actual_max = 0;
	if (caixas.empty()) throw MaquinaSemCaixas();
	auto priority_cx = caixas;
	while(!priority_cx.empty()){
	    if (actual_max <= priority_cx.top().getSize()){
	        cx = priority_cx.top();
	        actual_max = cx.getSize();
	    }
	    priority_cx.pop();
	}
	return cx;
}



