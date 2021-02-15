#include "Company.h"
#define DEFAULT_DAY 1
#define DAY_MONTH_SIZE 2
#define CLIENTS "CLIENTS:"
#define PRODUCTS "PRODUCTS:"
#define TRANSACTIONS "TRANSACTIONS:"
#define CHANGE_TOPIC "###"
#define MBWAY "MW"
#define CREDIT_CARD "CC"
#define COMMA ','
#define HYPHEN '-'

// Company Class Implementation

Company::Company()
{
  stores.clear();
  transactions.clear();
  soldProducts.clear();
  companyName = "";
  oStore = new OnlineStore();
  cashEarned = 0;
  total_products = 0;
}

void Company::initialize(const std::string& file)
{
    std::ifstream in(file);
    std::string text, type, number, text_sb;
    std::vector<std::pair<Product*, unsigned int>> cart;
    bool client, bySup;
    int nif;
    Payment *pay;


    if(!in)
    {
        throw InvalidFile(file);
    }

    getline(in, text, '\n');

    companyName = text;

    getline(in, text, '\n');    //Location of the first store

    while(text !=  CLIENTS)
    {
        auto * pS = new PhysicalStore;
        pS->setLocation(text);
        try {
            addStore(pS);
        }
        catch(PhysicalStoreAlreadyExists &error){
            throw;
        }
        getline(in, text, '\n');
    }

    getline(in, text, '\n'); //Name of the first client
    while(text != PRODUCTS)
    {
        auto c = new Client;
        c->setName(text);

        getline(in, text, '\n');
        c->setNIF(stoi(text));

        getline(in, text, '\n');

        if(text != CHANGE_TOPIC)    //If text == "###" the client is not registered
        {
            auto rC = new RegisteredClient(c->getName(), c->getNIF(), text);
            delete c;

            getline(in, text, '\n');
            while((text != CHANGE_TOPIC) && (text != "CHAT:")){  //Reads client payment information
                std::stringstream s(text);
                s >> text_sb;   //Type of the payment method
                if (text_sb == MBWAY) {
                    s >> text_sb;
                    auto p = new MBWay(stoi(text_sb));
                    rC->addPaymentMethod(p);
                } else if (text_sb == CREDIT_CARD) {
                    std::string month, year, cN, cvv;
                    s >> text_sb;
                    month = text_sb.substr(0, DAY_MONTH_SIZE);
                    year = text_sb.substr(DAY_MONTH_SIZE + 1); //Substring from the position 2 forward
                    s >> cN >> cvv;
                    auto p = new CreditCard(stoll(cN), stoi(cvv), Date(DEFAULT_DAY, stoi(month), stoi(year)));
                    rC->addPaymentMethod(p);
                } else {

                    throw InvalidPayment();
                }
                getline(in, text, '\n');
            }
            if(text == "CHAT:") readMessages(in, rC);
            try {
                oStore->addClient(rC);
            }
            catch(ClientAlreadyExists &error){
                throw;
            }
        }
        else {
            try {
                oStore->addClient(c);   //If the client isn't registered
            }
            catch(ClientAlreadyExists &error){
                throw;
            }
        }
        getline(in, text, '\n');
    }

    getline(in, text, '\n'); //Description of the first product of the file
    while(text != TRANSACTIONS)
    {
        std::string description = text.substr(0, text.find(COMMA));
        double price = stod(text.substr(text.find(COMMA) + 1));
        auto p = new Product(description, price);
        getline(in, text, '\n');
        while(text != CHANGE_TOPIC) //After the product is the location of the stores that are selling it
        {
            size_t pos1 = text.find(HYPHEN);
            size_t pos2 = text.find(COMMA);
            std::string loc = text.substr(0, pos1);
            std::string cS = text.substr(pos1 + 1, pos2 - 1);
            std::string sL = text.substr(pos2 + 1);
            auto sP = new StoreProduct(p, stoi(cS), stoi(sL));
            try {
                if (loc == "Online") {
                    oStore->addProduct(sP);
                } else {
                    auto ps = new PhysicalStore(loc);
                    FindPhysicalStore x(ps);
                    auto it = find_if(stores.begin(), stores.end(), x);
                    if(it != stores.end())
                        (*it)->addProduct(sP);
                    else
                        throw PhysicalStoreDoesNotExist(loc);
                }
                if(oStore->findProduct(sP) == -1)
                    throw ProductDoesNotExist(p->getDescription(), true);
            }
            catch(ProductAlreadyExists &error){
                throw;
            }
            catch(ProductDoesNotExist &error){
                throw;
            }
            catch(PhysicalStoreDoesNotExist &error){
                throw;
            }
            getline(in, text, '\n');
        }
        getline(in, text, '\n');
    }

    while(getline(in, text, '\n')){ //This loop ends when the file is in the end
        client = false;
        cart.clear();
        if(text.size() == 9){       //If the text.size() == 9, we are dealing with a client transaction
            client = true;
            nif = stoi(text);
        }
        else if(text == "True"){    //Otherwise the transaction is a ReStock(True if the restock is from a supplier
            bySup = true;
        }
        else if(text == "False"){   //False if the restock is from a PhysicalStore
            bySup = false;
        }
        else
            throw InvalidFile("Invalid transaction in file: " + file);
        getline(in, text, '\n');
        Date d(text);
        try {
            Supplier supplier_var;
            if(client) {    //If we are dealing with a client transaction, it is necessary to save the payment method
                getline(in, text, '\n');
                std::stringstream s(text);
                s >> type;
                if (type == MBWAY) {
                    s >> number;
                    pay = new MBWay(stoi(number));
                } else if (type == CREDIT_CARD) {
                    std::string date, cvv;
                    s >> date;
                    date = "01/" + date;    //Credit cards only have month and year in the validity
                    Date temp(date);
                    s >> number >> cvv;
                    pay = new CreditCard(stoll(number), stoi(cvv), temp);
                } else if (type == "MB") {
                    s >> number;
                    pay = new MultiBanco(stoi(number));
                } else {
                    throw InvalidPayment();
                }
            }else if(bySup){
                getline(in, text, '\n');
                std::stringstream s(text);
                std::string name;
                double price;
                s >> name;
                s >> price;
                supplier_var.setName(name);
                supplier_var.setPrice(price);
            }
            getline(in, text, '\n');
            while (text != CHANGE_TOPIC) {
                size_t pos1 = text.find(COMMA);
                size_t pos2 = text.find(COMMA, pos1 + 1);
                std::string product_name = text.substr(0, pos1);
                std::string price = text.substr(pos1 + 1, pos2);
                std::string qt = text.substr(pos2 + 1);
                auto p = new Product(product_name, stod(price));
                cart.emplace_back(p, stoi(qt));
                getline(in, text, '\n');
                if(client) {
                    soldProducts.emplace_back(p, stoi(qt));
                    total_products += stoi(qt);
                }
            }
            if (client) {
                auto cT = new ClientTransaction(d, cart, oStore, nif);
                cT->setPaymentMethod(pay);
                transactions.push_back(cT);
                cashEarned += cT->getValue();
            } else{
                auto reStock=new ReStock(d, cart, oStore, bySup);
                reStock->setSupplier(supplier_var);
                transactions.push_back(reStock);
            }

        }
        catch(InvalidDate &error) {
            throw;
        }
        catch(InvalidPayment &error){
            throw;
        }
    }
    in.close();
    readSuppliers("SUPPLIERS.txt");
    readFleet("FLEET.txt");
}

Company::~Company() {
    for (auto &t : transactions)
        delete t;
    delete oStore;
    for (auto &s : stores)
        delete s;
}

void Company::setCompanyName(const std::string& name)
{
    companyName = name;
}

std::string Company::getCompanyName() const
{
    return companyName;
}

void Company::setStores(const std::vector<PhysicalStore *>& value)
{
    stores = value;
}

void Company::addStore(PhysicalStore * pS) {
    FindPhysicalStore x(pS);
    auto it = find_if(stores.begin(), stores.end(), x);
    if(it == stores.end())
        stores.push_back(pS);
    else
        throw PhysicalStoreAlreadyExists(pS->getLocation());
    sortStores();
}

void Company::removeStore(PhysicalStore * pS){
    FindPhysicalStore x(pS);
    auto it = find_if(stores.begin(), stores.end(), x);
    if(it != stores.end())
        stores.erase(it);
    else
        throw PhysicalStoreDoesNotExist();
}

std::vector<PhysicalStore *> Company::getStores() const
{
    return stores;
}

void Company::setTransactions(const std::vector<Transaction *>& tr)
{
    transactions = tr;
}

std::vector<Transaction *> Company::getTransactions() const
{
    return transactions;
}

void Company::showStatistics(std::vector<Transaction *>& tr) const
{
    double temp_cash = 0;
    std::vector<std::pair<Product *, unsigned int>> temp_soldProducts;
    unsigned int temp_total  = 0;
    for(Transaction * t: tr){
        temp_cash += t->getValue();
        if(dynamic_cast<ClientTransaction *>(t) != nullptr) { //The statistics are only of the client transactions
            for (std::pair<Product *, unsigned int> c: t->getCart()) {
                FindProduct_pair x(c);
                auto it = find_if(temp_soldProducts.begin(), temp_soldProducts.end(), x);
                if (it != temp_soldProducts.end()) { //If the product already exists
                    it->second += c.second;
                } else
                    temp_soldProducts.push_back(c);
                temp_total += c.second;
            }
        }
    }
    std::cout << std::endl;
    if(!tr.empty()) {
        std::cout <<  "Balance: " << temp_cash << std::endl;

        sort(temp_soldProducts.begin(), temp_soldProducts.end(), [](const std::pair<Product *, unsigned int> &p1, const std::pair<Product *, unsigned int> &p2){return p1.second > p2.second;});
        std::cout << std::endl << "Top 5:" << std::endl;
        for(int i = 0; i < 5; i++){
            std::cout << '\t' << i + 1 << ". ";
            if(i >= temp_soldProducts.size())
                std::cout << "Not enough products" << std::endl;
            else
                std::cout << temp_soldProducts[i].first->getDescription() << " -> " << temp_soldProducts[i].second << " (" << std::fixed << std::setprecision(2) << 100 * (temp_soldProducts[i].second / float(temp_total)) << " %)" << std::endl;
        }

        std::cout << std::endl << "Top 5 less sold products:" << std::endl;
        for(int i = 1; i <= 5; i++){
            std::cout << '\t' << i << ". ";
            if(i > temp_soldProducts.size())
                std::cout << "Not enough products" << std::endl;
            else
                std::cout << temp_soldProducts[temp_soldProducts.size() - i].first->getDescription() << " -> " << temp_soldProducts[temp_soldProducts.size() - i].second << " (" << std::fixed << std::setprecision(2) << 100 * (temp_soldProducts[temp_soldProducts.size() - i].second / float(temp_total)) << " %)" << std::endl;
        }

        sort(tr.begin(), tr.end(), [](Transaction *t1, Transaction * t2){return *t1 < *t2;});
        for(size_t i = tr.size() - 1; i >= 0; i--)
            if(dynamic_cast<ClientTransaction *>(tr[i]) != nullptr) {
                std::cout << std::endl << "Biggest purchase: " << std::fixed << std::setprecision(2) << tr[i]->getValue() << std::endl;
                break;
            }
    }
    else{
        std::cout << "There aren't transactions to calculate the statistics" << std::endl;
    }
    std::cout << std::endl << std::endl;

}

void Company::showAllStatistics() {
    std::cout << std::endl;
    if(!transactions.empty()) {
        std::cout << "Balance: " << std::fixed << std::setprecision(2) << cashEarned << std::endl;

        sort(soldProducts.begin(), soldProducts.end(),
             [](const std::pair<Product *, unsigned int> &p1, const std::pair<Product *, unsigned int> &p2) {
                 return p1.second > p2.second;
             });
        std::cout << std::endl << "Top 5:" << std::endl;
        for (int i = 0; i < 5; i++) {
            std::cout << '\t' << i + 1 << ". ";
            if (i >= soldProducts.size())
                std::cout << "Not enough products" << std::endl;
            else
                std::cout << std::fixed << soldProducts[i].first->getDescription() << " -> " << soldProducts[i].second << " ("
                          << std::setprecision(2) << 100 * (soldProducts[i].second / float(total_products)) << " %)"
                          << std::endl;
        }

        sort(soldProducts.begin(), soldProducts.end(),
             [](const std::pair<Product *, unsigned int> &p1, const std::pair<Product *, unsigned int> &p2) {
                 return p1.second > p2.second;
             });
        std::cout << std::endl << "Top 5 less sold products:" << std::endl;
        for (int i = 1; i <= 5; i++) {
            std::cout << '\t' << i << ". ";
            if (i > soldProducts.size())
                std::cout << "Not enough products" << std::endl;
            else
                std::cout  << std::fixed << soldProducts[soldProducts.size() - i].first->getDescription() << " -> "
                          << soldProducts[soldProducts.size() - i].second << " (" << std::setprecision(2)
                          << 100 * (soldProducts[soldProducts.size() - i].second / float(total_products)) << " %)"
                          << std::endl;
        }


        sort(transactions.begin(), transactions.end(), [](Transaction *t1, Transaction *t2) { return *t1 < *t2; });
        for (size_t i = transactions.size() - 1; i >= 0; i--)
            if (dynamic_cast<ClientTransaction *>(transactions[i]) != nullptr) {
                std::cout << std::endl << "Biggest purchase: " << std::fixed << std::setprecision(2) << transactions[i]->getValue() << std::endl;
                break;
            }
    }
    else
        std::cout << "There aren't transactions to calculate the statistics" << std::endl;
    std::cout << std::endl << std::endl;
}

void Company::showStatsByDay(const Date& date) const
{
    FindTransactionByDay x(date, true);
    std::vector<Transaction *> tr(transactions.size());
    auto it = std::copy_if(transactions.begin(), transactions.end(), tr.begin(), x); //Copy to tr all the transactions of the day given by date
    tr.resize(distance(tr.begin(), it));
    showStatistics(tr);
}

void Company::showStatsByMonth(const Date& date) const
{
    FindTransactionByMonth x(date, true);
    std::vector<Transaction *> tr(transactions.size());
    auto it = std::copy_if(transactions.begin(), transactions.end(), tr.begin(), x); //Copy to tr all the transactions of the month given by date
    tr.resize(distance(tr.begin(), it));
    showStatistics(tr);
}

void Company::showStatsByYear(const Date& date) const
{
    FindTransactionByYear x(date, true);
    std::vector<Transaction *> tr(transactions.size());
    auto it = std::copy_if(transactions.begin(), transactions.end(), tr.begin(), x); //Copy to tr all the transactions of the year given by date
    tr.resize(distance(tr.begin(), it));
    showStatistics(tr);
}

void Company::addTransaction(Transaction * t)
{
    int index;
    transactions.push_back(t);
    if(dynamic_cast<ClientTransaction *>(t) != nullptr) //The transaction is a client transaction
    {
        cashEarned += t->getValue();
        std::vector<std::pair<Product *, unsigned int>> cart = t->getCart();
        for(std::pair<Product *, unsigned int> c: cart)
        {
            FindProduct_pair x(c);
            auto it = find_if(soldProducts.begin(), soldProducts.end(), x);
            if(it == soldProducts.end()) //If the product was never sold
                soldProducts.push_back(c);
            else
                it->second += c.second;
            total_products += c.second;
            auto sP = new StoreProduct(new Product(c.first->getDescription(), c.first->getPrice()));
            index = oStore->findProduct(sP);
            oStore->getProducts()[index]->setCurrentStock(oStore->getProducts()[index]->getCurrentStock() - c.second); //Update the current stoke
            delete sP;
        }
        if(!dynamic_cast<ClientTransaction *>(t)->stockNeededEmpty()){
            repositionByStore(dynamic_cast<ClientTransaction *>(t)->getStockNeeded(), t->getDate());
        }
    }
}

void Company::repositionByStore(std::vector<std::pair<Product *, unsigned int>>& stockNeeded , const Date& date){
    std::vector<std::pair<Product*, unsigned int>> modifiedStockNeeded(stockNeeded);
    bool supplier=false;
    unsigned int index_physical, index_online;
    for (std::pair<Product *, unsigned int> &sN :stockNeeded ) {
        sort(stores.begin(),stores.end(),ComparatorByProduct(sN.first));
        for (PhysicalStore * & s:stores) {
            auto sp = new StoreProduct(new Product(sN.first->getDescription(), sN.first->getPrice()), 0, 0);
            index_physical = s->findProduct(sp);
            if(index_physical != -1) {
                auto actualSp=s->getProducts()[index_physical];
                int possibleRestock=(int)actualSp->getCurrentStock()-(int)actualSp->getStockLimit(); //Max quantity that can be removed from the store (if lower or equal than 0 is none)
                if ((int)sN.second<=possibleRestock) //All of the quantity needed can be restocked
                {
                    actualSp->reduceCurrentStock(sN.second);
                    index_online = oStore->findProduct(sp);
                    oStore->getProducts()[index_online]->increaseCurrentStock(sN.second);
                    sN.second=0;
                    break;
                }
                else{
                    if (possibleRestock>0){ //If it is possible to remove some quantity that needs to be restocked
                        actualSp->reduceCurrentStock(possibleRestock);
                        index_online = oStore->findProduct(sp);
                        oStore->getProducts()[index_online]->increaseCurrentStock(possibleRestock);
                        sN.second-=possibleRestock;
                    }
                }
            }
            delete sp;
        }
        if (sN.second!=0)supplier=true; //In case there is still quantity to be restocked, do it with the supplier
    }
    if (supplier){
        for(std::pair<Product *, unsigned int> sN :stockNeeded){
            missingStock.push_back(sN);
        }
    }
    for (int i = 0; i < stockNeeded.size(); ++i) {
        modifiedStockNeeded[i].second -= stockNeeded[i].second;
    }
    int i = 0;
    while(i < modifiedStockNeeded.size()) {
        if (modifiedStockNeeded[i].second == 0)
            modifiedStockNeeded.erase(modifiedStockNeeded.begin() + i);
        else
            i++;
    }
    if(!modifiedStockNeeded.empty())
        addTransaction(dynamic_cast<Transaction *>(new ReStock(date,modifiedStockNeeded,getOnlineStore(),false)));
}

void Company::repositionBySupplier(std::vector<std::pair<Product *, unsigned int>>& stockNeeded, const Date& date){
    int index;
    for (std::pair<Product *, unsigned int> sN :stockNeeded ) {
        auto sp = new StoreProduct(new Product(sN.first->getDescription(), sN.first->getPrice()), 0, 0);
        index = oStore->findProduct(sp);
        delete sp;
        oStore->getProducts()[index]->setCurrentStock(oStore->getProducts()[index]->getCurrentStock()+sN.second);
    }
    addTransaction(dynamic_cast<Transaction *>(new ReStock(date, stockNeeded, getOnlineStore(), true)));
}

void Company::writeFile(const std::string& file) const
{
    std::ofstream out;
    out.open(file);
    if(!out)
    {
        throw InvalidFile(file);
    }

    out << companyName << std::endl;

    for(PhysicalStore* pS: stores)
    {
        out << pS->getLocation() << std::endl;
    }

    oStore->sortClients();
    out << CLIENTS << std::endl;
    for(Client * c: oStore->getClients())
    {
        out << c->getName() << std::endl;
        out << c->getNIF() << std::endl;
        auto rC = dynamic_cast<RegisteredClient *>(c);
        if( rC != nullptr) //If it is a registered client
        {
            out << rC->getEmail() << std::endl;
            for(Payment * p: rC->getPaymentMethods()) {
                out << p->writeToFile() << std::endl;
            }
            if(!rC->noMessages()) {
                out << "CHAT:" << std::endl;
                rC->writeChat(out);
            }
        }
        out << CHANGE_TOPIC << std::endl;
    }

    out << PRODUCTS << std::endl;
    for(StoreProduct* sP:oStore->getProducts())
    {
        out << sP->getProduct()->getDescription() << COMMA << sP->getProduct()->getPrice() << std::endl;
        out << "Online-" << sP->getCurrentStock() << COMMA << sP->getStockLimit() << std::endl;
        for(PhysicalStore * pS:stores)
        {
            int index = pS->findProduct(sP);
            if(index != -1)
                out << pS->getLocation() << HYPHEN << pS->getProducts()[index]->getCurrentStock() << "," << pS->getProducts()[index]->getStockLimit() << std::endl;
        }
        out << CHANGE_TOPIC << std::endl;
    }

    out << TRANSACTIONS << std::endl;
    for(Transaction *t: transactions){
        auto temp = dynamic_cast<ClientTransaction *>(t);
        if(temp != nullptr){
            out << temp->getNif() << std::endl;
            out << temp->getDate() << std::endl;
            out << temp->getPaymentMethod()->writeToFile() << std::endl;
            for(auto elem:t->getCart()){
                out << elem.first->getDescription() << COMMA << elem.first->getPrice() << COMMA << elem.second << std::endl;
            }
        }
        else{
            auto _temp = dynamic_cast<ReStock *>(t);
            if(_temp->getBySupplier())
                out << "True" << std::endl;
            else
                out << "False" << std::endl;
            out << _temp->getDate() << std::endl;
            if(_temp->getBySupplier()){
                out << _temp->getSupplier().getName() << " " << _temp->getSupplier().getPrice() << std::endl;
            }
            for(auto elem:t->getCart()){
                out << elem.first->getDescription() << COMMA << '0' << COMMA << elem.second << std::endl;
            }
        }
        out << CHANGE_TOPIC << std::endl;
    }
    out.close();
    writeSuppliers("SUPPLIERS.txt");
    writeFleet("FLEET.txt");
}

bool Company::showTransactions(std::vector<Transaction *>& tr, bool client) const
{
    if(!tr.empty()) {
        sort(tr.begin(), tr.end(), [](Transaction *t1, Transaction *t2){return t1->getTransactionID() < t2->getTransactionID();});
        std::cout << "\tTRANSACTION\t" << "\tDATE\t";
        if (client) {
            std::cout << "\t\tVALUE\t" << "\tNIF" << std::endl;
            for (Transaction *t: tr) {
                if(dynamic_cast<ClientTransaction *>(t) != nullptr)
                    std::cout << '\t' << std::setfill('0') << std::setw(10) << t->getTransactionID() << "\t|\t"
                              << t->getDate() << "\t|\t" << std::fixed << std::setprecision(2) << t->getValue() << "\t|\t" << dynamic_cast<ClientTransaction *>(t)->getNif()
                              << std::endl;
            }
        } else {
            std::cout << "\t\tFROM\t" << std::endl;
            for (Transaction *t: tr) {
                if(dynamic_cast<ReStock *>(t) != nullptr) {
                    std::cout << '\t' << std::setfill('0') << std::setw(10) << t->getTransactionID() << "\t|\t"
                              << t->getDate() << "\t|\t";
                    if (dynamic_cast<ReStock *>(t)->getBySupplier())
                        std::cout << "SUPPLIER\t" << std::endl;
                    else
                        std::cout << "STORE\t" << std::endl;
                }
            }
        }
    }
    else {
        std::cout << "No transactions to show" << std::endl << std::endl;
        return false;
    }
    return true;
}

bool Company::showAllTransactions(bool client)
{
    return showTransactions(transactions, client);
}

bool Company::showTransactionsByDay(const Date& date, bool client) const
{
    FindTransactionByDay x(date, client);
    std::vector<Transaction *> tr(transactions.size());
    auto it = std::copy_if(transactions.begin(), transactions.end(), tr.begin(), x); //Copy to tr all the transactions of the day given by date
    tr.resize(distance(tr.begin(), it));
    return showTransactions(tr, client);
}

bool Company::showTransactionsByMonth(const Date& date, bool client) const
{
    FindTransactionByMonth x(date, client);
    std::vector<Transaction *> tr(transactions.size());
    auto it = std::copy_if(transactions.begin(), transactions.end(), tr.begin(), x);  //Copy to tr all the transactions of the month given by date
    tr.resize(distance(tr.begin(), it));
    return showTransactions(tr, client);
}

bool Company::showTransactionsByYear(const Date& date, bool client) const
{
    FindTransactionByYear x(date, client);
    std::vector<Transaction *> tr(transactions.size());
    auto it = std::copy_if(transactions.begin(), transactions.end(), tr.begin(), x);  //Copy to tr all the transactions of the year given by date
    tr.resize(distance(tr.begin(), it));
    return showTransactions(tr, client);
}

OnlineStore *Company::getOnlineStore() const {return oStore;}

void Company::showProductsStats(bool admin) const {
    int index;
    if(oStore->getProducts().empty()) //Online store is empty
        std::cout << "Currently there are no products for sale." << std::endl;
    else {
        for (StoreProduct *sp: oStore->getProducts()) {
            std::cout << sp->getProduct()->getDescription() << " -> " << sp->getProduct()->getPrice() << std::endl;
            index = oStore->findProduct(sp);
            StoreProduct *p = oStore->getProducts()[index];
            if (admin) { //This function works differently if the products must be shown to a client or to an admin
                std::cout << "Online Store" << "->" << p->getCurrentStock() << "|" << p->getStockLimit() << std::endl;
                for (PhysicalStore *s:stores) {
                    index = s->findProduct(sp);
                    if(index != -1)
                        std::cout << s->getLocation() << "->" << s->getProducts()[index]->getCurrentStock() << "|" << s->getProducts()[index]->getStockLimit() << std::endl;
                }
            } else {
                std::cout << "Current stock" << "\t->\t" << p->getCurrentStock() << std::endl;
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void Company::showStores() const{
    for(PhysicalStore * pS:stores){
        std::cout << pS->getLocation() << ":" << std::endl;
        if(pS->getProducts().empty())
            std::cout << "\tThere are no products in this store" << std::endl;
        for(StoreProduct * sp:pS->getProducts()){
            std::cout << '\t' << sp->getProduct()->getDescription() << " | CS = "<< sp->getCurrentStock() << " | SL = " << sp->getStockLimit() << std::endl;
        }
    }
    std::cout << std::endl;
}

void Company::sortStores() {
    sort(stores.begin(), stores.end(), [](PhysicalStore *pS1, PhysicalStore *pS2){return *pS1 < *pS2;});
}

void Company::showTransactionsDetails(int id, int client, int all, const Date& d) const{
    FindTransaction *x;
    switch(all){
        case 0: {
            x = new FindTransaction(id, client);
            break;
        }
        case 1: {
            x = new FindTransactionByDay(id, d, client);
            break;
        }
        case 2:{
            x = new FindTransactionByMonth(id, d, client);
            break;
        }
        case 3:{
            x = new FindTransactionByYear(id, d, client);
            break;
        }

        default:{
            x= nullptr;
            break;
        }
    }
    auto it = find_if(transactions.begin(), transactions.end(), *x);
    if(it == transactions.end())
        std::cout << "There is no transaction of that type associated to the given ID" << std::endl;
    else
        std::cout << (*it)->printTransaction() << std::endl;
}

size_t Company::getNumberMessages() const {
    return messagesToProcess.size();
}

bool Company::noMessages() const {
    return messagesToProcess.empty();
}

HashTableMessage Company::getMessagesToProcess() const {
    return messagesToProcess;
}

bool Company::addMessage(Client * client, ClientMessage * msg){
    int index = oStore->findClient(client);
    RegisteredClient * temp = dynamic_cast<RegisteredClient *>(oStore->getClients()[index]);
    if(temp != nullptr){
        messagesToProcess.insert(msg);
        temp->addMessage(msg);
        return true;
    }
    return false;
}

bool Company::processMessage(std::string eMail, AdminMessage * answer){
    int index = oStore->findRegisteredClient(eMail);
    RegisteredClient * client = dynamic_cast<RegisteredClient *>(oStore->getClients()[index]);
    if(client != nullptr) {
        HashTableMessage temp = messagesToProcess;
        std::vector<ClientMessage *> msgToProcess;
        int counter = 1;
        if(client->noMessages()) { client->addMessage(answer); return true; }
        while (dynamic_cast<AdminMessage *>(client->getMessage(client->getMessages().size() - counter)) == nullptr) {
            msgToProcess.push_back(dynamic_cast<ClientMessage *>(client->getMessage(client->getMessages().size() - counter)));
            dynamic_cast<ClientMessage *>(client->getMessage(client->getMessages().size() - counter))->processMessage();
            if(client->getMessages().size() - counter == 0) break; //No more messages
            counter++;
        }
        for(const auto& msg:msgToProcess){
            for(const auto& elem:temp){
                if(*elem == *msg){
                    temp.erase(elem);
                    break;
                }
            }
        }
        messagesToProcess = temp;
        client->addMessage(answer);
        return true;
    }
    return false;
}

void Company::showMessages() const{
    int i = 0;
    for(const auto &msg:messagesToProcess){
        std::cout << i << ". \t" << msg->getEMail() << "\t-\t";
        if(msg->getMsg().size() >= 10) std::cout << msg->getMsg().substr(0, 10) << "...\t-\t";
        else std::cout << msg->getMsg() << "\t-\t";
        std::cout << msg->getDate() << std::endl;
        i++;
    }
}

void Company::insertSupplier(Supplier supplier) {
    for(BST<Supplier> &supplierTree:suppliers){
        if(!supplierTree.isEmpty()){
            BSTItrPre<Supplier> iter(supplierTree);
            if(iter.retrieve().getProductName()==supplier.getProductName()){
                supplierTree.insert(supplier);
                return;
            }
        }
    }
    BST<Supplier> bst(Supplier("",0,"",0));
    bst.insert(supplier);
    suppliers.push_back(bst);
}

unsigned int Company::searchSuppliers(std::string productName) const {
    for (int i = 0; i < suppliers.size(); ++i) {
        BSTItrPre<Supplier> iter(suppliers[i]);
        if(iter.retrieve().getProductName()==productName) return i;
    }
    return -1;
}

void Company::removeSupplier(Supplier supplier) {
    for (int i = 0; i < suppliers.size(); ++i) {
        BSTItrIn<Supplier> iter(suppliers[i]);
        if (iter.retrieve().getProductName() == supplier.getProductName()) {
            while (!iter.isAtEnd()) {
                if (iter.retrieve() == supplier) {
                    suppliers[i].remove(supplier);
                    if (suppliers[i].isEmpty()) suppliers.erase(suppliers.begin() + i);
                    return;
                } else {
                    iter.advance();
                }
            }
            break;
        }
    }
}

bool Company::repositionBySupplier(pair<Product *, unsigned int> &stockNeeded, const Date &date, Supplier supplier) {
    removeSupplier(supplier);
    int index;
    auto sp = new StoreProduct(new Product(stockNeeded.first->getDescription(), stockNeeded.first->getPrice()), 0, 0);
    index = oStore->findProduct(sp);
    delete sp;
    if ((int)stockNeeded.second<=supplier.getCurrentStock()) //All of the quantity needed can be restocked
    {
        supplier.setCurrentStock(supplier.getCurrentStock()-stockNeeded.second);
        oStore->getProducts()[index]->increaseCurrentStock(stockNeeded.second);
        //Add transaction to the transaction list
        vector<pair<Product *, unsigned int>> x;
        x.push_back(stockNeeded);
        auto transactionRestock = new ReStock(date, x, getOnlineStore(), true);
        transactionRestock->setSupplier(supplier);
        addTransaction(dynamic_cast<Transaction *>(transactionRestock));
        if(supplier.getCurrentStock()>0) insertSupplier(supplier);
        stockNeeded.second=0;
    }
    else{
        if (supplier.getCurrentStock()>0){ //If it is possible to remove some quantity that needs to be restocked
            oStore->getProducts()[index]->increaseCurrentStock(supplier.getCurrentStock());
            //Add transaction to the transaction list
            vector<pair<Product *, unsigned int>> x;
            x.push_back(make_pair(stockNeeded.first,supplier.getCurrentStock()));
            auto transactionRestock = new ReStock(date, x, getOnlineStore(), true);
            transactionRestock->setSupplier(supplier);
            addTransaction(dynamic_cast<Transaction *>(transactionRestock));
            stockNeeded.second-=supplier.getCurrentStock();
        }
    }
    if (stockNeeded.second!=0){
        return false; //Reposition not done yet
    }
    return true; //Reposition done
}

void Company::readMessages(std::istream & in, RegisteredClient * c){
    std::string text, eMail = "empty", date = "empty", msg;
    Message * last, * temp;
    getline(in, text, '\n');
    while(text != CHANGE_TOPIC){
        eMail = text;
        getline(in, text, '\n');
        date = text;
        getline(in, text, '\n');
        try {
            if (eMail == "admin") temp = new AdminMessage(text, Date(date));
            else temp = new ClientMessage(text, eMail, Date(date));
        }catch(InvalidDate &error){
            throw;
        }
        c->addMessage(temp);
        last = temp;
        getline(in, text, '\n');
    }
    if(eMail == "empty" && date == "empty") return;
    auto test = dynamic_cast<ClientMessage *>(last);
    if(test != nullptr) messagesToProcess.insert(test);
}

void Company::readSuppliers(const string &file) {
    std::ifstream in(file);
    std::string text, name, nameProduct;
    int nif, currentStock;
    double price;

    if(!in)
    {
        throw InvalidFile(file);
    }

    while (getline(in, text, '\n')){
        if(text=="") break;
        //Read name
        name=text;
        //Read nif
        getline(in, text, '\n');
        nif=stoi(text);
        //Read product name, price and quantity
        getline(in, text, '\n');
        std::stringstream s(text);
        s >> nameProduct;
        s >> price;
        s >> currentStock;
        Supplier supplier(name,nif,nameProduct,price);
        supplier.setCurrentStock(currentStock);
        insertSupplier(supplier);
        //Change topic
        getline(in, text, '\n');
    }

    in.close();

}

void Company::readFleet(const string &file) {
	std::ifstream in(file);
	std::string vanPlate, currentLine;
	unsigned int totalCapacity, remainingCapacity, currentLoad;

	if (!in) throw InvalidFile(file);

	while (!in.eof()) {
		std::getline(in, currentLine);
		std::istringstream input(currentLine);

		input >> vanPlate >> totalCapacity >> remainingCapacity >> currentLoad;
		fleet.emplace(vanPlate, totalCapacity, remainingCapacity);
	}
	in.close();
}

void Company::writeSuppliers(const string &file) const {
    std::ofstream out;
    out.open(file);
    if(!out)
    {
        throw InvalidFile(file);
    }

    for(BST<Supplier> supplierTree: suppliers)
    {
        BSTItrIn<Supplier> iter(supplierTree);
        while(!iter.isAtEnd())
        {
            Supplier s=iter.retrieve();
            out << s.getName() << std::endl;
            out << s.getNif() << std::endl;
            out << s.getProductName() << " " << s.getPrice() << " " << s.getCurrentStock() << std::endl;
            iter.advance();
            if(!iter.isAtEnd()) out << CHANGE_TOPIC << std::endl;
        }
        out << CHANGE_TOPIC << std::endl;
    }
    out.close();
}

void Company::writeFleet(const string & file) const {
	std::ofstream out;
	out.open(file);
	if (!out) throw InvalidFile(file);

	priority_queue<Van> auxFleet = fleet;
	bool firstElement = true;

	while (!auxFleet.empty()) {
		Van currentVan = auxFleet.top();

		std::string plate = currentVan.getVanPlate();
		unsigned int totalCap = currentVan.getTotalCapacity();
		unsigned int remCap = currentVan.getRemainingCapacity();
		unsigned int currLoad = currentVan.getCurrentLoad();

		if (!firstElement) out << std::endl << plate << " " << totalCap << " " << remCap << " " << currLoad;
		else {
			firstElement = false; out << plate << " " << totalCap << " " << remCap << " " << currLoad;
		}
		auxFleet.pop();
	}
	out.close();
}

const std::vector<std::pair<Product *, unsigned int>> &Company::getMissingStock() const {
    return missingStock;
}

void Company::setMissingStock(const std::vector<std::pair<Product *, unsigned int>> &missingStock) {
    Company::missingStock = missingStock;
}

const vector<BST<Supplier>> &Company::getSuppliers() const {
    return suppliers;
}

void Company::removeMissingProduct(int index) {
    missingStock.erase(missingStock.begin()+index);
}

void Company::setMissingProductQuantity(int index, int quantity) {
    missingStock[index].second=quantity;
}

bool Company::addOrderToDispatch(Transaction * transaction) {

	// Requires two vectors for keep tracking of changes
	std::vector<Van> aux, temp;
	bool dispatched = false;
	unsigned int loadCap = transaction->getOrderCapacity();

	while (!fleet.empty() && !dispatched) {

		Van vehicle = fleet.top();
		if (vehicle.getRemainingCapacity() < loadCap) {
			aux.push_back(vehicle);
			temp.push_back(vehicle);
			fleet.pop();
		}
		else {
			vehicle.loadOrder(loadCap);
			fleet.pop(); fleet.push(vehicle);
			dispatched = true;
		}
	}

	// Didn't Find any Available Space
	if (!dispatched) {
		unsigned int loadCapAux = loadCap;

		for (Van v : aux) {
			if (loadCapAux >= v.getRemainingCapacity()) {
				loadCapAux -= v.getRemainingCapacity();
				v.loadOrder(v.getRemainingCapacity());
			}
			else {
				v.loadOrder(loadCapAux);
				loadCapAux = 0; dispatched = true;
			}
		}
	} else {
		for (Van &v : aux)
			fleet.push(v);
		return dispatched;
	}

	fleet = dispatched ? priority_queue<Van>(aux.begin(), aux.end()) : priority_queue<Van>(temp.begin(), temp.end());
	return dispatched;
}

void Company::vanInTransit() {
	if (fleet.empty())
		std::cout << "There are no Vehicles to send!" << std::endl;

	Van vanToSend = fleet.top(); fleet.pop();
	try {
		vanToSend.sendVan(false);
	}
	catch (VanNotReady& error) {
		std::cout << error.printError() << std::endl;
		std::cout << "Do you really want to send this Vehicle? (yes/no)" << std::endl;
		std::string response; getline(std::cin, response, '\n');

		if (response == "yes")
			vanToSend.sendVan(true);
	}
	fleet.push(vanToSend);
}

std::string Company::showFleet() const {
	priority_queue<Van> fleetAux = fleet;
	std::string res = "Plate\t\tMaxCap\tRemaining\tLoad\n";
	while (!fleetAux.empty()) {
		Van v = fleetAux.top(); fleetAux.pop();

		std::string plate = v.getVanPlate(),
					maxCap = to_string(v.getTotalCapacity()),
					remCap = to_string(v.getRemainingCapacity()),
					currLoad = to_string(v.getCurrentLoad());
		res += plate + '\t' + maxCap + '\t' + remCap + "\t\t" + currLoad + '\n';
	}

	return res;
}
