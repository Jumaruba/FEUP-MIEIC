//
// Created by allanbs on 23/12/19.
//

#ifndef AEDA_PROJ1_WORKSHOP_H
#define AEDA_PROJ1_WORKSHOP_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

/**
 * @file Workshop.h
 * @brief It contains the Class Workshop definition
 */
using namespace std;


class Workshop{
private:
    string name;
    vector<string> brands;
    int unavailability;
public:
    /**
     * @brief Default constructor
     */
    explicit Workshop(string name) : name(name){};
    /**
     * Constructor for the Workshop
     * @param name The name of the workshop
     * @param aux vector containing the brands in which this workshops specializes in
     * @param nani Initial unavailability
     */
    Workshop(string name,vector<string> &aux,int nani);
    /**
     * @brief Gets the unavailability of the workshop
     * @return int
     */
    int get_unavailability() const {return unavailability;};
    /**
     * @brief Gets the Workshop's name
     * @return string
     */
    string getName() const{return name;};
    /**
     * @brief Gets the vector containing brands
     * @return vector of strings(brands)
     */
    vector<string> getBrands()const{return brands;};
    /**
     * @brief Checks if this Workshop contains given brand
     * @param name brand to check for
     * @return int
     */
    bool checkForBrand(string name)const;
    /**
     * @brief Order workshops in ascending order of unavailability
     * @param w1 the Workshop to compare with
     * @return True: if this Workshop 's unavailability is greater than w1's,False otherwise
     */
    bool operator<(const Workshop &w1)const;
    /**
     * @brief Checks for equality between two workshops
     * @param w1 Workshop to compare with
     * @return True if the names are equal,False otherwise
     */
    bool operator==(const Workshop& w1) const { return name==w1.getName();};
    /**
     * @brief Display workshop info in a human-friendly way
     * @param out output stream to write to
     * @param w workshop to display
     * @return output stream used
     */
    friend ostream& operator<<(ostream& out, Workshop w);
    /**
     * @brief Sets the unavailability of the workshop
     * @param a new unavailability
     */
    void setUn(int a) { unavailability = a;};
    /**
     * @brief Adds new brand to the workshop
     * @param n name of the new brand to be added
     */
    void addBrand(string n){brands.push_back(n);};


};
/**
* @brief Prints table to display workshops
*/
void headerWorkshop();



#endif //AEDA_PROJ1_WORKSHOP_H
