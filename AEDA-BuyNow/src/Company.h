#ifndef COMPANY_H
#define COMPANY_H

#include <fstream>
#include "Transaction.h"
#include <map>
#include "Utils.h"
#include <unordered_set>
#include <stack>
#include <queue>
#include "Van.h"

struct MessageHash {

    int operator()(ClientMessage * msg) const {
        int v = 0;
        for(auto elem:msg->getMsg()){
            v += 37*elem;
        }
        for(auto elem: msg->getEMail()){
            v += 37*elem;
        }
        return v;
    }

    bool operator()(ClientMessage * msg1, ClientMessage * msg2) const {
        return *msg1 == *msg2;
    }
};

typedef unordered_set<ClientMessage *, MessageHash, MessageHash> HashTableMessage;

/**
  * @class Company
  */
class Company
{
private:
    std::string companyName;
    std::vector<PhysicalStore *> stores;
    std::vector<Transaction *> transactions;
    OnlineStore * oStore;
    std::vector<std::pair<Product *, unsigned int>> soldProducts;
    double cashEarned;
    unsigned int total_products = 0;
    //Project part 2
    HashTableMessage messagesToProcess;
    std::vector<BST<Supplier>> suppliers;
    std::vector<std::pair<Product *, unsigned int>> missingStock;
    std::priority_queue<Van> fleet;
public:
    /**
     * @brief Empty Constructor
     */
    Company();
    /**
     * @brief Load Company data from a file
     * @param file Where the data is
     * @throw InvalidFile If the file is incorrect
     * @throw PhysicalStoreAlreadyExists If the file defines the same store twice or more times
     * @throw InvalidPayment If there was an error associated to the payment method
     * @throw ProductAlreadyExists If the product already is in the vector of products
     * @throw ProductDoesNotExist If the product written in the file does not exist
     * @throw PhysicalStoreDoesNotExist If the physical store associated to a product does not exist
     * @throw InvalidDate If the date of the transaction is invalid
     * @throw ClientAlreadyExists If the same client is more than 1 times in the file
     */
    void initialize(const std::string& file);
    /**
     * @brief Load Suppliers data from a file
     * @param file Where the data is
     */
    void readSuppliers(const std::string& file);
    /**
     * @brief Loads fleet into the priority_queue
     * @param file containing fleet's data
     */
    void readFleet(const std::string& file);
    /**
     * @brief Class Destructor deallocates the memory owned
     */
    virtual ~Company();
    /**
     * @brief Set the company name
     * @param name Name of the company
     */
    void setCompanyName(const std::string& name);
    /**
     * @brief Get the company name
     * @return name Name of the company
     */
    std::string getCompanyName() const;
    /**
     * @brief Set the stores of the company
     * @param value Vector with the stores of the company
     */
    void setStores(const std::vector<PhysicalStore *>& value);
    /**
     * @brief Get the stores of the company
     * @return stores Vector with the stores of the company
     */
    std::vector<PhysicalStore *> getStores() const;
    /**
     * @brief Adds a PhysicalStore to the company if it does not exist
     * @param pS store Store to be added
     * @throw PhysicalStoreAlreadyExists If pS already exists
     */
    void addStore(PhysicalStore * pS);
    /**
     * @brief Removes a PhysicalStore from the company if it exists
     * @param pS Store to be removed
     * @throw PhysicalStoreDoesNotExist If pS does not belong to the company
     */
    void removeStore(PhysicalStore * pS);
    /**
     * @brief Set all the transactions of the company
     * @param tr Vector with the transactions of the company
     */
    void setTransactions(const std::vector<Transaction *>& tr);
    /**
     * @brief Get all the transactions of the company
     * @return All the Transactions of the company
     */
    std::vector<Transaction *> getTransactions() const;
    /**
     * @brief Get the Online Store of the company
     * @return Pointer to an Online Store
     */
    OnlineStore * getOnlineStore() const;
    /**
      * @brief Show the statistics of the company
      * @param tr Transactions that should be shown
      */
     void showStatistics(std::vector<Transaction *>& tr) const;
     /**
      * @brief Show all the statistics of the company
      */
     void showAllStatistics();
     /**
      * @brief Show the statistics of the company of a specific day
      * @param date Date to calculate the statistics
      */
     void showStatsByDay(const Date& date) const;
     /**
      * @brief Show the statistics of the company of a specific month
      * @param date Date to calculate the statistics (Only used the month and the year of the date)
      */
     void showStatsByMonth(const Date& date)const;
     /**
      * @brief Show the statistics of the company of a specific year
      * @param date Date to calculate the statistics (Only used the year of the date)
      */
     void showStatsByYear(const Date& date) const;
     /**
      * @brief Adds a transaction to the vector of transactions
      * @param t Transaction that should be added
      */
    void addTransaction(Transaction * t);
    /**
     * @brief Stock reposition in the online store from the physical stores
     * @param stockNeeded Vector of products and respective quantity to be restocked
     * @param date Date of the transaction
     */
    void repositionByStore(std::vector<std::pair<Product *, unsigned int>>& stockNeeded,const Date& date);
    /**
     * @brief Stock reposition in the online store from the supplier
     * @param stockNeeded Vector of products and respective quantity to be restocked
     * @param date Date of the transaction
     */
    void repositionBySupplier(std::vector<std::pair<Product *, unsigned int>>& stockNeeded,const Date& date);
    /**
     * @brief Store company data into a file
     * @param file File where the data should be stored
     * @throw InvalidFile if the given file is invalid
     */
    void writeFile(const std::string& file) const;
    /**
     * @brief Store suppliers data into a file
     * @param file File where the data should be stored
     */
    void writeSuppliers(const std::string& file) const;
    /**
     * @brief Stores fleet's data into a file
     * @param file File where data should be stored
     * @throw INvalidFile if the given file is invalid
     */
    void writeFleet(const std::string& file) const;
    /**
     * @brief Show in the screen the transactions of the company
     * @param tr Vector with the transactions that should be shown on the screen
     * @param client Tells if the transactions that should be shown are client transactions or not
     * @return True if tr wasn't empty, false otherwise
     */
    bool showTransactions(std::vector<Transaction *>& tr, bool client) const;
    /**
     * @brief Show in the screen all the transactions of the company
     * @param client Tells if the transactions that should be shown are client transactions or not
     * @return True if any transaction was shown, false otherwise
     */
    bool showAllTransactions(bool client);
    /**
     * @brief Show in the screen all the transactions of a specific day
     * @param d Day that should be shown in the screen
     * @param client Tells if the transactions that should be shown are client transactions or not
     * @return True if any transaction was shown, false otherwise
     */
    bool showTransactionsByDay(const Date& date, bool client) const;
    /**
     * @brief Show in the screen all the transactions of a specific month
     * @param d Month that should be shown in the screen
     * @param client Tells if the transactions that should be shown are client transactions or not
     * @return True if any transaction was shown, false otherwise
     */
    bool showTransactionsByMonth(const Date& date, bool client) const;
    /**
     * @brief Show in the screen all the transactions of a specific year
     * @param d Year that should be shown in the screen
     * @param client Tells if the transactions that should be shown are client transactions or not
     * @return True if any transaction was shown, false otherwise
     */
    bool showTransactionsByYear(const Date& date, bool client) const;
    /**
     * @brief Shows the information about the products in the OnlineStore
     * @param admin Bool to distinguish if it is to show to a client or to the admin
     */
    void showProductsStats(bool admin) const;
    /**
     * @brief Shows the PhysicalStores and their products information
     */
    void showStores() const;
    /**
     * @brief Sorts the PhysicalStores vector by location of each store
     */
    void sortStores();
    /**
     * @brief Show a detailed version of a specific transaction
     * @param id Id of the transaction
     * @param client True if it is a client transaction, false otherwise
     * @param all Variable used to specify if the transaction is a result of a search on all the transactions, by day, by month or by year
     * @param d Date date that should be used to search the product, if all = 0, date has a default value
     */
    void showTransactionsDetails(int id, int client, int all, const Date& d) const;

    /*############################# 2 Part #############################*/
    /**
     * @brief Get the number of messages to process
     * @return The number of messages to process
     */
    size_t getNumberMessages() const;
    /**
     * @brief Tell if the argument messagesToProcess is empty
     * @return True if it is empty, false otherwise
     */
    bool noMessages() const;
    /**
     * @brief Get the messages to process
     * @return The hash table with the messages to process
     */
    HashTableMessage getMessagesToProcess() const;
    /**
     * @brief Add a message to a client
     * @param client Client that sent the message
     * @param msg Message sent
     * @return True if the addiction was a success, false otherwise
     */
    bool addMessage(Client * client, ClientMessage * msg);
    /**
     * @brief Process a message
     * @param eMail Email of the client that sent the message
     * @param answer Answer of the admin
     * @return True if the operation was a success, false otherwise
     */
    bool processMessage(std::string eMail, AdminMessage * answer);
    /**
     * @brief Show all the messages to process on the screen
     */
    void showMessages() const;
    /**
     * @brief Read the messages of a client from a file
     * @param in Istream associated to a file
     * @param c Registered client who the messages are associated to
     */
    void readMessages(std::istream & in, RegisteredClient * c);
    /**
     * @brief Suppliers get function
     * @return All the available suppliers
     */
    const vector<BST<Supplier>> &getSuppliers() const;
    /**
     * @brief Insert a new supplier in the suppliers vector
     * @param supplier New supplier available
     */
    void insertSupplier(Supplier supplier);
    /**
     * @brief Remove a supplier from the suppliers vector
     * @param supplier To be removed
     */
    void removeSupplier(Supplier supplier);
    /**
     * @brief Search in the suppliers vector all the suppliers that can restock the product
     * @param productName Product to be restocked
     * @return index of the BST with the suppliers of the product, -1 if there are no suppliers for that product
     */
    unsigned int searchSuppliers(std::string productName) const;
    /**
     * @brief Stock reposition in the online store from the supplier
     * @param stockNeeded pair of the product and respective quantity to be restocked
     * @param date of the transaction
     * @param supplier that is restocking
     * @return true if fully restocked, false otherwise
     */
    bool repositionBySupplier(std::pair<Product *, unsigned int>& stockNeeded, const Date& date, Supplier supplier);
    /**
     * @brief Missing stock get function
     * @return online store missing stock
     */
    const std::vector<std::pair<Product *, unsigned int>> &getMissingStock() const;
    /**
     * @brief Missing stock set function
     * @param missingStock New mising stock value
     */
    void setMissingStock(const std::vector<std::pair<Product *, unsigned int>> &missingStock);
    /**
     * @brief Remove a missingProduct from the missingStock vector
     * @param index in the missingStock vector
     */
    void removeMissingProduct(int index);
    /**
     * @brief Sets the quanity of a missingProduct from the missingStock vector
     * @param index in the missingStock vector
     * @param quantity to be set
     */
    void setMissingProductQuantity(int index, int quantity);
    /**
     * @brief Adds a transaction to the queue of dispatch
     * @param transaction to be added to the waiting queue
     */
    bool addOrderToDispatch(Transaction* transaction);
    /**
     * @brief Puts the Van with the least capacity available to deliver its orders
     */
    void vanInTransit();
    /**
     * @brief Gives all the info related to the company's fleet
     * @return String with all the info from each vehicle
     */
    std::string showFleet() const;
};

/**
 * @class FindTransaction
 */
class FindTransaction {
public:
    bool _client = true;
    int _id = -1;
    /**
     * @brief Class constructor
     */
    FindTransaction(){ _id = -1;};
    /**
     * @brief Class constructor
     * @param client True if it should be searched a client transaction, false otherwise
     */
    explicit FindTransaction(bool client){_client = client;}
    /**
     * @brief Class constructor
     * @param id Id of the transaction
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransaction(int id, bool client){_id = id; _client = client;}
    /**
     * @brief Comparator used when the searching is by Date
     * @param t Transaction used
     * @return True if they are at the same date, false otherwise
     */
    virtual bool operator()(Transaction * t) const{
        if(_client && dynamic_cast<ClientTransaction *>(t) == nullptr || !_client && dynamic_cast<ReStock *>(t) == nullptr)
            return false;
        if(_id != -1)
            return _id == t->getTransactionID();
        return false;
    }
};

/**
 * @class FindTransactionByDay
 */
class FindTransactionByDay :public FindTransaction{
    Date date;
public:
    /**
     * @brief Class constructor
     * @param id Id of the transaction
     * @param d Date to be compared with
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransactionByDay(unsigned int id, const Date& d, bool client):FindTransaction((int)id, client){date = d;}
    /**
     * @brief Class constructor
     * @param d Date to be compared with
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransactionByDay(const Date& d, bool client):FindTransaction(client){date = d;}
    /**
     * @brief Comparator used when the searching is by day
     * @param t Transaction used
     * @return True if they are at the same date, false otherwise
     */
    bool operator()(Transaction * t) const override {
        if(_client && dynamic_cast<ClientTransaction *>(t) == nullptr || !_client && dynamic_cast<ReStock *>(t) == nullptr)
            return false;
        if(_id != -1)
            return _id == t->getTransactionID();
        return (t->getDate() == date);
    }
};

/**
 * @class FindTransactionByMonth
 */
class FindTransactionByMonth: public FindTransaction {
public:
    Date date;
    /**
     * @brief Class constructor
     * @param id Id of the transaction
     * @param d Date to be compared with
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransactionByMonth(int id, const Date& d, bool client):FindTransaction(id, client){date = d;}
    /**
     * @brief Class constructor
     * @param d Date to be compared with
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransactionByMonth(const Date& d, bool client):FindTransaction(client) {date = d;}
    /**
     * @brief Comparator used when the searching is by month
     * @param t Transaction used
     * @return True if they are at the same month and year, false otherwise
     */
    bool operator()(Transaction * t) const override {
        if(_client && dynamic_cast<ClientTransaction *>(t) == nullptr || !_client && dynamic_cast<ReStock *>(t) == nullptr)
            return false;
        if(_id != -1)
            return _id == t->getTransactionID();
        return (t->getDate().getMonth() == date.getMonth() && t->getDate().getYear() == date.getYear());
    }
};

/**
 * @class FindTransactionByYear
 */
class FindTransactionByYear: public FindTransaction{
public:
    Date date;
    /**
     * @brief Class constructor
     * @param id Id of the transaction
     * @param d Date to be compared with
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransactionByYear(int id, const Date& d, bool client):FindTransaction(id, client){date = d;}
    /**
     * @brief Class constructor
     * @param d Date to be compared with
     * @param client True if it should be searched a client transaction, false otherwise
     */
    FindTransactionByYear(const Date& d, bool client):FindTransaction(client){date = d;}
    /**
     * @brief Comparator used when the searching is by year
     * @param t Transaction used
     * @return True if they are at the same year, false otherwise
     */
    bool operator()(Transaction * t) const override {
        if(_client && dynamic_cast<ClientTransaction *>(t) == nullptr || !_client && dynamic_cast<ReStock *>(t) == nullptr)
            return false;
        if(_id != -1)
            return _id == t->getTransactionID();
        return (t->getDate().getYear() == date.getYear());
    }
};

#endif // COMPANY_H
