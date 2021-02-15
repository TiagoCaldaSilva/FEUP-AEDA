#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


bool Bet::contains(unsigned num) const
{
	return numbers.end() != numbers.find(num);
}

void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    res result;
    for(unsigned u:values){
        if(n == 0) return;
        result = numbers.emplace(u);
        if(result.second)
            n--;
    }
}

unsigned Bet::countRights(const tabHInt& draw) const
{
	unsigned result = 0;
	for(unsigned value:draw)
	    if(contains(value)) result++;
	return result;
}
