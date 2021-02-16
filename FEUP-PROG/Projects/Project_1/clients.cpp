//
// Created by maruba on 18-03-2019.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include "menu.h"
#include "clients.h"
#include "aux.h"

using namespace std;

//GLOBAL VARIABLES------------------------------------------------------------------------------------------------------

extern vector<client> c;
extern std::vector<std::string> text;

//FUNCTIONS-------------------------------------------------------------------------------------------------------------

//Count the number of packages in a string

int client::countPack(std::string word) {
    int contador = 0;                               //counter
    for (int i = 0; i < word.size(); i++) {         //counts the number of ";"
        if (word[i] == ';')
            contador++;
    }
    contador++;                                     //sum +1 to the result
    return contador;                                //return the number of packages
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//store the information of clients from the text vector to structs

void putClient() {
    client provisorio;          //temporary client struct
    int contador = 0;           //count the line of a client
    for (int i = 0; i < text.size(); i++) {     //for each client, store the information at the temporary struct
        trim(text[i]);
        if (text[i] != "::::::::::") {
            if (contador == 0)
                provisorio.name = text[i];

            else if (contador == 1)
                provisorio.nif = stoi(text[i]);

            else if (contador == 2)
                provisorio.nPeople = stoi(text[i]);

            else if (contador == 3) {
                split(provisorio.address, text[i], '/');
            } else if (contador == 4) {
                provisorio.listPacks = text[i];
                provisorio.nPurchased = provisorio.countPack(text[i]);
            }

            contador++;


        } else {                                //if it finds ":::::::::::::"
            contador = 0;                       //back to line zero of a client
            c.push_back(provisorio);            //push the temporary struct to the vector of structs
        }

    }
    c.push_back(provisorio);                    //push the last client
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//calls the functions to manage the client given the option

void manageClient(int option) {
    if (option == 1) {
        newClient();                //creates a new client
    } else if (option == 2) {
        changeClient();             //change a client
    } else if (option == 3) {
        removeClient();             //remove a client
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//function to creates a new client

void newClient() {
    client aux;
    cin.ignore();

    cout << "Type the name: ";
    getline(cin, aux.name);         //set the name

    cout << "Type the nif: ";
    aux.nif = isInt();              //set a valid int for the nif

    cout << "Type the number of people at person's family: ";
    aux.nPeople = isInt();          //set a valid int of the number of people

    cout << "Type the address: " << endl;
    addAddress(aux.address);        //set the address

    cout << "Type the list of packages purchased: ";
    getline(cin, aux.listPacks);                        //set the list of packages
    aux.nPurchased = aux.countPack(aux.listPacks);      //figure out the number of packages

    c.push_back(aux);                                   //push the new client to the clients vector

    cout << "Done! Press ENTER to continue...";
    cin.ignore();

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//separate a string given the string to be separated (m), string to put the result (line), and the caracter to use as parameter so separate

void split(std::vector<string> &m, string line, char caracter) {
    string aux;             //aux string
    m.clear();
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == caracter) {
            trim(aux);                      // we are removing unnecessary spaces;
            m.push_back(aux);
            aux = "";
        } else
            aux.push_back(line[i]);

    }
    trim(aux);
    m.push_back(aux);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void addAddress(std::vector<string> &m) {  //add a new address for the client
    string aux;
    cin.ignore();
    for (int i = 0; i < 5; i++) {
        if (i == 0)
            cout << "Street: ";  //in the first interaction asks the street
        else if (i == 1)
            cout << "Door number: ";  //in the second interaction asks the door number
        else if (i == 2)
            cout << "Floor number: "; //in the third interaction asks the floor number
        else if (i == 3)
            cout << "Zip code: ";  // in the fourth asks the zip code
        else if (i == 4)     // at the 5º operation, asks the city 
            cout << "City: ";

        getline(cin, aux);  //set the user input
        trim(aux);          //remove all lateral spaces 
        m.push_back(aux);   // add the information to the client 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void changeClient() {
    string name;    //client's name
    int position;  //position of the client
    int option;     //menu option 
    string aux;     // aux string for some propourse 
    string operation = "Y"; //Y if the user wanna do a client chage again for the same client
    bool again = false;


    cin.ignore();
    position = searchName();

    do {
        clear_screen();

        cout << left << setw(25) << "| NAME"        //print formated information
             << setw(15) << "| NIF"
             << setw(15) << "| NUMPEOPLE"
             << setw(55) << "| ADDRESS"
             << setw(20) << "| LISTPACKS"
             << setw(40) << "| NUMPACKS" << endl;

        cout
                << "----------------------------------------------------------------------------------------------------------------------------------------------"
                << endl;

        cout << left << "|" << setw(24) << c[position].name   //show client information
             << "|" << setw(14) << c[position].nif
             << "|" << setw(14) << c[position].nPeople
             << "|" << setw(54) << concatenate(c[position].address)
             << "|" << setw(19) << c[position].listPacks
             << "|" << c[position].nPurchased << endl << endl;



        cout << "----------- CLIENT CHANGE MENU ---------------" << endl
             << "1. Name" << endl
             << "2. Nif" << endl
             << "3. Number of people" << endl
             << "4. Address" << endl
             << "5. List of packages" << endl
             << "6. Back" << endl;


        option = cin_menu(6, 1);
        clear_screen();
        if (option == 1) {                                                   // if it's wanna change the name
            cout << "The actual name is: " << c[position].name << endl;     //show the actual name

            if (proceed()) {                                                //asks if the user wanna proceed with the action
                cin.ignore();
                cout << "Type the name: ";
                getline(cin, aux);                                          //user types the new name
                c[position].name = aux;
                cout << "The actual name is: " << c[position].name << endl; //shows the new actual name
                cin.ignore();
            }
        }
//--------------------------------------------------------------------------------------------------------------------
        else if (option == 2) {                                         //if it's wanna change the name
            cout << "The actual nif is: " << c[position].nif << endl;   //show the actual name
            if (proceed()) {                                            //asks if the user wanna proceed with the action
                cin.ignore();
                cout << "Type the nif: ";
                c[position].nif = isInt();                              //user types the new nif
                cout << "The actual nif is: " << c[position].nif << endl;   //shows the new actual name
                cin.ignore();
                cin.ignore();
            }
        }
//--------------------------------------------------------------------------------------------------------------------
        else if (option == 3) {                                         //if it's wanna change the number of people at family
            cout << "The actual Number of people is: " << c[position].nPeople << endl;   //shows the actual number

            if (proceed()) {                                            //asks if the user wanna proceed with the action
                cout << "Type the number of people: ";
                c[position].nPeople = isInt();                          //user types the new number
                cout << "The actual Number of people is: " << c[position].nPeople << endl;  //show the new actual number
                cin.ignore();
                cin.ignore();
            }
        }
//--------------------------------------------------------------------------------------------------------------------
        else if (option == 4) {                                         //if the client wanna change the address
            cout << "The actual address is: "
                << c[position].address[0] << " / "
                << c[position].address[1] << " / "
                 << c[position].address[2] << "/ "
                 << c[position].address[3] << " / "
                 << c[position].address[4] << endl;  //shows the actual address

            if (proceed()) {                        //asks if the client wanna proceed with the action
                cout << "Type the new address: ";
                cin.ignore();
                c[position].address.clear();        //clear the previous address
                addAddress(c[position].address);    //user types the new address

                cout << "The actual address is: " << c[position].address[0] << " / "
                    << c[position].address[1] << " / "
                     << c[position].address[2] << "/ "
                     << c[position].address[3] << " / "
                     << c[position].address[4] << endl;  //shows the new actual address
            }
        }
//--------------------------------------------------------------------------------------------------------------------
        else if (option == 5) {
            cout << "The actual list o packages is: " << c[position].listPacks << endl;
            if (proceed()) {                            //asks if the client wanna proceed with the action 
                cout << "Type the new package list: ";
                cin.ignore();
                getline(cin, c[position].listPacks);        //change the list of packages 
                cout << "The actual list o packages is: " << c[position].listPacks << endl;  //show the new package list 
                cin.ignore();

            }
        }

        cout << "Other client change operation ?[y|n]" << endl;
//--------------------------------------------------------------------------------------------------------------------
        operation = valid_yes();  //asks if the user wanna do another operation. 
    


    } while (operation == "Y");

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int searchName() {
    char srepeat = 'n';
    string name;
    do {
        cout << "Type the name of the client: ";
        getline(cin, name);     //user types the name of the client
        for (int i = 0; i < c.size(); i++) {          // checks the name for each element of the vector
            if (maiusculo(c[i].name) == maiusculo(name))                    // if the name matches, then return the postion
                return i;
        }
        cout << "Error! It's not possible to find " << name << ". Do you wanna try again?[y|any letter]";  //case it's not possible to find the client
        cin >> srepeat;                             //it asks if the user wanna try again
        cin.ignore();
    } while (srepeat == 'y');                       //if the user wanna try again, repeat the action
    return -1;  // case the user dont wish to repeat afeter an error
}    //searchs a position for a client, given the name

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void removeClient() {
    int position;

    cin.ignore();
    position = searchName();            //searches the position for the client
    c.erase(c.begin() + position);      //erases the client
    cout << "Done! Press ENTER to continue...";
    cin.ignore();
}   //removes a client from the struct vector

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string concatenate(vector<string> v) {
    string aux;                   //final string
    for (int i = 0; i < v.size(); i++) {
        aux += v[i];             //add each vector to a string
        if (i != v.size() - 1)   //do not add "/" for the last string
            aux += '/';         //add "/" between two strings

    }
    trim(aux);

    return aux;
}  //concatenated a vector using "/" as a separator

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
            position = searchName();                    //search the postion of the client in the client struct vector

            cout << left << setw(25) << "| NAME"        //print formated information
                 << setw(15) << "| NIF"
                 << setw(15) << "| NUMPEOPLE"
                 << setw(55) << "| ADDRESS"
                 << setw(20) << "| LISTPACKS"
                 << setw(40) << "| NUMPACKS" << endl;

            cout
                    << "----------------------------------------------------------------------------------------------------------------------------------------------"
                    << endl;

            cout << left << "|" << setw(24) << c[position].name
                 << "|" << setw(14) << c[position].nif
                 << "|" << setw(14) << c[position].nPeople
                 << "|" << setw(54) << concatenate(c[position].address)
                 << "|" << setw(19) << c[position].listPacks
                 << "|" << c[position].nPurchased << endl;


            cout << endl <<"Press ENTER to continue...";
            cin.ignore();

        } else if (option == 2) {   //

            cout << left << setw(25) << "| NAME"        //print formated information
                 << setw(15) << "| NIF"
                 << setw(15) << "| NUMPEOPLE"
                 << setw(55) << "| ADDRESS"
                 << setw(20) << "| LISTPACKS"
                 << setw(40) << "| NUMPACKS" << endl;


            cout
                    << "----------------------------------------------------------------------------------------------------------------------------------------------"
                    << endl;


            for (int position = 0; position < c.size(); position++) {
                cout << left << "|" << setw(24) << c[position].name
                     << "|" << setw(14) << c[position].nif
                     << "|" << setw(14) << c[position].nPeople
                     << "|" << setw(54) << concatenate(c[position].address)
                     << "|" << setw(19) << c[position].listPacks
                     << "|" << c[position].nPurchased << endl;


            }
            cout << endl <<"Press ENTER to continue...";
            cin.ignore();
            cin.ignore();

        }
    } while (option != 3);  // if the option is "back", do not nothing


}//menu for client visualization and printing
