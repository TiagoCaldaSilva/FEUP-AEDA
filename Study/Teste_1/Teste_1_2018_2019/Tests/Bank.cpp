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
    double sum = 0;
    for(auto elem: accounts)
        if(elem->getCodH() == cod1)
            sum += elem->getWithdraw();
	return sum;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	vector<BankOfficer>::iterator it = find(bankOfficers.begin(), bankOfficers.end(), BankOfficer(name));
	if(it == bankOfficers.end())
	    return res;
	res = it->getAccounts();
	bankOfficers.erase(it);
    return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    vector<BankOfficer>::iterator it = find(bankOfficers.begin(), bankOfficers.end(), BankOfficer(name));
    if(it == bankOfficers.end())
        throw NoBankOfficerException(name);
    it->addAccount(ac);
    *bo = *it;
    return *bo;
}


// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), [](Account *a1, Account* a2) {
        if(a1->getBalance() == a2->getBalance())
            return a1->getCodIBAN() < a2->getCodIBAN();
        return a1->getBalance() < a2->getBalance();
    });
}

