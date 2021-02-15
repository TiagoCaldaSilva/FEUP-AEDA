/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
	static unsigned int ID;
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;
    bool operator==(const BankOfficer &b) const;
	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
	bool operator>(const BankOfficer &b1);

};

template <class T>
unsigned int numberDifferent (const vector<T> & v1){
    vector<T> done;
    unsigned int result = 0;
    for(auto elem:v1){
        if(find(done.begin(), done.end(), elem) != done.end())
            continue;
        result++;
        done.push_back(elem);
    }
    return result;
}

#endif /* SRC_BANKOFFICER_H_ */
