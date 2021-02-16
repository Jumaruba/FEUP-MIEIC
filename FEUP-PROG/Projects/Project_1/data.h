//
// Created by maruba on 18-03-2019.
//

#pragma once

#include <iostream>
#include <string>

//CLASS-----------------------------------------------------------------------------------------------------------------

typedef struct{
    int year;
    int month;
    int day;

}data;

//FUNCTIONS-------------------------------------------------------------------------------------------------------------

int getDay(std::string word);               //return the day from a string to an int
int getMonth(std::string word);             //return the month from a string to an int
int getYear(std::string word);              //return the year from a string to an int
bool bissexto(int ano);                     //descobre so o ano é bissexto
int dias_no_mes(int ano, int mes);          //returns the number of days in a specific month of a specif year
int checkDay(int year, int month);          //checks if it's a valid day given the year and month
int checkMonth();                           // checks if it's a valid month