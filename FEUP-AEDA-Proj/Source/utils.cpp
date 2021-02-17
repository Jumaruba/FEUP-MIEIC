//
// Created by maruba on 06/11/19.
//

#include "../Header/utils.h"

/**
 * @file utils.cpp
 * @brief Implementation of functions that are useful in the project
 */

int checkOption(int min, int max) {
    int input;

    while (true) {
        try {
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Invalid Input. Please enter an integer");

            }
                //if it's not in the interval
            else if (input > max || input < min) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Given input is not an option. Try again");
            } else
                return input;
        }
        catch (WrongInput_option &error) {
            cout << error.getInfo() << endl;
            continue;
        }
    }

}

int validServiceId(Empresa &e) {
    int id;
    while (true) {
        cout << "Type the id: ";
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        try {
            e.SearchSer(id);
            return id;
        }
        catch (NoService &error) {
            cout << "The id " << error.getInfo() << " does not exist!" << endl;
            cout << "Type 1 to " << Empresa::nSer << endl;
            continue;
        }
    }
}

int validClientNif(Empresa &e) {
    long long int nif;
    while (true) {
        cout << "Type the nif [EXIT -1]  ";
        cin >> nif;
        if (nif == -1) return -1;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (e.SearchCli(nif) != -1)
            return nif;
        else
            cout << "No client with nif " << nif << endl;

    }
}

double checkNumber() {
    double input;
    while (true) {
        try {
            cout << "[EXIT -1] ";
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Invalid Input. Please enter an integer");

            } else
                return input;
        }
        catch (WrongInput_option &error) {
            cout << error.getInfo() << endl;
            continue;
        }
    }
}


void wait() {
    cout << endl << "[PRESS ENTER]";
    cin.ignore();
    while (cin.get() != '\n') {};
}

void clear_screen() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}