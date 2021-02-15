#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
private:
    std::string description;
    double price;
public:
  /**
   * @brief Product Class Constructor
   * @param description Product description
   * @param price Product price
   */
  Product(const std::string& description, double price);
  /**
   * @brief Product Class Constructor
   * @param description Product description
   */
  explicit Product(const std::string& description);
  /**
   * @brief Default Destructor
   */
  virtual ~Product();
  /**
   * @brief Set the value of description
   * @param value The new value of description
   */
  void setDescription(const std::string& value);
  /**
   * @brief Get the value of description
   * @return The value of description
   */
  std::string getDescription() const;
  /**
   * @brief Set the value of price
   * @param value The new value of price
   */
  void setPrice(double value);
  /**
   * @brief Get the value of price
   * @return The value of price
   */
  double getPrice() const;
  /**
   * @brief Product Comparison by description
   * @param  productCompared Product to be compared
   * @return Boolean value indicating the equality of the products
   */
  bool operator==(const Product& productCompared) const;
};


#endif // PRODUCT_H
