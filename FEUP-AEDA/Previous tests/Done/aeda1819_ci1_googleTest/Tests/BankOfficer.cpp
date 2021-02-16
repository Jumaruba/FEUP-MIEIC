/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

long int BankOfficer::quantidade = 0;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    this->name = name;
    id = ++quantidade;

}


const bool BankOfficer::operator>(const BankOfficer &m) const {
    if (this->getAccounts().size() > m.getAccounts().size())
        return true;
    else if (this->getAccounts().size() < m.getAccounts().size())
        return false;
    return (this->name > m.name);
}

