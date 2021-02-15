#include "player.h"

//TODO
void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    unsigned counter = 0;
	for(Bet b:bets){
        counter += b.contains(num);
	}
	return counter;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	for(auto b:bets){
	    if(b.countRights(draw) > 3)
	        res.insert(b);
	}
	return res;
}
