#include "player.h"

void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const
{
	int result = 0;
    tabHInt temp = {num};
	for(Bet b:bets)
	    result += b.countRights(temp);
	return result;
}

tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet result;
	for(Bet b: bets)
	    if(b.countRights(draw) > 3)
	        result.insert(b);
	return result;
}
