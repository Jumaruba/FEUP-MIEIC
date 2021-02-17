//
// Created by maruba on 23/12/19.
//

#ifndef AEDA_PROJ1_MOTORISTA_H
#define AEDA_PROJ1_MOTORISTA_H
#include "bst.h"
#include "Errors.h"

#include <fstream>
#include <iomanip>
#include <istream>
#include <algorithm>
#include <string>
#include <vector>

/**
 * @file Motorista.h
 * @brief It contains the Class Motorista and Workers that manages the BST of workers
 */

class Motorista {
private:
    std::string name;       /**<Name of the worker**/
    long long int nif;      /**<Nif of the worker**/
    float hours;            /**<Number of hours of work on the day**/
public:
    /**
     * @brief Default constructor
     */
    Motorista(): name(""), nif(0), hours(0) {};
    /**
     * Constructor for the Motorista
     * @param name The name of the worker
     * @param nif The nif of the worker
     * @param Hours Number of daily hours
     */
    Motorista(std::string Name, long long int Nif, float Hours): name(Name), nif(Nif), hours(Hours){};
    /**
     * @brief Organized by growing order of hours
     * @param driver The Motorista to be compared to
     * @return True: case the number of hours is less then the number of hours of driver, false otherwise
     */
    bool operator<(const Motorista &driver) const;
    /**
     * @brief Compares two Motorista variables
     * @param driver The Motorista to be compared to
     * @return True: case are equal, false otherwise
     */
    bool operator==(const Motorista &driver) const;
    /**
     * @brief Get the number of hours until now
     * @return Float with hours
     */
    float getHours() const;
    /**
     * @brief Get the name of the motorista
     * @return string with the name
     */
    std::string getName() const;
    /**
     * Get the Nif
     * @return the NIF
     */
    long long int getNif() const;
    /**
     * Set the hours worked in a day
     * @param h The hours to be set
     * @return true: if h <= 24; else false
     */
    bool setHours(const float & h);
    /**
     * Print the Motorista information
     * @param out
     * @param w Motorista to be printed
     * @return
     */
    friend ostream &operator<<(ostream &out,const Motorista& w);
    /**
     * @brief Change the name of the Motorista
     * @param name New name to substituted the old name
     */
    void setName(const string& name);
};


class Workers{
private:
    BST<Motorista> BST_Workers;
public:
    /**
     * Default constructor
     */
    Workers(): BST_Workers(Motorista("",0,0)) {};
    /**
     * Get the Binary Tree in a vector in a In order sequence
     * @return Vector with the binary tree
     */
    vector<Motorista> getBST();
    /**
     * Adds a worker to the BST, case the Nif is not repeated
     * @param new_motorista The worker to be added
     * @return return true if the worker was added, else false
     */
    bool addMotorista(const Motorista& new_motorista);
    /**
     * Remove the given motorista
     * @param motorista Worker to be removed
     * @return true if it was removed successfully, false otherwise
     */
    bool removeMotorista(const Motorista& motorista);
    /**
     * @brief Prints the content of the BST
     * @param n Number of elements to print
     */
    void printBST(int n);
    /**
     * @brief Prints the content of the BST by reverse order, so that the elements are in descending order of hours
     * @param n Number of elements to print
     * @attention For the implementation of this function, the bst.h has been changed. Two new function has been implemented: void getReversedTree(vector<Comparable>& v) const and void getReversedTree_aux(BinaryNode<Comparable> *t, vector<Comparable> &v).
     */
    void printBST_reversed(int n);
    /**
     * @brief read from Ficheiros, the file with Motoristas and insert on the BST
     */
    void readMotorista();

    /**
     * It prints the bst in an alphabetic other of Motorista name
     * @param n Number of elements to be printed
     */
    void printBST_alphabetic(int n);
    /**
     * @brief Search for Motorista with the specific nif
     * @param Nif Nif to be searched
     * @return throw an exception if it doesn't exist, else return the Motorista with the nif asked
     */
    Motorista check_nif(long long int Nif) const;
    /**
     * @brief Update the file Motoristas with the information in the BST
     */
    void rewrite_file();
    /**
     * @brief Change the name of a Motorista
     * @param motorista Motorista whose name will be changed
     * @param name New name of the Motorista
     * @return true in case of success, false otherwise
     */
    bool setName(Motorista& motorista, const string& name);
    /**
     * Allocate a Motorista to work for more x hours
     * @param tempo Number of hours to increase the work
     * @return true case the Motorista has been allocated, false otherwise
     */
    bool allocateMotorista(float tempo);
    /**
     * @brief set hours to zero in all elements in the BST
     */
    void resetHours();
};




#endif //AEDA_PROJ1_MOTORISTA_H
