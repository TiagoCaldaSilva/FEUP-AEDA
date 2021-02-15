#ifndef STOREPRODUCT_H
#define STOREPRODUCT_H

#include "Product.h"

class StoreProduct
{
private:
    Product * product;
    unsigned int currentStock;
    unsigned int stockLimit;

public:
  /**
   * @brief StoreProduct Class Constructor
   * @param product Product pointer
   * @param currentStock Existing stock of the product in the store
   * @param stockLimit Stock minimum that the store must have for the product
   */
  explicit StoreProduct(Product * product, unsigned int currentStock = 0, unsigned int stockLimit = 0);
  /**
   * @brief StoreProduct Destructor deallocates the memory owned
   */
  ~StoreProduct();
  /**
   * @brief Set the value of product
   * @param value The new value of product
   */
  void setProduct(Product* value);
  /**
   * @brief Get the value of product
   * @return The value of product
   */
  Product* getProduct() const;
  /**
   * @brief Set the value of currentStock
   * @param value The new value of currentStock
   */
  void setCurrentStock(unsigned int value);
  /**
   * @brief Get the value of currentStock
   * @return The value of currentStock
   */
  unsigned int getCurrentStock() const;
  /**
   * @brief Set the value of stockLimit
   * @param value The new value of stockLimit
   */
  void setStockLimit(unsigned int value);
  /**
   * @brief Get the value of stockLimit
   * @return The value of stockLimit
   */
  unsigned int getStockLimit() const;
  /**
   * @brief Reduce the current stock
   * @param quantity Quantity to be reduced from the currentStock
   */
  void reduceCurrentStock(unsigned int quantity);
  /**
   * @brief Increase the current stock
   * @param quantity Quantity to be increased in the currentStock
   */
  void increaseCurrentStock(unsigned int quantity);
  /**
   * @brief lower operator
   * @param productCompared StoreProduct to be compared
   * @return Boolean value to whether to first object is lower than the other, by name of the product
   */
  bool operator<(const StoreProduct& productCompared) const;
  /**
   * @brief Comparison operator
   * @param productCompared StoreProduct to be compared
   * @return Boolean value to whether the first object's product is equal to the second one
   */
  bool operator==(const StoreProduct& productCompared) const;
};


#endif // STOREPRODUCT_H
