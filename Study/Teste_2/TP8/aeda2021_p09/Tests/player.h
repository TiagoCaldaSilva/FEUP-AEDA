#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

//TODO
struct betHash
{
	int operator() (const Bet& b) const
	{
		unsigned index = 0;
		for(unsigned n:b.getNumbers()){
		    index += 37*n;
		}
		return index % b.getNumbers().size();
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
	    if(b1.getNumbers().size() != b2.getNumbers().size()) return false;
		for(unsigned int it : b1.getNumbers()){
		    if(b2.contains(it) == 0) return false;
		}
		return true;
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
