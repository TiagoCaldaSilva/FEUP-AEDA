#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}

BinaryTree<Circle> getBinaryTree(int pos, vector<int> &points, vector<bool> &states){
    if((2*pos +1) >= points.size()) return BinaryTree<Circle>(Circle(points[pos], states[pos]));
    else return BinaryTree<Circle>(Circle(points[pos], states[pos]), getBinaryTree(2*pos + 1, points, states), getBinaryTree(2*pos+2, points, states));
}

//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game = BinaryTree<Circle>(Circle(points[0], states[0]), getBinaryTree(1, points, states), getBinaryTree(2, points, states));
}


//TODO
string Game::writeGame()
{
	BTItrLevel<Circle> it(game);
	string result = "";
	while(!it.isAtEnd()){
	    result += to_string(it.retrieve().getPoints()) + "-";
	    if(it.retrieve().getState())
	        result += "true-";
	    else result += "false-";
	    result += to_string(it.retrieve().getNVisits()) + '\n';
	    it.advance();
	}
	return result;
}


//TODO
int Game::move()
{
    int pos = 0, next_pos = 0, points = 0;
	BTItrLevel<Circle> it(game);
	while(!it.isAtEnd()){
	    if(it.retrieve().getState())
	        next_pos = 2*pos +2;
	    else
	        next_pos = 2*pos +1;
	    it.retrieve().changeState();
	    it.retrieve().addVisit();
	    points = it.retrieve().getPoints();
	    for(int i = pos; i < next_pos && !it.isAtEnd(); i++){
            it.advance(); pos++;
        }
	}
	return points;
}


//TODO
int Game::mostVisited()
{
	BTItrLevel<Circle> it(game);
    int max = 0;
    it.advance();
    while(!it.isAtEnd()){
        if(it.retrieve().getNVisits() > max) max = it.retrieve().getNVisits();
        it.advance();
    }
    return max;

}
