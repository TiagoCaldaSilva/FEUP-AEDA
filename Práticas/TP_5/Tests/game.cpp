#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}


//Como fazer iniciação de lista ou vetor?
Game::Game()
{
    kids.clear();
}


Game::Game(list<Kid>& l2)
{
    kids = l2;
}


void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}


list<Kid> Game::getKids() const
{
    return kids;
}


string Game::write() const
{
    string res = "";
    list<Kid> l = kids;
    for(list<Kid>::iterator it = l.begin(); it != l.end(); ++it)
    {
        res += (*it).getName() + " : " + to_string((*it).getAge()) + '\n';
    }
    return res;
}


//ver, no final vetor kids fica vazio
/*Kid& Game::loseGame(string phrase)
{
    if(kids.size() == 1)
    {
        return *kids.begin();
    }

    int n = numberOfWords(phrase) % kids.size();

    if( n == 0 )
        n = kids.size();

    list<Kid>::iterator it = kids.begin();
    for(int i = 1; i < n; i++)
        it++;

    kids.remove((*it));

    return loseGame(phrase);

}*/


Kid& Game::loseGame(string phrase)
{
    int n;
    list<Kid>::iterator it = kids.begin();
    while(kids.size() != 1)
    {
        n = numberOfWords(phrase) % kids.size();

        if(kids.size() == 2)
            if (n == 0)
                it++;
        else {
                if (n == 0) {
                    if (it == kids.begin())
                        it = kids.end();
                    it--;
                } else
                    for (int i = 0; i < n; i++) {
                        it++;
                        if (it == kids.end())
                            it = kids.begin();
                    }
            }
        it = kids.erase(it);
        if(it == kids.end())
            it = kids.begin();

    }
    return *kids.begin();
}


list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}


list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;

    for(list<Kid>::iterator it = kids.begin(); it != kids.end(); ++it)
    {
        if((*it).getAge() > id)
        {
            kids.remove((*it));
            res.push_back((*it));
        }
    }
    return res;
}


void Game::setKids(const list<Kid>& l1)
{
    kids = l1;
}


bool Game::operator==(Game& g2)
{
    return kids == g2.kids;
}


//verificar forma de fazer
list<Kid> Game::shuffle() const
{
    int n;
    list<Kid> res;
    vector<bool> x(kids.size(), 0);
    while(res.size() != kids.size()){
        n = rand() % kids.size();
        if(!x[n]){
            list<Kid>::const_iterator it = kids.begin();
            for(int j = 0; j < n; it++, j++) {}
            res.push_back((*it));
            x[n] = 1;
        }
    }
    return res;
}
