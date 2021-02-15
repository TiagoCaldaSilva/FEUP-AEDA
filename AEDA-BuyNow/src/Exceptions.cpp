#include "Exceptions.h"

// PaymentMethodAlreadyExists exception Class Implementation

PaymentMethodAlreadyExists::PaymentMethodAlreadyExists(){
    error = "The payment method given, was already used.";
}

std::string PaymentMethodAlreadyExists::printError() const {
    return error;
}

std::ostream& operator<<(std::ostream& out, const PaymentMethodAlreadyExists& error) {
    out << error.printError();
    return out;
}

// PaymentMethodAlreadyExists exception Class Implementation

ClientDoesNotExist::ClientDoesNotExist() {
    error = "The given client does not exist.";
}

std::string ClientDoesNotExist::printError() const {
    return error;
}

std::ostream& operator<<(std::ostream& out, const ClientDoesNotExist& error) {
    out << error.printError();
    return out;
}

// InvalidFile exception Class Implementation

InvalidFile::InvalidFile(const std::string& s) {
    msg = s + " does not exist\n";
}

std::string InvalidFile::printError() const {
    return msg;
}

std::ostream& operator<<(std::ostream& out, const InvalidFile& error){
    out << error.printError();
    return out;
}

// InvalidDate exception Class Implementation

InvalidDate::InvalidDate(const std::string& error)
{
    invalidDate = error;
}

std::string InvalidDate::printError() const { return invalidDate; }

std::ostream& operator<<(std::ostream& out, const InvalidDate& invalidInput) { out << invalidInput.invalidDate; return out; }

// InvalidPayment exception Class Implementation

InvalidPayment::InvalidPayment(){invalidPayment = "Invalid method of payment.";}

InvalidPayment::InvalidPayment(const std::string& error)
{
    invalidPayment = error;
}

std::string InvalidPayment::printError() const { return invalidPayment; }

std::ostream& operator<<(std::ostream& out, const InvalidPayment& invalidInput) { out << invalidInput.invalidPayment; return out; }

// ProductDoesNotExist exception Class Implementation

ProductDoesNotExist::ProductDoesNotExist(const std::string& description, bool store)
{
    if(store)invalidProduct = "The following product does not exist: " + description;
    else invalidProduct = "The following product does not belong to the basket: " + description;
}

std::string ProductDoesNotExist::printError() const { return invalidProduct; }

std::ostream& operator<<(std::ostream& out, const ProductDoesNotExist& invalidInput) { out << invalidInput.invalidProduct; return out; }


// ProductAlreadyExist exception Class Implementation

ProductAlreadyExists::ProductAlreadyExists(const std::string& description)
{
    invalidProduct = "The following product already exists: " + description;
}

std::string ProductAlreadyExists::printError() const { return invalidProduct; }
std::ostream& operator<<(std::ostream& out, const ProductAlreadyExists& invalidInput) { out << invalidInput.invalidProduct; return out; }

//PhysicalStoreAlreadyExists exception Class Implementation

PhysicalStoreAlreadyExists::PhysicalStoreAlreadyExists(const std::string& location){
    error = "The following store already exists: " + location;
}

std::string PhysicalStoreAlreadyExists::printError() const { return error;}

std::ostream& operator<<(std::ostream& out, const PhysicalStoreAlreadyExists& invalidInput) { out << invalidInput.printError(); return out; }

//PhysicalStoreDoesNotExist exception Class Implementation

PhysicalStoreDoesNotExist::PhysicalStoreDoesNotExist(){
    error = "That store does not exist";
}

PhysicalStoreDoesNotExist::PhysicalStoreDoesNotExist(const std::string& loc){
    error = "The store \"" + loc + "\" does not exist";
}
std::string PhysicalStoreDoesNotExist::printError() const { return error;}

std::ostream& operator<<(std::ostream& out, const PhysicalStoreDoesNotExist& invalidInput) { out << invalidInput.printError(); return out; }

// NotEnoughStock Exception Implementation

NotEnoughStock::NotEnoughStock(const std::string& description)
{
    invalidStock = "The store does not have enough stock of the following item: " + description;
}

std::string NotEnoughStock::printError() const { return invalidStock; }

std::ostream& operator<<(std::ostream& out, const NotEnoughStock& invalidStock) { out << invalidStock.invalidStock; return out; }

// ClientAlreadyExists Exception Implementation

ClientAlreadyExists::ClientAlreadyExists(int ind, unsigned int n){
    index = ind;
    nif = n;
}

int ClientAlreadyExists::getIndex() const {
    return index;
}

std::string ClientAlreadyExists::printError() const {
    return "The client with the nif: " + std::to_string(nif) + " already exists";
}

std::ostream& operator<<(std::ostream& out, const ClientAlreadyExists& error){
    out << error.printError() << std::endl;
    return out;
}

// VanLoadException Class Implementation

VanLoadException::VanLoadException() = default;

std::ostream& operator<<(std::ostream& out, const VanLoadException& error) {
    out << error.printError() << std::endl;
    return out;
}

// VanLoadException Subclasses Implementation

VanAlreadyFull::VanAlreadyFull() : VanLoadException() { invalidLoad = "The Van is already Full!"; }
std::string VanAlreadyFull::printError() const { return invalidLoad; }

VanAlreadyEmpty::VanAlreadyEmpty() : VanLoadException() { invalidLoad = "The Van is already Empty!"; }
std::string VanAlreadyEmpty::printError() const { return invalidLoad; }

VanNotReady::VanNotReady(const unsigned int loadRatio) : VanLoadException(), loadRatio(loadRatio) {
    invalidLoad = "The Van is only " + std::to_string(loadRatio) + "% full (below 90%)!";
}
std::string VanNotReady::printError() const { return invalidLoad; }
