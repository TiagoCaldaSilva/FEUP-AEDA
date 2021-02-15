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
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if (!numVehicles())
        return 0;
    int year = vehicles[0]->getYear();
    for(Vehicle * v:vehicles)
    {
        if(v->getYear() < year)
            year = v->getYear();
    }
    return year;
}

ostream & operator<<(ostream & o, const Fleet & f)
{
    for(Vehicle * v: f.getVehicles())
    {
        v->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator()(int yearM) const {
    vector<Vehicle *> result;
    for(Vehicle * v: vehicles)
        if(v->getYear() == yearM)
            result.push_back(v);
    return result;
}

float Fleet::totalTax() const{
    float sum = 0;
    for(Vehicle * v:vehicles)
        sum+= v->calculateTax();
    return sum;
}

bool comparator(Vehicle * v1, Vehicle* v2)
{
    return v1->getYear() < v2->getYear();
}

unsigned Fleet::removeOldVehicles(int y1){
    sort(vehicles.begin(), vehicles.end(), comparator);
    int i= 0;
    for(i; i< vehicles.size(); i++)
        if(vehicles[i]->getYear() > y1)
            break;
    vehicles.erase(vehicles.begin(), vehicles.begin() + i);
    return i -1;
}