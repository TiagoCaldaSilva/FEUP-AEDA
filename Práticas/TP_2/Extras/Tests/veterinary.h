#ifndef SRC_VETERINARY_H_
#define SRC_VETERINARY_H_

#include <string>
using namespace std;

class Veterinary {
    string name;
    long codOrder;
public:
    /**
     * Constructor of the class veterinary
     * @param nome name of the veterinary
     * @param cod  code of the veterinary
     */
    Veterinary(string nome, int cod);
    /**
     * Function that returns the name of the veterinary
     * @return the name of the veterinary
     */
    string getName() const;
    /**
     * Function that returns the information of the veterinary
     * @return a string with the name and the code of the veterinary
     */
    string getInfo() const;
    
};


#endif /* SRC_VETERINARY_H_ */
