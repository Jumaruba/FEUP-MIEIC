#ifndef PROJECT_2_MENU_H
#define PROJECT_2_MENU_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "agency.h"
#include "clients.h"
#include "packs.h"

//BEFORE START++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Agency readAgency();        //this functions reads agency.txt and call the following functions

void readPack(Agency a);    //this function reads the pack file 
void readClient(Agency a);  //this function reads the client file 
void putClient();           //this function store all the information from clients file into a vector<Clients> c
void putPack();             //this function store all the information from packs file into a  vector<Packs> p

//START+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//1 MENU LAYER----------------------------------------------------------------------------------------------------------
void mainMenu(Agency a);   //PRINCIPAL MENU


//2 MENU LAYER----------------------------------------------------------------------------------------------------------
int menuManage(const std::string& optCap, const std::string& opt);   //visualize general menu for clients and packages managements
void manageClient(int option);   //this functions deals with the clients management
void managePack(int option);     //this functions deals with the packages management

int menuVisual();               
void clientVisual();
void packagesVisual();

//3 MENU LAYER - manageClient-------------------------------------------------------------------------------------------
void newClient();     //this function creates a new client
void changeClient();  //this function changes a client (search by NIF)
void removeClient();  //this function removes a client (delete) 

//3 MENU LAYER - managePack---------------------------------------------------------------------------------------------
void newPack();     //this function creates a new pack
void changePack();  //this function changes a client (search by ID)
void removePack();  //this function DO NOT remove a pack. It actually changes a state of a pack (available or not)

//ENDING----------------------------------------------------------------------------------------------------------------
void writeClient(); //this function "updates" the information about clients at the file
void writePack();   //this function "updates" the information about packages at the file

//SEARCHING FUNCTIONS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int searchPack();   //search by id at vector<Packs> p (vector where packages information is stored)
int searchPack_bool(int number);  //search if there is package with the id int number
int searchNif();  //search by nif at vector<Clients> c (vector where clients information is stored)
int searchNif_bool(int number); //search if there is a client with the nif int number

//MOST VISITED PLACES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

std::vector<std::pair<std::string, int>> sortedVisitedPlace();  //returns a sorted vector<pair<string,int>> that contains the most visited places 
void placesHead(); //head for the visualization table for the most visited places 
void visualizePlaces(std::pair<std::string,int> p); //this function visualizes a data for the table of the most visited places 
void showMostVisited(std::vector<std::pair<std::string,int>> v);  //this function shows the table of the most visited places 

//CLIENTS SUGGESTION OF PACKAGES TO BUY+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

std::vector<std::string> clientSuggestion(std::vector<std::pair<std::string,int>> v);
void showClientSuggestion(std::vector<int> id);//this function shows the table for suggested packages to buy for each client
void headClientSuggestion(int nDigitos);  //head for the visualiation table for the suggestion of packages 
void visualizeClientSuggestion(int id,Clients& client, int n, int digitos, int size); //this function visualizes a data for table of suggestions
std::vector<int> getPackageId(std::vector<std::string> placeClient); //this functions returns the order that ids appear at vector<Pack> p; 

#endif //PROJECT_2_MENU_H
