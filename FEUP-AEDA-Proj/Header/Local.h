//
// Created by maruba on 14/10/19.
//

#ifndef AEDA_PROJ1_LOCAL_H
#define AEDA_PROJ1_LOCAL_H
#include <iostream>
#include <string>
using namespace std;

/**
 * @file Local.h
 * @brief File with the declaration of Local class reponsable to handle the location of the services
 */
/**
 * @brief Class that handles the locals of transportation
 * 
 */
class Local {
private:
    string name;                                    /**<Name of the local**/
    double x, y;                                    /**<Latitude and Longitude**/
public:
    /**
     * @brief Construct a new Local object
     * 
     */
    Local();
    /**
     * @brief Construct a new Local object
     * 
     * @param Name Name of the local
     * @param X Latitude
     * @param Y Longitude
     */
    Local(string  Name, double X, double Y);
    /**
     * @brief Get the Latitude
     * 
     * @return double 
     */
    double get_Coordx() const;
    /**
     * @brief Get the Longitude
     * 
     * @return double 
     */
    double get_Coordy() const;
    /**
     * @brief Get the Name parameter
     * 
     * @return string 
     */
    string getName() const;

};


#endif //AEDA_PROJ1_LOCAL_H
