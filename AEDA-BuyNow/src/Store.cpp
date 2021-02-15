#include "Store.h"

// Store Class Implementation

Store::Store() = default;

Store::Store(const std::vector<StoreProduct *>& products)
{
    this->products = products;
}

Store::~Store() = default;

std::vector<StoreProduct*> Store::getProducts() const
{
    return products;
}

void Store::addProduct(StoreProduct * newProduct)
{
    int index = findProduct(newProduct);
    if(index == -1)
        products.push_back(newProduct);
    else
        throw ProductAlreadyExists(newProduct->getProduct()->getDescription());
}

void Store::removeProduct(StoreProduct * product)
{
    int index = findProduct(product);
    if(index == -1)
        throw ProductDoesNotExist(product->getProduct()->getDescription(),true);
    products.erase(products.begin() + index);
}

void Store::setProducts(const std::vector<StoreProduct *>& value)
{
    products = value;
}

int Store::findProduct(StoreProduct * sp) {
    if(products.size() <= 10){
        for (int i = 0; i < products.size(); i++)
            if (*(products[i]) == *sp)
                return i; //Found
        return -1; //Not found
    }
    else {
        sortProducts();
        int left = 0, right = (int) products.size() - 1;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (*products[middle] < *sp)
                left = middle + 1;
            else if (*sp < *products[middle])
                right = middle - 1;
            else
                return middle; //Found
        }
        return -1; //Not found
    }
}

void Store::sortProducts() {
    sort(products.begin(), products.end(), [](StoreProduct *sp1, StoreProduct * sp2){return *sp1 < *sp2;});
}

// PhysicalStore Class Implementation

PhysicalStore::PhysicalStore():Store()
{
    location = "";
}

PhysicalStore::PhysicalStore(const std::string& value) :Store()
{
    location = value;
}

PhysicalStore::PhysicalStore(const std::string& value, const std::vector<StoreProduct *>& p) :Store(p)
{
    location = value;
}

PhysicalStore::~PhysicalStore() = default;

std::string PhysicalStore::getLocation() const
{
    return location;
}

void PhysicalStore::setLocation(const std::string& value)
{
    location = value;
}

bool PhysicalStore::operator==(const PhysicalStore& pS) const
{
    return location == pS.getLocation();
}

bool PhysicalStore::operator<(const PhysicalStore& pS) const {
    return location < pS.location;
}

// OnlineStore Class Implementation

OnlineStore::OnlineStore() :Store()
{
    clients.clear();
}

OnlineStore::~OnlineStore() {
    for (auto &c : clients)
        delete c;

    // All the products are in the onlineStore, so they are deallocated here to avoid repeated deallocations
    for (auto &sP : products)
        delete sP;
}

void OnlineStore::addClient(Client * newClient)
{
    int index = findClient(newClient);
    if(index != -1)
        throw ClientAlreadyExists(index, newClient->getNIF());
    clients.push_back(newClient);
    sortClients();
}

void OnlineStore::removeClient(Client * removedClient)
{
    int index = findClient(removedClient);
    if(index == -1)
        throw ClientDoesNotExist();
    clients.erase(clients.begin() + index);
}

void OnlineStore::removeClient(int index)
{
    clients.erase(clients.begin() + index);
}

void OnlineStore::setClients(const std::vector<Client *>& value)
{
    clients = value;
}

std::vector<Client *> OnlineStore::getClients() const
{
    return clients;
}

void OnlineStore::showClients(int x)  {
    sortClients();
    std::vector<Client *> temp(clients.size());
    switch(x){
        case -1 :{
            //Copy to the vector temp all the non-registered clients
            auto it = std::copy_if(clients.begin(), clients.end(), temp.begin(), [](Client *c) {
                if (dynamic_cast<RegisteredClient *>(c) == nullptr) { return true; } else { return false; }
            });
            temp.resize(distance(temp.begin(), it));
            if(temp.empty())
                std::cout << "\tNo clients found" << std:: endl;
            for (Client *c: temp) {
                std::cout << '\t' << c->getName() << " - " << c->getNIF() << std::endl << std::endl;
            }
            break;
        }
        case 0 :{
            //Copy to the vector temp all the registered clients
            auto it = std::copy_if(clients.begin(), clients.end(), temp.begin(), [](Client *c) {
                if (dynamic_cast<RegisteredClient *>(c) == nullptr)
                    return false;
                else return true;
            });
            temp.resize(distance(temp.begin(), it));
            if(temp.empty())
                std::cout << "\tNo clients found" << std:: endl;
            for (Client *c: temp) {
                auto *rc = dynamic_cast<RegisteredClient *>(c);
                std::cout << rc->getID() << "\t| " << rc->getName() << " - " << c->getNIF() << " - " << rc->getEmail()
                          << std::endl;
                for (Payment *p: rc->getPaymentMethods())
                    std::cout << "\t\t" << *p << std::endl;
                std::cout << std::endl;
            }
            break;
        }
        case 1:
            std::cout << "Non-registered clients:" << std::endl;
            showClients(-1);
            std::cout << "Registered clients:" << std::endl;
            showClients(0);
            break;
        default:
            break;
    }
}

void OnlineStore::sortClients() {
    sort(clients.begin(), clients.end(), [](Client *c1, Client *c2){return *c1 < *c2;});
}

int OnlineStore::findClient(Client * cl){
    if(clients.size() <= 10){
        for (int i = 0; i < clients.size(); i++)
            if (*clients[i] == *cl)
                return i; //Found
        return -1; //Not found
    }
    //sortClients();
    int left = 0, right = int(clients.size()) - 1;
    while (left <= right){
        int middle = (left + right) / 2;
        if (*clients[middle] < *cl)
            left = middle + 1;
        else if (*cl < *clients[middle])
            right= middle - 1;
        else
            return middle; //Found
    }
    return -1; //Not found
}

int OnlineStore::findRegisteredClient(std::string eMail){
    auto temporary = new RegisteredClient("", 0, eMail);
    for (int i = 0; i < clients.size(); i++) {
        auto temp = dynamic_cast<RegisteredClient *>(clients[i]);
        if (temp != nullptr && temp->getEmail() == temporary->getEmail())
            return i; //Found
    }
    return -1; //Not found
}