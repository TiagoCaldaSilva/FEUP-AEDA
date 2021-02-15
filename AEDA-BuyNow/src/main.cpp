#include "Menus.h"
#define FILE "COMPANY.txt"

/*
 *  DELETES
 */

int main() {

    // Reference Generation
    srand(time(nullptr));

    int in;
    Company c;
    try {
        c.initialize(FILE);
    }
    catch(InvalidDate &error){
        std::cout << error << std::endl;
    }
    catch(InvalidFile &error){
        std::cout << error << std::endl;
        return 1;
    }
    catch(InvalidPayment &error){
        std::cout << "ERROR IN " << FILE << ":\n\t" << error << std::endl;
        return 1;
    }
    catch(ProductAlreadyExists &error){
        std::cout << error << std::endl;
        return 1;
    }
    catch(ProductDoesNotExist &error){
        std::cout << error << std::endl;
        return 1;
    }
    catch(PhysicalStoreAlreadyExists &error){
        std::cout << error << std::endl;
        return 1;
    }
    catch(ClientAlreadyExists &error){
        std::cout << error << std::endl;
        return 1;
    }
    do {
        std::cout << std::endl << "Welcome to "<< c.getCompanyName() <<"!!" << std::endl << std::endl
                      << "\tHow do you want to login?" << std::endl <<
                  "\t\t1. Admin" << std::endl <<
                  "\t\t2. Client" << std::endl <<
                  "\t\t3. Exit" << std::endl;

        std::cin >> in;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000000, '\n');
            std::cout << "Invalid output, please try again." << std::endl;
        }
        else if(std::cin.peek() != '\n') {
            std::cin.ignore(1000000, '\n');
            std::cout << "Invalid output, please try again." << std::endl;
        }
        if(in == 1)
            admin(&c);
        if(in == 2)
            client(&c);
    }while(in != 3);
    try {
        c.writeFile(FILE);
    }
    catch(InvalidFile &error){
        std::cout << error << std::endl;
        return 1;
    }
    return 0;
}
