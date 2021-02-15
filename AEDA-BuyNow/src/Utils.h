#ifndef AEDA_BUYNOW_UTILS_H
#define AEDA_BUYNOW_UTILS_H
#include "Store.h"


/**
  * @class ComparatorByProduct
  */
class ComparatorByProduct
{
private:
    Product * product;
public:
    /**
     * @brief ComparatorByProduct Class Constructor
     * @param product Product to be compared
     */
    ComparatorByProduct(Product * product):product(product){}
    /**
     * @brief Function operator in order to call the comparator for a certain product
     * @param s1 Physical store to be compared
     * @param s2 Physical store to be compared
     * @return Boolean value to whether the quantity of the product is lower in s1 or s2
     */
    bool operator()(PhysicalStore * s1, PhysicalStore * s2) const {
        unsigned int n1=0,n2=0;
        for (StoreProduct * sP:s1->getProducts()) {
            if(*(sP->getProduct()) == *product) {
                n1 = sP->getCurrentStock();
                break;
            }
        }
        for(StoreProduct * sP:s2->getProducts()){
            if(*(sP->getProduct()) == *product) {
                n2 = sP->getCurrentStock();
                break;
            }
        }
        return n1<n2;
    }

};

/**
 * @class FindProduct_pair
 */
class FindProduct_pair{
public:
    Product * p;
    /**
     * @brief Class constructor
     * @param p1 Pair with the product that should be found
     */
    explicit FindProduct_pair(const std::pair<Product *, unsigned  int>& p1){p = p1.first;}
    /**
     * @brief Comparator function used to compare two products
     * @param sp2 Product number 2
     * @return True if they are the same, false otherwise
     */
    bool operator()(const std::pair<Product *, unsigned  int>& p2) const{
        return (*p) == *(p2.first);
    }
};

#endif //AEDA_BUYNOW_UTILS_H
