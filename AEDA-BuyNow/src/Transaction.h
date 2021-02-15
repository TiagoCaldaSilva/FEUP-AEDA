#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include "Product.h"
#include "Payment.h"
#include "Supplier.h"
#include "Utils.h"

/**
 * @class Transaction
 */
class Transaction {
protected:
    Date date;
    std::vector<std::pair<Product *, unsigned int>> cart;
    double value;
    OnlineStore * oStore;
    unsigned int transactionID;
    unsigned int orderCapacity;

    static unsigned int ID;
    static const unsigned short int FP_PRECISION;
public:
  /**
   * @brief Transaction Class Constructor
   * @param date Date of the transaction
   * @param cart Vector with all the items which the Client desires
   * @param oStore OnlineStore responsible for the transaction
   * @param reStock True when derived Class ReStock calls this constructor, false otherwise
   */
  Transaction(const Date& date, std::vector<std::pair<Product *, unsigned int>>& cart, OnlineStore * oStore, bool reStock = false);
  /**
   * @brief Default Destructor
   */
  virtual ~Transaction();
  /**
   * @brief Set the value of date
   * @param value The new value of date
   */
  void setDate(const Date& newDate);
  /**
   * @brief Get the value of date
   * @return The value of date
   */
  const Date& getDate() const;
  /**
   * @brief Set the value of cart
   * @param value The new value of cart
   */
  void setCart(std::vector<std::pair<Product *, unsigned int>>& newCart);
  /**
   * @brief Get the value of cart
   * @return The value of cart
   */
   std::vector<std::pair<Product*, unsigned int>> getCart() const;
  /**
   * @brief Get the order's value
   * @return The order's value
   */
  double getValue() const;
  /**
   * @brief Retrieves the ID from this Transaction
   * @return TransactionID from this Transaction
   */
  unsigned int getTransactionID() const;
  /**
   * @brief Retrieves the order Volume
   * @return orderCapacity from this transaction
   */
  unsigned int getOrderCapacity();
  /**
   * @brief Prints the list of products in the cart
   * @return String containing all the information in the cart
   */
  virtual std::string printTransaction() const;
  /**
   * @brief Adds a product to the cart
   * @param product Product added to the cart
   * @param quantity Quantity of the product
   */
  virtual bool addProduct(Product * product, unsigned int quantity);
  /**
   * @brief Removes a product from the cart
   * @param product Product removed from the cart
   */
  virtual void removeProduct(const Product& product);
  /**
   * @brief Changes the quantity of a product
   * @param product Product whose quantity will be changed
   * @param newQuantity New quantity of the product
   * @throw ProductDoesNotExist if product is not in the cart
   */
  virtual void changeQuantity(Product * product, unsigned int newQuantity);
  /**
   * @brief sorts the cart (by the product description or by the most expensive items)
   * @param comparator Function to determine how the cart should be sorted
   */
  void sortCart(bool comparator(std::pair<Product *, unsigned int>, std::pair<Product *, unsigned int>));
  /**
   * @param rhsTransaction Transaction to be compared
   * @return Bool true if rhsTransaction value is bigger than this->Transaction value
   */
  bool operator<(const Transaction& rhsTransaction) const;
};

/**
 * @class ClientTransaction
 */
class ClientTransaction: public Transaction {
private:
    const unsigned int nif;
    Payment * paymentMethod;
    std::vector<std::pair<Product *, unsigned int>> stockNeeded;
    bool deliveryAtHome;
public:
    /**
     * @brief ClientTransaction Class Constructor
     * @param date Date of the transaction
     * @param cart Vector with all the items which the Client desires
     * @param oStore OnlineStore responsible for the transaction
     * @param cNIF Client's NIF
     */
    ClientTransaction(const Date& date, std::vector<std::pair<Product *, unsigned int>>& cart, OnlineStore * oStore, unsigned int cNIF);
    /**
     * @brief Default Destructor
     */
    ~ClientTransaction();
    /**
     * @brief Retrieves the payment method from this transaction
     * @return Payment object pointer from paymentMethod
     */
    Payment * getPaymentMethod() const;
    /**
     * @brief Sets the payment method of a given transaction
     * @param payMethod used to pay the transaction
     */
    void setPaymentMethod(Payment * payMethod);
    /**
     * @brief Sets the current Order/Transaction to be delivered at Client Address
     */
    void setHomeDelivery();
    /**
     * @brief Gets the Client's NIF
     * @return Client NIF
     */
    unsigned int getNif() const;
    /**
     * @brief Checks if a given product has enough quantity for a Client order
     * @param index Index of the product in which the stock will be checked
     * @param quantity Quantity of the product requested by the Client
     * @param changeQt Set to false by default, should be true if its called from changeQuantity method
     * @throw NotEnoughStock If quantity is bigger than the current OnlineStore stock
     */
    void checkStock(int index, unsigned int quantity, bool changeQt = false);
    /**
     * @brief Adds a product to the cart
     * @param product Product added to the cart
     * @param quantity Quantity of product
     * @return True if the product was successfully added, otherwise false
     * @throw NotEnoughStock If the quantity is bigger than the current OnlineStore stock
     * @throw ProductDoesNotExist If the product isn't listed in the OnlineStore
     */
    bool addProduct(Product * product, unsigned int quantity);
    /**
     * @brief Removes a product from the cart
     * @param product Product removed from the cart
     */
    void removeProduct(const Product& product);
    /**
     * @brief Changes the quantity of a product
     * @param product Product whose quantity will be changed
     * @param newQuantity New quantity of the product
     * @throw NotEnoughStock If the quantity is bigger than the current OnlineStore stock
     * @throw ProductDoesNotExist If the method tries to change the quantity of product that's not in the cart
     */
    void changeQuantity(Product * product, unsigned int newQuantity);
    /**
     * @brief Prints the transaction information
     * @return String containing all the information about the transaction
     */
    std::string printTransaction() const;
    /**
     * @brief Verifies if there's need to call reStock
     * @return True if stockNeeded is empty else returns false
     */
    bool stockNeededEmpty() const;
    /**
     * @brief Retrieves the vector with the quantities needed for a future reStock call
     * @return Vector with the needed products and respective quantities for a future reStock call
     */
    std::vector<std::pair<Product *, unsigned int>>& getStockNeeded();
};

/**
 * @class ReStock
 */
class ReStock: public Transaction {
private:
    bool bySupplier;
    Supplier supplier;
public:
    /**
     * @brief ReStock Class Constructor
     * @param date Date of the transaction
     * @param sN Vector of products and respective quantity that were restocked
     * @param oStore OnlineStore responsible for the transaction
     * @param bySupplier Boolean value to distinguish if the transaction was made with the supplier or with other physical stores
     */
    ReStock(const Date& date, std::vector<std::pair<Product *, unsigned int>>& sN, OnlineStore * oStore, bool bySupplier);
    /**
     * @brief Set the value of bySupplier
     * @param value The new value of bySupplier
     */
    void setBySupplier(bool value);
    /**
     * @brief Get the value of bySupplier
     * @return The value of bySupplier
     */
    bool getBySupplier() const;
    /**
     * @brief Get the value of supplier
     * @return The value of supplier
     */
    const Supplier &getSupplier() const;
    /**
     * @brief Set the value of supplier
     * @param supplier The new value of supplier
     */
    void setSupplier(const Supplier &supplier);
    /**
     * @brief Prints the transaction information
     * @return String containing all the information about the transaction
     */
    std::string printTransaction() const;
};

#endif // TRANSACTION_H
