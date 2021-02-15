#include <iostream>
/**
 * @class PaymentMethodAlreadyExists Exception
 */
class PaymentMethodAlreadyExists: public std::exception {
    std::string error;
public:
    /**
     * @brief PaymentMethodAlreadyExists Exception Constructor
     */
    explicit PaymentMethodAlreadyExists();
    /**
     * @brief Prints the reason that throws the exception
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const PaymentMethodAlreadyExists& error);
};

/**
 * @class ClientDoesNotExist Exception
 */
class ClientDoesNotExist: public std::exception{
private:
    std::string error;
public:
    /**
     * @brief ClientDoesNotExist Exception Constructor
     * */
    ClientDoesNotExist();
    /**
     * @brief Prints the reason that throws the exception
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const ClientDoesNotExist& error);
};

/**
 * @class InvalidFile Exception
 */
class InvalidFile: public std::exception{
private:
    std::string msg;
public:
    /**
     * @brief Prints the reason of the exception
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief InvalidFile Exception Constructor
     * @param s Name of the file that does not exist
     */
    explicit InvalidFile(const std::string& s);
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const InvalidFile& error);
};

/**
 * @class InvalidDate Exception
 */
class InvalidDate: public std::exception{
private:
    std::string invalidDate;
public:
    /**
     * @brief InvalidDate Exception Constructor
     * @param month True whether month value is invalid or not
     * @param day True whether day value is invalid or not
     * @param date Object that thrown the exception
     */
    explicit InvalidDate(const std::string& error);
    /**
     * @brief Prints the date that thrown this exception and explains its reason
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const InvalidDate& error);
};

/**
 * @class InvalidPayment Exception
 */
class InvalidPayment: public std::exception{
private:
    std::string invalidPayment;
public:
    InvalidPayment();
    /**
     * @brief InvalidPayment Exception constructor
     * @param string String containing error information
     */
    explicit InvalidPayment(const std::string& error);
    /**
     * @brief Prints the the reason why a Payment object thrown this exception
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const InvalidPayment& error);
};

/**
 * @class ProductDoesNotExist Exception
 */
class ProductDoesNotExist: public std::exception{
private:
    std::string invalidProduct;
public:
    /**
     * @brief ProductDoesNotExist Exception Constructor
     * @param store Value to indicate if the product does not exist in the store or in the transaction cart
     */
    ProductDoesNotExist(const std::string& description,bool store);
    /**
     * @brief Prints the description of the product that thrown this exception and explains its reason
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const ProductDoesNotExist& error);
};

/**
 * @class ProductAlreadyExists Exception
 */
class ProductAlreadyExists: public std::exception{
private:
    std::string invalidProduct;
public:
    /**
     * @brief ProductAlreadyExist Exception Constructor
     * @param product Object that thrown the exception
     */
    explicit ProductAlreadyExists(const std::string& description);
    /**
     * @brief Prints the description of the product that thrown this exception and explains its reason
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const ProductAlreadyExists& error);
};

/**
 * @class PhysicalStoreAlreadyExists Exception
 */
class PhysicalStoreAlreadyExists: public std::exception{
private:
    std::string error;
public:
    /**
     * @brief PhysicalStoreAlreadyExists Exception Constructor
     * @param location Location of the store that already exists
     */
    explicit PhysicalStoreAlreadyExists(const std::string& location);
    /**
     * @brief Prints the reason that throws the exception
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const PhysicalStoreAlreadyExists& error);
};

/**
 * @class PhysicalStoreDoesNotExist Exception
 */
class PhysicalStoreDoesNotExist: public std::exception{
private:
    std::string error;
public:
    /**
     * @brief PhysicalStoreDoesNotExist Exception Constructor
     */
    explicit PhysicalStoreDoesNotExist();
    /**
     * @brief PhysicalStoreDoesNotExist Exception Constructor
     * @param loc Location of the store that does not exist
     */
    explicit PhysicalStoreDoesNotExist(const std::string& loc);
    /**
     * @brief Prints the reason of the exception
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const PhysicalStoreDoesNotExist& error);
};

/**
 * @class NotEnoughStock Exception
 */
class NotEnoughStock: public std::exception{
private:
    std::string invalidStock;
public:
    /**
     * @brief NotEnoughStock Exception Constructor
     */
    explicit NotEnoughStock(const std::string& description);
    /**
     * @brief Prints the Product description that thrown this exception and explains its reason
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const NotEnoughStock& error);
};

/**
 * @class ClientAlreadyExists
 */
class ClientAlreadyExists: public std::exception{
private:
    int index;
    unsigned int nif;
public:
    /**
     * @brief ClientAlreadyExists Exception Constructor
     * @param ind Index of the client in the vector of clients where it exists
     * @param nif Nif of the client that thrown this exception
     */
    ClientAlreadyExists(int ind, unsigned int n);
    /**
     * @brief Get the position of the client in the vector of clients
     * @return The position in the vector
     */
    int getIndex() const;
    /**
     * @brief Prints the nif of the client that thrown this exception and explains its reason
     * @return String with exception's information
     */
    std::string printError() const;
    /**
     * @brief Writes the exception to out
     * @param out Ostream to be writen the exception
     * @param error Exception thrown
     * @return Param out with the error inside
     */
    friend std::ostream& operator<<(std::ostream& out, const ClientAlreadyExists& error);
};




/**
 * @Class VanLoadException
 */
class VanLoadException : public std::exception {
protected:
    std::string invalidLoad;

public:
    /**
     * @brief VanLoadException Constructor
     */
    VanLoadException();

    /**
     * @brief returns the corresponding error message
     * @return string with the correspondent error message
     */
    virtual std::string printError() const = 0;

    friend std::ostream& operator<<(std::exception& out, const VanLoadException& error);
};

/**
 * @class VanAlreadyFull
 */
class VanAlreadyFull : public VanLoadException {
public:
    /**
     * @brief VanAlreadyFull Constructor
     */
    VanAlreadyFull();
    /**
     * @brief returns the corresponding error message
     * @return string with the correspondent error message
     */
    virtual std::string printError() const;
};

class VanAlreadyEmpty : public VanLoadException {
public:
    /**
     * @brief VanAlreadyEmpty Constructor
     */
    VanAlreadyEmpty();
    /**
     * @brief returns the corresponding error message
     * @return string with the correspondent error message
     */
    virtual std::string printError() const;
};

class VanNotReady : public VanLoadException {
private:
    unsigned int loadRatio;

public:
    /**
     * @brief VanNotReady Constructor
     */
    VanNotReady(const unsigned int loadRatio);
    /**
     * @brief returns the corresponding error message
     * @return string with the correspondent error message
     */
    virtual std::string printError() const;
};