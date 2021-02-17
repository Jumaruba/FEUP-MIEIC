//
// Created by julia on 26/12/2019.
//

#include "../Header/Date.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "../Header/Date.h"


using namespace std;

/**
 * @file Date.cpp
 * @brief It contains the implementation of the class Date
 */

Date::Date() {
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);   //get the current time

    this->day = TM.tm_mday;
    this->month = TM.tm_mon + 1;
    this->year = TM.tm_year + 1900;
}

Date::Date(unsigned int year, unsigned int month, unsigned int day) {
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(string yearMonthDay) // yearMonthDay must be in format "yyyy/mm/dd"
{
    year = stoi(yearMonthDay.substr(0, 4));
    month = stoi(yearMonthDay.substr(5, 7));
    day = stoi(yearMonthDay.substr(8));
}


void Date::setYear(unsigned int year) {
    this->year = year;
}

void Date::setDate(std::string yearMonthDay) {
    year = stoi(yearMonthDay.substr(0, 4));
    month = stoi(yearMonthDay.substr(5, 7));
    day = stoi(yearMonthDay.substr(8));
}

unsigned int Date::getYear() const {
    return year;
}




string Date::getDate() const
{
    string d, m, y;
    if (day < 10)
        d = '0' + to_string(day);
    else
        d = to_string(day);
    if (month < 10)
        m = '0' + to_string(month);
    else
        m = to_string(month);

    return to_string(year) + "/" + m + "/" + d;
}



bool Date::isAfter(const Date &date) {
    if (date.year > this->year)
        return true;
    else if (date.year < this->year)
        return false;
    else if (date.month > this->month)
        return true;
    else if (date.month < this->month)
        return false;
    else if (date.day > this->day)
        return true;
    return false;
}

bool Date::bissexto(int ano) //Check if the year is a leap year
{
    if (ano % 400 == 0)
        return true;
    else if (ano % 4 == 0 && ano % 100 != 0)
        return true;
    return false;
}

int Date::daysInMonth(int ano, int mes)  //returns the number of days in a specific month of a specifc year
{
    vector<int> meses = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && bissexto(ano))
        return 29;
    return meses[mes];
}


string getTimeNow() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer,80,"%Y/%m/%d",ltm);
    return string(buffer);
}