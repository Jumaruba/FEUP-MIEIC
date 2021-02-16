//
// Created by maruba on 13-04-2019.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map>
#include <utility>
#include <iterator>
#include "menu.h"
#include "clients.h"

using namespace std;


//GLOBAL VARIABLES ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

vector<Clients> c;
std::vector<std::string> text;
std::vector<Packs> p;

//FUNCTIONS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//BEFORE START+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// reads agency file

/*
function: reads agency file 

line: what is written at file agency in a specific line
*/


Agency readAgency() {

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

    Agency a(text[0], text[1], text[2], text[3], text[4], text[5]); //store all the text information into the agency class "a"
    readClient(a);       //reads clients file and visualstore the clients information into the client class "c"
    readPack(a);         //reads packages file and store the ifnormation into the package class "a"
    file.close();
    return a;
}

//---------------------------------------------------------------------------------------------------------------------

/*
function: this function read clients file and store the information into the vector<Clients> c

line: whats is written in the file of clients in a specific line
*/

void readClient(Agency a) {
    text.clear();                               // clear the previous information at the string vector text
    string line;                                // string to read the lines

    ifstream file;
    file.open(a.getCliente());                  //opening clients file

    if (file.is_open()) {
        while (getline(file, line)) {		//for each line of the text
            text.push_back(line);               //storing information at text vector
        }
    } else
        cout << "Error! " << a.getCliente() << " not found." << endl;

    putClient();                                //store the information read into vector<Clients> c in the right format
    file.close();
}

//---------------------------------------------------------------------------------------------------------------------

//read package file and store information into the struct Pack p

/*
function: this function read clients file and store the information into the vector<Packs> p 

line: what is written in the file of packages in a specific line
*/

void readPack(Agency a) {
    text.clear();                               // clear the previous information at the string vector text
    string line;                                // string to read the lines

    ifstream file;
    file.open(a.getPack());                    	//opening package file

    if (file.is_open()) {
        while (getline(file, line)) {
            text.push_back(line);               //storing information at text vector
        }
    } else
        cout << "Error!" << a.getPack() << " not found." << endl;

    putPack();                                  //store the information read into vector<Packages> p in the right format
    file.close();
}

//--------------------------------------------------------------------------------------------------------------------

/*
function: this function reads clients file and store the information into the GLOBAL VARIABLE vector<Clients> c 

vector<string> information: each string of this vector is a line of the file about clients
Clients temporary: temporary object that will be added to the global variable vector<Clients> c
*/

void putClient() {
    vector<string> information;


    for (int i = 0; i < text.size(); i++) {     //for each client, store the information at the temporary object
        trim(text[i]);
        if (text[i] != "::::::::::") {

            information.push_back(text[i]); //push_back the line to the vector
        } 
	    else {                            //if it finds ":::::::::::::"
            Clients temporary(information[0], information[1], information[2], information[3], information[4], information[5]);  //Initializing the temporary object
            c.push_back(temporary);            //push the temporary Client to the vector of Clients
            information.clear();		//clear to add the information about the new client
        }

    }
    Clients temporary(information[0], information[1], information[2], information[3], information[4], information[5]);
    c.push_back(temporary);                    //push the last client
}

//--------------------------------------------------------------------------------------------------------------------

/*
function: this function reads the package file and sotre the information the GLOBAL VARIABLE vector<Packs> p

vector<string> information: each string of this vector is a line of the file about packages 
Packs temporary: temporary object that will be added to the GLOBAL VARIABLE vector<Packs> p
*/

void putPack() {
    vector<string> information;


    for (int i = 1; i < text.size(); i++) {     //for each client, store the information at the temporary object
        trim(text[i]);
        if (text[i] != "::::::::::") {
            information.push_back(text[i]); //push_back the line to the vector
        } else {                              //if it finds ":::::::::::::"
            Packs temporary(information[0], information[1], information[2], information[3], information[4],
                            information[5], information[6]);
            p.push_back(temporary);            //push the temporary Client to the vector of Clients
            information.clear();
        }

    }
    Packs temporary(information[0], information[1], information[2], information[3], information[4], information[5],
                    information[6]);
    p.push_back(temporary);                    //push the last client
}

//END+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
function:Write all the client information into a temporary file
@param file output stream
@param srtStream stringstream to read file
*/
void writeClient() {
    cout << fixed << setprecision(2);
    ofstream file;
    stringstream strStream;
    file.open("provisorioC.txt");               //creating temporary file

    for (int i = 0; i < c.size(); i++) {        //storing the clients information into the temporary file
        strStream << c[i];
        if (i != c.size() - 1) {
            strStream << '\n';
            strStream << "::::::::::\n"; //End of one client
        }

    }
    file << strStream.str(); //Closing streams
    file.close();
}

//--------------------------------------------------------------------------------------------------------------------

/*function: Write all package information into a temporary file
@param file: file output stream
@param strStream string stream to read file
*/
void writePack() {
    cout << fixed << setprecision(2);
    ofstream file;
    stringstream strStream;
    file.open("provisorioP.txt");                           //storing packages information into the temporary file

    strStream << p[p.size() - 1].getId() << '\n';   //id of the last package on the list
    for (int i = 0; i < p.size(); i++) {                    //storing the package information into the temporary file
        strStream << p[i];
        if (i != p.size() - 1) {
            strStream << '\n';
            strStream << "::::::::::\n";//End of one pack
        }

    }
    file << strStream.str(); //Closing streams
    file.close();
}

//MENU LAYER 1++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/*
function: this function is the MAIN MENU that will call other menus 

int menu_option: menu option given by the user for the MAIN MENU (LAYER 1)
int second_option: menu option given by the user for the MENU LAYER 2
int position_pack: the position of the package at vector<Packs> p
int position_client: the position of the client at vector<Clients> c that will buy the package
auto v: vector<pair<string, int>> sorted by the second argument of the pair<string, int>  
auto v1: vector<string> v1 gets the relation of places that a client should visit as a suggestion 
auto ids: /this is vector<int> ids. The position 0 corresponds to the package id that the clients of the position 0 of the vector<Clients> c should buy and so on.
*/


void mainMenu(Agency a) {
    int menu_option = 0;                 
    int second_option = 0;                 
    int position_pack;                      
    int position_client;                   

    while (menu_option != 7) {              //if menu_option == 7, exit program

        clear_screen();                     //clear screen for linux and windows
	
	//MENU VISUALIZATION 
	    
        cout << "-------------- MENU -------------- " << endl       //show menu
             << "1. Clients management" << endl
             << "2. Turistic packages management" << endl
             << "3. Information visualization" << endl
             << "4. Buy a package" << endl
             << "5. Visualize most visited places" << endl
             << "6. Client Suggestion" << endl
             << "7. Exit" << endl;


        menu_option = cin_menu(7, 1);           //user type a VALID menu option
        clear_screen();                         //clear screen for linux and windows

        //CLIENT MANAGEMENT 
	    
        switch (menu_option) {
            case 1: {
                second_option = menuManage("CLIENT", "client");  //show menu and get the option for this secondary menu
                clear_screen();
                manageClient(second_option);                     //Handle the option selected by the user
                break;
            }

         //PACKAGE MANAGEMENT 

            case 2: {
                second_option = menuManage("PACKAGE", "package");//show menu and get the option for this secondary menu
                clear_screen();
                managePack(second_option);                       //handle the option selected by the user
                break;
            }

         //INFORMATION VISUALIZATION

            case 3: {
                second_option = menuVisual();                   //shows menu and get the option for this secondary menu
                clear_screen();                                 //clear screen for linux and windows
                if (second_option != 3) {                       //back option
                    if (second_option == 1) {                   
                        clientVisual();                         //MENU LAYER 3 client visualization 
                    } else
                        packagesVisual();                       //MENU LAYER 3 package visualization 
                }
                break;
            }

        //BUY A NEW PACKAGE 

            case 4: {
                position_pack = searchPack();           //search the position of the package to be purchased at vector<Packs> p
		    
                if (position_pack!= -1 ) {		//the position_pack == -1 if the package DOESN'T exist
			
                    if (p[position_pack].getId() > 0) {  //id> 0 if package is available
			    
                        cin.ignore();
                        position_client = searchNif();     //search the NIF of the clients to whom the package will be added
			    

                                c[position_client].appendListPacks(p[position_pack].getId());  //add the package to the client list of packages
                                c[position_client].setProfit();     //updating the amount purchased

                                for (int j = 0; j < p.size(); j++ )     //update packages reservations
                                    p[j].setReserved();

                                cout << "Done. Press ENTER to continue...";
                                cin.ignore();
                                cin.ignore();
                            
                        
                    } else if (position_pack < 0) {     //if the package doesn't exist
                        cout << "Type positive numbers!" << endl;
                        cout << "Press ENTER to continue...";
                        cin.ignore();
                        cin.ignore();
                    }
                }

                break;
            }
			
                
	//VISUALIZE THE MOST VISITED PLACES 

            case 5: {
                auto v = sortedVisitedPlace();	//get a vector<pair<string, int>> sorted by the second argument of the pair<string, int> 
                showMostVisited(v);		//this shows a table of the most visited places 
                
		cout << endl;
                cout << "Press ENTER to continue..." << endl;
                cin.ignore();
                cin.ignore();

                break;
            }

	//VISUALIZE SUGGESTION OF PACKAGES TO BUY FOR EACH CLIENT

            case 6: {
                auto v = sortedVisitedPlace();  //vector<pair<string, int>> v sorted by the second argument of the pair<string, int> 
                auto v1 = clientSuggestion(v);  //this vector<string> v1 gets the relation of places that a client should visit as a suggestion 
		    
                auto ids = getPackageId(v1);    
		    //this is vector<int> ids. The position 0 corresponds to the package id that the client 
		    // of the position 0 of the vector<Clients> c should buy and so on.
		    
                showClientSuggestion(ids);  	// this shows a table of suggested packages that each client should buy 
                cout << "Press ENTER to continue... " << endl;
                cin.ignore();
                cin.ignore();
            }

         //EXIT MENU

            case 7: {
                string file;
                writeClient();                  //write all the clients information into a provisory file
                writePack();                    //write all the packages information into a provisory file
                remove(a.getPack().c_str());         //remove the original package file
                remove(a.getCliente().c_str());      //remove the original package client
                rename("provisorioC.txt",
                       a.getCliente().c_str());   //rename the client provisory file to the original one
                rename("provisorioP.txt",
                       a.getPack().c_str());      //rename the package provisory file to the original one

                break;

            }


        }

        if (menu_option != 7 && menu_option !=
                                5) {     //even if the user don't wanna exit, for each interaction, the information will stored at provisory files
            writeClient();          //write all the clients information into a provisory file
            writePack();            //write all the packages information into a provisory file
        }
    }
}


//MENU LAYER 2 (MANAGEMENT)++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//calls the functions to manage the client given the option


/*
function: visualization of the 2 LAYER MENU 
option: the menu option 
*/

int menuVisual() {
    int variable;

    cout << "---------------- VISUALIZATION MENU ----------------" << endl
         << "1. Clients" << endl
         << "2. Packages" << endl
         << "3. Back" << endl;

    variable = cin_menu(3, 1);      //desired option given by the user
    return variable;                //return the option
}


/*
function: handle the menu for CLIENT MANAGEMENT (new client, change client information and remove a client) 

option: the menu option 
*/


void manageClient(int option) {
    if (option == 1) {
        newClient();                //creates a new client
    } else if (option == 2) {
        changeClient();             //change a client
    } else if (option == 3) {
        removeClient();             //remove a client
    }
}



/*
function: handle the menu for PACKAGE MANAGEMENT (new package, change package information and changes a state of a package) 

option: the menu option 
*/


void managePack(int option) {
    clear_screen();
    switch (option) {
        case 1:
            newPack();      //it creates a new package
            break;
        case 2:
            changePack();   //it changes a specific component in a package
            break;
        case 3:
            removePack();   //it DOESN'T remove a package. It actually changes a availability of a package
            break;
    }
}


/*
function: this functions shows the LAYER MENU 2 for management of packages and clients (both) 

@param optCap: can be "CLIENT" or "PACKAGE" 
@param opt: can be "client" or "package" 
return desired menu option
*/

int menuManage(const string &optCap, const string &opt) {
    string j;
    if (opt == "client") // checks if current option is "client"
        j = "Remove";
    else
        j = "Change availability";
    int variable;
//table for information visualization format
    cout << "-------------- " << optCap << "S" << " MANAGEMENT" << " --------------" << endl
         << "1. New " << opt << endl
         << "2. Change " << opt << endl
         << "3. " << j << " " << opt << endl
         << "4. Back"
         << endl;

    variable = cin_menu(4, 1);          //menu option desired
    return variable;
}

//MENU LAYER 2 (MENU VISUALIZATION)+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
funtion: Client visualization
@param option menu option given by user
@param position client position in struct vector
*/
void clientVisual() {
    int option;                                         // menu option typed by the user
    int position;                                       // position of the  client int the struct vector
	
    do {
        clear_screen();
        cout << "Type the option you wish to change:" << endl
             << "1. One client" << endl
             << "2. All clients" << endl
             << "3. Back" << endl;

        option = cin_menu(3, 1);                        //set the option given by the user
        clear_screen();                                 //clear screen

        if (option == 1) {                              //information just for one client
            cin.ignore();
            position = searchNif();                    //search the postion of the client in the client struct vector
            if (position != -1) {
                c[position].headInfoClient();                     //shows the head table
                c[position].visualizeClient();                    //shows the clients information

                cout << endl << "Press ENTER to continue...";
                cin.ignore();
                cin.ignore();
            }

        } else if (option == 2) {
            int position = 0;

            c[position].headInfoClient();                     //show the head table

            for (int position = 0; position < c.size(); position++)
                c[position].visualizeClient();                //shows the clients information



            cout << endl << "Press ENTER to continue...";
            cin.ignore();
            cin.ignore();
        }
    } while (option != 3);  // if the option is "back", do not nothing


}//menu for client visualization and printing

/*
function: package visualization
@param place: place to search for
@param option: menu option given
@param begin: begining date for pack
@param end: ending date for pack
*/

void packagesVisual() {  //menu for visualization package
    string place; // the name of the specif place we wanna search
    int option = 0;
    Date begin;
    Date end;


    do {
        bool show_cabecalho = false;

        clear_screen();
        cout << "---------------- PACKAGE VISUALIZATION MENU ----------------" << endl
             << "1. All the packages" << endl
             << "2. Packages related to a place" << endl
             << "3. Packages between dates" << endl
             << "4. Packages related to a place and between two dates" << endl
             << "5. Packages related to a client " << endl
             << "6. All packages purchased" << endl
             << "7. Total profit and packages purchased" << endl
             << "8. Back" << endl;

        option = cin_menu(8, 1);
        clear_screen();

        switch (option) {
            case 1: { //Print all packages
                p[0].headInfoPack();
                for (int i = 0; i < p.size(); i++) {
                    p[i].visualizePack();// print package
                }
                cout << endl << "Press ENTER to continue...";
                cin.ignore();
                cin.ignore();
                break;
            }

            case 2: { //Print all packages related to a given place

                cin.ignore();
                cout << "Type the name of the place (EXIT-0): ";
                getline(cin, place);
                if (place != "0") {//->0 exits operation
                    for (int i = 0; i < p.size(); i++) { //if this place is a destine of this pack
                        if (p[i].searchPlace(place)) { //if its true
                            if (!show_cabecalho) {
                                show_cabecalho = true;
                                p[i].headInfoPack();
                            }
                            p[i].visualizePack();//prints the pack
                        }
                    }
                    if (!show_cabecalho) {
                        cout << "No package is related to " << place << endl;
                        cout << "Press ENTER to continue...";
                        cin.ignore();
                    } else {
                        cout << endl << "Done. Press ENTER to continue...";
                        cin.ignore();
                    }
                }
                break;
            }


            case 3: { // Print all packages related between two dates
                cout << "Type begin date: " << endl;
                begin.setDate(); //Set begining dadte
                cout << "Type ending date: " << endl;
                end.setDate(); // Set ending date

                for (int i = 0; i < p.size(); i++) {
                    if (end.isBefore(p[i].dEnd) && begin.isAfter(p[i].dBegin)) {
                        if (!show_cabecalho) {
                            show_cabecalho = true;
                            p[0].headInfoPack();//Print info table
                        }
                        p[i].visualizePack(); //Print pack
                    }
                }
                if (!show_cabecalho) {
                    cout << "No package is related to the conditions specified" << endl;
                    cout << "Press ENTER to continue...";
                    cin.ignore();

                } else {
                    cout << endl << "Done. Press ENTER to continue...";
                    cin.ignore();
                }
                break;
            }


            case 4: { // Print all packages related between a place and two dates
                cout << "Type begin date: " << endl;
                begin.setDate();//Set begining date
                cout << "Type ending date: " << endl;
                end.setDate();//Set ending date
                cin.ignore();
                cout << "Type the place: ";
                cin.ignore();
                getline(cin, place);//Get place

                for (int i = 0; i < p.size(); i++) {
                    if (p[i].searchPlace(place) && end.isBefore(p[i].dEnd) && begin.isAfter(p[i].dBegin)) {
                        if (!show_cabecalho) {
                            show_cabecalho = true;
                            p[i].headInfoPack();//Print info table
                        }
                        p[i].visualizePack();
                    }
                }
                if (!show_cabecalho) {
                    cout << "No package is related to " << place << endl;
                    cout << "Press ENTER to continue...";
                    cin.ignore();
                } else {
                    cout << endl << "Done. Press ENTER to continue...";
                    cin.ignore();
                }

                break;
            }


            case 5: { // Print all packages related to a client
                int cPosition;
                int pPosition;
                cin.ignore();
                cPosition = searchNif();   //client position;
                if (cPosition != -1) {
                    for (int i = 0; i < c[cPosition].getVectorPacks().size(); i++) {
                        pPosition = searchPack_bool((c[cPosition].getVectorPacks()[i]));
                        if (pPosition != -1) {              // if the package is at the list
                            if (!show_cabecalho) {
                                show_cabecalho = true;      //show the cabecalho se houver packages disponiveis
                                p[pPosition].headInfoPack(); //print info table
                            }
                            p[pPosition].visualizePack();             //show the package
                        }

                    }
                    if (!show_cabecalho) {
                        cout << "No package is related to " << c[cPosition].getName() << endl;
                        cout << "Press ENTER to continue...";
                        cin.ignore();
                        cin.ignore();
                    } else {
                        cout << endl << "Done. Press ENTER to continue...";
                        cin.ignore();
                        cin.ignore();

                    }
                }

                break;
            }


            case 6: { //Print all packages purchased
                vector<int> allpurchased; //vector of purchased packs
                for (auto x: c) {
                    for (auto j: x.getVectorPacks()) {
                        allpurchased.push_back(j);//push back all packages in all clients
                    }
                }

                duplicate(allpurchased);

                p[0].headInfoPack(); //print info table
                for (auto x: p) {//for every x(item) in packs vector
                    for (auto j: allpurchased) {
                        if (x.getId() == j)
                            x.visualizePack();//print pack
                    }
                }
                cout << endl << "Press ENTER to coninue ...";
                cin.ignore();
                cin.ignore();
                break;

            }

            case 7: { //Total profit and number of packs purchased
                vector<string> allPacks;
                float profit = 0;
                int totalPurchased = 0;  //number o packages purchased;

                for (int i = 0; i < c.size(); i++) {
                    split(allPacks, c[i].getListPacks(), ';');  //puting all packages in a pack;
                    totalPurchased += c[i].getPurchased();//adds to the total purchased packs
                }

                    for (auto total: c)
                        profit += total.getProfit();


                    cout << endl << "TOTAL PURCHASED = " << totalPurchased << endl;
                    cout << "TOTAL PROFIT = " << profit << endl;

                    cout << "Done. Press ENTER to continue...";
                    cin.ignore();
                    cin.ignore();
                    cout << endl;
                    clear_screen();
                    break;
                }
            }
        }while (option != 8);//->8 exits operation
}  //menu for packing visualization


//3 LAYER MENU (CLIENT MANAGEMENT)+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*function: creates a new client
@param aux auxiliary client
*/
void newClient() {
    Clients aux;
    cin.ignore();

    cout << "Type the name (EXIT - 0): ";
    aux.setName();//Sets name
    if (aux.getName() != "NAME") {
        cout << "Type the nif (EXIT - 0): ";
        aux.setNif();//Sets nif
        if (aux.getNif() != 0000000000) {//cant be 00000000000
            cout << "Type the number of people at person's family (EXIT -0): ";
            aux.setPeople();//Set number of people in family
            if (aux.getPeople() != 0) {//->0 exits operation
                cout << "Type the address:" << endl;
                aux.setAddress();//Set adr4ess
                if (aux.getVectorAddress()[4] != "CITY") { //Cannot be "CITY"
                    aux.setListPacks();//Set list of packages
                    aux.setProfit();

                    for (int j = 0; j < p.size(); j++ )     //update packages reservations
                        p[j].setReserved();

                    if (aux.getVectorPacks()[0] != 0) { //->0 exits operation
                        c.push_back(aux); //Add the new client to the clients vector
                        cout << "Done! Press ENTER to continue...";
                        cin.ignore();
                        cin.ignore();
                    }
                }
            }
        }
    }

}
/*
function: Change client
*/

void changeClient() {
    string name;    //client's name
    int position;  //position of the client
    int option;     //menu option
    string aux;     // aux string for some propourse
    string operation = "Y"; //Y if the user wanna do a client chage again for the same client


    cin.ignore();
    position = searchNif(); //Search client index at vector based on nif given by the user
    if (position != -1) {
        do {
            clear_screen();


            c[position].headInfoClient(); // Print table of client at index 'position' in client vector
            c[position].visualizeClient(); // Print client information at index 'position' in client vector
            cout << endl;

            cout << "What do you wish to change? " << endl
                 << "1. Name" << endl
                 << "2. Nif" << endl
                 << "3. Number of people" << endl
                 << "4. Address" << endl
                 << "5. List of packages" << endl
                 << "6. Back" << endl;


            option = cin_menu(6, 1);
            clear_screen();

            switch (option) {
                case 1: { // if client wants to change the name
                    cout << "The actual name is: " << c[position].getName() << endl;     //show the actual name
                    cin.ignore();
                    cout << "Type the name (EXIT -0): "; //user types the new name
                    c[position].setName(); // Set name of client at index 'position' in client vector
                    cout << "The actual name is: " << c[position].getName() << endl; //shows the new actual name


                    break;
                }

                case 2:  // If client wants to change nif
                {
                    cout << "The actual nif is: " << c[position].getNif() << endl;   //show the actual nif
                    cin.ignore();
                    cout << "Type the nif (EXIT -0): ";
                    c[position].setNif(); // Set nif of client at index 'position' in client vector
                    cout << "The actual nif is: " << c[position].getNif() << endl;   //shows the new actual nif
                    cin.ignore();

                    break;
                }

                case 3:  //If client wants to change number of people in his family
                {
                    cout << "The actual Number of people is: " << c[position].getPeople()
                         << endl;   //shows the actual number
                    cout << "Type the number of people (EXIT -0): ";
                    c[position].setPeople(); // Set number of people in family of client at index 'position' in client vector
                    cout << "The actual Number of people is: " << c[position].getPeople()
                         << endl;  //show the new actual number
                    cin.ignore();

                    break;
                }

                case 4:  //if the client wanna change the address
                {
                    cout << "The actual address is: "
                         << c[position].getAddress() << endl;  //shows the actual address
                    c[position].setAddress(); // Set adress of client at index 'position' in client vector
                    cout << "The actual address is: "
                         << c[position].getAddress() << endl;  //shows the new actual address


                    break;
                }

                case 5: //If client wants to change list of packages
                {
                    cout << "The actual list o packages is: " << c[position].getListPacks() << endl;

                    c[position].setListPacks(); // Set package list of client at index 'position' in client vector
                    c[position].setProfit();
                    for (int j = 0; j < p.size(); j++ )     //update packages reservations
                        p[j].setReserved();
                    cout << "The actual list o packages is: " << c[position].getListPacks()
                         << endl;  //show the new package list
                    break;

                }
            }


                    cout << "Other client change operation ?[y|n]" << endl;

                    operation = valid_yes();  //asks if the user wanna do another operation.



            }while (operation == "Y");
        }

    }


/*
function: remove client
@param position: client index
*/
void removeClient() {
    int position; //Index of client

    cin.ignore();
    position = searchNif();            //searches the position for the client
    if (position != -1) {
        c.erase(c.begin() + position);      //erases the client
        for (int j = 0; j < p.size(); j++ )     //update packages reservations
            p[j].setReserved();
        cout << "Done! Press ENTER to continue...";
        cin.ignore();
        cin.ignore();
    }
}   //removes a client from the struct vector



//3 LAYER MENU (PACKAGE MANAGEMENT)+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
function: create new package
@param aux new package
*/
void newPack() {
    Packs aux;
    cout << "Type the new ID (EXIT -0): ";
    aux.setId();                                // set the id and checks if it's integer
    if (aux.getId() != 0) {
		cout<<"City-Locale,locale,locale...."<<endl;
        cin.ignore();
        cout << "Type the locals (EXIT -0): ";
        aux.setLocal();                             //set the local of auxiliary pack
        if (aux.getLocal() != "0") {
			cout<<"DD/MM/YYYY"<<endl;
            cout << "BEGIN date: " << endl;
            aux.dBegin.setDate(); //Set begining date of auxiliary pack

            cout << "ENDING date: " << endl;
            aux.dEnd.setDate(); //Set ending date of auxiliary pack

            cout << "Type the price (EXIT -0): ";
            aux.setPrice();                             // get the prince and checks if it's float
            if (aux.getPrice() != 0) {
                aux.setReserved();
                    cout << "Type the max number of people (EXIT -0): ";
                    aux.setMaxPeople();                         // get the number of max people and checks if it's integer
                    if (aux.getMaxPeople() != 0) {
                        p.push_back(aux);                           //add the package to the package vector

                        cout << "Done! Press ENTER to continue...";
                        cin.ignore();
                        cin.ignore();
                    }
                }
            }
        }
    }


/*
function: Edit an existing package
@param position index at package vector
@param operation: operation to be performed in menu
@param again control loop
@param option menu ooption given by the user
@param aux auxiliary string
*/

void changePack() {
    int position;
    string operation = "y";
    bool again = false;
    int option;
    string aux;

    cin.ignore();
    position = searchPack();  //position = -1 case it's not possible to find a package
    clear_screen();

    if (position != -1) {
        do {
            cout << endl;
            p[position].headInfoPack();
            p[position].visualizePack();
            cout << endl;

            cout << "Type the option you wish to change:" << endl
                 << "1. Id" << endl
                 << "2. Local" << endl
                 << "3. Begin date" << endl
                 << "4. Ending date" << endl
                 << "5. Price" << endl
                 << "6. Number max of people" << endl
                 << "7. Back" << endl;


            option = cin_menu(7, 1);

            switch (option) {
                case 1: { //Change pack ID
                    cout << "The actual id is: " << p[position].getId() << endl;
                    cin.ignore();
                    cout << "Type the new id (EXIT -0): ";
                    p[position].setId(); //Change ID of pack at index position in pack vector
                    cout << "The actual id is: " << p[position].getId() << endl;


                    break;
                }
                case 2: { //Change pack local
                    cout << "The actual locals are: " << p[position].getLocal() << endl;
                    cin.ignore();
                    cout << "Type the new locals (EXIT -0): ";
                    p[position].setLocal(); //Change local of pack at index position in pack vector
                    cout << "The actual locals are: " << p[position].getLocal() << endl;
                    cin.ignore();


                    break;
                }
                case 3: { //Change pack's begining date
                    cout << "The actual begin date is: " << p[position].dBegin.getDate() << endl;
                    if (proceed()) {
                        cin.ignore();
                        cout << "Type the new date: " << endl;
                        p[position].dBegin.setDate(); //Change begining date of pack at index position in pack vector
                        cout << "The actual begin date is: " << p[position].dBegin.getDate() << endl;
                        cin.ignore();
                    }
                    break;
                }
                case 4: //Change pack's ending date
                    cout << "The actual ending date is: " << p[position].dEnd.getDate() << endl;
                    if (proceed()) {
                        cin.ignore();
                        cout << "Type the new date: " << endl;
                        p[position].dEnd.setDate(); //Change ending date of pack at index position in pack vector
                        cout << "The actual ending date is: " << p[position].dEnd.getDate() << endl;
                        cin.ignore();
                    }
                    break;
                case 5: { //Change pack's price
                    cout << "The actual price is: " << p[position].getPrice() << endl;

                    cin.ignore();
                    cout << "Type the new price (EXIT -0): ";
                    p[position].setPrice(); //Change price of pack at index position in pack vector
                    cout << "The actual price is: " << p[position].getPrice() << endl;
                    cin.ignore();

                    break;
                }


                case 6: { //Change maximum number of people
                    cout << "The actual number of people is: " << p[position].getMaxPeople() << endl;

                    cin.ignore();
                    cout << "Type the new number o people (EXIT -0): ";
                    p[position].setMaxPeople(); //Change maximum number of people of pack at index position in pack vector
                    cout << "The actual max number of people is: " << p[position].getMaxPeople() << endl;
                    cin.ignore();
                    break;
                }
            }

            if (option != 7) {
                cout << "Other package change operation ?[y|n]" << endl;
                operation = valid_yes();
            }
        } while (operation == "Y"); //In case the user pressed y when asked for [y/n]
    }
}  //to change a package
/*
function: remove a package
@param position pack index at pack vector
*/

void removePack() {
    int position;

    cin.ignore();
    position = searchPack();//get pack index
    p[position].setIdSimple(0 - p[position].getId());//set ID
    cout << "Done! Press ENTER to continue...";
    cin.ignore();
} // to remove a pack


//OTHERS ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
function: the function asks the id package and find it's position on the GLOBAL VARIABLE vector<Packs> p
*/
int searchPack() {
    string srepeat = "N";                                   	//case the client wants to repeat the action for search
    int id,k=0;                                                 //number of the id to searched
    do {
        cout << "Type the id of the package (exit - 0): ";
        id = isNum(int(0));                                     //checking if the input is int
        if (id != 0) {                                       	//if it's 0 the mission is aborted
            for (int i = 0; i < p.size(); i++) {            	//searchs for package position
                if (p[i].getId() == id and id>=0){
                    return i;                               	//return the position
				}
				else if(p[i].getId() == id && id<0){
					k = 1;
            	}
			}
			if(k == 0){
            cout << "Error! It's not possible to find " << id
                 << ". Do you wanna try again?[y|n]";   	// case is hasnt's been found

            srepeat = valid_yes();                          	// in case of failure, it asks the client if its wanna try again
			}
			else if(k == 1){
			cout << "Error! This package is unavailable " << " "
                 << ". Do you wanna try again?[y|n]";   	// case is hasnt's been found

            srepeat = valid_yes();                   
			}
        }
    } while (srepeat == "Y");
    return -1;
}

//---------------------------------------------------------------------------------------------------------------------
/*
function: search the pack that contains number as id and returns if there's a package with the given id

int number: given ID
*/

int searchPack_bool(int number) {

    for (int i = 0; i < p.size(); i++) {  
        if (p[i].getId() == number)   	   // if found
            return i;                    //return the position
    }
    return -1;                           //else return -1
}


//---------------------------------------------------------------------------------------------------------------------

/*
function: this functions returns the client's position at the GLOBAL VARIABLE vector<Clients> c

nif: input for client's nif
*/


int searchNif() {
    string again = "N";
    do {
        cout << "Type the client's NIF (EXIT -0): ";
	    
        int nif = isNum(int(0));
        if (nif == 0) {	//case the user wants to cancel the operation 
            break;
        }
        for (int i = 0; i < c.size(); i++) { //search the nif in vector<Clients> c 
            if (c[i].getNif() == nif)
                return i;	//returns the position at vector<Clients> c
        }

        cout << "There is no nif = " << nif << ". Would you wish to try again?[y|n] ";
        again = valid_yes();	
    } while (again == "Y");
    return -1;
}

//---------------------------------------------------------------------------------------------------------------------

/*
function: this function searches the client that contains int number as NIF and returns if there's a client with the given nif
*/

int searchNif_bool(int number) {
    for (int i = 0; i < c.size(); i++) {
        if (c[i].getNif() == number)
            return i;
    }
    return -1;
}


//THE MOST VISITED PLACES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*
function: returns a sorted vector<pair<string,int>>. It's sorted by the second argument of pair

map<string, int> places: a relation <package local, number of times it was visited> 
vector<pair<string,int>> v: the sorted vector to be returned 
map<string, int>::iterator it: iterator to deal with the map<string, int> places 
*/

vector<pair<string, int>> sortedVisitedPlace() {

    map<string, int> places;
    string aux;
    vector<pair<string, int>> v;
    map<string, int>::iterator it;

//this for loop creates the map<string, int> places
	
    for (auto x: p) {				//for each package 
        for (auto local: x.getPlacesVec()) {	//for each local in each package
            aux = maiusculo(local);		//local in upper case 
            
	//this piece of code cleans the local string(aux)----
	    if (aux == "-")
                continue;
            else if (aux[aux.size() - 1] == ',') {
                aux.erase(aux.end() - 1);
            }
	//----------------------------------------------------
            places.insert(pair<string, int>(aux, 0)); //add the local and the to the map<string, int> places
        }
    }

//this for loop counts how many times the place was visited 

    for (auto pack: p) {

        //for all the locals related to the package, increases by the number of times it was visited (the second argument at map places)
        for (auto local: pack.getPlacesVec()) {
            it = places.find(maiusculo(local));
            it->second += pack.getReserved();
        }
    }




//transfering the components of map<string,in> places to vector<pair<string,int>> v
    for (auto itr = places.begin(); itr != places.end(); itr++)
        v.emplace_back(*itr);
	
//sort the vector<pair<string,int>> v by the second parameter of pair<string,int> 
    sort(v.begin(), v.end(), [=](std::pair<string, int> &a, std::pair<string, int> &b) {
        return a.second > b.second;
    });

    return v;
}

//--------------------------------------------------------------------------------------------------------------------

/*
function: this function shows the head of the table for the most visited places 
*/

void placesHead() {
    cout << endl;
    cout << left << setw(25) << "| PLACE"        //print formated information
         << setw(15) << "| NUM PURCHASED" << endl;
    cout
            << "---------------------------------------------" << endl;
}
//---------------------------------------------------------------------------------------------------------------------

/*
function: this function shows the data of each place: the name and the number og times it was visited 

pair<string, int> p: pair containing the information 
*/


void visualizePlaces(pair<string, int> p) {
    cout << left << "|" << setw(24) << p.first  //show client information
         << "|" << setw(14) << p.second << endl;
}

//---------------------------------------------------------------------------------------------------------------------
/*
function:this function actually shows the table of the most visited places  

pair<string, int> p: pair containing the information 
*/

void showMostVisited(vector<pair<string, int>> v) {
    int see;
    cout << "There is a total of " << v.size() << " possible destinations. How many of the most visited places do you wish to visualize? ";
    see = cin_menu(v.size(), 1);        //see needs to be smaller than size
    placesHead();
    for (int i = 0; i < see; i++) {
        visualizePlaces(v[i]);
    }

}

//CLIENTS SUGGESTION OF PACKAGES TO BUY+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/*
function:this function returns a vector<string> with the place the client should visited based on the most visited places

vector<pair<string, int>> v: vector containing the relation <place, number of times it was visited> 
vector<string> places: contains the places that the client has already visited 
vector<string> placeClient: vector containing the place the client should visit
bool there: control loop 
*/

vector<string> clientSuggestion(vector<pair<string, int>> v) {
    //criar um vetor dos lugares que o cliente ja foi
    //comparar com vector de pares

    vector<string> places;
    vector<string> placeClient;
    bool there;

	
    for (auto client: c) {
        there = false;
        for (auto j: client.getVectorPacks()) {
            for (auto pack: p) {
                if (pack.getId() == j) {
                    for (auto lugares: pack.getPlacesVec()) {
                        places.push_back(lugares);	//push the places the client has already visited in a certain package
                    }
                }
            }
        }
	    
        for (auto itr = v.begin(); itr != v.end(); itr++) {	//for each place of the most visited places 
            there = false;		//considering that the place wasn't visited yet
            
	    for (auto l: places) {
                if (maiusculo(l) == itr->first) {
                    there = true;	// if the place is actually visited
                    break;		//stop searching
                }
            }
            if (!there) {		//if the place wasn't visited 
                placeClient.push_back(itr->first);	//add the place to the vector placeClient
                break;
            }
        }
	    places.clear();
    }


    return placeClient;


}

//-------------------------------------------------------------------------------------------------------------------

/*
function:given a vector with the places the client should visit,returns a vector with the package that each client should buy

 vector<int> package: vector to be returned
*/

vector<int> getPackageId(vector<string> placeClient) {
    vector<int> package;
    for (auto j: placeClient) {
        for (int i = 0; i < p.size(); i++) {
            for (auto x: p[i].getPlacesVec()) { //search the ID releated to the place j
                if (maiusculo(x) == j)
                    package.push_back(p[i].getId()); //if there is this place in the vector, add to the vector 
            }
        }
    }

    return package;

}

//-------------------------------------------------------------------------------------------------------------------

/*
function: actually shows the table with clients and the packages suggested 
*/

void showClientSuggestion(vector<int> id) {
    int nDigitos = digits(id.size());
    int size = id.size();
    headClientSuggestion(nDigitos);
    for (int i = 0; i < size; i++)
        visualizeClientSuggestion(id[i], c[i], i, nDigitos, size);

}

//--------------------------------------------------------------------------------------------------------------------

/*
function: shows the data for the table of suggested packages to a client buys 
*/

void visualizeClientSuggestion(int id, Clients &client, int n, int nDigitos, int size) {

    cout.fill(' ');


    cout << left << "|" << setw(39) << client.getName()   //show client information
         << "|" << setw(19) << client.getNif()
         << "|" << setw(14) << id << endl;


}

//----------------------------------------------------------------------------------------------------------------------

/*
function: shows the head of the table for packages suggested for clients
*/

void headClientSuggestion(int nDigitos) {

    cout << left << setw(40) << "| NAME"        //print formated information
         << setw(20) << "| NIF"
         << setw(15) << "| PACKAGE SUGGESTION" << endl;

    cout << "------------------------------------------------------------------------------------" << endl;

}
