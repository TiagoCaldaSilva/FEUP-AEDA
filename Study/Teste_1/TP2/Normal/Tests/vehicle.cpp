#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) {
    brand = b;
    month = m;
    year = y;
}

int Vehicle::info() const {
    cout << "Brand: " << brand << " -> "
        << month << "/" << year << endl;
    return 3;
}

int Vehicle::info(ostream &o) const {
    o << "Brand: " << brand << " -> "
         << month << "/" << year << endl;
    return 3;
}

int Vehicle::getYear() const {
    return year;
}

string Vehicle::getBrand() const {
    return brand;
}

bool Vehicle::operator<(const Vehicle &v) const {
    if(year != v.year)
        return year < v.year;
    return month < v.month;
}

MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl):Vehicle(b,m,y) {
    fuel = f;
    cylinder = cyl;
}

int MotorVehicle::getCyl() const {
    return cylinder;
}

string MotorVehicle::getFuel() const {
    return fuel;
}

int MotorVehicle::info() const {
    cout << "Brand: " << brand << " -> "
         << month << "/" << year << " || Fuel -> " << fuel << " || Cylinder -> " << cylinder << endl;
    return 5;
}

int MotorVehicle::info(ostream &o) const {
    o << "Brand: " << brand << " -> "
         << month << "/" << year << " || Fuel -> " << fuel << " || Cylinder -> " << cylinder << endl;
    return 5;
}

float MotorVehicle::calculateTax() const {
    if ((fuel == "gas" && cylinder <= 1000) || (fuel != "gas" && cylinder <= 1500)) {
        if (year <= 1995)
            return 8.1;
        else
            return 14.56;
    }
    else if ((fuel == "gas" && cylinder > 1000 && cylinder <= 1300) ||
               (fuel != "gas" && cylinder > 1500 && cylinder <= 2000)){
        if (year <= 1995)
            return 14.56;
        else
            return 29.06;
    }
    else if((fuel == "gas" && cylinder > 1300 && cylinder <= 1750) ||
            (fuel != "gas" && cylinder > 2000 && cylinder <= 3000)){
        if (year <= 1995)
            return 22.65;
        else
            return 45.15;
    }
    else if((fuel == "gas" && cylinder > 1750 && cylinder <= 2600) ||
            (fuel != "gas" && cylinder > 3000)){
        if (year <= 1995)
            return 54.89;
        else
            return 113.98;
    }
    else if(fuel == "gas" && cylinder > 2600 && cylinder <= 3500){
        if (year <= 1995)
            return 87.13;
        else
            return 181.17;
    }
    else
    {
        if (year <= 1995)
            return 148.37;
        else
            return 320.89;
    }
}

Car::Car(string b, int m, int y, string f, int cyl): MotorVehicle(b,m,y,f,cyl){}


Truck::Truck(string b, int m, int y, string f, int cyl, int ml):MotorVehicle(b,m,y,f,cyl) {maximumLoad = ml;}

int Truck::info() const {
    cout << "Brand: " << brand << " -> "
         << month << "/" << year << " || Fuel -> " << getFuel() << " || Cylinder -> " << getCyl() << " || Maximum Load -> " << maximumLoad << endl;
    return 6;
}

int Truck::info(ostream &o) const {
    o << "Brand: " << brand << " -> "
         << month << "/" << year << " || Fuel -> " << getFuel() << " || Cylinder -> " << getCyl() << " || Maximum Load -> " << maximumLoad << endl;
    return 6;
}

Bicycle::Bicycle(string b, int m, int y, string t):Vehicle(b,m,y) {type = t;}

int Bicycle::info() const {
    cout << "Brand: " << brand << " -> "
         << month << "/" << year << " || Type -> " << type << endl;
    return 4;
}

int Bicycle::info(ostream &o) const {
    o << "Brand: " << brand << " -> "
         << month << "/" << year << " || Type -> " << type << endl;
    return 4;
}

float Bicycle::calculateTax() const {
    return 0;
}