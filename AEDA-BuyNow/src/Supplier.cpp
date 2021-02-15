#include "Supplier.h"

// Supplier Class Implementation

Supplier::Supplier()
{
    name = "";
    nif = 0;
}

Supplier::~Supplier() = default;

Supplier::Supplier(std::string name, unsigned int nif, std::string productName, double price):name(name),nif(nif),productName(productName),price(price) {}

const string &Supplier::getName() const {
    return name;
}

void Supplier::setName(const string &name) {
    Supplier::name = name;
}

unsigned int Supplier::getNif() const {
    return nif;
}

void Supplier::setNif(unsigned int nif) {
    Supplier::nif = nif;
}

const string &Supplier::getProductName() const {
    return productName;
}

void Supplier::setProductName(const string &productName) {
    Supplier::productName = productName;
}

double Supplier::getPrice() const {
    return price;
}

void Supplier::setPrice(double price) {
    Supplier::price = price;
}

unsigned int Supplier::getCurrentStock() const {
    return currentStock;
}

void Supplier::setCurrentStock(unsigned int currentStock) {
    Supplier::currentStock = currentStock;
}

bool Supplier::operator<(const Supplier &sp2) const {
    if(price<sp2.price) return true;
    else if(price==sp2.price){
        if(currentStock<sp2.currentStock) return true;
        else if(currentStock==sp2.currentStock) {
            if(name<sp2.name) return true;
        }
    }
    return false;
}

bool Supplier::operator==(const Supplier &sp2) const {
    return (name==sp2.name && productName==sp2.productName);
}

Supplier::Supplier(std::string name, double price): name(name),price(price) {

}
