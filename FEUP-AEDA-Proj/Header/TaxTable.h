//
// Created by allanbs on 15/10/19.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;
#ifndef AEDA_PROJ1_TAXTABLE_H
#define AEDA_PROJ1_TAXTABLE_H

/**
 * @file TaxTable.h
 * @brief Declarations of the class TaxTable responsable to handle the classes of the trucks
 */
/**
 * @brief Class to store taxes read from tax file
 */
class TaxTable{
public:
    map<string,double> table;       /**<map with each tax**/
public:
    /**
     * @brief Constructor for TaxTable Class
     * @param input Input stream to read from tax file
     */
    TaxTable(istream& input);
    /**
     *
     * @return return map size
     */
    int tableSize() const {return table.size();};

};




































#endif //AEDA_PROJ1_TAXTABLE_H
