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
    /**
     * Constructor of the class Animal
     * @param animal's name
     * @param age animal's age
     */
    Animal(string name, int age);
    /**
     * Destructor of the class Animal
     */
    virtual ~Animal(){};
    /**
     * Function that returns the name of the animal
     * @return animal's name
     */
    string getName() const;
    /**
     * Function that returns the age of the animal
     * @return animal's age
     */
    int getAge() const;
    /**
     * Function that returns the veterinary of the animal
     * @return animal's veterinary
     */
    Veterinary *getVeterinary() const;
    /**
     * Function that assign a veterinary to the animal
     * @param vet Pointer of the veterinary that should be assign to the animal
     */
    void setVeterinary(Veterinary *vet);
    /**
     * Function that returns the youngest animal that already has been created
     * @return the youngest animal
     */
    static int getYoungest();
    /**
     * Function that returns all the information about the animal
     * @return a string with the information of the animal
     */
    virtual string getInfo() const;  // info concerning name, age, name of the veterinary (if any)
    /**
     * Function that tells if the animal is young (should be re-defined in every derivated class)
     * @return true if the animal is young, false if not
     */
    virtual bool isYoung() const {};
};


class Dog: public Animal {
    string breed;
public:
    /**
     * Constructor of the class Dog
     * @param name Name of the dog
     * @param age Age of the dog
     * @param breed breed of the dog
     */
   Dog(string name, int age, string breed);
   /**
    * Function that tells if the dog is young
    * @return true if the age is less than 5, false otherwise
    */
   virtual bool isYoung() const;
   /**
    * Function that returns all the information about the animal
    * @return a string with the name, age, info of the vet and the breed of the animal
    */
   virtual string getInfo() const;
// to complete
};


class Flying {
    int maxVelocity;
    int maxAltitude;
public:
    /**
     * Constructor of the class Flying
     * @param maxv Maximum Velocity of the animal
     * @param maxa Maximum Altitude of the animal
     */
    Flying(int maxv, int maxa);
    /**
     * Returns the max Velocity of the animal
     * @return the max velocity of the animal
     */
    int getMaxV() const;
    /**
     * Returns the max altitude of the animal
     * @return the max altitude of the animal
     */
    int getMaxA() const;
//to complete
};


class Bat: public Animal, public Flying {
public:
    /**
     * Constructor of the class bat
     * @param name name of the bat
     * @param age age of the bat
     * @param maxv maximum velocity of the bat
     * @param maxa maximum altitude of the bat
     */
    Bat(string name, int age, int maxv, int maxa);
    /**
     * Function that tells if the bat is young
     * @return true if the bat's age is less than 4 years, false otherwise
     */
    virtual bool isYoung() const;
    /**
     * Function that returns the information of the bat
     * @return a string with the Name, age, info of the vet and the max velocity and max altitude of the bat
     */
    virtual string getInfo() const;
// to complete
};

#endif /* SRC_ANIMAL_H_ */
