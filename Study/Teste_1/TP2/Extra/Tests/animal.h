#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinary.h"
#include <string>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    Veterinary *vet;
    static int youngest;
public:
    Animal(string name, int age);
    virtual ~Animal(){};
    string getName() const;
    int getAge() const;
    Veterinary *getVeterinary() const;
    void setVeterinary(Veterinary *vet);
    static int getYoungest();
    virtual string getInfo() const;  // info concerning name, age, name of the veterinary (if any)
    virtual bool isYoung() const = 0;
    bool operator==(const Animal &a) const;
};


class Dog: public Animal {
    string breed;
public:
    Dog(string name, int age, string breed);
    virtual bool isYoung() const;
    virtual string getInfo() const;
// to complete
};


class Flying {
protected:
    int maxVelocity;
    int maxAltitude;
public:
   Flying(int maxv, int maxa);
//to complete
};


class Bat: public Animal, public Flying {
public:
    Bat(string name, int age, int maxv, int maxa);
    virtual bool isYoung() const;
    virtual string getInfo() const;
// to complete
};

#endif /* SRC_ANIMAL_H_ */
