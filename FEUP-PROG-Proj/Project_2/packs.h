#ifndef PROJECT_2_PACKS_H
#define PROJECT_2_PACKS_H

#include <iostream>
#include <string>
#include <vector>
#include "data.h"


class Packs {
public:

    //CONSTRUCTORS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Packs();
    Packs(std::string id, std::string local, std::string dBegin, std::string dEnd, std::string price, std::string maxPeople, std::string reserved);

    //SET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void setId();
    void setIdSimple(int num);  //set the if without any confirmation or cancel option 
    void setLocal();            
    void setPrice();
    void setMaxPeople();
    void setReserved();

    //GET++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    int getId();            
    std::string getLocal(); //this function get the local of package in a string format
    float getPrice();
    int getMaxPeople();
    std::vector<std::string> getPlacesVec();    //this function gets the vector of places that a package covers
    int getReserved();

    //OTHERS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    bool searchPlace(const std::string& place);  //returns if a place is at a package
    void headInfoPack();    //this function shows the head for the package table 
    void visualizePack();   //this function shoes the data for the package table 

    //FRINED FUNCTION++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    friend std::ostream& operator<<(std::ostream& out ,const Packs& p);  //overload to store the class information into a stream in the right format

    //DATE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Date dBegin;    //date of begining of the package 
    Date dEnd;      //date of the end of the package 

private:
    int id;
    std:: string local;
    float price;
    int maxPeople;
    int reserved;

    bool repeatId(int id);              //this function checks if there is a pack with the same id

};


#endif //PROJECT_2_PACKS_H
