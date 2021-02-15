#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <cmath>
#include <ctime>
#include "Date.h"

#define MBW_ERROR "MBWay - Invalid phone number.\n"
#define MB_ERROR "MB - Invalid Reference.\n"
#define CC_ERROR "Credit Card - Invalid CC or CVV number.\n"

/**
 * @class Payment
 */
class Payment {
public:
  /**
   * @brief Payment Class Constructor
   */
  Payment();
  /**
   * @brief Default Destructor
   */
  virtual ~Payment();
  /**
   * @brief Prints the payment method information
   * @return String containing all the data relative to the payment method
   */
  virtual std::string printPayment() const = 0;
  /**
   * @brief Verifies whether the data from the payment method is valid or not
   * @return True if valid, false otherwise
   */
  virtual bool verifyPayment() const = 0;
  /**
   * @brief Function used to write a payment in a specific file
   * @return String with the info of the payment
   */
  virtual std::string writeToFile() const = 0;
  /**
   * @brief Writes the payment to out
   * @param out Ostream to be writen the payment
   * @param paymentPrinted Payment to be writen to out
   * @return Param out with the payment inside
   */
  friend std::ostream& operator<<(std::ostream& out, const Payment& paymentPrinted);
  /**
   * Class InvalidPayment
   */
  friend InvalidPayment;
};

/**
 * @class MBWay
 */
class MBWay: public Payment {
private:
    unsigned long int phoneNumber;
    static const unsigned int NUM_DIGITS_IN_PHONE_NUMBER = 9;
    static const unsigned int FIRST_DIGIT_FROM_PHONE_NUMBER = 9;
public:
    /**
     * @brief MBWay class Constructor
     * @param phoneNumber Client's phone number
     * @throw InvalidPayment If phoneNumber is invalid (i.e. its length being different of 9 digits)
     */
    explicit MBWay(unsigned long int phoneNumber);
    /**
     * @brief Default Destructor
     */
    virtual ~MBWay();
    /**
     * Get the value of phoneNumber
     * @return The value of phoneNumber
     */
    unsigned long int getPhoneNumber() const;
    /**
     * @brief Prints the payment method information
     * @return String containing all the data relative to the payment method
     */
    std::string printPayment() const override;
    /**
     * @brief Verifies whether the data from the payment method is valid or not
     * @return True if valid, false otherwise
     */
    bool verifyPayment() const override;
    /**
     * @brief Function used to write a payment in a specific file
     * @return String with the info of the payment
     */
    std::string writeToFile() const override;
};


class MultiBanco: public Payment {
private:
    unsigned long int reference;
    static const unsigned int NUM_DIGITS_IN_REFERENCE = 9;
public:
    /**
     * @brief Multibanco Class Constructor
     */
    MultiBanco();
    /**
     * @brief Multibanco Class Constructor
     * @param reference Reference of the payment
     * @throw InvalidPayment If reference is invalid (i.e. its length being different of 9 digits)
     */
    explicit MultiBanco(unsigned long int reference);
    /**
     * @brief Default Destructor
     */
    virtual ~MultiBanco();
    /**
     * @brief Generates the reference for payment
     * @return Unsigned long int reference for payment
     */
    unsigned long int generateReference();
    /**
     * Get the value of reference
     * @return The value of reference
     */
    unsigned long int getReference() const;
    /**
     * @brief Prints the payment method information
     * @return String containing all the data relative to the payment method
     */
    std::string printPayment() const override;
    /**
     * @brief Verifies whether the data from the payment method is valid or not
     * @return True if valid, false otherwise
     */
    bool verifyPayment() const override;
    /**
     * @brief Function used to write a payment in a specific file
     * @return String with the info of the payment
     */
    std::string writeToFile() const override;

};


class CreditCard: public Payment {
private:
    Date validity;
    long long cardNumber;
    unsigned short int CVV;
    static const unsigned int NUM_DIGITS_CARD_NUMBER = 16;
    static const unsigned int NUM_DIGITS_CVV = 3;
public:
    /**
     * @brief CreditCard Class Constructor
     * @param cardNumber 16 digit field with the value of the card number
     * @param CVV 3 digit field with the value of the CVV
     * @param validity Validity of the card
     * @throw InvalidPayment If cardNumber or CVV are invalid
     */
    CreditCard(long long cardNumber, unsigned short int CVV, const Date& validity);
    /**
     * @brief Default Destructor
     */
    virtual ~CreditCard();
    /**
     * @brief Get the value of cardNumber
     * @return The value of cardNumber
     */
    const Date& getCardValidity() const;
    /**
     * @return Unsigned long int containing the card number
     */
    long long getCardNumber() const;
    /**
     * @return Unsigned short int containing the CVV
     */
    unsigned short int getCVV() const;
    /**
     * @brief Prints the payment method information
     * @return String containing all the data relative to the payment method
     */
    std::string printPayment() const override;
    /**
     * @brief Verifies whether the data from the payment method is valid or not
     * @return True if valid, false otherwise
     */
    bool verifyPayment() const override;
    /**
     * @brief Function used to write a payment in a specific file
     * @return String with the info of the payment
     */
    std::string writeToFile() const override;
};

#endif // PAYMENT_H
