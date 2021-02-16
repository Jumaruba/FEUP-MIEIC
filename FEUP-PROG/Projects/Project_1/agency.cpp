//
// Created by maruba on 18-03-2019.
//

#include "agency.h"
#include "menu.h"
#include <iostream>

using namespace std;


//GLOBAL VARIABLES------------------------------------------------------------------------------------------------------

extern std::vector <std::string> text;              //vector contains the text read; 
extern agency a;                                    //contains the struct that contains informations about the agency;


//FUNCTION--------------------------------------------------------------------------------------------------------------

//This function stores the file information into agency a
void agency::readfile() {
    a.name = text[0];                               //agency's name;
    a.nif = stoi(text[1]);                          //agency's nif
    a.website = text[2];                            //agency's website
    a.address = text[3];                            //agency's address
    a.cliente = text[4];                            //file containing information about the clients
    a.pack = text[5];                               //file containing information about the packages

}