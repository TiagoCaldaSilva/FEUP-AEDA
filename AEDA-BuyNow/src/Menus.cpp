#include "Menus.h"

void companyStats(Company * c){
    std::string text;
    unsigned int day, month, year;
    bool end = false;
    while(!end) {
        day = 1, month = 1, year = 1;
        try {
            std::cout << "Statistics:" << std::endl
                      << "\t1. See all the statistics" << std::endl
                      << "\t2. See statistics of a specific day" << std::endl
                      << "\t3. See statistics of a specific month" << std::endl
                      << "\t4. See statistics of a specific year" << std::endl
                      << "\t5. Exit" << std::endl;
            getline(std::cin, text, '\n');
            if (text.size() != 1) {
                std::cout << "Invalid output, please try again." << std::endl;
                continue;
            }
            switch (text[0]) {
                case '1':
                    c->showAllStatistics();
                    break;
                case '2':
                    std::cout << "Day: ";
                    std::cin >> day;
                    std::cout << "Month: ";
                    std::cin >> month;
                    std::cout << "Year: ";
                    std::cin >> year;
                    c->showStatsByDay(Date(day, month, year));
                    std::cin.ignore();
                    break;
                case '3':
                    std::cout << "Month: ";
                    std::cin >> month;
                    std::cout << "Year: ";
                    std::cin >> year;
                    c->showStatsByMonth(Date(day, month, year));
                    std::cin.ignore();
                    break;
                case '4':
                    std::cout << "Year: ";
                    std::cin >> year;
                    c->showStatsByYear(Date(day, month, year));
                    std::cin.ignore();
                    break;
                case '5':
                    end = true;
                    break;
                default:
                    std::cout << "Invalid output, please try again." << std::endl;
                    break;
            }
        }
        catch(InvalidDate &error){
            std::cin.ignore();
            std::cout << error << std::endl;
        }
    }
}

void transactions(Company * c){
    bool exit = false, client = false, error = false;
    int id, all;
    std::string text;
    unsigned int day, month, year;
    while(!exit){
        std::cout << "What kind of transactions?" << std::endl
                  << "\t1. Client Transactions" << std::endl
                  << "\t2. Others" << std::endl
                  << "\t3. Exit" << std::endl;
        getline(std::cin, text, '\n');
        if(text.size() != 1) {
            std::cout << "Invalid output, please try again." << std::endl;
            continue;
        }
        switch (text[0]) {
            case '1':
                client = true;
                break;
            case '2':
                client = false;
                break;
            case '3':
                exit = true;
                break;
            default:
                std::cout << "Invalid output, please try again." << std::endl;
                break;
        }
        if(!exit) {
            while (!exit) {
                day = 1, month = 1, year = 1;
                try {
                    std::cout << "Transactions:" << std::endl
                              << "\t1. See all the transactions" << std::endl
                              << "\t2. See transactions of a specific day" << std::endl
                              << "\t3. See transactions of a specific month" << std::endl
                              << "\t4. See transactions of a specific year" << std::endl
                              << "\t5. Exit" << std::endl;
                    getline(std::cin, text, '\n');
                    if (text.size() != 1)
                        std::cout << "Invalid output, please try again." << std::endl;
                    switch (text[0]) {
                        case '1':
                            error = !c->showAllTransactions(client);
                            all = 0;
                            break;
                        case '2':{
                            all = 1;
                            std::cout << "Day: ";
                            std::cin >> day;
                            std::cout << "Month: ";
                            std::cin >> month;
                            std::cout << "Year: ";
                            std::cin >> year;
                            Date temp(day, month, year);
                            std::cout << std::endl;
                            error = !(c->showTransactionsByDay(temp, client));
                            std::cin.ignore();
                            break;
                        }
                        case '3':
                            all = 2;
                            std::cout << "Month: ";
                            std::cin >> month;
                            std::cout << "Year: ";
                            std::cin >> year;
                            std::cout << std::endl;
                            error = !c->showTransactionsByMonth(Date(day, month, year), client);
                            std::cin.ignore();
                            break;
                        case '4':
                            all = 3;
                            std::cout << "Year: ";
                            std::cin >> year;
                            std::cout << std::endl;
                            error = !c->showTransactionsByYear(Date(day, month, year), client);
                            std::cin.ignore();

                            break;
                        case '5':
                            exit = true;
                            break;
                        default:
                            std::cout << "Invalid output, please try again." << std::endl;
                            break;
                    }
                    if(!error) {
                        do {
                            error = false;
                            if (!exit) {
                                std::cout << std::endl
                                          << "Do you want to see a more detailed version of a specific transaction? "
                                          << std::endl
                                          << "\t1. YES" << std::endl << "\t2. NO" << std::endl;
                                getline(std::cin, text, '\n');
                                if (text.size() != 1)
                                    std::cout << "Invalid output, please try again." << std::endl;
                                switch (text[0]) {
                                    case '1':
                                        std::cout << "What is the ID of the transaction that you want to see? "
                                                  << std::endl;
                                        std::cin >> id;
                                        if (std::cin.fail()) {
                                            std::cin.clear();
                                            error = true;
                                        }
                                        if (std::cin.peek() != '\n') {
                                            std::cin.ignore(100000, '\n');
                                            error = true;
                                        }
                                        if (error)
                                            std::cout << "Invalid output, please try again." << std::endl;
                                        else {
                                            c->showTransactionsDetails(id, client, all, Date(day, month, year));
                                            std::cin.ignore();
                                        }
                                        break;
                                    case '2':
                                        exit = true;
                                        break;
                                    default:
                                        std::cout << "Invalid output, please try again." << std::endl;
                                        break;
                                }
                            }
                        } while (!exit);
                    }
                }
                catch(InvalidDate &error){
                    std::cin.ignore();
                    std::cout << error.printError() << std::endl;
                }
            }
            exit = false; //To exit to transactions menu
        }
    }
}

void products(Company * c){
    std::string text;
    bool end = false, done, ignore;
    double price;
    unsigned int currentStock, stockLim;
    while(!end) {
        std::cout << "Products" << std::endl
                  << "\t1. Show products" << std::endl
                  << "\t2. Add product" << std::endl
                  << "\t3. Add a product to a store" << std::endl
                  << "\t4. Remove product" << std::endl
                  << "\t5. Exit" << std::endl;
        getline(std::cin, text, '\n');
        if (text.size() != 1) {
            std::cout << "Invalid output, please try again." << std::endl;
            continue;
        }
        switch(text[0]){
            case '1': {
                c->showProductsStats(true);
                break;
            }
            case '2': {
                std::cout << "Product description: ";
                getline(std::cin, text, '\n');
                if(text.empty()){
                    std::cout << "Invalid Input, please try again." << std::endl;
                    break;
                }
                std::cout << "Price: ";
                std::cin >> price;
                auto new_product = new Product(text, price);
                try {
                    std::cout << "Please give CURRENT STOCK | STOCK LIMIT to the online store:\n";
                    std::cout << "CURRENT STOCK: ";
                    std::cin >> currentStock;
                    std::cout << "STOCK LIMIT: "; std:: cin >> stockLim;
                    c->getOnlineStore()->addProduct(new StoreProduct(new_product, currentStock, stockLim));
                    if(currentStock < stockLim){
                        //The reStock of a product with a lower quantity of current stock than the stock limit (2 * the difference between them)
                        std::vector<std::pair<Product *, unsigned int>> x(1, std::make_pair(new_product, 2 * (stockLim - currentStock)));
                        c->repositionByStore(x, Date(1,1,1));
                    }
                    std::cout << std::endl << "Please give CURRENT STOCK | STOCK OK to the physical stores:" << std::endl
                              << "(PRESS ENTER IF YOU DO NOT WANT TO ADD THE PRODUCT TO A SPECIFIC STORE)" << std::endl << std::endl;

                    ignore = true;  //ignore = true when we need to clear the buffer to use getline()
                    for (PhysicalStore *&p:c->getStores()) {
                        std::cout << p->getLocation() << std::endl;
                        std::cout << "CURRENT STOCK: ";
                        if(ignore){
                            std::cin.ignore();
                            ignore = false;
                        }
                        getline(std::cin, text, '\n');
                        if(!text.empty()) {
                            currentStock = stoi(text);
                            std::cout << "STOCK OK: ";
                            std::cin >> stockLim;
                            ignore = true;
                            p->addProduct(new StoreProduct(new_product, currentStock, stockLim));
                        }
                    }
                }
                catch(ProductAlreadyExists &error)
                {
                    std::cin.ignore();
                    std::cout << error << std::endl;
                }
                if(ignore)
                    std::cin.ignore();
                break;
            }
            case '3': {
                done = false;
                ignore = false;
                std::cout << "Product description: ";
                getline(std::cin, text, '\n');
                if(text.empty()){
                    std::cout << "Invalid Input, please try again." << std::endl;
                    break;
                }
                auto product = new Product(text, 0);
                auto new_sP = new StoreProduct(product, 0, 0);
                int index_sP = c->getOnlineStore()->findProduct(new_sP);
                delete new_sP;
                if(index_sP == -1){
                    std::cout << "The product given does not exist" << std::endl;
                }
                else {
                    for (PhysicalStore *&pS: c->getStores()) {
                        int index = pS->findProduct(new_sP);
                        if (index == -1) {
                            if (!done) {
                                std::cout << std::endl << "Please give CURRENT STOCK | STOCK OK to the physical stores:"
                                          << std::endl
                                          << "(PRESS ENTER IF YOU DO NOT WANT TO ADD THE PRODUCT TO A SPECIFIC STORE)"
                                          << std::endl << std::endl;
                                done = true;
                            }

                            std::cout << pS->getLocation() << std::endl;
                            std::cout << "CURRENT STOCK: ";
                            if(ignore){ //ignore = true when we need to clear the buffer to use getline()
                                std::cin.ignore();
                                ignore = false;
                            }
                            getline(std::cin, text, '\n');
                            if (!text.empty()) {
                                currentStock = stoi(text);
                                std::cout << "STOCK OK: ";
                                std::cin >> stockLim;
                                ignore = true;
                                pS->addProduct(new StoreProduct(c->getOnlineStore()->getProducts()[index_sP]->getProduct(), currentStock, stockLim));
                            }
                        }
                    }
                }
                if(ignore)
                    std::cin.ignore();
                break;
            }
            case '4':{
                std::cout << "Product description: ";
                getline(std::cin, text, '\n');
                if(text.empty()){
                    std::cout << "Invalid Input, please try again." << std::endl;
                    break;
                }
                auto sp = new StoreProduct(new Product(text, 0), 0, 0);
                try{
                    c->getOnlineStore()->removeProduct(sp);
                    for(PhysicalStore* &p: c->getStores())
                    {
                        try {
                            p->removeProduct(sp);
                        }
                        catch (ProductDoesNotExist& error) { continue; }
                        // Only the onlineStore has all the products
                        // so a physicalStore might throw an exception which must be ignored
                    }
                    std::cout << "The product " << text << " has been removed" << std::endl;

                }
                catch( ProductDoesNotExist &error){
                    std::cout << error << std::endl;
                }
                delete sp;
                break;
            }
            case '5':{
                end = true;
                break;
            }
            default:
                std::cout << "Invalid output, please try again." << std::endl;
                break;
        }
    }
}

void admin_clients(Company * c){
    std::string text;
    bool end = false;
    while(!end) {
        std::cout << std::endl << "\tClient" << std::endl;
        std::cout << "\t\t1. Show clients" << std::endl
                  << "\t\t2. Remove client" << std::endl
                  << "\t\t3. Exit" << std::endl;
        getline(std::cin, text, '\n');
        if (text.size() != 1) {
            std::cout << "Invalid output, please try again." << std::endl;
            continue;
        }
        switch(text[0]) {
            case '1':
                while(!end){
                    std::cout << std::endl << "\tShow Clients" << std::endl
                              << "\t\t1. Registered clients" << std::endl
                              << "\t\t2. Non-registered clients" << std::endl
                              << "\t\t3. All clients" << std::endl
                              << "\t\t4. Exit" << std::endl;
                    getline(std::cin, text, '\n');
                    if (text.size() != 1) {
                        std::cout << "Invalid output, please try again." << std::endl;
                        continue;
                    }
                    switch(text[0]){
                        case '1':
                            c->getOnlineStore()->showClients(0);
                            break;
                        case '2':
                            c->getOnlineStore()->showClients(-1);
                            break;
                        case '3':
                            c->getOnlineStore()->showClients(1);
                            break;
                        case '4':
                            end = true;
                            break;
                        default:
                            std::cout << "Invalid output, please try again." << std::endl;
                            break;
                    }
                }
                end = false;
                break;
            case '2':
                while(!end) {
                    std::cout << "Please give the nif of the client that you want to remove: (0 to exit)";
                    getline(std::cin, text, '\n');
                    if(text.size() == 1 && text[0] == '0')
                        end = true;
                    else {
                        if (text.size() != 9) {
                            std::cout << "Invalid output, please try again." << std::endl;
                            continue;
                        }
                        auto *cl = new Client("", stoi(text));
                        try {
                            c->getOnlineStore()->removeClient(cl);
                            std::cout << "The given client was successfully removed" << std::endl;
                        }catch(ClientDoesNotExist &error) {
                            std::cout << error << std::endl;
                        }
                        delete cl;
                    }
                }
                end = false;
                break;
            case '3':
                end = true;
                break;
            default:
                std::cout << "Invalid output, please try again." << std::endl;
                break;
        }
    }
}

void stores(Company * c){
    std::string text;
    bool end = false;
    while(!end) {
        std::cout << "\tStores" << std::endl;
        std::cout << "\t\t1. Show stores" << std::endl
                  << "\t\t2. Add store" << std::endl
                  << "\t\t3. Remove store" << std::endl
                  << "\t\t4. Exit" << std::endl;
        getline(std::cin, text, '\n');
        if (text.size() != 1) {
            std::cout << "Invalid output, please try again." << std::endl;
            continue;
        }
        switch(text[0]){
            case '1':
                c->showStores();
                break;
            case '2': {
                std::cout << "Location: ";
                getline(std::cin, text, '\n');
                if(text.empty()) {
                    std::cout << "Invalid Input, please try again." << std::endl;
                    break;
                }
                auto *pS = new PhysicalStore(text);
                try{
                    c->addStore(pS);
                }
                catch(PhysicalStoreAlreadyExists &error){
                    std::cout << error << std::endl;
                }
                break;
            }
            case '3': {
                std::cout << "Location: ";
                getline(std::cin, text, '\n');
                if (text.empty()){
                    std::cout << "Invalid Input, please try again." << std::endl;
                    break;
                }
                auto *pS = new PhysicalStore(text);
                try {
                    c->removeStore(pS);
                }
                catch (PhysicalStoreDoesNotExist &error) {
                    std::cout << error << std::endl;
                }
                break;
            }
            case '4':
                end = true;
                break;
            default:
                std::cout << "Invalid output, please try again." << std::endl;
                break;
        }
    }
}

void admin_messages(Company * c){
    int counter;
    bool atLeast1, end = false;
    std::string text;
    std::vector<RegisteredClient *> clients;
    Date date = getDate();
    do {
        counter = 0;
        atLeast1 = false;
        std::cout << "Messages:" << std::endl
                  << "\t1. Answer messages" << std::endl
                  << "\t2. Chats" << std::endl
                  << "\t3. Exit" << std::endl;
        getline(std::cin, text, '\n');
        if (text.size() != 1) {
            std::cout << "Invalid output, please try again." << std::endl;
            continue;
        }
        switch (text[0]) {
            case '1': {
                if(c->noMessages()){
                    std::cout << "There are no messages to answer, please try again later" << std::endl;
                    break;
                }
                c->showMessages();
                std::cout << "Which message do you want to answer? ";
                getline(std::cin, text, '\n');
                if (text.size() != 1 || std::stoi(text) >= c->getNumberMessages()) {
                    std::cout << "Invalid output, please try again." << std::endl;
                    continue;
                }
                int cnt = 0;
                for (auto elem: c->getMessagesToProcess()) {
                    if (cnt == std::stoi(text)){
                        RegisteredClient * temp = dynamic_cast<RegisteredClient *>(c->getOnlineStore()->getClients()[c->getOnlineStore()->findRegisteredClient(elem->getEMail())]);
                        openChat("admin", temp, c, &date);
                        break;
                        }
                    cnt++;
                }
                break;
            }
            case '2':
            {
                for (auto elem:c->getOnlineStore()->getClients()) {
                    auto temp = dynamic_cast<RegisteredClient *>(elem);
                    if (temp != nullptr) {
                        atLeast1 = true;
                        if (!temp->noMessages()) {
                            std::cout << counter << ".\t" << temp->getEmail() << "\t\t";
                            if (temp->getLastMessage()->getMsg().size() > 30)
                                std::cout << temp->getLastMessage()->getMsg().substr(0, 30) << "..." << std::endl;
                            else std::cout << temp->getLastMessage()->getMsg() << std::endl;
                        } else
                            std::cout << counter << ".\t" << temp->getEmail() << "\t\t" << "///////////////" << std::endl;
                        clients.push_back(temp);
                        counter++;
                    }
                }
                std::cout << counter + 1 << ".\t" << "Back" << std::endl;
                if (atLeast1) {
                    std::cout << "Which chat do you want to open? ";
                    getline(std::cin, text, '\n');
                    if(text.size() == 1 && std::stoi(text) == counter + 1){ end = true; break;}
                    else if (text.size() != 1 || std::stoi(text) >= counter) {
                        std::cout << "Invalid output, please try again." << std::endl;
                        continue;
                    }
                    openChat("admin", clients[std::stoi(text)], c, &date);
                }
                break;
            }
            case '3': {
                end = true;
                break;
            }
            default: {
                std::cout << "Invalid output, please try again." << std::endl;
                break;
            }
        }
    }while(!end);
}

void openChat(std::string who, RegisteredClient * client, Company * c, Date * date){
    std::string text;
    if(!client->noMessages() && *date < client->getLastMessage()->getDate()){
        std::cout << "Your date is invalid. This chat has messages that occur in " << client->getLastMessage()->getDate()
                  << " and your date is: " << *date << std::endl;
        return;
    }
    client->showMessages();
    std::cout << std::endl;
    if(who == "admin") std::cout << who << ':' << std::endl;
    else std::cout << client->getEmail() << ':' << std::endl;
    while(getline(std::cin, text, '\n')){
        if(text == "_BACK_")
            break;
        if (who == "admin") {
            auto aM = new AdminMessage(text, *date);
            c->processMessage(client->getEmail(), aM);
        } else {
            auto cM = new ClientMessage(text, client->getEmail(), *date);
            c->addMessage(client, cM);
        }
    }
}

void admin(Company * c){
    std::cin.ignore(1);
    std::string user, pass, text;
    bool end = false;
    do {
        std::cout << "(Press enter twice to go back)" << std::endl;
        std::cout << "Username:";
        getline(std::cin, user, '\n');
        std::cout << "Password:";
        getline(std::cin, pass, '\n');
        if (pass == ADMIN_PASS && user == ADMIN_USER) {
            break;
        }
        else if(pass.empty() && user.empty()) {
            end = true;
            break;
        }
        std::cout << "Invalid username or password, please try again." << std::endl;
    }while(true);
    while(!end){
        end = false;
        std::cout << "\tWhat do you want to do?" << std::endl;
        std::cout << "\t\t1. See statistics" << std::endl
                  << "\t\t2. Transactions" << std::endl
                  << "\t\t3. Products" << std::endl
                  << "\t\t4. Clients" << std::endl
                  << "\t\t5. Stores" << std::endl
                  << "\t\t6. Messages" << std::endl
                  << "\t\t7. Restock" << std::endl
                  << "\t\t8. Fleet Management" << std::endl
                  << "\t\t9. Exit" << std::endl;
        getline(std::cin, text, '\n');
        if(text.size() != 1) {
            std::cout << "Invalid output, please try again." << std::endl;
            continue;
        }
        switch(text[0]){
            case '1':
                companyStats(c);
                break;
            case '2':
                transactions(c);
                break;
            case '3':
                products(c);
                break;
            case '4':
                admin_clients(c);
                break;
            case '5':
                stores(c);
                break;
            case '6':
                admin_messages(c);
                break;
            case '7':
                admin_restock(c);
                break;
        	case '8':
				admin_fleet(c);
        		break;
            case '9':
                end = true;
                break;
            default:
                std::cout << "Invalid output, please try again." << std::endl;
                break;
        }
    }
}

void paymentMethod(Company * c,Client * client, Transaction * transaction, bool exists) {
    char paymentOption;
    bool option4 = false;
    bool done = false;
    do {
        std::cout << "\tInsert the way you wish to pay:" << std::endl <<
                  "\t\t1. MBWay" << std::endl <<
                  "\t\t2. ATM" << std::endl <<
                  "\t\t3. Credit Card" << std::endl;
        if (exists && dynamic_cast<RegisteredClient *>(client) != nullptr &&
            dynamic_cast<RegisteredClient *>(client)->paymentMethodsNotEmpty()) {
            std::cout << "\t\t4. Choose from already used payment methods" << std::endl;
            option4 = true;
        }
        std::cin >> paymentOption;
        switch (paymentOption) {
            case '1': {
                std::cout << "Insert the phone number you wish to use:" << std::endl;
                unsigned long int phoneNumber;
                std::cin >> phoneNumber;
                try {
                    Payment *mbway = new MBWay(phoneNumber);
                    dynamic_cast<ClientTransaction *>(transaction)->setPaymentMethod(mbway);

                    if (dynamic_cast<RegisteredClient *>(client) != nullptr) {
                        try {
                            dynamic_cast<RegisteredClient *>(client)->addPaymentMethod(mbway);
                            c->addTransaction(transaction);
                            std::cout << mbway->printPayment() << std::endl;
                            std::cout << "Your order has been successfully processed." << std::endl;
                            done= true;
                            break;
                        }
                        catch (PaymentMethodAlreadyExists &paymentMethodAlreadyExists) {
                            std::cout << paymentMethodAlreadyExists
                                      << " Would you like to continue with the purchase? (yes/no)" << std::endl;
                            std::string s;
                            std::cin >> s;
                            if (s == "yes") {
                                c->addTransaction(transaction);
                                std::cout << mbway->printPayment() << std::endl;
                                std::cout << "Your order has been successfully processed."<< std::endl;
                                done= true;
                                break;
                            } else if (s == "no") {
                                std::cout << "Your order has not been processed, try another option."<< std::endl;
                                delete mbway;
                                break;
                            }

                        }
                    }
                    else{
                        c->addTransaction(transaction);
                        std::cout << mbway->printPayment() << std::endl;
                        std::cout << "Your order has been successfully processed." << std::endl;
                        done= true;
                        break;
                    }

                }
                catch (InvalidPayment &invalidPayment) {
                    std::cout << invalidPayment << std::endl;
                    break;
                }
                break;
            }
            case '2': {
                Payment *atm = new MultiBanco();
                dynamic_cast<ClientTransaction *>(transaction)->setPaymentMethod(atm);
                c->addTransaction(transaction);
                std::cout << atm->printPayment() << std::endl;
                std::cout << "Your order has been successfully processed. ";
                done=true;
                break;
            }
            case '3': {
                long long cardNumber;
                long long CVV;
                Date validity;
                std::cout << "Insert the card number and the respective verification value (CVV):" << std::endl;
                std::cin >> cardNumber >> CVV;

                unsigned short int month;
                unsigned int year;
                std::cout << "Insert the credit card validity date (month/year):" << std::endl;
                std::cin >> month;
                std::cin.ignore();
                std::cin >> year;
                try {
                    validity.setMonth(month);
                }
                catch (InvalidDate &invalidDate) {
                    std::cout << invalidDate << std::endl;
                    break;
                }
                validity.setYear(year);
                try {
                    Payment *creditCard = new CreditCard(cardNumber, CVV, validity);
                    dynamic_cast<ClientTransaction *>(transaction)->setPaymentMethod(creditCard);
                    if (dynamic_cast<RegisteredClient *>(client) != nullptr) {
                        try {
                            dynamic_cast<RegisteredClient *>(client)->addPaymentMethod(creditCard);
                            c->addTransaction(transaction);
                            std::cout << creditCard->printPayment() << std::endl;
                            std::cout << "Your order has been successfully processed." << std::endl;
                            done= true;
                            break;
                        }
                        catch (PaymentMethodAlreadyExists &paymentMethodAlreadyExists) {
                            std::cout << paymentMethodAlreadyExists
                                      << " Would you like to continue with the purchase? (yes/no)" << std::endl;
                            std::string s;
                            std::cin >> s;
                            if (s == "yes") {
                                c->addTransaction(transaction);
                                std::cout << creditCard->printPayment() << std::endl;
                                std::cout << "Your order has been successfully processed."<< std::endl;
                                done= true;
                                break;
                            } else if (s == "no") {
                                std::cout << "Your order has not been processed, try another option."<< std::endl;
                                delete creditCard;
                                break;
                            }

                        }
                    }
                    else{
                        c->addTransaction(transaction);
                        std::cout << creditCard->printPayment() << std::endl;
                        std::cout << "Your order has been successfully processed." << std::endl;
                        done= true;
                        break;
                    }
                }
                catch (InvalidPayment &invalidPayment) {
                    std::cout << invalidPayment << std::endl;
                    break;
                }
                break;
            }
            case '4': {
                if (option4) {
                    int i=0;
                    for (Payment * payment:dynamic_cast<RegisteredClient*>(client)->getPaymentMethods()) {
                        if (dynamic_cast<MBWay*>(payment)!= nullptr || dynamic_cast<CreditCard*>(payment)!= nullptr)
                            std::cout << std::to_string(i) << ". " << payment->printPayment() << std::endl;
                        i++;
                    }
                    std::cout << "Insert the one you wish to use (-1 if want to go back):"<< std::endl;
                    int index;
                    std::cin >> index;
                    if (index!=-1){
                        dynamic_cast<ClientTransaction *>(transaction)->setPaymentMethod(dynamic_cast<RegisteredClient*>(client)->getPaymentMethods()[index]);
                        c->addTransaction(transaction);
                        std::cout << "Your order has been successfully processed." << std::endl;
                        done=true;
                    }
                }
                break;
            }
            default: break;
        }
    }while (!done);
}

void clientDelivery(Company* company, Transaction* transaction) {
	std::cout << "Would you like to get home delivery? (yes/no)" << std::endl;
	std::string response; std::cin >> response;

	if (response == "yes") {
		dynamic_cast<ClientTransaction *>(transaction)->setHomeDelivery();
		if (company->addOrderToDispatch(transaction))
			std::cout << "Your Order shall be delivered at your Address." << std::endl;
		else
			std::cout << "Due to the size of your order, we are unable to deliver it to your address." << std::endl;
	}
}

void clientOperations(Company * c, Client * client,Date * date, bool exists){
    char client_op;
    std::vector<std::pair<Product*, unsigned int>> cart;
    Transaction* transaction= new ClientTransaction(*date, cart, c->getOnlineStore(), client->getNIF());
    do {
        std::cout << std::endl << "Welcome " << client->getName() << " to "<< c->getCompanyName() << "!!" << std::endl << std::endl
                  << "\tWhat do you want to do:" << std::endl <<
                  "\t\t1. See all products" << std::endl <<
                  "\t\t2. See the current basket" << std::endl <<
                  "\t\t3. Add to basket" << std::endl <<
                  "\t\t4. Edit the basket" << std::endl<<
                  "\t\t5. Proceed to checkout" << std::endl<<
                  "\t\t6. Leave without buying" << std::endl<<
                  "\t\t7. Contact us" << std::endl;


        std::cin >> client_op;
        switch (client_op) {
            case '1': {c->showProductsStats(false);
                break;
            }
            case '2':{
                std::cout << transaction->printTransaction() << std::endl;
                break;
            }
            case '3':{
                std::string description;
                unsigned quantity;

                std::cout << "Insert the product and the quantity you desire:" << std::endl;
                std::cin.ignore(100,'\n');
                getline(std::cin, description);
                std::cin >> quantity;
                try {
                    if(transaction->addProduct(new Product(description),quantity)){
                        std::cout << "\nThe product was successfully added to the basket." << std::endl;
                    }else{
                        std::cout << "\nProduct belongs to the basket, if you want to change its quantity try editing the basket." << std::endl;
                    }
                }
                catch (NotEnoughStock& stockError) {
                    std::cout << stockError << std::endl;
                    break;
                }
                catch (ProductDoesNotExist& prdtError) {
                    std::cout << prdtError << std::endl;
                    break;
                }
                break;
            }
            case '4':{
                std::string description;
                unsigned quantity;

                std::cout << "Insert the product and the quantity you desire to change to (0 in case you wish to remove the product):" << std::endl;
                std::cin.ignore(100,'\n');
                getline(std::cin, description);
                std::cin >> quantity;
                try {
                    transaction->changeQuantity(new Product(description),quantity);
                    std::cout << "\nThe product was successfully edited." << std::endl;
                }
                catch (NotEnoughStock& stockError) {
                    std::cout << stockError << std::endl;
                    break;
                }
                catch (ProductDoesNotExist& prdtError) {
                    std::cout << prdtError << std::endl;
                    break;
                }
                break;
            }
            case '5':{
                if (transaction->getCart().empty()){
                    std::cout << "\nYour basket is empty." << std::endl;
                }else{
                    std::cout << transaction->printTransaction() << std::endl;
                    paymentMethod(c,client,transaction,exists);
					clientDelivery(c, transaction);
                }
                std::cout << "Thanks for coming to "<< c->getCompanyName()<<"." << std::endl;
                client_op='6';
                break;
            }
            case '6':{
                std::cout << "Thanks for coming to "<< c->getCompanyName()<<"." << std::endl;
                break;
            }
            case '7':{
                auto temporary = dynamic_cast<RegisteredClient *>(client);
                if(temporary != nullptr){
                    std::cin.ignore();
                    openChat("client", temporary, c, date);
                }else{
                    std::cout << "To contact with us you must register in our system." << std::endl;
                }
            }

            default: break;

        }
    }while (client_op!='6');
}

void client(Company *c){
    bool validDate=false;
    Date* transactionDate = new Date;
    do {
        std::cout << "Insert the current date (day/month/year):" << std::endl;
        unsigned short int day;
        unsigned short int month;
        unsigned int year;
        std::cin >> day;
        std::cin.ignore();
        std::cin >> month;
        std::cin.ignore();
        std::cin >> year;
        try {
            transactionDate->setYear(year);
            transactionDate->setMonth(month);
            transactionDate->setDay(day);
            validDate= true;
        }
        catch (InvalidDate& invalidDate) {
            std::cout << invalidDate << std::endl;
        }
    }while (!validDate);
    char client_reg;
    int clientIndex;
    do {
        std::cout << std::endl << "Welcome to "<< c->getCompanyName()<<" store customer!!" << std::endl << std::endl
                  << "\tWould you like to make a registry in our system?" << std::endl <<
                  "\t\t1. Yes" << std::endl <<
                  "\t\t2. No" << std::endl <<
                  "\t\t3. I'm already registered" << std::endl <<
                  "\t\t4. Edit my information" << std::endl <<
                  "\t\t5. Go back" << std::endl;

        std::cin >> client_reg;
        switch (client_reg) {
            case '1':{
                std::string name, email;
                unsigned int nif;

                std::cout << "Insert your name, email and nif by order:" << std::endl;
                std::cin.ignore(100,'\n');
                getline(std::cin, name);
                getline(std::cin, email);
                std::cin >> nif;
                Client *client= new RegisteredClient(name, nif, email);
                try {
                    c->getOnlineStore()->addClient(client);
                    clientOperations(c, client,transactionDate,false);
                    client_reg='5';
                }
                catch(ClientAlreadyExists &error) {
                    clientIndex = error.getIndex();
                    if (dynamic_cast<RegisteredClient *>(c->getOnlineStore()->getClients()[clientIndex]) != nullptr) {
                        delete client;
                        std::cout << "Client is already registered in the system, try another option." << std::endl;
                    }
                    else {
                        c->getOnlineStore()->removeClient(clientIndex);
                        c->getOnlineStore()->addClient(client);
                        clientOperations(c, client, transactionDate, false);
                        client_reg = '5';
                    }
                }
                break;
            }

            case '2':{
                std::string name;
                unsigned int nif;

                std::cout << "Insert your name and nif by order:" << std::endl;
                std::cin.ignore(100,'\n');
                getline(std::cin, name);
                std::cin >> nif;
                auto client= new Client(name, nif);
                try{
                    c->getOnlineStore()->addClient(client);
                    clientOperations(c, client,transactionDate,false);
                    client_reg='5';
                }
                catch (ClientAlreadyExists &error) {
                    clientIndex = error.getIndex();
                    delete client;
                    if(c->getOnlineStore()->getClients()[clientIndex]->getName() != name){
                        std::cout << "Invalid correspondence between inserted name and nif." << std::endl;
                    }
                    else{
                        clientOperations(c, c->getOnlineStore()->getClients()[clientIndex], transactionDate, true);
                        client_reg='5';
                    }
                }
                break;
            }
            case '3':{
                unsigned int nif;

                std::cout << "Insert your nif :" << std::endl;
                std::cin >> nif;

                Client *client= new RegisteredClient("", nif, "");
                clientIndex = c->getOnlineStore()->findClient(client);
                if(clientIndex != -1){
                    if (dynamic_cast<RegisteredClient*>(c->getOnlineStore()->getClients()[clientIndex]) != nullptr)
                    {
                        clientOperations(c, c->getOnlineStore()->getClients()[clientIndex], transactionDate, true);
                        client_reg='5';
                    }
                    else{
                        std::cout << "The input nif belongs to an already existing client, although it is not registered you can do it by selecting the option to register." << std::endl;
                    }
                }
                else{
                    std::cout << "Client does not exist, try another option." << std::endl;
                }
                break;
            }
            case '4':{
                unsigned int nif;

                std::cout << "Insert your nif :" << std::endl;
                std::cin >> nif;
                auto client= new Client("", nif);
                clientIndex = c->getOnlineStore()->findClient(client);
                if(clientIndex != -1){
                    client=c->getOnlineStore()->getClients()[clientIndex];
                    if (dynamic_cast<RegisteredClient*>(client)!= nullptr)
                    {
                        //Registered
                        std::cout << "Current information:" << std::endl;
                        std::cout << "Name - "<< client->getName() << std::endl;
                        std::cout << "Email - "<< dynamic_cast<RegisteredClient*>(client)->getEmail() << std::endl << std::endl;
                        std::string modifyOperation, modifiedArgument;
                        std::cout << "Insert the parameter you want to change (name or email):" << std::endl;
                        std::cin >> modifyOperation;
                        std::cin.ignore(100,'\n');
                        if (modifyOperation=="name"){
                            std::cout << "Insert the new value for that parameter:" << std::endl;
                            getline(std::cin,modifiedArgument);
                            client->setName(modifiedArgument);
                            std::cout << "Change of name was successful" << std::endl;
                        }
                        else if (modifyOperation=="email"){
                            std::cout << "Insert the new value for that parameter:" << std::endl;
                            std::cin >> modifiedArgument;
                            dynamic_cast<RegisteredClient*>(client)->setEMail(modifiedArgument);
                            std::cout << "Change of email was successful" << std::endl;

                        }
                        else
                            std::cout << "Invalid change parameter" << std::endl;
                    }
                    else{
                        //Not registered
                        std::cout << "Current information:" << std::endl;
                        std::cout << "Name - "<< client->getName() << std::endl;
                        std::string modifyOperation, modifiedArgument;
                        std::cout << "Do you want to change the name (yes/no):" << std::endl;
                        std::cin >> modifyOperation;
                        std::cin.ignore(100,'\n');
                        if (modifyOperation=="yes"){
                            std::cout << "Insert the new value for name:" << std::endl;
                            getline(std::cin,modifiedArgument);
                            client->setName(modifiedArgument);
                            std::cout << "Change of name was successful" << std::endl;
                        }
                        else if (modifyOperation=="no"){
                            std::cout << "No changes were made to your information" << std::endl;

                        }
                        else
                            std::cout << "Invalid input" << std::endl;
                    }
                }
                else{
                    std::cout << "Client does not exist, try another option." << std::endl;
                }
                break;
            }

            default: break;
        }
    }while (client_reg!='5');
}

Date getDate(){
    bool validDate= false;
    Date result;
    do {
        std::cout << "Insert the current date (day/month/year):" << std::endl;
        unsigned short int day;
        unsigned short int month;
        unsigned int year;
        std::cin >> day;
        std::cin.ignore();
        std::cin >> month;
        std::cin.ignore();
        std::cin >> year;
        try {
            result = Date(day, month, year);
            validDate= true;
        }
        catch (InvalidDate& invalidDate) {
            std::cout << invalidDate << std::endl;
        }
    }while (!validDate);
    std::cin.ignore();
    return result;
}

void admin_restock(Company *c) {
    Date date=getDate();
    int counter=0, missingStock_index;
    bool end = false;
    std::string text;
    do {
        auto missing_stock(c->getMissingStock());
        if(missing_stock.empty()){
            std::cout << "No missing products." << std::endl;
            break;;
        }
        //Show missing products
        counter=0;
        std::cout << "Missing products(choose the one you want to restock):" << std::endl;
        std::cout <<std::endl <<  "\t Product / Quantity" << std::endl;
        for(std::pair<Product*,unsigned int> sN:missing_stock){
            std::cout << "\t" << counter << ". " << sN.first->getDescription() << " / " << sN.second << std::endl;
            counter++;
        }
        std::cout <<"(Press enter to leave)" << std::endl;
        //Get input
        getline(std::cin, text, '\n');
        if(text.empty()) break;
        if (text.size() != 1 || stoi(text)>=counter) {
            std::cout << "Invalid input, please try again." << std::endl;
            continue;
        }else{
            missingStock_index=stoi(text);
            //Show available suppliers
            int index=c->searchSuppliers(missing_stock[missingStock_index].first->getDescription());
            if(index==-1){
                std::cout << "No suppliers available" << std::endl;
                break;
            }else{
                do{
                    std::cout << "Choose an option:\n" << std::endl;
                    std::cout <<  "0. By ascending price" << std::endl;
                    std::cout <<  "1. By descending price" << std::endl;
                    getline(std::cin, text, '\n');
                    if (text=="0" || text=="1") {
                        break;
                    }else{
                        std::cout << "Invalid input, please try again.\n" << std::endl;
                    }
                }while(true);
                if(text=="0"){
                    //Show by price ascending
                    std::cout << "Available Suppliers:" << std::endl;
                    BSTItrIn<Supplier> iter(c->getSuppliers()[index]);
                    counter=0;
                    while (!iter.isAtEnd()){
                        std::cout << "\t" << counter << ". " << iter.retrieve().getName()<<  " (" << iter.retrieve().getPrice() <<"$)"  << std::endl;
                        counter++;
                        iter.advance();
                    }
                    //Get input
                    getline(std::cin, text, '\n');
                    if (text.size() != 1 || stoi(text)>=counter) {
                        std::cout << "Invalid input, please try again." << std::endl;
                        continue;
                    }else{
                        //Restock the item
                        BSTItrIn<Supplier> iter(c->getSuppliers()[index]);
                        counter=0;
                        while (!iter.isAtEnd()){
                            if(counter==stoi(text)){ //Found Supplier
                                if(c->repositionBySupplier(missing_stock[missingStock_index],date,iter.retrieve())){ //Successful restock
                                    c->removeMissingProduct(missingStock_index);
                                    std::cout << "Restock was successful." << std::endl;
                                    end=true;
                                    break;
                                }else{
                                    c->setMissingProductQuantity(missingStock_index, missing_stock[missingStock_index].second);
                                    std::cout << "The restock was partially successful, still missing some quantity." << std::endl;
                                    break;
                                }
                            }
                            counter++;
                            iter.advance();
                        }
                    }
                }else{
                    //Show by price descending
                    std::stack<Supplier> supplierStack;
                    std::cout << "Available Suppliers:" << std::endl;
                    BSTItrIn<Supplier> iter(c->getSuppliers()[index]);
                    counter=0;
                    while (!iter.isAtEnd()){
                        supplierStack.push(iter.retrieve());
                        iter.advance();
                    }
                    while (!supplierStack.empty()){
                        std::cout << "\t" << counter << ". " << supplierStack.top().getName()<<  " (" << supplierStack.top().getPrice() <<"$)"  << std::endl;
                        counter++;
                        supplierStack.pop();
                    }
                    //Get input
                    getline(std::cin, text, '\n');
                    if (text.size() != 1 || stoi(text)>=counter) {
                        std::cout << "Invalid input, please try again." << std::endl;
                        continue;
                    }else{
                        //Restock the item
                        BSTItrIn<Supplier> iter(c->getSuppliers()[index]);
                        text=to_string(counter-stoi(text)-1);
                        counter=0;
                        while (!iter.isAtEnd()){
                            if(counter==stoi(text)){ //Found Supplier
                                if(c->repositionBySupplier(missing_stock[missingStock_index],date,iter.retrieve())){ //Successful restock
                                    c->removeMissingProduct(missingStock_index);
                                    std::cout << "Restock was successful." << std::endl;
                                    end=true;
                                    break;
                                }else{
                                    c->setMissingProductQuantity(missingStock_index, missing_stock[missingStock_index].second);
                                    std::cout << "The restock was partially successful, still missing some quantity." << std::endl;
                                    break;
                                }
                            }
                            counter++;
                            iter.advance();
                        }
                    }
                }
            }
        }
    }while(!end);
}

void admin_fleet(Company * c) {
	bool end = false;
	std::string option;

	do {
		std::cout << "What you would like to do next?" << std::endl;
		std::cout << "\t\t1. View the Fleet" << std::endl;
		std::cout << "\t\t2. Send a Vehicle" << std::endl;
		getline(std::cin, option, '\n');

		switch (option[0]) {
			case '1':
				std::cout << c->showFleet();
				break;
			case '2':
				c->vanInTransit();
				c->showFleet();
				break;
			default:
				std::cout << "Invalid input, please try again." << std::endl;
		}

		if (option[0] == '1' || option[0] == '2') end = true;
	} while(!end);
}