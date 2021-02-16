#include <iostream> 
#include <string> 
#include "1.h"

using namespace std; 

class Person{
    Person(string name, string gender, Date birthdate);
    string getName();  
    string getGender();
    Date getBirth(); 
    string Person::getGender();

    private:
        string name;
        string gender;
        Date birthdate;
};

    Date Person::getBirth(){
        return this-> birthdate; 
    }

    string Person::getGender(){
        return this-> gender; 
    }

    string Person::getGender(){
        return this-> gender; 
    }

    string Person::getName(){
        return this->name; 
    }

    Person::Person(string name, string gender, Date birthdate){
        this-> name = name; 
        this-> gender = gender; 
        this-> birthdate = birthdate; 
    }