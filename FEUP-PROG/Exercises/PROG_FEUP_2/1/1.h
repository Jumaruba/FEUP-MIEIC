#pragma once 

#include <iostream> 
#include <string> 

class Date{
    public: 
        Date();  // construtor por omissão 
        Date(unsigned int year, unsigned int month,unsigned int day);  //construtor dado os parametros 
        Date(std::string yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"
        void setYear(unsigned int year);
        void setMonth(unsigned int month);
        void setDay(unsigned int day);
        void setDate(unsigned int year, unsigned int month, unsigned int day);
        unsigned int getYear() const;
        unsigned int getMonth() const;
        unsigned int getDay() const;
        std::string getDate() const; // returns the date in format "yyyy/mm/dd"
        void show() const; // shows the date on the screen in format "yyyy/mm/dd"
        bool isValid();  // return if this is a valid day 
        bool isEqualTo(const Date &date);
        bool isAfter(const Date &date); //checks if a date is after another
        bool isBefore(const Date &date); //checks if a date is before another
          

    private:
        unsigned int year;
        unsigned int month;
        unsigned int day; 

        bool bissexto(int ano); //Descobre se o ano eh bissexto
        int daysInMonth(int ano, int mes);  //returns the number of days in a specific month of a specif year
 
};
