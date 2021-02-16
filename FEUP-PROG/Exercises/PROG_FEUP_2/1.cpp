#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
#include "1.h"

using namespace std; 

        Date::Date(){
            time_t tt; 
            time(&tt); 
            tm TM = *localtime(&tt); 

            this->day =TM.tm_mday; 
            this->month = TM.tm_mon +1; 
            this->year = TM.tm_year + 1900; 
        }
        Date::Date(unsigned int year, unsigned int month,unsigned int day){
            this-> day = day;
            this-> month = month; 
            this-> year = year; 
        }
        Date::Date(string yearMonthDay) // yearMonthDay must be in format "yyyy/mm/dd"
        {
            year = stoi(yearMonthDay.substr(0,4));
            month = stoi(yearMonthDay.substr(5,7));
            day = stoi(yearMonthDay.substr(8));
        }
        void Date::setYear(unsigned int year){
            this -> year = year; 
        }
        void Date::setMonth(unsigned int month){
            this-> month = month;
        }
        void Date::setDay(unsigned int day) {
            this-> day = day; 
        }
        void Date::setDate(unsigned int year, unsigned int month, unsigned int day){
            this-> day = day;
            this-> month = month; 
            this-> year = year;
        }
        unsigned int Date::getYear() const{
            return year; 
        }
        unsigned int Date::getMonth() const{
            return month; 
        }
        unsigned int Date::getDay() const{
            return day; 
        }
        string Date::getDate() const // returns the date in format "yyyy/mm/dd"
        {   
            string d, m ,y; 
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
        void Date::show() const // shows the date on the screen in format "yyyy/mm/dd"
        {
            cout << Date::getDate() << endl; 
        }

        bool Date::isValid(){  // return if this is a valid day 
            if (daysInMonth(year, month) != day)
                cerr << "Invalid input!" << endl; 
                return false; 
        }

        bool Date::isEqualTo(const Date &date){
            if (date.year == this->year && date.month == this->month && date.day == this->day)
                return true;
            else 
                return false; 
        }

        bool Date::isAfter(const Date &date){ //checks if a date is after another
            if (date.year > this-> year)
                return true;
            else if(date.year < this-> year)
                return false; 
            else 
                if(date.month > this-> month) 
                    return true; 
                else if (date.month < this-> month)
                    return false; 
                else 
                    if(date.day > this->day)
                        return true;
                    return false; 
        }
        bool Date::isBefore(const Date &date){  //checks if a date is before another
            return !isAfter(date); 
        }
        bool Date::bissexto(int ano) //Descobre se o ano eh bissexto
        {
            if (ano % 400 == 0)
                return true;
            else if (ano % 4 == 0 && ano % 100 != 0)
                return true;
            return false;
        }

        int Date::daysInMonth(int ano, int mes)  //returns the number of days in a specific month of a specif year
        {
            vector<int> meses = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

            if (mes == 2 && bissexto(ano))
                return 29;
            return meses[mes];
        }


int main(){
    Date j; 
    j.show(); 
    Date m(2019,4,5); 
    cout << endl; 
    cout << m.isAfter(j); 
    return 0; 
}