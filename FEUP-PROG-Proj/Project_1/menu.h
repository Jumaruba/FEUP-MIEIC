//
// Created by maruba on 18-03-2019.
//

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "agency.h"
#include "clients.h"
#include "packs.h"




void readAgency();                                          //reads the agency.txt file and add package and client name file a struct
void readClient();                                          //reads clients file and store the text at a string vector
void readPack();                                            //reads package file and store the text at a string vetor
void mainMenu();                                            //shows and manage the principal menu
int menuManage(std::string optCap,std::string opt);         //show menu for clients and packages management
int menuVisual();                                           //shows and get the input for visualization menu
void writeClient();                                         //write clients information into the clients file
void writePack();                                           //writes the package file into the package file


