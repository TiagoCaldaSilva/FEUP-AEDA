#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1){
    animals.push_back(a1);
}

string Zoo::getInfo () const
{
    string result = "";
    for(Animal * a:animals)
    {
        result += a->getInfo() + '\n';
    }
    return result;
}

bool Zoo::isYoung(string nameA){
    for(Animal * a: animals)
    {
        if(a->getName() == nameA)
            return a->isYoung();
    }
    return 0;
}

void Zoo::allocateVeterinarians(istream &isV)
{
    string name, cod;
    while(getline(isV, name, '\n'))
    {
        getline(isV, cod, '\n');
        veterinarians.push_back(new Veterinary(name, stoi(cod)));
    }
    int size = 0;
    for(Animal * a:animals)
    {
        size %= veterinarians.size();
        a->setVeterinary(veterinarians[size]);
        size++;
    }
}

bool Zoo::removeVeterinary(string nameV) {
    bool exist = false;
    int ind = 0;
    for(ind; ind < veterinarians.size(); ind++)
    {
        if(veterinarians[ind]->getName() == nameV) {
            exist = true;
            break;
        }
    }
    if(!exist)
        return exist;
    veterinarians.erase(veterinarians.begin() + ind);
    if(ind == veterinarians.size())
        ind == 0;
    for(Animal * &a:animals)
    {
        if(a->getVeterinary()->getName() == nameV)
            a->setVeterinary(veterinarians[ind]);
    }
    return exist;
}

bool Zoo::operator<(Zoo& zoo2) const{
    int sum1, sum2;
    for(Animal *a:animals)
        sum1 += a->getAge();
    for(Animal *b:zoo2.animals)
        sum2 += b->getAge();
    return sum1 < sum2;
}