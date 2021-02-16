//
// Created by maruba on 18-03-2019.
//

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "data.h"

// this struct will contain the information about the agency 

typedef struct
{
    std::string name;		
    int nif;					
    std::string address;	
    std::string website;	
    std::string cliente;
    std::string pack;

    void readfile();  //reads the file which the name was given by the user; 

} agency;


