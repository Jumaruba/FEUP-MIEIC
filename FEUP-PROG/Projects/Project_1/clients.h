//
// Created by maruba on 18-03-2019.
//

#pragma once

#include <vector>
#include <string>
#include "data.h"
#include "aux.h"

//STRUCT----------------------------------------------------------------------------------------------------------------

typedef struct{
    std::string name;
    int nif;
    int nPeople;
    std::vector <std::string> address;
    std::string listPacks;
    int nPurchased;


    int countPack(std::string word);        //Count the number of packages in a string


}client;

//FUNCTIONS-------------------------------------------------------------------------------------------------------------

void putClient();                           //store the information of clients from the text vector to structs

void manageClient(int option);              //calls the functions to manage the client given the option
void newClient();                           //creates a new client
void split(std::vector<std::string>& m, std::string line, char caracter);   //separate a string given the string to be separated (m), string to put the result (line), and the caracter to use as parameter so separate
void addAddress(std::vector<std::string>&m);//function to add a new address
void changeClient();                        //
int searchName();                           //search the position of a client in a vector
void removeClient();                        //remove a client
std::string concatenate(std::vector <std::string> v);
void clientVisual();                        //fuctions that visualize the clients


