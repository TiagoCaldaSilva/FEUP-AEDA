#include "animal.h"
#include <sstream>
using namespace std;

int Animal::youngest = 100000;

Animal::Animal(string name, int age) {
    this->name = name;
    this->age = age;
    if(age < youngest)
        youngest = age;
    string nome = "";
    int cod = 0;
    vet = new Veterinary(nome, cod);
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

int Animal::getYoungest() {
    return youngest;
}

string Animal::getInfo() const {
    if(vet->getName() == "")
        return name + ", " + to_string(age);
    return name + ", " + to_string(age) + ", " + vet->getInfo();
}

bool Animal::operator==(const Animal &a) const
{
    return name == a.name;
}



Dog::Dog(string name, int age, string breed):Animal(name, age) {
    this->breed = breed;
}

bool Dog::isYoung() const {
    return age < 5;
}

string Dog::getInfo() const {
    if(vet->getName() == "")
        return name + ", " + to_string(age) + ", " + breed;
    return name + ", " + to_string(age) + ", " + vet->getInfo() + ", " + breed;
}


Flying::Flying(int maxv, int maxa) {
    maxAltitude = maxa;
    maxVelocity = maxv;
}


Bat::Bat(string name, int age, int maxv, int maxa):Animal(name, age), Flying(maxv, maxa) {}

bool Bat::isYoung() const {
    return age < 4;
}

string Bat::getInfo() const {
    if(vet->getName() == "")
        return name + ", " + to_string(age) + ", " + to_string(maxVelocity) + ", " + to_string(maxAltitude);
    return name + ", " + to_string(age) + ", " + vet->getInfo() + ", " + to_string(maxVelocity) + ", " + to_string(maxAltitude);
}