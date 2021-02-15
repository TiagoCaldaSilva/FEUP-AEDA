#include "Transaction.h"

// Transaction Class Implementation

unsigned int Transaction::ID = 1;
unsigned const short int Transaction::FP_PRECISION = 2;

Transaction::Transaction(const Date& date, std::vector<std::pair<Product *, unsigned int>>& cart, OnlineStore * oStore, bool reStock) : date(date), cart(cart), oStore(oStore)
{
    transactionID = ID; ID++;
    value = 0.0;
    orderCapacity = 0;
    if (!reStock)
        for (const std::pair<Product *, unsigned int> &nextProduct : cart)
            value += nextProduct.first->getPrice() * nextProduct.second;
}

Transaction::~Transaction() = default;

void Transaction::setDate(const Date& newDate) { date = newDate; }

const Date& Transaction::getDate() const { return date; }

void Transaction::setCart(std::vector<std::pair<Product *, unsigned int>>& newCart) { cart = newCart; }

std::vector<std::pair<Product *, unsigned int>> Transaction::getCart() const { return cart; }

double Transaction::getValue() const { return value; }

unsigned int Transaction::getTransactionID() const { return transactionID; }

unsigned int Transaction::getOrderCapacity() {
	orderCapacity = 0;
	for (std::pair<Product*, unsigned int> prdt : cart)
		orderCapacity += prdt.second;
	return orderCapacity;
}

std::string Transaction::printTransaction() const
{
    std::stringstream ss;
    ss << "Transaction ID: " << std::to_string(transactionID) << "\n\n";
    for (const std::pair<Product*, unsigned int>& nextProduct : cart)
    {
        double orderPrice = nextProduct.first->getPrice() * nextProduct.second;
        ss << nextProduct.first->getDescription() << "  x" << std::to_string(nextProduct.second) << "  - " << std::fixed << std::setprecision(FP_PRECISION) << orderPrice << '\n';
    }
    ss << "Total: " << std::fixed << std::setprecision(2) << value;
    return ss.str();
}

bool Transaction::addProduct(Product * product, unsigned int quantity)
{
    FindProduct_pair x(std::make_pair(product, quantity));
    auto it = std::find_if(cart.begin(), cart.end(), x);
    if (it != cart.end()) return false;

    cart.emplace_back(product, quantity);
    value += product->getPrice() * quantity;
    return true;
}

void Transaction::removeProduct(const Product& product)
{
    // Sequential Search
    for (auto cartItr = cart.begin(); cartItr != cart.end(); cartItr++)
    {
        if ((*(*cartItr).first) == product)
        {
            value -= (*cartItr).first->getPrice() * (*cartItr).second;
            cart.erase(cartItr); break;
        }
    }
}

void Transaction::changeQuantity(Product * product, unsigned int newQuantity)
{
    FindProduct_pair x(std::make_pair(product, 0));
    auto it = std::find_if(cart.begin(), cart.end(), x);
    if (it == cart.end()) throw ProductDoesNotExist(product->getDescription(),false);

    value -= product->getPrice() * it->second;   //Remove the old quantity from value
    value += product->getPrice() * newQuantity;   //Add the new quantity to value
    if (!newQuantity) removeProduct(*product);
    else it->second = newQuantity;
}

// Comparator Functions
bool ByName(std::pair<Product *, unsigned int>& lhsObj, std::pair<Product *, unsigned int>& rhsObj)
{
    return (lhsObj.first->getDescription() < rhsObj.first->getDescription());
}

bool ByValue(std::pair<Product *, unsigned int>& lhsObj, std::pair<Product *, unsigned int>& rhsObj)
{
    if (lhsObj.first->getPrice() * lhsObj.second > rhsObj.first->getPrice() * rhsObj.second) return true;
    else if (lhsObj.first->getPrice() * lhsObj.second == rhsObj.first->getPrice() * rhsObj.second) {
        if (ByName(lhsObj, rhsObj)) return true;
    }
    return false;
}

void Transaction::sortCart(bool (*comparator)(std::pair<Product*, unsigned int>, std::pair<Product*, unsigned int>))
{
    // IntroSort Algorithm from STL
    sort(cart.begin(), cart.end(), comparator);
}

bool Transaction::operator<(const Transaction& rhsTransaction) const { return (value < rhsTransaction.value); }


// ClientTransaction Class Implementation

ClientTransaction::ClientTransaction(const Date& date, std::vector<std::pair<Product *, unsigned int>>& cart, OnlineStore * oStore, unsigned int cNIF) : Transaction(date, cart, oStore) , nif(cNIF) {
	deliveryAtHome = false;
}

ClientTransaction::~ClientTransaction() = default;

Payment * ClientTransaction::getPaymentMethod() const { return paymentMethod; }

void ClientTransaction::setPaymentMethod(Payment * payMethod) { paymentMethod = payMethod; }

void ClientTransaction::setHomeDelivery() { deliveryAtHome = true; }

unsigned int ClientTransaction::getNif() const { return nif; }

void ClientTransaction::checkStock(int index, const unsigned int quantity, bool changeQt)
{
    auto product = oStore->getProducts()[index]->getProduct();
    StoreProduct* prdt = oStore->getProducts()[index];
    if (quantity > prdt->getCurrentStock()) throw NotEnoughStock(product->getDescription());
    else if (prdt->getCurrentStock() - quantity < prdt->getStockLimit())
    {
        // When reStock is called the quantity of the new product will be:
        // newStock = (StockLimit - CurrentStock + quantity) + 2 * StockLimit
        if (changeQt)
        {
            for (std::pair<Product *, unsigned int> &prdtToChangeQuantity : stockNeeded)
                if (prdtToChangeQuantity.first == product)
                {
                    prdtToChangeQuantity.second = (prdt->getStockLimit() - prdt->getCurrentStock() + quantity) + 2 * prdt->getStockLimit();
                    break;
                }
        }
        else stockNeeded.emplace_back(prdt->getProduct(), (prdt->getStockLimit() - prdt->getCurrentStock() + quantity) + 2 * prdt->getStockLimit());
    }
}

bool ClientTransaction::addProduct(Product * product, unsigned int quantity)
{
    // Checking Stock
    try {
        auto sP = new StoreProduct(new Product(product->getDescription(), 0));
        int index = oStore->findProduct(sP);
        delete sP; // Deallocates the product previously allocated
        if (index == -1) throw ProductDoesNotExist(product->getDescription(), true);
        checkStock(index, quantity);
        return Transaction::addProduct(oStore->getProducts()[index]->getProduct(), quantity);
    }
    catch (NotEnoughStock& stockError) { throw; }
    catch (ProductDoesNotExist& prdtError) { throw; }
}

void ClientTransaction::removeProduct(const Product& product)
{
    Transaction::removeProduct(product);
    for (auto stockItr = stockNeeded.begin(); stockItr != stockNeeded.end(); ++stockItr)
    {
        if (*(stockItr->first) == product) { stockNeeded.erase(stockItr); break; }
    }
}

void ClientTransaction::changeQuantity(Product * product, unsigned int newQuantity)
{
    int index;
    // Checking Stock
    try {
        auto sP = new StoreProduct(new Product(product->getDescription(), 0));
        index = oStore->findProduct(sP);
        delete sP; // Deallocates the product previously allocated
        if (index == -1) throw ProductDoesNotExist(product->getDescription(), true);
        checkStock(index, newQuantity, true);
    }
    catch (NotEnoughStock& stockError) { throw; }
    catch (ProductDoesNotExist& prdtError) { throw; }

    try { Transaction::changeQuantity(oStore->getProducts()[index]->getProduct(), newQuantity); }
    catch (ProductDoesNotExist& prdtError) { throw; }
}

bool ClientTransaction::stockNeededEmpty() const { return stockNeeded.empty(); }
std::vector<std::pair<Product *, unsigned int>>& ClientTransaction::getStockNeeded() { return stockNeeded; }

std::string ClientTransaction::printTransaction() const
{
    return "Client's NIF: " + std::to_string(nif) + '\n' + Transaction::printTransaction();
}

// Restock Class Implementation

ReStock::ReStock(const Date& date, std::vector<std::pair<Product *, unsigned int>>& sN, OnlineStore * oStore, bool bySupplier) : Transaction(date, sN, oStore, true), bySupplier(bySupplier) {}

void ReStock::setBySupplier(bool value) { bySupplier = value; }

bool ReStock::getBySupplier() const { return bySupplier; }

std::string ReStock::printTransaction() const {
    std::stringstream ss;
    ss << "Transaction ID: " << std::to_string(transactionID) << "\n";
    if (getBySupplier()) ss<<"From: Supplier" << "\n\n";
    else ss<<"From: Store" << "\n\n";
    for (const std::pair<Product*, unsigned int>& nextProduct : cart)
        ss << nextProduct.first->getDescription() << "  x" << std::to_string(nextProduct.second);
    return ss.str();
}

const Supplier &ReStock::getSupplier() const {
    return supplier;
}

void ReStock::setSupplier(const Supplier &supplier) {
    ReStock::supplier = supplier;
}
