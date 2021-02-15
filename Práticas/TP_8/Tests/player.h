#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

struct betHash
{
	int operator() (const Bet& b) const
	{
        int v = 0;
        for(unsigned x:b.getNumbers()){
            v = 37*v + x;
        }
        return v;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
		for(unsigned b: b1.getNumbers()) {
            if(!b2.contains(b))
                return false;
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
