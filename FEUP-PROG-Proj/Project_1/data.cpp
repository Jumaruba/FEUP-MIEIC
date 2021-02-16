//
// Created by maruba on 18-03-2019.
//

#include <iostream>
#include <string>
#include <vector>
#include "data.h"


using namespace std;

//FUNCTION-----------------------------------------------------------------------------------------------------------------------

//return the day from a string to an int

int getDay(string word){  
    string aux;
    int m;

    aux.push_back(word[8]);
    aux.push_back(word[9]);
    m = stoi(aux);
    return m;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//return the month from a string to an int

int getMonth(string word){
    string aux;
    int m;

    aux.push_back(word[5]);
    aux.push_back(word[6]);

    m = stoi(aux);
    return m;
}  //get the month in a string

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Return the year from a string to an int

int getYear(string word){
    string aux;
    int m;
    aux.push_back(word[0]);
    aux.push_back(word[1]);
    aux.push_back(word[2]);
    aux.push_back(word[3]);


    m = stoi(aux);
    return m;
}  //get the year in a string

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Descobre se o ano eh bissexto

bool bissexto(int ano)
{
    if (ano % 400 == 0)
        return true;
    else if (ano % 4 == 0 && ano % 100 != 0)
        return true;
    return false;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++6++++++++++++++++++++++++++++++++++++++

int dias_no_mes(int ano, int mes)  //returns the number of days in a specific month of a specif year
{
    vector<int> meses = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && bissexto(ano))
        return 29;
    return meses[mes];
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//checks if it's a valid day given the year and month

int checkDay(int year, int month){
    int provisorio;                                 // input given by the user
    int days = dias_no_mes(year, month);            // number of days given the year and month


    do {
        if (cin >> provisorio) {                            //get the input
            if (provisorio > days || provisorio <= 0){      //checks if it's a valid day
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid day. This month has "<< days << " days. Try again: ";
            }
            else
                return provisorio;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again: "; //precisa checar
        }
    } while (true);

};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// checks if it's a valid month

int checkMonth(){
    int provisorio;         //input given by the user

    do {
        if (cin >> provisorio) {
            if (provisorio > 12 || provisorio <= 0){           //checks if it's a valid month
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid month. A year has 12 months. Try again: ";
            }
            else
                return provisorio;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again: ";
        }
    } while (true);
}