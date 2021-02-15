#include "vehicle.h"
#include <iostream>

#define members_V  3;
#define members_MV  5;
using namespace std;

Vehicle::Vehicle(string b, int m, int y)
{
    brand =b; month = m; year = y;
}

string Vehicle::getBrand() const
{
    return brand;
}

int Vehicle::getYear() const
{
    return year;
}

int Vehicle::info() const
{
    cout << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    return members_V;
}

int Vehicle::info(ostream &o) const
{
    o << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    return members_V;
}

bool Vehicle::operator < (const Vehicle & v) const
{
    if(year < v.year)
        return true;
    else if((year == v.year) && (month < v.month))
        return true;
    return false;
}




MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) :Vehicle(b, m, y)
{
    fuel = f;
    cylinder = cyl;
}

string MotorVehicle::getFuel() const
{
    return fuel;
}

int MotorVehicle::getCyl() const
{
    return cylinder;
}

int MotorVehicle::info() const
{
    cout << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    cout << "Fuel = " << fuel << "\nCylinder = " << cylinder << endl;
    return members_MV;
}

int MotorVehicle::info(ostream &o) const
{
    o << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    o << "Fuel = " << fuel << "\nCylinder = " << cylinder << endl;
    return members_MV;
}

float MotorVehicle::calculateTax() const
{
    pair<float, float> x;
    bool valid = false;
    vector<pair<float, float>> _v = {make_pair(14.56, 8.10), make_pair(29.06, 14.56), make_pair(45.15, 22.65), make_pair(113.98, 54089), make_pair(181.17, 87.13), make_pair(320.89,148.37)};
    if(fuel == "gas")
    {
        vector<int> vg = {1000, 1300, 1750, 2600, 3500};
        for(int i = 0; i < vg.size(); i++)
        {
            if(cylinder <= vg[i])
            {
                x = _v[i];
                valid = true;
                break;
            }
        }
        if(!valid)
            pair<float, float> x(_v[vg.size() -1]); //if cylinder > 3500
    }
    else
    {
        vector<int> vo = {1500,2000,3000};
        for(int i = 0; i < vo.size(); i++)
        {
            if(cylinder <= vo[i])
            {
                x = _v[i];
                valid = true;
                break;
            }
        }
        if(!valid)
            x = _v[vo.size() -1]; //if cylinder > 3000
    }
    if(year > 1995)
        return x.first;
    else
        return x.second;
}




Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b,m,y,f,cyl) {}

int Car::info() const
{
    cout << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    cout << "Fuel = " << getFuel() << "\nCylinder = " << getCyl() << endl;
    return members_MV;
}




Truck::Truck(string b, int m, int y, string f, int cyl, int ml) :MotorVehicle(b, m, y, f, cyl) {maximumLoad = ml;}

int Truck::info() const
{
    cout << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    cout << "Fuel = " << getFuel() << "\nCylinder = " << getCyl() << endl;
    cout << "Maximum Load: " << maximumLoad << endl;
    int n = members_MV;
    n++; //WHY NOT RETURN MEMBERS_MV +1;
    return n;
}

int Truck::info(ostream &o) const
{
    o << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    o << "Fuel = " << getFuel() << "\nCylinder = " << getCyl() << endl;
    o << "Maximum Load: " << maximumLoad << endl;
    int n = members_MV;
    n++; //WHY NOT RETURN MEMBERS_MV +1;
    return n;
}




Bicycle::Bicycle(string b, int m, int y, string t) :Vehicle(b, m, y) {type = t;}

int Bicycle::info() const
{
    cout << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    cout << "Type = " << type << endl;
    int n = members_V;
    n++;
    return n;
}

int Bicycle::info(ostream &o) const
{
    o << "Brand = " << brand << "\nYear = " << year << "\nMonth = " << month << endl;
    o << "Type = " << type << endl;
    int n = members_V;
    n++;
    return n;
}

float Bicycle::calculateTax() const
{
    return 0;
}