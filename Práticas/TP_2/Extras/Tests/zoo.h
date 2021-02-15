#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
	vector<Animal *> animals;
	vector<Veterinary *> veterinarians;
public:
    /**
     * Function that returns the number of the animals of the zoo
     * @return the number of animals
     */
	unsigned numAnimals() const;
	/**
	 * Function that returns the number os veteriarians of the zoo
	 * @return the number of veterinarians
	 */
	unsigned numVeterinarians() const;
	/**
	 * Function that adds an animal to the zoo
	 * @param a1 pointer to the animal
	 */
    void addAnimal(Animal *a1);
    /**
     * Function that returns the information of all the animals of the zoo
     * @return a string with all the information of the animals of the zoo
     */
    string getInfo() const;
    /**
     * Function that determines if the animal is young
     * @param nameA name of the animal
     * @return true if the animal is young, false otherwise
     */
    bool isYoung(string nameA);
    /**
     * Function that allocate a set of veterinarians to the zoo. The set of veterinarians are in the file opened with istream
     * @param isV istream that has open the file were the information of the veterinarians is
     */
    void allocateVeterinarians(istream &isV);
    /**
     * Function that remove a veterinary of the zoo and allocate another veterinary to the animals that the veterinary removed
     * was allocated
     * @param nameV name of the veterinary
     * @return true if the _____ was done
     */
    bool removeVeterinary(string nameV);
    /**
     * Function that compares two zoos
     * @param zoo2 zoo that must be compared with
     * @return true if the sum of the age of all the animals of the zoo is less than the sum of the age of alll the animals of the
     * zoo2,false otherwise
     */
    bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
