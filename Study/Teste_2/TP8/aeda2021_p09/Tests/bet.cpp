#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
	return numbers.count(num);
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    int i = 0;
    while(numbers.size() != n){
        if(numbers.count(values[i]) == 0)
            numbers.insert(values[i]);
        i++;
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
    int counter = 0;
	for(unsigned value:numbers){
	    counter += draw.count(value);
	}
	return counter;
}
