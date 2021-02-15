#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

//TODO
Client::Client() {
}

//TODO
unsigned Client::getNumGifts() const {
    return 0;
}


//TODO
Counter::Counter(unsigned wt): wrappingTime(wt) {
}

//TODO
unsigned Counter::getActualTime() const {
    return 0;
}

//TODO
unsigned Counter::getNextEnter() const {
    return 0;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return 0;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return 0;
}

//TODO
unsigned Counter::getNextLeave() const {
    return 0;
}

//TODO
Client & Counter::getNextClient() {
    Client *cl = new Client();
    return *cl;
}

//TODO
void Counter::enter()
{
}

//TODO
void Counter::leave()
{
}

//TODO
void Counter:: nextEvent()
{
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
     return out;
}


