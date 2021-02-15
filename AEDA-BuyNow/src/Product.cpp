#include "Product.h"

// Product Class Implementation

Product::Product(const std::string& description, double price) : description(description), price(price) {}

Product::Product(const std::string& description): description(description) {price=0.0;}

Product::~Product() = default;

void Product::setDescription(const std::string& value) { description = value; }

std::string Product::getDescription() const { return description; }

void Product::setPrice(double value) { price = value; }

double Product::getPrice() const { return price; }

bool Product::operator==(const Product& productCompared) const {
    return (description==productCompared.description);
}
