//
// Created by maruba on 18-03-2019.
//


// quando comprar um pacote, verificar se ele nao ja foi comprado


#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include "menu.h"


using namespace std;



//GLOBAL VARIABLES -----------------------------------------------------------------------------------------------------

vector<client> c;
std::vector<std::string> text;
agency a;
std::vector<pack> p;


//FUNCTIONS-------------------------------------------------------------------------------------------------------------

// reads agency file
void readAgency() {

    string line;                                            //string to store the actual line read

    ifstream file;
    file.open("agency.txt");

    if (file.is_open()) {
        while (getline(file, line)) {
            text.push_back(line);                           //push_back all the text at text vector

        }
    } else
        cout << "Error! agency.txt not found." << endl;     // case if it weren't able to open the file

    file.close();

    a.readfile();                                           //store all the text information into the agency struct "a"
    readClient();                                           //read clients file and store the clients information into the client struct "c"
    readPack();                                             //read packages file and store the ifnormation into the package struct "a"
    file.close();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//read clients file and store information into the struct Client c

void readClient() {
    text.clear();                               // clear the previous information at the string vector text
    string line;                                // string to read the lines

    ifstream file;
    file.open(a.cliente);                       //opening clients file

    if (file.is_open()) {
        while (getline(file, line)) {
            text.push_back(line);               //storing information at text vector
        }
    } else
        cout << "Error! " << a.cliente << " not found." << endl;

    putClient();                                //store the information read into clients struct "c"
    file.close();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//read package file and store information into the struct Pack p

void readPack() {
    text.clear();                               // clear the previous information at the string vector text
    string line;                                // string to read the lines

    ifstream file;
    file.open(a.pack);                          //opening package file

    if (file.is_open()) {
        while (getline(file, line)) {
            text.push_back(line);               //storing information at text vector
        }
    } else
        cout << "Error!" << a.pack << " not found." << endl;

    putPack();                                  //store the information read into clients struct "c"
    file.close();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//main menu

void mainMenu() {
    int menu_option = 0;                    // option given by the user about the number to  be selected
    int second_option = 0;                  // option for the second menu
    int position_pack;                      // the position of the package to be purchased
    int position_client;                    // position of the client that will by the package

    while (menu_option != 5) {              //if menu_option == 5, exit program

        clear_screen();                     //clear screen for linux and windows

        cout << "-------------- MENU -------------- " << endl       //show menu
             << "1. Clients management" << endl
             << "2. Turistic packages management" << endl
             << "3. Information visualization" << endl
             << "4. Buy a package" << endl
             << "5. Exit" << endl;


        menu_option = cin_menu(5, 1);           //user type a VALID menu option
        clear_screen();                         //clear screen for linux and windows
//--------------------------------------------------------------------------------------------------------------------
        //client management

        if (menu_option == 1) {
            second_option = menuManage("CLIENT", "client");  //show menu and get the option for this secondary menu
            clear_screen();
            manageClient(second_option);                     //actions for clients management
        }
//--------------------------------------------------------------------------------------------------------------------
        //packages management

        else if (menu_option == 2) {
            second_option = menuManage("PACKAGE", "package");//show menu and get the option for this secondary menu
            clear_screen();
            managePack(second_option);                       //actions for packages management

        }
//--------------------------------------------------------------------------------------------------------------------
        //information visualization

        else if (menu_option == 3) {
            second_option = menuVisual();                   //show menu and get the option for this secondary menu
            clear_screen();                                 //clear screen for linux and windows
            if (second_option != 3) {                       // back option
                if (second_option == 1) {                   //visualization avoid clients
                    clientVisual();                         //menu and actions for clients visualization
                } else
                    packagesVisual();                       //menu and actions for packages visualizations
            }
        }

//--------------------------------------------------------------------------------------------------------------------
        //buy a new package

        else if (menu_option == 4) {
            position_pack = searchPack();           //search the position of the package to be purchased
            if (p[position_pack].identifier > 0) {  //if the pack is available and != 0
                cin.ignore();
                position_client = searchName();     //search the name of the clients to whom the package will be added
                if (position_client != -1) {        //if there is a package, format the package to string
                    c[position_client].listPacks.append(" ; ");
                    c[position_client].listPacks.append(to_string(p[position_pack].identifier));
                    cout << "Done. Press ENTER to continue...";
                    cin.ignore();
                } else if (position_pack < 0) {     //if the package doesn't exist
                    cout << "Type positive numbers!" << endl;
                    cout << "Press ENTER to continue...";
                    cin.ignore();
                    cin.ignore();
                }
            }
        }
//--------------------------------------------------------------------------------------------------------------------

        //exit option

        else if (menu_option == 5) {
            string file;
            writeClient();                  //write all the clients information into a provisory file
            writePack();                    //write all the packages information into a provisory file
            remove(a.pack.c_str());         //remove the original package file
            remove(a.cliente.c_str());      //remove the original package client
            rename("provisorioC.txt", a.cliente.c_str());   //rename the client provisory file to the original one
            rename("provisorioP.txt", a.pack.c_str());      //rename the package provisory file to the original one

        }
        if (menu_option != 5) {     //even if the user don't wanna exit, for each interaction, the information will stored at provisory files
            writeClient();          //write all the clients information into a provisory file
            writePack();            //write all the packages information into a provisory file
        }
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Menu for clients and packages management

int menuManage(const string optCap, const string opt) {
    int variable;
    cout << "-------------- " << optCap << "S" << " MANAGEMENT" << " --------------" << endl
         << "1. New " << opt << endl
         << "2. Change " << opt << endl
         << "3. Remove " << opt << endl
         << "4. Back"
         << endl;

    variable = cin_menu(4, 1);          //menu option desired
    return variable;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Menu for visualization

int menuVisual() {
    int variable;

    cout << "---------------- VISUALIZATION MENU ----------------" << endl
         << "1. Clients" << endl
         << "2. Packages" << endl
         << "3. Back" << endl;

    variable = cin_menu(3, 1);      //desired option given by the user
    return variable;                //return the option
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Write all the client information into a temporary file

void writeClient() {
    cout << fixed << setprecision(2);
    ofstream file;
    file.open("provisorioC.txt");               //creating temporary file

    for (int i = 0; i < c.size(); i++) {        //storing the clients information into the temporary file
        file << c[i].name + '\n'
             << to_string(c[i].nif) + '\n'
             << to_string(c[i].nPeople) + '\n'
             << concatenate(c[i].address) + '\n'
             << c[i].listPacks;
        if (i != p.size() - 1) {
            file << '\n';
            file << "::::::::::\n";
        }

    }
    file.close();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Write all package information into a temporary file

void writePack() {
    cout << fixed << setprecision(2);
    ofstream file;
    file.open("provisorioP.txt");                           //storing packages information into the temporary file

    file << to_string(p[p.size() - 1].identifier) + '\n';   //id of the last package on the list
    for (int i = 0; i < p.size(); i++) {                    //storing the package information into the temporary file
        file << to_string(p[i].identifier) + '\n'
             << p[i].local + '\n'
             << concDate_begin(p[i]) + '\n'
             << concDate_end(p[i]) + '\n'
             << to_string(p[i].price) + '\n'
             << to_string(p[i].places) + '\n'
             << to_string(p[i].maxPeople);
        if (i != p.size() - 1) {
            file << '\n';
            file << "::::::::::\n";
        }

    }
    file.close();
}

