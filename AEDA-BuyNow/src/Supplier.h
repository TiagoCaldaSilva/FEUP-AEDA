#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "BST.h"
#include <string>

/**
  * @class Supplier
  */
class Supplier
{
private:
    std::string name;
    unsigned int nif;
    std::string productName;
    double price;
    unsigned int currentStock;
public:
    /**
     * @brief Default Constructor
     */
    Supplier();
    /**
     * @brief Default Destructor
     */
    virtual ~Supplier();
    /**
     * @brief Class constructor
     * @param name Name of the supplier
     * @param nif Nif of the supplier
     * @param productName Name of the product being sold
     * @param price Price of the product sold
     */
    Supplier(std::string name, unsigned int nif, std::string productName, double price);
    /**
     * @brief Class constructor
     * @param name Name of the supplier
     * @param price Price of the product sold
     */
    Supplier(std::string name,double price);
    /**
     * @brief Get the name of the supplier
     * @return String with the name of the supplier
     */
    const std::string &getName() const;
    /**
     * @brief Set the name of the supplier to name
     * @param name New name for the supplier
     */
    void setName(const std::string &name);
    /**
     * @brief Get the supplier nif
     * @return Nif of the supplier
     */
    unsigned int getNif() const;
    /**
     * @brief Set the nif of the supplier to nif
     * @param nif New nif for the supplier
     */
    void setNif(unsigned int nif);
    /**
     * @brief Get the name of the product sold
     * @return String with the name of the product being sold
     */
    const string &getProductName() const;
    /**
     * @brief Set the name of the product sold
     * @param productName New name for the product sold
     */
    void setProductName(const string &productName);
    /**
     * @brief Get the product's price
     * @return Product price
     */
    double getPrice() const;
    /**
     * @brief Set the product's price to price
     * @param price New price for product
     */
    void setPrice(double price);
    /**
     * @brief Get the current stock of the product
     * @return The current stock of the product
     */
    unsigned int getCurrentStock() const;
    /**
     * @brief Set the current stock of the product to currentStock
     * @param currentStock new current stock for the product
     */
    void setCurrentStock(unsigned int currentStock);
    /**
     * @brief Lower of operator, ordered by price, current stock and name
     * @param sp2 Supplier to be compared with this
     * @return Boolean value that tells if this is lower than sp2
     */
    bool operator<(const Supplier& sp2) const;
    /**
     * @brief Equal operator, a supplier is the same as other if their name and product sold are the same
     * @param sp2 Supplier to be compared with this
     * @return Boolean value that tells if this is equal to sp2
     */
    bool operator==(const Supplier& sp2) const;

};








#endif //SUPPLIER_H
