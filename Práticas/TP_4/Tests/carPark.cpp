#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}


int CarPark::clientPosition(const string & name) const
{
    InfoCard x;
    x.name = name;
    return sequentialSearch(clients, x);
}


unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if(pos == -1)
        throw ClientDoesNotExist(name);
    return clients[pos].frequency;
}


bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

// TODO: to modify -> não se modificou ?????
bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}


bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    freePlaces--;
    clients[pos].frequency++;
    return true;
}

// TODO: to modify -> não se modificou ?????
bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;
    if(p < 0 || p >= clients.size())
        throw PositionDoesNotExist(p);
    info = clients[p];
    return info;
}


void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}


void CarPark::sortClientsByName()
{
    //Insertion sort
    for (unsigned int p = 1; p < clients.size(); p++)
    {
        InfoCard tmp =clients[p];
        int j;
        for (j = p; j > 0 && tmp.name < clients[j-1].name; j--)
            clients[j] = clients[j-1];
        clients[j] = tmp;
    }
}


vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    sortClientsByFrequency();
    for(size_t i = 0; i < clients.size(); i++)
    {
        if(clients[i].frequency <= f2 && clients[i].frequency >= f1)
            names.push_back(clients[i].name);
    }
    return names;
}


ostream & operator<<(ostream & os, const CarPark & cp)
{
    for(size_t i = 0; i < cp.clients.size(); i++)
    {
        os << cp.clients[i].name << ", " << cp.clients[i].present << ", " << cp.clients[i].frequency << endl;
    }
    return os;
}


bool InfoCard::operator==(InfoCard &x) const
{
    return name == x.name;
}


bool InfoCard::operator<(InfoCard &x) const
{
    if (frequency == x.frequency)
        return (name < x.name);
    return (frequency > x.frequency );
}