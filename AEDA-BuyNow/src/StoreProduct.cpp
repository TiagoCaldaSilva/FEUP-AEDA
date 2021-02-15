#include "StoreProduct.h"

// StoreProduct Class Implementation

StoreProduct::StoreProduct(Product * product, unsigned int currentStock, unsigned int stockLimit) :
product(product), currentStock(currentStock), stockLimit(stockLimit) {}

StoreProduct::~StoreProduct() { delete product; }

void StoreProduct::setProduct(Product * value){ product = value; }

Product * StoreProduct::getProduct() const { return product; }

void StoreProduct::setCurrentStock(unsigned int value){ currentStock = value; }

unsigned int StoreProduct::getCurrentStock() const{ return currentStock; }

void StoreProduct::setStockLimit(unsigned int value) { stockLimit = value; }

unsigned int StoreProduct::getStockLimit() const { return stockLimit; }

bool StoreProduct::operator<(const StoreProduct& productCompared) const { return product->getDescription() < productCompared.getProduct()->getDescription(); }

void StoreProduct::reduceCurrentStock(unsigned int quantity) { currentStock-=quantity; }

void StoreProduct::increaseCurrentStock(unsigned int quantity){ currentStock+=quantity; }

bool StoreProduct::operator==(const StoreProduct& productCompared) const {return *product == *productCompared.product;}
