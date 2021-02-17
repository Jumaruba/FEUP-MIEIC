//
// Created by allanbs on 23/12/19.
//

#include <vector>
#include <string>
#include "../Header/Workshop.h"
using namespace std;

/**
 * @file Workshop.cpp
 * @brief It contains the implementation of the class Workshop
 */

Workshop::Workshop(string name,vector<string>& aux,int nani){
    this->name = name;
    brands.assign(aux.begin(),aux.end());
    unavailability = nani;
}

bool Workshop::operator<(const Workshop & w1) const{
    return unavailability > w1.get_unavailability();
}

bool Workshop::checkForBrand(string name)const {
    for(auto &brand : brands){
        if(brand == name) return true;
    }
    return false;
}
ostream& operator<<(ostream& out, Workshop w){
    string m;                                   //string with the brands
    for (auto const& i: w.brands) m+= i + " | ";
    out << left << setw(30) << w.name << setw(20)  << w.unavailability << m << endl;
    return out;
}

void headerWorkshop(){
    cout << left << setw(30) << "NAME" << setw(20)  << "AVAILABLE IN" << "BRANDS" << endl;
    cout << "===================================================================================================" << endl;
}
