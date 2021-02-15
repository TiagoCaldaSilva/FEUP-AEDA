#include "zoo.h"
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1)
{
    animals.push_back(a1);
}

string Zoo::getInfo() const
{
    string result = "";
    for(size_t i = 0; i < animals.size(); i++)
    {
        result += animals[i]->getInfo();
    }
    return result;
}

bool Zoo::isYoung(string nameA)
{
    for(size_t  i = 0; i < animals.size(); i++)
    {
        if(((*animals[i]).getName() == nameA) && ((*animals[i]).isYoung()))
        {
            return true;
        }
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV)
{
    string name, age;
    while(getline(isV, name, '\n'))
    {
        getline(isV, age, '\n');
        Veterinary *x = new Veterinary(name, stoi(age));
        veterinarians.push_back(x);
    }

    int n = veterinarians.size();

    for(size_t i = 0; i < animals.size(); i++)
    {
        int x = i % n;
        (*animals[i]).setVeterinary(veterinarians[x]);
    }
}

bool Zoo::removeVeterinary(string nameV)
{
    for(size_t i = 0; i < veterinarians.size(); i++)
    {
        if((*veterinarians[i]).getName() == nameV) {
            Veterinary *x = veterinarians[i];
            for(size_t j = 0; j < animals.size(); j++)
            {
                if(animals[j]->getVeterinary() == x )
                {
                    if(i == veterinarians.size())
                        animals[j]->setVeterinary(veterinarians[0]);
                    else
                        animals[j]->setVeterinary(veterinarians[i+1]);
                }
            }
            veterinarians.erase(veterinarians.begin() + i);delete x;
            return true;
        }
    }
    return false;
}

bool Zoo::operator < (Zoo& zoo2) const
{
    int sum1 = 0, sum2 = 0;
    for(size_t i = 0; i < animals.size(); i++)
    {
        sum1 += animals[i]->getAge();
    }
    for(size_t i = 0; i < zoo2.animals.size(); i++)
    {
        sum2 += zoo2.animals[i]->getAge();
    }
    return sum1 < sum2;
}
