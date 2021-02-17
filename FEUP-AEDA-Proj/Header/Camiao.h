//
// Created by allanbs on 15/10/19.
//
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <iomanip>
#include "TaxTable.h"
#include "Workshop.h"

using namespace std;
#ifndef AEDA_PROJ1_CAMIAO_H
#define AEDA_PROJ1_CAMIAO_H
extern TaxTable *table;

/**
 * @file Camiao.h
 * @brief It contains the declarations of the class Camiao and its sub-classes.
 */

/**
 * @brief Class responsable for truck management
 */
class Camiao {
protected:
    long long int CargaMax;                  /**<Camiao max storage, if negative means that the truck is not available anymore*/
    long long int id;                        /**<The camiao identification*/
    double totalProfit;                     /**<Total profit the of the truck**/
    string brand;                            /**<Camiao 's brand**/
public:
    /**
     * Contructor
     * @param carg CargaMax in kg measure
     * @param id identification of the truck
     */
    Camiao(const long long int& carg, const long long int& id,string name);
    /**
     * @brief Default destructor
     */
    virtual ~Camiao();
    /**
     * @return the default price of the truck for one service
     */
    virtual double cal_preco() = 0;
    /**
     * @return the type of the truck
     */
    virtual string getType() const = 0;
    /**
     * @brief Compute that the truck was added to a service and then increase it's total Profit
     *
     */
    void addedToService();
    /**
     * @brief Get the Id parameter
     * @return int
     */
    int getId() const { return id; }
    /**
     * @brief Get the Carga Max parameter
     * @return int
     */
    int getCargaMax() const {return CargaMax;}
    /**
     * @brief Get the Profit parameter
     * @return double
     */
    double getProfit() const {return totalProfit; }
    /**
     * @brief remove the truck
     * It does not actually remove the truck, due the register of the client.
     * What it really does is to set the CargaMax as negative.
     * On this way it will not be allocated anymore but will keep the register
     */
    void removeTruck();
    /**
    * @brief Get the brand parameter
    * @return string
    */
    string getBrand() const{return brand;};
    /**
    * @brief Request generic service for this truck;
     * keep in mind hat generic services require only the earliest available
     * workshop
    * @return Workshops
    */
    Workshop requestGenericService(priority_queue<Workshop>& aux);
    /**
    * @brief Request specific service for this truck;
     * keep in mind hat specific services require  the earliest available
     * workshop that is specialized in this truck's brand
    * @return Workshop
    */
    Workshop requestSpecificService(priority_queue<Workshop>& aux);

};

/**
 * @brief Camiao Truck with frozens as product
 *
 */
class Congelado : public Camiao {
private:
    double tax = table->table["Congelado"];             /**<Get the taxes*/
public:
    /**
     * Contructor
     * @param carg cargaMax
     * @param disp If it's available or not
     * @param temp Temperature
     */
    Congelado(long long int carg, long long int Id,string name);
    /**
     * Default destructor
     */
    ~Congelado();
    /**
     * @brief The default price of the truck for one service
     * @return double
     */
    double cal_preco();
    /**
     * @brief Get the Type parameter
     * @return string
     */
    string getType() const;

};

/**
 * @brief Camiao Sub class that handles trucks with dangerous products 
 * 
 */
class Perigoso : public Camiao {
private:
    double tax = table->table["Perigoso"];/**<Get the taxes*/
public:
    /**
     * Constructor
     * @param carg cargaMax
     * @param disp If it's available or not
     */
    Perigoso(long long int carg, long long int Id,string name);
    /**
     * Default destructor
     *@brief Destroy the Perigoso object
     */
    ~Perigoso();
    /**
     * @brief calculates the price for one service
     * @return the price
     */
    double cal_preco();
    /**
     * @brief Get the Type parameter
     * @return string
     */
    string getType() const;

};

/**
 * @brief Camiao Truck with animals as product
 */
class Animals : public Camiao {
private:
    double tax = table->table["Animal"];        /**<Get the taxes*/
public:
    /**
     * Contructor
     * @param carg CargaMax
     * @param Id id
     */
    Animals(long long int carg, long long int Id,string name);
    /**
     * Default destructor
     *
     */
    ~Animals();
    /**
     * @brief The default price of the truck for one service
     * @return double
     */
    double cal_preco();
    /**
     * @brief Get the Type parameter
     * @return string
     */
    string getType() const;

};

/**
 * @brief Camiao Sub class for base products
 */
class Base: public Camiao {
private:
    double tax = table->table["Base"];      /**<Get the taxes*/
public:
    /**
     * @brief Construct a new Base object
     * @param carg The actual storage
     * @param Id The identification number of the truck
     */
    Base(long long int carg, long long int Id,string name): Camiao(carg, Id, name) {};
    /**
     * @brief Get the Type object
     * @return string
     */
    string getType() const;
    /**
     * @brief The default price of the truck for one service
     * @return double
     */
    double cal_preco();

};

/**
 * @brief It compares two trucks
 *
 * @param c1 first client
 * @param c2 second client
 * @return true if profit c1 < c2. If they have the same profit compare the max storage c1<c2. If they have the same storage return true
 * @return false  if profit c2 < c1. If they have the same profit compare the max storage c2<c1.
 */
bool Compare(const Camiao* c1, const Camiao* c2);
#endif //AEDA_PROJ1_CAMIAO_H
