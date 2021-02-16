//
// Created by maruba on 18-03-2019.
//

#pragma once

#include <iostream>
#include <string>
#include "data.h"
#include "clients.h"
#include "aux.h"


//STRUCT---------------------------------------------------------------------------------------------------------------

typedef struct {
    int identifier;         //pack id
    std::string local;      //pack address
    data dBegin;            //date of beginning
    data dEnd;              //date of ending
    float price;            //pack price
    int places;             //number of places
    int maxPeople;          //max number of people
}pack;

//FUNCTION--------------------------------------------------------------------------------------------------------------

void putPack();                                     //read the file
void managePack(int option);
int searchPack();
void removePack();
void changePack();
void newPack();
void showPack(pack aux);
std::string concDate_begin(pack aux);
std::string concDate_end(pack aux);
void packagesVisual();
void showPack_cabecalho ();
bool searchPlace(std::string place, std::string destines);
bool searchData(data begin, data end, data dBegin, data dEnd);
void inputData(data& begin, data& end);
int searchPack_bool(int number);
bool pack_there(int id);