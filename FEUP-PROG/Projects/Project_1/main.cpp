#include <iostream>
#include <vector>
#include "agency.h"
#include "menu.h"
#include "data.h"
#include "packs.h"



using namespace std;

//GLOBAL VARIABLES -----------------------------------------------------------------------------------------------------

extern std::vector <std::string> text;
extern agency a;
extern vector <client> c;
extern std::vector<pack> p;

//FUNCTION--------------------------------------------------------------------------------------------------------------

int main() {
    readAgency();   //read the file agency and consequently all the other files and store the information at vector structs
    mainMenu();     //starts the program



    return 0;
}
