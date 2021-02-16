//
// Created by maruba on 13-04-2019.
//

#include "packs.h"
#include "clients.h"
#include "data.h"
#include "aux.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

extern std::vector<Packs> p;
extern vector<Clients> c;

//CONSTRUCTORS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Packs::Packs() {
    this->id = 0;
    this->local = "0";
    this->price = 0;
    this->maxPeople = 0;
    this->reserved = 0;
}

//----------------------------------------------------------------------------------------------------------------------
Packs::Packs(string id, string local, string dBegin, string dEnd, string price,
             string maxPeople, string reserved) {

    this->id = stoi(id);
    this->local = local;
    this->dBegin.setDate(dBegin);
    this->dEnd.setDate(dEnd);
    this->price = stof(price);
    this->maxPeople = stoi(maxPeople);
    this->reserved = stoi(reserved);

}

//SET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
function: checks if there's already the id and if there isn't set
@param id: id given by the user
@param again: if there's already an id then set to "Y"
*/
void Packs::setId() {
    int id;
    string again;

    do { //Keep checking for input until a valid one is given by the user
        id = isNum(int(0));
        if (id != 0) {
            if (repeatId(id)) { //case theres already a package with given ID
                cout << "There is already a pack with this id. Try again: " << endl;
                again = "Y";
            } else {
                this->id = id;
                again = "F";
            }
        }
        else
            again = "F";//in case the clieetn cancelled the operation
    } while (again == "Y");

}

void Packs::setIdSimple(int num){ //Set id
    this->id = num;
}


void Packs::setLocal() { //set locale,if given input is different than "0"
    string local;
    getline(cin, local);
    if (local != "0")//in case the client wants to cancel the operation
        this->local = local;


}


void Packs::setPrice() { //set package price if given price != 0
    float num = isNum(float(0.1));
    if (num!= 0)//num==0->cancelled operation
        this->price = num;


}

void Packs::setMaxPeople() { //Set max number of people that can buy a given package

    int maxPeople = isNum(int(0));
    if (maxPeople != 0)//maxpeople==0->cancelled operation
        this->maxPeople = maxPeople;

}

void Packs::setReserved() { //update how many were reserved
    this->reserved = 0;
    for (auto client: c){
        for (auto m: client.getVectorPacks())
            if (m== id)
                this->reserved+= client.getPeople();
    }
}


//GET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int Packs::getId() { //returns ID
    return id;
}


string Packs::getLocal() { //returns local
    return local;
}


float Packs::getPrice() { //returns price
    return price;
}


int Packs::getMaxPeople() { //returns max number of people in the package
    return maxPeople;
}

/*
function:places into vector
@param v vector of places
returns vector with places in string format
*/
vector<string> Packs::getPlacesVec(){
    vector<string> v;
    split(v, this->local, ',', '-');
    return v;

}

int Packs::getReserved(){
    return this->reserved;
}

//OTHERS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
function: it checks if there's already a pack with the id given
@param id: id to be searched and compared
return if id is already in a package or not
*/

bool Packs::repeatId(int id) {
    if (id != 0) {                                   //the id can't be equal to 0
        for (int i = 0; i < p.size(); i++) {        //it searchs for the id
            if (p[i].id == id)
                return true;                        //if it's been found, return true
        }
    } else
        cerr << "Not possible to atribute id = 0" << endl;
    return false;                                   //the given id doesn't exist yet
}

//----------------------------------------------------------------------------------------------------------------------

void Packs::headInfoPack() { //format table to visualize information
    cout.fill(' ');
    cout << left << setw(6) << "| ID"
         << setw(70) << "| LOCAL"
         << setw(15) << "| BEGIN DATE"
         << setw(15) << "| END DATE"
         << setw(15) << "| PRICE"
         << setw(15) << "| NUM_RESERVED"
         << "| MAX_PEOPLE" << endl;
    cout
            << "------------------------------------------------------------------------------------------------------------------------------------------------------------------"
            << endl;

};


//----------------------------------------------------------------------------------------------------------------------

void Packs::visualizePack() {  // print any pack info
    cout.fill(' ');

    cout << left << '|' << setw(5) << this->id
         << '|' << setw(69) << this->local
         << '|' << setw(14) << dBegin.getDate()
         << '|' << setw(14) << dEnd.getDate()
         << '|' << setw(14) << this->price
         << '|' << setw(14) << this->reserved
         << '|' << this->maxPeople << endl;

}  //print any pack info

//----------------------------------------------------------------------------------------------------------------------
/*
funtion: search for places within a pack
@param destines string with pack's places
@param auxplace lower case version of destines
@param aux auxiliar string
return whether or not a place exists in a given package
*/

bool Packs::searchPlace(const string &place) {
    string destines = this->getLocal();
    string auxplace = maiusculo(place);     //getting a lower case version of place
    string aux;                             // a string the will extract the substring

    for (int i = 0; i < destines.size(); i++) {
        if (!isalpha(destines[i]) && destines[i] != ' ') {
            trim(aux); // we are removing unnecessary spaces;
            if (auxplace == aux)
                return true;
            aux = "";
        } else
            aux.push_back(toupper(destines[i]));
    }
    if (place == aux)
        return true;
    return false;
}  //checks if a place is at a pack

//----------------------------------------------------------------------------------------------------------------------

/*
function: overload operator to write a class in a file
*/
 ostream& operator<<(ostream& out ,const Packs& p){
        out    << p.id << '\n'
               << p.local << '\n'
               << p.dBegin.getDate() << '\n'
               << p.dEnd.getDate() << '\n'
               << p.price << '\n'
               << p.maxPeople <<'\n'
               << p.reserved;
}
