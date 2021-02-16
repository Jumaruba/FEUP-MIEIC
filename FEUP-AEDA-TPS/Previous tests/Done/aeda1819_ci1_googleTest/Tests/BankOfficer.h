/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
    static long int quantidade;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;
	//-------
	BankOfficer(string nm);
    const bool operator >(const BankOfficer& m) const;
    const BankOfficer &addAccountToBankoOfficer(Account *ac, string name);

};

template <class T>
unsigned int numberDifferent(const vector<T> & v1){
    vector<T> aux;
    bool tem;
    int contador = 0;
    if (v1.empty()) return 0;

    for (int i = 0; i< v1.size(); i++){
      tem = false;
        for (int j = 0; j < aux.size(); j++) {
            if (aux[j] == v1[i]) {
                tem = true;
                break;
            }
        }
        if (!tem){
            aux.push_back(v1[i]);
            contador++;
        }

    }
    return contador ;
}

#endif /* SRC_BANKOFFICER_H_ */
