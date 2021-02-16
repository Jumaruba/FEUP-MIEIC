#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <sstream>
#include "clients.h"
#include "aux.h"
#include "menu.h"
#include "packs.h"


using namespace std;

extern vector<Clients> c;
extern vector<Packs> p;

//CONSTRUCTORS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Default constructor 
Clients::Clients() {
    this->name = "NAME";
    this->nif = 0000000000;
    this->nPeople = 0;
    this->address = {"STREET", "DOOR NUMBER", "FLOOR", "ZIP", "CITY"};
    this->listPacks = {0};
    this->nPurchased = 0;
    this->profit = 0;
}


Clients::Clients(string name, string nif, string nPeople, string address, string listPacks, string profit) {
    this->name = name;
    this->nif = stoi(nif);
    this->nPeople = stoi(nPeople);
    split(this->address, address, '/');
    splitInt(this->listPacks, listPacks, ';');
    this->nPurchased = this->listPacks.size();
    this->profit = stof(profit);


}

//SET++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
function: set name

name: input
*/

void Clients::setName() {
    string name; //aux string to get the input
    getline(cin, name);
    if (name != "0")                    //case the user wanna to cancel the operation 
        this->name = name;
}

//----------------------------------------------------------------------------------------------------------------------

/*
function: set a new nif

nif: input 
again: true if incorrect input or repeated nif
position: -1 if there is not a client if the same nif
*/

void Clients::setNif() {
    int position;
    bool again = true;
    do {
        int nif = isNum(int(0));                    //set the nif variable and checks if it's valid
        if (nif != 0) {                             //case the user wanna to cancel the operation 
            position = searchNif_bool(nif);
            if (position == -1) {                   
                this->nif = nif;
                again = false;
            } else
                cout << "There's already a client with this nif. Try again: ";
        }
        else
            again = false;
    }while (again);

}

//----------------------------------------------------------------------------------------------------------------------

/*
function: set the number of people at client's family

nPeople = input
*/

void Clients::setPeople() {
    int nPeople;

    nPeople = isNum(int(0));
    if (nPeople != 0)                       //case the user wanna to cancel the operation 
        this->nPeople = nPeople;

}

//----------------------------------------------------------------------------------------------------------------------

void Clients::setAddress() {
    auto aux = addAddress();
    bool dont = false;
    for (int i = 0; i< aux.size(); i++){
        if (aux[i] == "0"){                 //case the user wanna to cancel the operation 
            dont = true;
            break;
        }
    }
    if (!dont)
        this->address = aux;     //user types the new address

}

//----------------------------------------------------------------------------------------------------------------------

/*
function: set a list of number of packages

pack: package id that is being purchased 
cancel: true if the any input == 0
*/

void Clients::setListPacks() {
    int pack;
    bool cancel = false;
    this->listPacks.clear();
        cout << "Type the number of packages (EXIT -0): ";
        this->setPurchased();			//change the number of packages purchased to this client
        if (this->nPurchased == 0)      //case the user wanna to cancel the operation 
            cancel = true;
        cout << "Type the new package list separated by spaces or ENTER (EXIT -0): ";
        cin.ignore();

        for(int i = 0; i< this->nPurchased; i++){
            int thereis = true;
            do {
                if(!thereis)
                    cout << "There is no package if ID " << pack << ". Try again: ";
                pack = isNum(int(0));        // get a valid int for pack;
                thereis = searchPack(pack);
            }while(thereis);

            if (pack == 0)              //case the user wanna to cancel the operation 
            {
                cancel = true;
                break;
            }
            this->listPacks.push_back(pack);    //input the list o packages

        }
        if (cancel)                             //case the user wanna to cancel the operation 
            this->listPacks = {0};              //default listPacks

}

//----------------------------------------------------------------------------------------------------------------------

void Clients::appendListPacks(int pack) {

    this->listPacks.push_back(pack);    //input the list o packages

}

//----------------------------------------------------------------------------------------------------------------------

void Clients::setPurchased() {
    this -> nPurchased = isNum(int(0));
}
//----------------------------------------------------------------------------------------------------------------------

//updates the profit
void Clients::setProfit() {
    this->profit = 0;
    for (auto client: this->listPacks){
        for (auto packs: p){
            if(packs.getId() == client)
                this->profit += packs.getPrice();
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------

/*
function: set all the address components of a client

final: final address vector to be returned and stored 
aux: information to be read
*/

vector<string> Clients::addAddress() {  //add a new address for the client
    string aux;     			// string that will set each element
    vector<string> final;  		// final vector to be returned
    cin.ignore();
    for (int i = 0; i < 5; i++) {
        if (i == 0)
            cout << "Street (EXIT -0): ";  	//in the first interaction asks the street
        else if (i == 1)
            cout << "Door number (EXIT -0): ";  	//in the second interaction asks the door number
        else if (i == 2)
            cout << "Floor number (EXIT -0): "; 	//in the third interaction asks the floor number
        else if (i == 3)
            cout << "Zip code (EXIT -0): ";  	// in the fourth asks the zip code
        else if (i == 4)     		// at the 5º operation, asks the city
            cout << "City (EXIT -0): ";

        getline(cin, aux); 		//set the user input
        trim(aux);          		//remove all lateral spaces
        final.push_back(aux);   	// add the information to the client
        if (aux == "0") {           //case the user wanna to cancel the operation 
            break;
        }
    }
    return final;
}


//GET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string Clients::getName() {
    return name;
}


int Clients::getNif() {
    return nif;
}


int Clients::getPeople() {
    return nPeople;
}


string Clients::getAddress() {
    return concatenate(address);
}

vector<string> Clients::getVectorAddress(){
    return address;
}

//get a string list os packs in the format: "1; 2; 3"
string Clients::getListPacks() {    
    return concatenateInt(listPacks);
}


std::vector<int> Clients::getVectorPacks(){
    return this->listPacks;
}


int Clients::getPurchased() {
    return nPurchased;
}

float Clients::getProfit(){
    return this->profit;
}


//VISUALIZATION+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Clients::visualizeClient() {
    cout.fill(' ');

    cout << left << "|" << setw(39) << this->getName()   //show client information
         << "|" << setw(14) << this->getNif()
         << "|" << setw(14) << this->getPeople()
         << "|" << setw(54) << this->getAddress()
         << "|" << setw(19) << this->getListPacks()
         << "|" << setw(19) << this->getPurchased()
         << "|" << this->getProfit() << endl;
}

void Clients::headInfoClient() {
    cout.fill(' ');

    cout << left << setw(40) << "| NAME"        //print formated information
         << setw(15) << "| NIF"
         << setw(15) << "| NUMPEOPLE"
         << setw(55) << "| ADDRESS"
         << setw(20) << "| LISTPACKS"
         << setw(20) << "| NUMPACKS"
         << "| TOTAL SPENT" << endl;
    cout
            << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
            << endl;
}

//OTHERS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
function: search if the pack is available or if it's exist

pack: pack id to be searched 
*/

bool Clients::searchPack(const int& pack){

    for (int i = 0; i < this->listPacks.size(); i++){
        if (this->listPacks[i] == pack)
            return true;
    }
        return false;

}

//----------------------------------------------------------------------------------------------------------------------

/*
function: store a class in a specific format in a stream
*/

ostream& operator<<(ostream& out, const Clients& c ){
    out  << c.name << '\n'
         << c.nif << '\n'
         << c.nPeople << '\n'
         << concatenate(c.address) << '\n'
         << concatenateInt(c.listPacks) << '\n'
         << c.profit;

}
