#ifndef PROJECT_2_AGENCY_H
#define PROJECT_2_AGENCY_H

#include <iostream>
#include <string>
#include <vector>

class Agency {
public:
    
    //CONSTRUCTOR++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Agency(const std::string& name, const std::string& nif, const std::string& address, const std::string& website,
           const std::string& cliente, const std::string& pack);
    
    //GET++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    std::string getCliente();                   //get clients name file
    std::string getPack();                      //get packages name file


private:
    std::string name;                           //agency's name;
    int nif;                                    //agency's nif
    std::string address;                        //agency's address
    std::string website;                        //agency's website
    std::string cliente;                        //name of the file with clients information
    std::string pack;                           //name of the file with packages information
};


#endif //PROJECT_2_AGENCY_H
