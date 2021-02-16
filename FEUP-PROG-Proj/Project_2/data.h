#ifndef PROJECT_2_DATA_H
#define PROJECT_2_DATA_H


#include <iostream>
#include <string>

class Date {
public:
    
    //CONTRUCTORS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Date();   // set the current time
    Date(unsigned int year, unsigned int month, unsigned int day);  //constructor given the parameters
    Date(std::string yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"

    //SET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void setYear(unsigned int year);
    void setMonth(unsigned int month);
    void setDay(unsigned int day);
    void setDate(unsigned int year, unsigned int month, unsigned int day);
    void setDate();
    void setDate(std::string date);

    //GET+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    std::string getDate() const; // returns the date in format "yyyy/mm/dd"

    //OTHERS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
    int checkDay(); //this function checks if it's a valid day for a specific month 
    int checkMonth(); //this function checks if it's a valid month (between 1 and 12 inclusive)
};


#endif //PROJECT_2_DATA_H
