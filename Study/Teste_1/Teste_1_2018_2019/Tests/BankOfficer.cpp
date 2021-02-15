/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::ID = 1;

BankOfficer::BankOfficer(): id(ID++) {}

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

bool BankOfficer::operator==(const BankOfficer &b) const {
    return name == b.name;
}

// a alterar
BankOfficer::BankOfficer(string name):id(ID++) {
    this->name = name;
}

bool BankOfficer::operator>(const BankOfficer &b1) {
    if(myAccounts.size() == b1.myAccounts.size())
        return name > b1.name;
    return myAccounts.size() > b1.myAccounts.size();
}