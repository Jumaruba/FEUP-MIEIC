//
// Created by maruba on 14/10/19.
//

#ifndef AEDA_PROJ1_EMPRESA_H
#define AEDA_PROJ1_EMPRESA_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <queue>
#include <unordered_set>

#include "Camiao.h"
#include "Servicos.h"
#include "Errors.h"
#include "Clientes.h"
#include "Workshop.h"
#include "Motorista.h"


/**
 * @file Empresa.h
 * @brief It contains the Empresa class declarations, resposable for the management of the enterprise
 */
using namespace std;
typedef priority_queue<Workshop> PQ;
typedef unordered_set<Clientes*, clienteHash, clienteHash> tabHCli;

/**
 * @brief Class that manages an enterprise
 */
class Empresa {
private:
    vector<Clientes *> cli;     /**< Vector that contains all clients of this enterprise*/
    vector<Camiao *> cam;       /**<Vector that contais all camioes of this enterprise*/
    vector<Servicos *> ser;     /**<Vector that contais all services offered for the enterprise*/
    Workers w;                  /**<Class that stores the workers BST**/
    vector<Workshop> wor;       /**<Vector containing all workshops bounded with this enterprise*/
    PQ pq;
    tabHCli inactive;           /**<Hash table containing inactive clients*/


public:
    static size_t nCam;         /**<How many trucks there are in the enterprise**/
    static size_t nCli;         /**<How many clients there are in the enterprise**/
    static size_t nSer;         /**<How many services there are in the enterprise in a specific month**/

    /**
     * @brief Read information from workshops.txt file and build the wor vector
     */
    void gravaWor();
    /**
     * @brief Read information from clients.txt file and build the cli vector
     */
    void gravaCli();
    /**
     * @brief Read information from camioes.txt file and build the cam vector
     */
    void gravaCam();
    /**
     * @brief Read information from servicos.txt file and build the ser vector
     */
    void gravaSer(Empresa &e, const int& month);
    /**
     * @brief Read information from Motorista.txt file and stores the information in the variable w
     */
    void readMotorista();
    /**
     * @brief Constructor for the class
     */

    Empresa();

    /**
     * @brief Destructor for the class that cleans all the alocated vectors
     */
    ~Empresa();

    /**
     * @brief Calculates the profit of the month
     * @return Returns the profit of the month
     */
    double getLucro_mes() const;

    /**
     * @brief Add a new client to the vector cli
     * @param name The name of the new client
     * @param nif Personal numeration of the client
     * @param date Date of the last service request
     */
    void addClientes(const string &name, const long long int &nif, const string& date = "1500/01/01");
    /**
     * @param Partida Departure Local
     * @param Destino Arrival local
     * @param Id Identificantion for the service
     * @param Tipo What kind of products it will transport
     */
    Servicos * addServico(Servicos* s, const long long int cliNif);
    /**
     * @brief Adds a new service when it is requested by a client
     * @param s Service to be added
     * @param cliNif Client that has requested the service
     * @return Requested service
     */
    Servicos * requestService(Servicos *s, const long long int cliNif);
    /**
     * @brief It adds a new truck to the enterprise
     * @param type the type of the trucm
     * @param cargaMax max number of items
     */
    void addCamiao(const int&  type, const long long int &cargaMax,string brand);

    /**
     * @brief Search for a client with nif given
     * @param nif Identification of the client
     * @return Return the position of client in the vector cli
     */
    long int SearchCli(const long long int &nif) const;

    /**
     * @brief Search for a service with the id given
     * @param id Identification of the service
     * @return Return the position of the service in the vector ser. If it doesn't exist throw an exception
     */
    size_t SearchSer(const long long int &id) const;
    /**
     * @brief Get the profit of the month for a specific type o truck
     *
     * @param type
     * @return double
     */
    double getLucro_camiaoMes(const string& type) const;
    /**
     * @brief get the workers BST, in order to use it's methods
     * @return Workers
     */
    Workers getBST() const;
    /**
     * @brief Display the clients information in a specific format
     *
     * @param nif Case it's a specific nif, the parameter nif must be diferent from zero
     * @param n Number of clients to be shown
     * @param f Function used to sort the vector
     */
    void display_clientesInfo(const long long int &nif= 0, long int n = 1, bool (*f)(const Clientes* c, const Clientes* c1) = Compare_clientes);
    /**
     * @brief Displays in a simple way the total profit of the month
     */
    void display_lucro_mes();
    /**
     * @brief display profit of each truck type
     *
     */
    void display_CamiaoProfit();

    /**
     * @brief
     *
     * @param id Identification of the service which must be different from zero case needs to display a specific service
     * @param n Number of services
     * @param f Function to sort the vector
     * @param type Type of the service (if it's necessary)
     */
    void display_servicoStatus(const long long int &id = 0, long int n = 10000, bool(*f)(const Servicos*, const Servicos*) = Compare_servico_profit, const string& type = "") const;

    /**
     * @brief Add a truck to a specific service based on its id
     *
     * @param id Identification of the truck
     * @param s Service to the truck be added to
     */
    void addCamiaoId_Servico(const int& id, Servicos* s);
    /**
     * @brief Choose trucks to be allocated to a service
     *
     * @param s Service requesting trucks
     * @return true if it allocated trucks successfully
     * @return false if it didn't allocate trucks successfully
     */
    bool allocateCamiao(Servicos* s);
    /**
     * @brief it changes the name of the client in the file and at the program
     */
    void changeClientName(const long long int& nif);
    /**
     * @brief remove a client
     * @param nif The nif of the client to be removed
     * @warning The clients are not deleted from the files, their nif are converted to negative ones. On this way the enterprise keeps the historic about the client and at the same time the client is "removed".
     */
    void removeClient(const long long int& nif);

    /**
     * @brief this method rewrites all the clients.
     * Usually this function is called when something has changed for a specific client
     */
    void rewriteClients();
    /**
     * @brief Reaccept a ex-client into the enterprise
     * After being excluded from the enterprise the client might want to become a client again.
     * @param nif Nif of the client
     */
    void reAcceptClient(const long int& pos);

    /**
     * @brief remove the truck from the enterprise
     * @param id the truck id
     * @warning it doesn't actually delete the truck. Just put the carga to negative to indicate that it's not avaialable anymore
     */
    void removeTruck(const long long int& id);

    /**
     * @brief rewrite the truck file
     */
    void rewriteTruck();
    /**
     * @brief get number of trucks
     *
     * @return long long int
     */
    long long int get_cam_num();
    /**
     * Display workers according to the option given
     * @param option 1: Print workers ascending order of hours, option 2: Print workers descending order of hours, option 3: Print workers in alphabetic order
     * @param n Number of workers to print
     */
    void displayWorkers(int option, int n);
    /**
     * Add a worker to the BST
     * @param m Worker to be added
     * @return false case the worker already exists, true otherwise
     */
    bool addMotorista(Motorista m);
    /**
     * Remove a worker from the BST
     * @param m Worker (Motorista) to be removed
     * @return false there isn't this worker, true otherwise
     */
    bool removeMotorista(Motorista m);
    /**
     * Change the Motorista name
     * @param m Motorista which the name will be changed
     * @param name New name of the Motorista
     * @return false, case the Motorista does not exist, true otherwise
     */
    bool setMotoristaName(Motorista m, const string& name);
    /**
     * Increase the number of hours of the Motorista
     * @param tempo Number of hours to increase
     * @return false, case it's not possible to allocate  a Motorista; true otherwise
     */
    bool allocateMotorista(float tempo);
    /**
     * Reset the hours in the elements of the BST
     */
    void resetHours();
    /**
  * @brief add Workshop to enterprise
  * @param brands brands vector
  * @param disp initial unavailability
  * @param name Workshop's name
  */
    void addWorkshop(string name,vector<string> &brands,int disp){wor.push_back(Workshop(name,brands,disp));pq.push(Workshop(name,brands,disp));rewriteWorkshops();};
    /**
     * @brief remove workshop from enterprise
     * @param name name of workshop to be removed
     * @return whether the workshop could be removed
     */
    bool removeWorkshop(string name);
    /**
     * @brief rewrite workshop file
     * @return long long int
     */
    void rewriteWorkshops();
    /**
     * @brief fill priority queue with workshops from wor vector
     */
    void fillQueue();
    /**
     * @brief get workshops in priority queue
     *
     * @return priority queue containing workshops
     */
    priority_queue<Workshop> getPQ() const {return pq;};
    /**
     * @brief swap current priority queue with new one
     */
    void swap_pq(priority_queue<Workshop> & aux){pq.swap(aux);updateWor();};
    /**
     * @brief get cam vector
     *
     * @return vector containing pointers to camiao
     */
    vector<Camiao*> getCamiao() const {return cam;};
    /**
     * @brief get ser vector
     *
     * @return vector containing pointers to services
     */
    vector<Servicos*> getServices() const {return ser;};
    /**
     * @brief get cli vector
     *
     * @return vector containing pointers to clientes
     */
    vector<Clientes*> getCli() const {return cli;};
    /**
     * @brief get wor vector
     *
     * @return vector containing workshops
     */
    vector<Workshop> getWor() const {return wor;};
    /**
     * @brief Update priority queue based on current wor vector;
     * this function is needed because rewriteWorkshops use wor vector and not the priority queue
     */
    void updateWor(){
        priority_queue<Workshop> aux = getPQ();
        wor.clear();
        while(!aux.empty()){
            wor.push_back(aux.top());
            aux.pop();
        }
    };
    // HASH TABLE -----------------------------------
    /**
     * @brief updates the hash tabl getting all inactive clients
     */
    void update_hash();
    /**
     * @brief display all x inactive clients in an unordered
     * @param x Number of clients to be displayed
     */
    void display_hash(long int x);
    /**
     * @brief Search for an specific inactive client given the nif
     * @param nif Identificantion of the client
     * @return If the client is not in the hash, return a dumb Client with name "". Else return the client.
     */
    Clientes SearchInactiveClient_hash(const long long int& nif);
    /**
     * @brief Display the first x elements in the hash table ordered by date
     */
    void display_dateOrdered_hash(long int x);

};

/**
 * @brief Header for list of services
 * 
 */
void headerServInfor();
/**
 * @brief Header for list of trucks
 * 
 */
void headerCamInfor();

/**
 * @brief Header for list of workers
 */
void headerWorkersInfor();

#endif //AEDA_PROJ1_EMPRESA_H
