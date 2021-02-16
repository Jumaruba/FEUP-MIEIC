#include <iostream>
#include <vector>
#include "agency.h"
#include "menu.h"
#include "data.h"
#include "packs.h"

using namespace std;


int main() {
    Agency a = readAgency();   //read the file agency and consequently all the other files and store the information at vector structs
    mainMenu(a);                //starts the program

    return 0;
}
