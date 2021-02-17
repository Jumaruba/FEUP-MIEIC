//
// Created by maruba on 23/12/19.
//

#include "../Header/Motorista.h"

using namespace std;

/**
 * @file Motorista.cpp
 * @brief It contains the implementation of the file Motorista.h
 */

float Motorista::getHours() const{
    return hours;
}

std::string Motorista::getName() const{
    return name;
}

long long int Motorista::getNif() const{
    return nif;
}

bool Motorista::operator<(const Motorista & driver) const{
    if( this->getHours() < driver.getHours()) return true;
    else if(this->getHours() > driver.getHours()) return false;
    else if(this->getNif() < driver.getNif()) return true;
    else if (this->getNif() > driver.getNif()) return false;
    return false;
}

bool Motorista::operator==(const Motorista & driver) const{
    return (this->nif == driver.getNif());
}

bool Motorista::setHours(const float & h) {
    //The number of hours cannot be higher than 24, neither lower than 0
    if(h > 24 || h<0) return false;
    this->hours= h;
    return true;
}

void Motorista::setName(const string& name){
    this->name = name;
}

ostream &operator<<(ostream &out,const Motorista& w){
    out << left << setw(30) << w.getName() << setw(20) << w.getNif() << w.getHours() << endl;
    return out;
}
vector<Motorista> Workers::getBST() {
    //Push back element by element in the vector temp
    BSTItrIn<Motorista> it(BST_Workers);
    vector<Motorista> temp;
    while (!it.isAtEnd()){
        temp.push_back(it.retrieve());
        it.advance();
    }
    return temp;
}

bool Workers::addMotorista(const Motorista& new_motorista) {
    //Before add the Motorista, checks if there is already this Motorista in the BST
    BSTItrLevel<Motorista> it(BST_Workers);
    while(!it.isAtEnd()){
        if (it.retrieve() == new_motorista) return false;
        it.advance();
    }

    return this->BST_Workers.insert(new_motorista);

}

void Workers::printBST(int n) {
    int counter = 0;
    BSTItrIn<Motorista> it(BST_Workers);
    while(!it.isAtEnd()){
        counter ++;
        cout << it.retrieve();
        it.advance();
        if (counter == n) break;
    }

}

void Workers::printBST_reversed(int n){
    int counter = 0;
    vector<Motorista> m;
    BST_Workers.getReversedTree(m);
    for (auto const& it: m){
        counter ++;
        cout << it;
        if (counter == n) break;
    }
}

void Workers::printBST_alphabetic(int n) {
    //The BST cannnot help with the alphabetic order
    //So the BST is passed to a vector and this one is sorted by the name
    vector<Motorista> m;
    int counter = 0;
    m = this->getBST();
    sort(m.begin(),m.end(), [](const Motorista& worker1, const Motorista& worker2){return worker1.getName() < worker2.getName();});
    for (const auto & i: m){
        counter ++;
        cout << i;
        if (counter == n) break;
    }
}

void Workers::readMotorista() {
    //Read the Workers from the data base on Ficheiros
    string name, aux;
    fstream file;
    file.open("../AEDA_Proj1/Ficheiros/Motoristas");
    while(!file.eof()){
        getline(file, name);
        if (name.empty()) break;
        getline(file, aux);
        long long int nif = stoi(aux);
        getline(file, aux);
        float hours = stof(aux);

        BST_Workers.insert(Motorista(name, nif, hours));
    }
    file.close();
}

Motorista Workers::check_nif(long long Nif) const{
    BSTItrLevel<Motorista> it(BST_Workers);
    while(!it.isAtEnd()){
        if (it.retrieve().getNif() == Nif) return it.retrieve();
        it.advance();
    }
    throw NoWorker();
}

bool Workers::removeMotorista(const Motorista &motorista) {
    BSTItrIn<Motorista> it (BST_Workers);
    while(!it.isAtEnd()){
        if (motorista == it.retrieve()) return BST_Workers.remove(it.retrieve());
        it.advance();
    }
    return false;
}

void Workers::rewrite_file() {
    ofstream file ("../AEDA_Proj1/Ficheiros/Motoristas");
    BSTItrLevel<Motorista> it (BST_Workers);
    while(!it.isAtEnd()){
        file<< it.retrieve().getName() << endl
            << it.retrieve().getNif() << endl
            << it.retrieve().getHours();
        it.advance();
        if (!it.isAtEnd()) file << endl;


    }
    file.close();
}

bool Workers::setName(Motorista &motorista, const string& name) {
    BSTItrIn<Motorista> it (BST_Workers);
    while(!it.isAtEnd()){
        if (motorista == it.retrieve()) {
            motorista = it.retrieve();
            BST_Workers.remove(it.retrieve());
            motorista.setName(name);
            BST_Workers.insert(motorista);
            return true;
        }
        it.advance();
    }
    return false;
}

bool Workers::allocateMotorista(float tempo) {
    Motorista temp;
    BSTItrIn<Motorista> it (BST_Workers);
    while(!it.isAtEnd()){
        if (it.retrieve().getHours() + tempo < 24){
            temp = it.retrieve();
            cout << "Worker: " << temp.getName() << endl;
            BST_Workers.remove(it.retrieve());
            temp.setHours(temp.getHours() + tempo);
            BST_Workers.insert(temp);
            rewrite_file();
            return true;
        }
        it.advance();
    }
    return false;
}

void Workers::resetHours() {
    vector<Motorista> m = getBST();
    BST_Workers.makeEmpty();
    for (auto & it: m){
        it.setHours(0);
        BST_Workers.insert(it);
    }
    this->rewrite_file();
}