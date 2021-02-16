#ifndef PROJECT_2_CLIENTS_H
#define PROJECT_2_CLIENTS_H

#include <vector>
#include <string>
#include <iostream>
#include "data.h"
#include "aux.h"

class Clients {
public:

//CONSTRUCTORS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Clients();
    Clients(std::string name, std::string nif, std::string nPeople, std::string address, std::string listPacks, std::string profit);

//SETS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void setName();
    void setNif();
    void setPeople();
    void setAddress();
    void setListPacks();
    void setPurchased();
    void setProfit();

//GETS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    std::string getName();
    int getNif();
    int getPeople();
    std::string getAddress();       //get the address formatted as string
    float getProfit();              //get the total amount that the client has bought
    std::string getListPacks();     //get the list of ids of purchased packages formatted as string
    std::vector<int> getVectorPacks();  //get list of packages ids in a vector format
    int getPurchased();                 //get the number of purchased packages
    std::vector<std::string> getVectorAddress(); //get address vector

//OTHERS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void visualizeClient();             //visualize the client's information
    void headInfoClient();              //visualize the head of the table
    void appendListPacks(int pack);     //append packages ids to the clients informations
    bool searchPack(const int& pack);   //search for a pack id and returns if exists or not (negative packages are not considered)



private:
    std::string name;                        //client's name
    int nif;                                 //client's nif
    int nPeople;                             //number of people at client's family
    std::vector <std::string> address;       //client's address
    std::vector <int> listPacks;             //list of packages purchased
    int nPurchased;                          //number of purchased packages
    float profit;                            //the total amount the client has bought

    std::vector<std::string> addAddress();

//FRIEND_FUNCTION+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    friend std::ostream& operator<<(std::ostream& out, const Clients& c );

};


#endif //PROJECT_2_CLIENTS_H
