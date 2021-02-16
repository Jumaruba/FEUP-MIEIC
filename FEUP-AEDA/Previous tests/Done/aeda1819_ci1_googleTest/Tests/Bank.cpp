/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double soma;
	for (auto it = accounts.begin(); it < accounts.end(); it++){
	    if ((*it)->getCodH() == cod1){
            soma+=(*it)->getWithdraw();
	    }
	}
	return soma;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for (auto it = bankOfficers.begin(); it < bankOfficers.end(); it++){
        if (it->getName() == name) {
            res = it->getAccounts();
            bankOfficers.erase(it, it+1);
            break;
        }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    for (auto it = bankOfficers.begin(); it!= bankOfficers.end(); it++){
        if (it->getName() == name) {
            it->addAccount(ac);
            *bo = *it;
            return *bo;
        }
    }
    throw NoBankOfficerException(name);

}


// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(),accounts.end(), [](const Account* a, const Account*b ){
        if (a->getBalance() < b->getBalance() ) return true;
        else if(a->getBalance() > b->getBalance()) return false;
        else return (a->getCodIBAN() < b->getCodIBAN());
    });
}


