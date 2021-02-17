//
// Created by allanbs on 15/10/19.
//
#include "../Header/TaxTable.h"
#include <string>
using namespace std;
/**
 * @file TaxTable.cpp
 * @brief Implementation of the class TaxTable responsable to handle the classes of the trucks
 */
TaxTable::TaxTable(istream &input) {
    string type;                    /**<Type of the truck**/
    string tax;                     /**<Value of the tax for this specific truck**/
    if(!input.eof())
    while(!input.eof()){
        getline(input,type);
        getline(input,tax);
        if(!type.empty() && !tax.empty()) table[type] = stod(tax);
    }
}
