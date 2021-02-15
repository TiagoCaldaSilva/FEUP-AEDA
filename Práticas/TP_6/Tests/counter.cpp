#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;


Client::Client() {
    numGifts = rand() % 5 + 1;
}


unsigned Client::getNumGifts() const {
    return numGifts;
}



Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    nextEnter = rand() % 20 +1;
    nextLeave = 0;
    numAttendedClients = 0;
}


unsigned Counter::getActualTime() const {
    return actualTime;
}


unsigned Counter::getNextEnter() const {
    return nextEnter;
}


unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}


unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}


unsigned Counter::getNextLeave() const {
    return nextLeave;
}


Client & Counter::getNextClient() {
    if(clients.empty())
        throw EmptyQueue();
    Client *cl = new Client();
    *cl = clients.front();
    return *cl;
}


void Counter::enter()
{
    Client *cl = new Client;
    nextEnter = rand() % 20 + 1 + actualTime;
    if(clients.empty()) {
        nextLeave = actualTime + wrappingTime * cl->getNumGifts();
    }
    clients.push(*cl);
    cout << "Time = " << actualTime << endl << "New customer arrives with " << cl->getNumGifts() << " gifts." << endl;
}


void Counter::leave()
{
    Client *cl = &(getNextClient());
    clients.pop();
    numAttendedClients++;
    if(!clients.empty())
        nextLeave = clients.front().getNumGifts() * wrappingTime + actualTime;
    else
        nextLeave = 0;
    delete cl;

    cout << "Client leaves at time = " << actualTime << endl;
}


void Counter:: nextEvent()
{
    if(nextEnter < nextLeave || nextLeave == 0){
        actualTime = nextEnter;
        enter();
    }
    else if(nextEnter > nextLeave && !clients.empty()){
        actualTime = nextLeave;
        leave();
    }
    else  // (nextEnter == nextLeave)
    {
        actualTime = nextEnter;
        enter();
        leave();
    }
}


ostream & operator << (ostream & out, const Counter & c2)
{
    out << "Number of attended clients: " << c2.numAttendedClients << endl;
    out << "Numeber of clients in the queue: " << c2.clients.size() << endl;
    return out;
}


