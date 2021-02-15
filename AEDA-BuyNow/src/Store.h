#ifndef STORE_H
#define STORE_H

#include "StoreProduct.h"
#include "Client.h"
#include <algorithm>


/**
  * @class Store
  */
class Store
{
protected:
    std::vector<StoreProduct *> products;
public:
  /**
   * @brief Empty Constructor
   */
  Store();
  /**
   * @brief Class constructor
   * @param products Vector with the products of the store
   */
  explicit Store(const std::vector<StoreProduct *>& products);
  /**
   * @brief Default Destructor
   */
  virtual ~Store();
  /**
   * @brief Get the products of the store
   * @return A vector with the products of the store
   */
  std::vector<StoreProduct*> getProducts() const;
  /**
   * @brief Add a new product to the store
   * @param newProduct Product that should be added
   * @throw ProductAlreadyExists if the newProduct already belongs to the store
   */
  void addProduct(StoreProduct * newProduct);
  /**
   * @brief Remove a product of the store
   * @param product Product that should be removed
   * @throw ProductDoesNotExist if the product does not belong to the store
   */
  void removeProduct( StoreProduct * product);
  /**
   * @brief Set the value of products
   * @param value The new value of products
   */
  void setProducts(const std::vector<StoreProduct *>& value);
  /**
   * @brief Search a certain product in the store
   * @param sp Product to be searched
   * @return The position of the value in the vector if exists, -1 otherwise
   */
  int findProduct(StoreProduct * sp);
  /**
   * @brief Sort the vector of Store Products according to their product
   */
  void sortProducts();
};

/**
  * @class PhysicalStore
  */
class PhysicalStore : public Store{
private:
    std::string location;
public:
    /**
     * @brief Class Constructor
     */
    PhysicalStore();
    /**
     * @brief Class constructor
     * @param value Location of the store
     */
    explicit PhysicalStore(const std::string& value);
    /**
     * @brief Class constructor
     * @param value Location of the store
     * @param p Vector of products
     */
    PhysicalStore(const std::string& value, const std::vector<StoreProduct *>& p);
    /**
     * @brief Default Destructor
     */
    ~PhysicalStore() override;
    /**
     * @brief Get location of the store
     * @return The location of the store
     */
    std::string getLocation() const;
    /**
     * @brief Set the location of the store
     * @param value The new value of location
     */
    void setLocation(const std::string& value);
    /**
     * @brief Operator used to compare the physical stores
     * @param pS Physical store that it should be compared with
     * @return True if they are the same store, false otherwise
     */
    bool operator==(const PhysicalStore& pS) const;
    /**
     * @brief Lower operator used to compare the physical stores by location
     * @param pS Physical store that it should be compared with
     * @return True if this is lower than pS, false otherwise
     */
    bool operator<(const PhysicalStore& pS) const;
};

/**
  * @class OnlineStore
  */
class OnlineStore :public Store
{
private:
    std::vector<Client *> clients;
public:
    /**
     * @brief Empty Constructor
     */
    OnlineStore();
    /**
     * @brief OnlineStore Destructor deallocates the memory owned
     */
    ~OnlineStore() override;
    /**
     * @brief Adds a new client to the store
     * @param newClient Client that should be added
     * @throw ClientAlreadyExists If the client is already in the vector
     */
    void addClient(Client * newClient);
    /**
     * @brief Remove a client from the store
     * @param removedClient Client that should be removed
     * @throw ClientDoesNotExist If removedClient does not belong to the store
     */
    void removeClient(Client * removedClient);
    /**
     * @brief Remove a client from the store by index
     * @param index Index of the client in the vector clients
     */
    void removeClient(int index);
    /**
     * @brief Set the vector of clients
     * @param value The new vector of clients
     */
    void setClients(const std::vector<Client *>& value);
    /**
     * @brief Get the set of clients
     * @return The vector of clients
     */
    std::vector<Client *> getClients() const;
    /**
     * @brief Function to show either the Clients or the RegisteredClients or both
     * @param x Parameter to decide which clients are to be shown
     */
    void showClients(int x) ;
    /**
     * @brief Function that uses the lower operator to sort the clients
     */
    void sortClients();
    /**
     * @brief Function that uses either sequential or binary search to find a client
     * @param cl Client to be searched
     * @return Index of the client in the vector clients, -1 if not found
     */
    int findClient(Client * cl);

    /*############################# 2 Part #############################*/
    /**
     * @brief Function that uses sequential search to find a registered client by email
     * @param eMail Email of the registered client
     * @return The index of the client int the vector of clients
     */
    int findRegisteredClient(std::string eMail);
};

/**
 * @class FindPhysicalStore
 */
class FindPhysicalStore{
    PhysicalStore * pS;
public:
    /**
     * @brief Class Constructor
     * @param ps Store to be searched
     */
    explicit FindPhysicalStore(PhysicalStore * ps) {pS = ps;}
    /**
     * @brief Operator used to search for a product
     * @param ps Product to be searched
     * @return True if ps is equal to pS
     */
    bool operator()(PhysicalStore * ps) const{ return *pS == *ps;}
};

#endif // STORE_H
