//
// Created by maruba on 13-04-2019.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "data.h"
#include "aux.h"

using namespace std;
//CONSTRUCTOR++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
//SET++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Date::setYear(unsigned int year) {
    this->year = year;
}

void Date::setMonth(unsigned int month) {
    this->month = month;
}

void Date::setDay(unsigned int day) {
    this->day = day;
}

void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {
    this->day = day;
    this->month = month;
    this->year = year;
}
/*
function: set the date
@param year year of Date
@param month month of Date
@param day day of Date
*/
void Date::setDate(){
	cout << "DD/MM/YYYY"<<endl;
        cout << "Year: ";
        this->year = isNum(int(0));//Year input
        cout << "Month: ";
        this->month = checkMonth();//Month input
        cout << "Day: ";
        this->day = checkDay();//Day input

}

void Date::setDate(std::string yearMonthDay){
    year = stoi(yearMonthDay.substr(0, 4));
    month = stoi(yearMonthDay.substr(5, 7));
    day = stoi(yearMonthDay.substr(8));
}

unsigned int Date::getYear() const {
    return year;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getDay() const {
    return day;
}
//GET++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
function: gets the date in string format
@param d day of Date
@param m month of Date
@param y year of Date
return Date formatted into string
*/
string Date::getDate() const // returns the date in format "yyyy/mm/dd"
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
//OTHERS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Date::show() const // shows the date on the screen in format "yyyy/mm/dd"
{
    cout << Date::getDate() << endl;
}

bool Date::isValid() {  // return if this is a valid day
    if (daysInMonth(year, month) != day)
        cerr << "Invalid input! This month has " << daysInMonth(year,month) << endl;
    return false;
}

bool Date::isEqualTo(const Date &date) { //verify if two dates are the same
    if (date.year == this->year && date.month == this->month && date.day == this->day)
        return true;
    else
        return false;
}

bool Date::isAfter(const Date &date) { //checks if a date is after another
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

bool Date::isBefore(const Date &date) {  //checks if a date is before another
    return !isAfter(date);
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
/*
function: checks if a day is valid or not
@param provisorio day input given by the user
@param days number of days in this specific month and year
return valid day
*/
int Date::checkDay(){
    int provisorio;                                 // input given by the user
    int days = daysInMonth(this->year, this->month);            // number of days given the year and month


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
            cout << "Invalid input. Try again: "; //needed check
        }
    } while (true);

};
/*
function: checks if a month is valid or not
@param provisorio month input given by the user
return valid month
*/
int Date::checkMonth(){
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
