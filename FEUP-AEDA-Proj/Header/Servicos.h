//
// Created by maruba on 14/10/19.
//

#ifndef AEDA_PROJ1_SERVICOS_H
#define AEDA_PROJ1_SERVICOS_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>


#define PI 3.14159265358979323846

#include "Local.h"
#include "Camiao.h"

extern TaxTable *table;
using namespace std;
/**
 * @file Servicos.h
 * @brief Declarations of Servicos class responsable for handle the services (individualy)
 */
/**
 * @brief Class that handles the services 
 * 
 */
class Servicos {
private:
    unsigned int id;
    std::vector<Camiao *> camioes;           /**<Vector with all the camioes used to this service*/
    Local arrival;                          /**<Arrival place */
    Local departure;                        /**<Departure place */
    string type;                            /**<Type of the products transporting*/
    double profit;                          /**<Profit of the service*/
    int carga;                              /**<Number of products of the service**/
    string condition = "None";              /**Condition to the product*/
    double tax_condition = table->table[condition];


public:
    /**
     * @brief Default contructor for Servicos
     */
    Servicos();

    /**
     * @brief Constructor for Servicos
     * @param Departure Name of the departure place
     * @param Arrival Name of the arrival place
     * @param Id Identification for the service
     * @param profit is initialized by cal_profit() function
     * @param Condition condition of the product (cold, hot, toxic...)
     */
    Servicos(const Local &Departure, const Local &Arrival, const unsigned int &Id, const string &Tipo, const int& Carga, const string& Condition = "None");
    /**
     * @brief Default destuctor for services
     */
    ~Servicos() {};


    /**
     * @brief Calculates the price according to the time of traveling, price of each camiao and the fixed tax
     * @param tax Fixed tax established by the enterprise
     * @param profit the total profit to be returned
     * @return Returns the profit based on the time
     */
    void cal_profitTime();

    /**
     * @brief Calculates the time of traveling according to geographic cordenates of the arrival and departure.
     * @return Returns the time of traveling
     */
    double cal_tempo();

    /**
     * @return Returns the number of camioes operating on this service
     */
    int num_camiao();


    /**
     * @brief Stores the information about the client at os;
     * @param out Ostream to store the information
     * @param servico Service to be displayed
     * @return Returns the ostream os
     */
    friend ostream &operator<<(ostream &out, Servicos servico);

    /**
     * @return Get the id of the service
     */
    unsigned int get_id() const;

    /**
     * @return the profit
     */
    double get_profit() const;

    /**
     * @return Returns the name of departure
     */
    string get_departure() const;

    /**
     * @return Returns the name of arrival
     */

    string get_arrival() const;

    /**
     * @return Returns the type of the service. What kind produtct it will transport
     */
    string get_tipo() const;

    /**
     * @brief Get the actual storage
     * 
     * @return storage
     */
    int get_carga() const;

    /**
     * @brief Get the truck id
     * 
     * @return return the id 
     */
    string get_camioes_id() const;

    /**
     * Adds a camiao to the service and increase the profit variable based on the camiao profit
     * @param camiao
     */
    void addCamiao(Camiao *camiao);

    /**
     * @brief Get the condition object
     * 
     */
    string get_condition();

};

/**
 * @function function that check if s' profit is bigger than s1's. If they gave the same profit, compare the id
 * @param s first service
 * @param s1 second service
 * @return true if profit s<s1. If they have the same return true if id s<s1
 * @return false if profit s1<s. Return false case they have the same profit and id s1<s
 */
bool Compare_servico_profit(const Servicos* c, const Servicos* c1);

/**
 * @function function that check if s' profit is lesser than s1's. If they gave the same profit, compare the id
 * @param s first service
 * @param s1 second service
 * @return true if profit s1<s. If they have the same return true if id s<s1
 * @return false if profit s<s1. Return false case they have the same profit and id s1<s
 */
bool Compare_servico_Leastprofit(const Servicos *s, const Servicos *s1);

#endif //AEDA_PROJ1_SERVICOS_H
