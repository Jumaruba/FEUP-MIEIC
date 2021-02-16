#include "agency.h"
#include "menu.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//CONSTRUCTORS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Agency::Agency(const string& name, const string& nif, const string& address, const string& website, const string& cliente, const string& pack) {
    this->name = name;                                  //agency's name;
    this->nif = stoi(nif);                              //agency's nif
    this->website = website;                            //agency's website
    this->address = address;                            //agency's address
    this->cliente = cliente;                            //file containing information about the clients
    this->pack = pack;                                  //file containing information about the packages

}

//GET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string Agency::getCliente() {                      //get clients name file 
    return cliente;
}

std::string Agency::getPack() {                         //get packages name file
    return pack;
}

