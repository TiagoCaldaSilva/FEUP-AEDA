#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1)
{
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const
{
    return int(vehicles.size());
}

int Fleet::lowestYear() const
{
    int y, y_;
    if (vehicles.size() == 0) //if the vector vehicles is empty, the function returns 0
        return 0;
    y = (*vehicles[0]).getYear();
    for(int i=1; i < vehicles.size(); i++) //in the end of the for loop, y is the year of the lowest vehicle
    {
        y_ = (*vehicles[i]).getYear();
        if(y_ < y)
            y = y_;
    }
    return y;
}

ostream & operator<<(ostream & o, const Fleet & f)
{
    for(int i = 0; i < f.numVehicles(); i++)
    {
        (*f.vehicles[i]).info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator () (int yearM) const
{
    vector<Vehicle *> v;
    for(int i= 0; i < vehicles.size(); i++)
    {
        if((*vehicles[i]).getYear() == yearM)
            v.push_back(vehicles[i]);
    }
    return v;
}

float Fleet::totalTax() const
{
    float sum = 0;
    for(int i = 0; i < vehicles.size(); i++)
    {
        sum += (*vehicles[i]).calculateTax();
    }
    return sum;
}

unsigned Fleet::removeOldVehicles(int y1)
{
    unsigned init = vehicles.size();
    for(int i = 0; i < vehicles.size(); i++)
    {
        if((*vehicles[i]).getYear() <= y1)
        {
            vehicles.erase(vehicles.begin() + i);
            i--;
        }
    }
    return (init - (unsigned)vehicles.size());
}
