//
// Created by maruba on 18-03-2019.
//

#include <iostream>
#include <string>
#include <vector>
#include "packs.h"
#include "data.h"
#include <iomanip>

using namespace std;

//GLOBAL VARIABLES------------------------------------------------------------------------------------------------------


extern std::vector<pack> p;             //vector to store all packages information
extern std::vector<std::string> text;   //file text
extern std::vector<client> c;           //vector to store all clients information


//FUNCTIONS-------------------------------------------------------------------------------------------------------------

//function will read the information in text vector and store all the information at <vector> package
void putPack() {
    pack aux;
    int contador = 0;  //the lines that represents the package information
    string auxiliar;


    for (int i = 1; i < text.size(); i++) { // for loop to read vector<pack> p
        trim(text[i]);                      // avoid extra spaces

        if (text[i] == "::::::::::") {
            contador = 0;                   //0 for the next client
            p.push_back(aux);               //add the client before
        }
        else {
            switch(contador){
                case 0:                             //line for the id
                    aux.identifier = stoi(text[i]);
                    break;
                case 1:                             //line for the local
                    aux.local = text[i];
                    break;
                case 2:                             //line for the beginning date
                    aux.dBegin.day = getDay(text[i]);
                    aux.dBegin.month = getMonth(text[i]);
                    aux.dBegin.year = getYear(text[i]);
                    break;
                case 3:                             //line for the ending date
                    aux.dEnd.day = getDay(text[i]);
                    aux.dEnd.month = getMonth(text[i]);
                    aux.dEnd.year = getYear(text[i]);
                    break;
                case 4:                             //line for the price
                    aux.price = stof(text[i]);
                    break;
                case 5:                             //line for the number of places
                    aux.places = stoi(text[i]);
                    break;
                case 6:                             //line for the max number o people
                    aux.maxPeople = stoi(text[i]);
                    break;
            }
            contador++;                             // getting to the next line
        }

    }

    p.push_back(aux);                               //add the last client on the list
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//the function asks the id package and find it's position on vector<pack> p
int searchPack() {
    string srepeat = "N";                                   //case the client wants to repeat the action for search
    int id;                                                 //number of the id to searched
    do {
        cout << "Type the id of the package (exit - 0): ";
        id = isInt();                                       //checking if the input is int
        if (id!= 0) {                                       //if it's 0 the mission is aborted
            for (int i = 0; i < p.size(); i++) {            //searchs for package position
                if (p[i].identifier == id)
                    return i;                               //return the position
            }
            cout << "Error! It's not possible to find " << id << ". Do you wanna try again?[y|n]";   // case is hasnt's been found

            srepeat = valid_yes();                          // in case of failure, it asks the client if its wanna try again
        }
    } while (srepeat == "Y");
    return -1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//checks if already exists a package with a given id

bool pack_there(int id){
    if (id!= 0) {                                   //the id can't be equals to 0
        for (int i = 0; i < p.size(); i++) {        //it searchs for the id
            if (p[i].identifier == id)
                return true;                        //if it's been found, return true
        }
    }
    else
        cout << "Not possible to atribute id = 0" << endl;
    return false;                                   //the given id doesn't exist yet
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// menu for manage package: new, change and remove

void managePack(int option) {   
    clear_screen();
    switch (option){
        case 1:
            newPack();      //it creates a new package
             break;
        case 2:
            changePack();   //it changes a specific component in a package
            break;
        case 3:
            removePack();   //it removes a specific package
            break;
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//creates a new package

void newPack() {  
    pack aux;

    cout << "Type the id: ";
    aux.identifier = isInt();                               // get the id and checks if it's integer

    cout << "Type the location: ";
    cin.ignore();
    getline(cin, aux.local);                                //get the local

    cout << "Type the BEGIN date: " << endl;
    cout << "Year: ";
    aux.dBegin.year = isInt();                              //get the begin year and checks if it's integer
    cout << "Month: ";
    aux.dBegin.month = checkMonth();                        //get the month and checks if it's acceptable
    cout << "Day: ";
    aux.dBegin.day = checkDay(aux.dBegin.year, aux.dBegin.month); //get the day and checks if there is this day in that year and month

    cout << "Type the ENDING date: " << endl;
    cout << "Year: ";
    aux.dEnd.year = isInt();                                // get end year and checks is it's integer
    cout << "Month: ";
    aux.dEnd.month = checkMonth();                          //get the month and checks if it's acceptable
    cout << "Day: ";
    aux.dEnd.day = checkDay(aux.dEnd.year, aux.dEnd.month); //get the day and checks if there is this day in that year and month

    cout << "Type the price: ";
    aux.price = isFloat();                                  // get the prince and checks if it's float

    cout << "Type the number of places: ";
    aux.places = isInt();                                   //get the number of places and checks if it's integer
    cout << "Type max people: ";
    aux.maxPeople = isInt();                                // get the number of max people and checks if it's integer

    p.push_back(aux);                                       //add the information to the vecetor

    cout << "Done! Press ENTER to continue...";
    cin.ignore();


}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
            cout<< endl;
            showPack_cabecalho();
            showPack(p[position]);
            cout << endl;

            cout << "Type the option you wish to change:" << endl
                 << "1. Id" << endl
                 << "2. Local" << endl
                 << "3. Begin date" << endl
                 << "4. Ending date" << endl
                 << "5. Price" << endl
                 << "6. Number of places" << endl
                 << "7. Number max o people" << endl
                 << "8. Back" << endl;


            option = cin_menu(9, 1);

            if (option == 1) {
                int id_aux;
                string again_1;
                cout << "The actual id is: " << p[position].identifier << endl;
                if (proceed()) {
                    cin.ignore();
                    do {
                        cout << "Type the new id: ";
                        id_aux = isInt();

                        if (!pack_there(id_aux)) {
                            p[position].identifier = id_aux;
                            cout << "The actual id is: " << p[position].identifier << endl;
                            cin.ignore();
                            again_1 = "N";
                        } else {
                            cout << "There is already a pack with this id. Do you wanna try this operation again?[y|n] " << endl;
                            again_1 = valid_yes();
                        }
                    } while (again_1 == "Y");
                }
            } else if (option == 2) {
                cout << "The actual locals are: " << p[position].local << endl;
                if (proceed()) {
                    cin.ignore();
                    cout << "Type the new locals: ";
                    getline(cin, aux);
                    p[position].local = aux;
                    cout << "The actual locals are: " << p[position].local << endl;
                    cin.ignore();
                }
            } else if (option == 3) {
                cout << "The actual begin date is: " << p[position].dBegin.year << "/" << p[position].dBegin.month <<
                     "/" << p[position].dBegin.day << endl;
                if (proceed()) {
                    cin.ignore();
                    cout << "Type the BEGIN date: " << endl;
                    cout << "Year: ";

                    p[position].dBegin.year = isInt();
                    cout << "Month: ";
                    p[position].dBegin.month = checkMonth();
                    cout << "Day: ";
                    p[position].dBegin.day = checkDay(p[position].dBegin.year, p[position].dBegin.month);

                    cout << "The actual begin date is: " << p[position].dBegin.year << "/" << p[position].dBegin.month
                         << "/" << p[position].dBegin.day << endl;
                    cin.ignore();
                }
            } else if (option == 4) {
                cout << "The actual ending date is: " << p[position].dEnd.year << "/" << p[position].dEnd.month << "/"
                     << p[position].dEnd.day << endl;
                if (proceed()) {
                    cin.ignore();
                    cout << "Type the BEGIN date: " << endl;
                    cout << "Year: ";
                    p[position].dEnd.year = isInt();
                    cout << "Month: ";
                    p[position].dEnd.month = checkMonth();
                    cout << "Day: ";
                    p[position].dEnd.day = checkDay(p[position].dEnd.year, p[position].dEnd.month);

                    cout << "The actual ending date is: " << p[position].dEnd.year << "/" << p[position].dEnd.month
                         << "/" << p[position].dEnd.day << endl;
                    cin.ignore();
                }
            } else if (option == 5) {
                cout << "The actual price is: " << p[position].price << endl;
                if (proceed()) {
                    cin.ignore();
                    cout << "Type the new price: ";
                    p[position].price = isFloat();
                    cout << "The actual price is: " << p[position].price << endl;
                    cin.ignore();
                }
            }

            if (option == 6) {
                cout << "The actual number of places is: " << p[position].places << endl;
                if (proceed()) {
                    cin.ignore();
                    cout << "Type the new number of places: ";
                    p[position].places = isInt();
                    cout << "The actual number of places is: " << p[position].places << endl;
                    cin.ignore();
                }
            } else if (option == 7) {
                cout << "The actual price is: " << p[position].maxPeople << endl;
                if (proceed()) {
                    cin.ignore();
                    cout << "Type the new number o people: ";
                    p[position].maxPeople = isInt();
                    cout << "The actual max number of people is: " << p[position].maxPeople << endl;
                    cin.ignore();
                }
            }
            if (option != 8) {
                cout << "Other package change operation ?[y|n]" << endl;
                operation = valid_yes();
            }

        } while (operation == "Y");
    }
}  //to change a package

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void removePack() {
    int position;

    cin.ignore();
    position = searchPack();
    p.erase(p.begin() + position);
    cout << "Done! Press ENTER to continue...";
    cin.ignore();
} // to remove a pack

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void showPack_cabecalho() {  //mostra o cabecalho de visualização
    cout << left << setw(6) << "| ID"
         << setw(70) << "| LOCAL"
         << setw(15) << "| BEGIN DATE"
         << setw(15) << "| END DATE"
         << setw(15) << "| PRICE"
         << setw(15) << "| PLACES"
         << "| MAX_PEOPLE" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void showPack(pack aux) {  // shows any pack

    cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << left << '|'<<  setw(5) << aux.identifier
            << '|'<< setw(69) << aux.local
            << '|'<< setw(14) << concDate_begin(aux)
            << '|'<< setw(14) << concDate_end(aux)
            << '|'<< setw(14) << aux.price
            << '|'<< setw(14) << aux.places
            << '|'<< aux.maxPeople << endl;

}  //shows any pack

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string concDate_begin(pack aux) {
    string m;
    string day;
    string month;
    if (aux.dBegin.month < 10)
        month = '0' + to_string(aux.dBegin.month);
    else
        month = to_string(aux.dBegin.month);
    if (aux.dBegin.day < 10)
        day = '0' + to_string(aux.dBegin.day);
    else
        day = to_string(aux.dBegin.day);

    m = to_string(aux.dBegin.year) + '/' + month + '/' + day;
    return m;
}  //concatenate the begin dates

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string concDate_end(pack aux) {
    string m;
    string day;
    string month;
    if (aux.dEnd.month < 10)
        month = '0' + to_string(aux.dEnd.month);
    else
        month = to_string(aux.dEnd.month);
    if (aux.dEnd.day < 10)
        day = '0' + to_string(aux.dEnd.day);
    else
        day = to_string(aux.dEnd.day);

    m = to_string(aux.dEnd.year) + '/' + month + '/' + day;
    return m;
}  //concatenate the ending dates

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void packagesVisual() {  //menu for visualization package
    string place; // the name of the specif place we wanna search
    int option = 0;
    data begin;  // those are to check if
    data end;


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
             << "7. Back" << endl;

        option = cin_menu(7, 1);
        clear_screen();
//--------------------------------------------------------------------------------------------------------------------

        if (option == 1) {
            showPack_cabecalho();
            for (int i = 0; i < p.size(); i++) {
                showPack(p[i]);
            }
            cout << endl<<"Press ENTER to continue...";
            cin.ignore();
            cin.ignore();
        }
//--------------------------------------------------------------------------------------------------------------------
        else if (option == 2) {

            cin.ignore();
            cout << "Type the name of the place: ";
            getline(cin, place);

            for (int i = 0; i < p.size(); i++) { //if this place is a destine of this pack
                if (searchPlace(place, p[i].local)) { //if its true
                    if (!show_cabecalho) {
                        show_cabecalho = true;
                        showPack_cabecalho();
                    }
                    showPack(p[i]);//shows the pack
                }
            }
            if (!show_cabecalho) {
                cout << "No package is related to " << place << endl;
                cout << "Press ENTER to continue...";
                cin.ignore();
            }
            else{
                cout << endl <<"Done. Press ENTER to continue...";
                cin.ignore();
            }
        }
//--------------------------------------------------------------------------------------------------------------------

        else if (option == 3) {
            inputData(begin, end);
            for (int i = 0; i < p.size(); i++) {
                if (searchData(begin, end, p[i].dBegin, p[i].dEnd)) {
                    if (!show_cabecalho) {
                        show_cabecalho = true;
                        showPack_cabecalho();
                    }
                    showPack(p[i]);
                }
            }
            if (!show_cabecalho) {
                cout << "No package is related to the conditions specified" << endl;
                cout << "Press ENTER to continue...";
                cin.ignore();
                cin.ignore();
            }
            else{
                cout << endl <<"Done. Press ENTER to continue...";
                cin.ignore();
                cin.ignore();
            }
        }
//--------------------------------------------------------------------------------------------------------------------

        else if (option == 4) {
            inputData(begin, end);
            cin.ignore();
            getline(cin, place);
            for (int i = 0; i < p.size(); i++) {
                if (searchPlace(place, p[i].local) && searchData(begin, end, p[i].dBegin, p[i].dEnd)) {
                    if (!show_cabecalho) {
                        show_cabecalho = true;
                        showPack_cabecalho();
                    }
                    showPack(p[i]);
                }
            }
            if (!show_cabecalho) {
                cout << "No package is related to " << place << endl;
                cout << "Press ENTER to continue...";
                cin.ignore();
            }
            else{
                cout << endl<<"Done. Press ENTER to continue...";
                cin.ignore();
            }
        }

//--------------------------------------------------------------------------------------------------------------------

        else if (option == 5){
            vector <string> pPurchased;  //packages bought by a client;
            int cPosition;
            int pPosition;
            cin.ignore();
            cPosition = searchName();   //client position;
            split(pPurchased, c[cPosition].listPacks, ';');    // spliting the packages into the vector
            for (int i = 0; i< pPurchased.size(); i++){         // for each purchased package in pPurchased
                pPosition = searchPack_bool(stoi(pPurchased[i]));
                if (pPosition != -1 ){              // if the package is at the list
                    if (!show_cabecalho) {
                        show_cabecalho = true;      //show the cabecalho se houver packages disponiveis
                        showPack_cabecalho();
                    }
                    showPack(p[pPosition]);               //show the package
                }

            }
            if (!show_cabecalho) {
                cout << "No package is related to " << c[cPosition].name << endl;
                cout << "Press ENTER to continue...";
                cin.ignore();
            }
            else{
                cout << endl <<"Done. Press ENTER to continue...";
                cin.ignore();
            }
        }

//--------------------------------------------------------------------------------------------------------------------
        else if(option == 6) {
            vector<string> allPacks;
            float profit = 0;
            int totalPurchased = 0;  //number o packages purchased;

            for (int i = 0; i < c.size(); i++) {
                split(allPacks, c[i].listPacks, ';');  //puting all packages in a pack;
                totalPurchased += c[i].nPurchased;


                for (int j = 0; j< allPacks.size(); j++){    // do a function to this
                    for (int packposition = 0; packposition < p.size(); packposition ++){
                        if (p[packposition].identifier == stoi(allPacks[j]))
                            profit += p[packposition].price;
                    }
                }
            }


            cout << endl << "TOTAL PURCHASED = " << totalPurchased << endl;
            cout << "TOTAL PROFIT = " << profit << endl;

            cout << "Done. Press ENTER to continue...";
            cin.ignore();
            cin.ignore();
            cout << endl;
            clear_screen();
        }

    } while (option != 7);
}  //menu for packing visualization

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool searchPlace(const string place, const string destines) {
    string auxplace = maiusculo(place);  //getting a minusculus version of place
    string aux; // a string the will extract the substring

    for (int i = 0; i < destines.size(); i++) {
        if (!isalpha(destines[i]) && destines[i] != ' ') {
            trim(aux); // we are removing unnecessary spaces;
            if (auxplace == aux)
                return true;
            aux = "";
        } else
            aux.push_back(toupper(destines[i]));
    }
    if (place == aux)
        return true;
    return false;
}  //checks if a place is at a pack

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool searchData(data begin, data end, data dBegin, data dEnd) {
    if (begin.year > dBegin.year)
        return false;
    else if (begin.year == dBegin.year) {
        if (begin.month > dBegin.month)
            return false;
        else if (begin.month == dBegin.month) {
            if (begin.day > dBegin.day)
                return false;
        }
    }

    if (end.year < dEnd.year)
        return false;
    else if (end.year == dEnd.year) {
        if (end.month < dEnd.month)
            return false;
        else if (end.month == dEnd.month) {
            if (end.day < dEnd.day)
                return false;
        }
    }
    return true;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void inputData(data &begin, data &end) {
    cout << "DATE OF BEGINIG: " << endl;
    cout << "Type the year: ";
    begin.year = isInt();
    cout << "Type the month: ";
    begin.month = checkMonth();
    cout << "Type the day: ";
    begin.day = checkDay(begin.year, begin.month);

    cout << "DATE OF ENDING: " << endl;
    cout << "Type the year: ";
    end.year = isInt();
    cout << "Type the month: ";
    end.month = checkMonth();
    cout << "Type the day: ";
    end.day = checkDay(begin.year, begin.month);
}  //get the date

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int searchPack_bool(int number){
    for (int i = 0; i< p.size(); i++){   //search the pack that contains number as id
        if (p[i].identifier == number)   // if found
            return i;                    //return the position
    }
    return -1;                           //else return -1
}

