#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}

BinaryTree<Circle> build(int h, vector<int> &points, vector<bool> &states, size_t i, Circle root, int pos_root){
    if((i + 1) == h)
        return BinaryTree<Circle>(root, Circle(points[2*pos_root +1], states[2*pos_root +1]), Circle(points[2*pos_root +2], states[2*pos_root +2]));
    return BinaryTree<Circle>(root, build(h, points, states, i + 1, Circle(points[2*pos_root + 1], states[2*pos_root + 1]), 2*pos_root +1), build(h, points, states, i + 1,Circle(points[2*pos_root +2], states[2*pos_root +2]), 2*pos_root + 2));
}

Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    Circle root(points[0], states[0]);
    game = build(h, points, states, 0, root, 0);
}


string Game::writeGame()
{
	BTItrLevel<Circle> it(game);
	string result = "";
	while(!it.isAtEnd()){
	    result += to_string(it.retrieve().getPoints()) + "-";
	    if(it.retrieve().getState())
	        result += "true";
	    else
	        result += "false";
	    result += "-" + to_string(it.retrieve().getNVisits()) + '\n';
	    it.advance();
	}
	return result;
}

int Game::move()
{
    int pos = 0, points;
    BTItrLevel<Circle> it(game);
    while(!it.isAtEnd()){
        it.retrieve().addVisit();
        bool right = it.retrieve().getState();
        it.retrieve().changeState();
        for(int i = 0; i < pos + 1; i++){
            it.advance();
            if(it.isAtEnd())
                return points;
        }
        pos = 2 * pos + 1;
        if(right) {
            it.advance();
            pos++;
        }
        points = it.retrieve().getPoints();
    }
    return points;
}

int Game::mostVisited()
{
	int max = 0;
	BTItrLevel<Circle> it(game);
	it.advance();
	while(!it.isAtEnd()){
	    if(max < it.retrieve().getNVisits())
	        max = it.retrieve().getNVisits();
	    it.advance();
	}
	return max;
}
