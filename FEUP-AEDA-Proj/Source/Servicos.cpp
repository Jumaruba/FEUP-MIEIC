//
// Created by maruba on 14/10/19.
//

#include "../Header/Servicos.h"

/**
 * @file Servicos.cpp
 * @brief Implementation of Servicos class responsable for handle the services (individualy)
 */

Servicos::Servicos() {
    id = -1;
}

Servicos::Servicos(const Local &Departure, const Local &Arrival, const unsigned int &Id,const string& Tipo, const int & Carga, const string& Condition) : id(Id), departure(Departure),

                                                                                         arrival(Arrival), type(Tipo), carga(Carga), condition(Condition) {
    profit = 0;
    cal_profitTime();
};


void Servicos::cal_profitTime() {
    profit += cal_tempo() * tax_condition;                                //get the base profit
    for (auto it = camioes.begin(); it < camioes.end(); it++)   //price of each truck
        profit += (*it)-> cal_preco();
}

double Servicos::cal_tempo() {
    double velocity = 60;
    double multiplier = PI / 180.0;
    double x1 = departure.get_Coordx() * multiplier;
    double x2 = arrival.get_Coordx() * multiplier;              // get the coordinates of the locals (arrival and departure)
    double y1 = departure.get_Coordy() * multiplier;
    double y2 = arrival.get_Coordy() * multiplier;
    double dy = y2 - y1;
    double r = 6378.137; //radius of the earth

    double distance = acos(sin(x1)*sin(x2)+cos(x1)*cos(x2)*cos(dy))*r;
    
    // it calculates the distance between the two points
    double time = distance/velocity;
    return time;                           //calculates the time in hours
}

int Servicos::num_camiao(){
    return camioes.size(); 
}

ostream &operator<<(ostream &os, Servicos servico) {
    os<<fixed<<setprecision(2);
    cout.fill();
    os << left << setw(10) << servico.id
               << setw(15) << servico.type
               << setw(10) << servico.cal_tempo()
               << setw(30) << servico.get_departure()
               << setw(30) << servico.get_arrival()
               << setw(15) << servico.num_camiao()
               << setw(15) << servico.get_profit()
               << setw(15) << servico.carga 
               << servico.condition <<endl;
    return os;
}


unsigned int Servicos::get_id() const{
    return id;
}

double Servicos::get_profit() const {
    return profit;
}


string Servicos::get_departure() const{
    return departure.getName();
}


string Servicos::get_arrival() const{
    return arrival.getName();
}

string Servicos::get_tipo() const{
    return type;
}


int Servicos::get_carga() const {
    return carga;
}


string Servicos::get_camioes_id() const {
    string s;

    for (int i = 0; i< camioes.size()-1; i++)
        s += to_string(camioes[i]->getId())+" ";
    
    //The last element must not contain a space, else we will get an error in the next exectuion
    s += to_string(camioes[camioes.size()-1]->getId());
    return s;
}

string Servicos::get_condition(){
    return condition; 
}

void Servicos::addCamiao(Camiao *camiao) {
    camioes.push_back(camiao);
    profit += camiao->cal_preco();
    camiao->addedToService();                       //increasing the truck totalProfit
}

//------------------------------------------------------------------------------------

bool Compare_servico_profit(const Servicos* s, const Servicos* s1){
    if (s->get_profit() < s1->get_profit()) return false;
    else if (s1->get_profit() < s->get_profit()) return true;
    else if(s->get_id() < s1->get_id()) return true;
    return false;
}

bool Compare_servico_Leastprofit(const Servicos *s, const Servicos *s1){
    if (s->get_profit() < s1->get_profit()) return true;
    else if (s1->get_profit() < s->get_profit()) return false;
    else if(s->get_id() < s1->get_id()) return true;
    return false;
}



