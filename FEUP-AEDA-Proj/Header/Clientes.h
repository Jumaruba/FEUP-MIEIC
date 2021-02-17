//
// Created by Amanda  on 2019-10-14.
//

#ifndef AEDA_01_CLIENTES_H
#define AEDA_01_CLIENTES_H
#include <string>
#include <iostream>
#include "Servicos.h"
#include "Date.h"

using namespace std;
/**
 * @file Clientes.h
 * @brief It contais the declarations of class Clientes responsable for Clients management
 */

/**
 * @brief Class responsable to handle the clients
 *
 */
class Clientes {
private:
    string name;                        /**<Name of the client*/
    long long int nif;                  /**<Identification of the client*/
    vector<Servicos *> services;        /**<Services requested by the client*/
    double profit;                      /**<Clients profit*/
    Date last_request;                  /**<Date of the last service request*/
public:
    /**
     * Default constructos
     */
    Clientes();
    /**
     * Constructor
     * @param n Clients name
     * @param anif Nif (identificantion of the client)
     */
    Clientes(const string &n, const long long int &anif);
    /**
     * Default destructor
     */
    ~Clientes();
    /**
     * @return Returns the profit of the client
     */
    double get_profit() const;
    /**
     * @return Returns the clients nif (identification)
     */
    long long int get_nif() const;

    /**
     * @return Returns the client's name
     */
    string getName() const{return name;};

    /**
   * Client request a service
   * @param servico Service to be added
   */
    void addService(Servicos *servico);
    /**
     * @brief Change the name of the client
     * @param name the new name of the client
     */
    void setName(const string& name);
    /**
     * @brief Change the nif of a client given the actual nif
     * @param nif The actual nif of the client
     */
    void setNif(const long long int& nif);
    /**
     * Display the information about the client
     * @param out ostream with the information
     * @param client object containing the client register
     * @return ostream with the information
     */
    friend ostream &operator<<(ostream &out, const Clientes &client);
    /**
     * Set the date of the last request
     * @param date String on the format yyyy/mm/dd
     */
    void setDate(const string& date);
    /**
     * @brief Get the date from the last request
     * @return String representing the date on the format yyyy/mm/dd
     */
    string getDate() const;

};
/**
 * @brief Compare the profit of the clients and compare the name
 *
 * @param c Pointer to the first client
 * @param c1 Pointer to the second client
 * @return true if profit c1<c. If they have the same profit return true if name c<c1. If the have also the same name return true
 * @return false if profit c<c1. If they have the same profit return false if name c1<c.
 */
bool Compare_clientes(const Clientes* c, const Clientes* c1);
/**
 * @brief Compare the the client and compare the name
 *
 * @param c Pointer to the first client
 * @param c1 Pointer to the second client
 * @return true if profit c<c1. If they have the same profit return true if name c<c1. If the have also the same name return true
 * @return false if profit c1<c. If they have the same profit return false if name c1<c.
 */
bool Compare_clientesLeast(const Clientes* c, const Clientes* c1);
/**
 * @brief Compare the names of the clients
 *
 * @param c Pointer to the first client
 * @param c1 Pointer to the second client
 * @return true if name c<c1. If they have the same name also return true
 * @return false if name c1<c.
 */
bool Compare_clientesAlphabetic(const Clientes *c, const Clientes* c1);

void headerClientes();
//HASH TABLE ----------------------------------------------------------------

struct clienteHash{
    int operator()(const Clientes* cli) const{
        return cli->get_nif();
    }
    bool operator()(const Clientes* cli1, const  Clientes * cli2) const{
        return cli1->get_nif() == cli2->get_nif();
    }
};
#endif //AEDA_01_CLIENTES_H
