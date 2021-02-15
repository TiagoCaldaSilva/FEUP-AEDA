#include "animal.h"
#include <sstream>

using namespace std;

int Animal::getYoungest()
{
    return youngest;
}

int Animal::youngest = 100;

Animal::Animal(string name, int age)
{
    vet = new Veterinary("", 0);
    this->name = name;
    this->age = age;
    if(age < youngest)
        youngest = age;
}

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

string Animal::getInfo() const
{
    string result = name + ", " + to_string(age);
    string v = vet->getName();
    if(v != "")
        result += ", " +  (*vet).getInfo();
    return  result ;
}




Dog::Dog(string name, int age, string breed) :Animal(name, age)
{
    this->breed = breed;
}

bool Dog::isYoung() const
{
    if(age < 5)
        return true;
    return false;
}

string Dog::getInfo() const
{
    string result = name + ", " + to_string(age) + ", ";
    string v = (*vet).getName();
    if(v != "")
        result += vet->getInfo() + ", ";
    return result + breed;
}



Flying::Flying(int maxv, int maxa)
{
    maxAltitude = maxa;
    maxVelocity = maxv;
}

int Flying::getMaxV() const
{
    return maxVelocity;
}

int Flying::getMaxA() const
{
    return maxAltitude;
}




Bat::Bat(string name, int age, int maxv, int maxa) :Animal(name, age), Flying(maxv, maxa) {}

bool Bat::isYoung() const
{
    if(age < 4)
        return true;
    return false;
}

string Bat::getInfo() const
{
    string result = name + ", " + to_string(age) + ", ";
    string v = (*vet).getName();
    if(v != "")
        result += vet->getInfo() + ", ";
    return result + to_string(getMaxV()) + ", " + to_string(getMaxA());
}