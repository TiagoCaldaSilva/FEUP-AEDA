#include "Client.h"

// Client Class Implementation

Client::Client()
{
  name = "";
  nif = 0;
}

Client::~Client() = default;

Client::Client(const std::string& name, unsigned int nif)
{
    this->name = name;
    this->nif = nif;
}

std::string Client::getName() const
{
    return name;
}

unsigned int Client::getNIF() const
{
    return nif;
}

void Client::setName(const std::string& value)
{
    name = value;
}

void Client::setNIF(unsigned int value)
{
    nif = value;
}

bool Client::operator==(const Client& c2) const
{
    return nif == c2.nif;
}

bool Client::operator<(const Client& c2) const {
    return name < c2.name;
}

// RegisteredClient Class Implementation

long RegisteredClient::ID_VALUE = 0;

RegisteredClient::RegisteredClient() :Client(), ID(++ID_VALUE)
{
    eMail = "";
    paymentMethods.clear();
}

RegisteredClient::RegisteredClient(const std::string& name, unsigned int nif, const std::string& email) :Client(name, nif), ID(++ID_VALUE)
{
    eMail = email;
}

RegisteredClient::RegisteredClient(const std::string& name, unsigned int nif) :Client(name, nif), ID(++ID_VALUE){}

RegisteredClient::RegisteredClient(const std::string& name, unsigned int nif, const std::string& email, const std::vector<Payment *>& pay_method):Client(name, nif), ID(++ID_VALUE)
{
    eMail = email;
}

RegisteredClient::~RegisteredClient() {
    for (auto &p : paymentMethods)
        delete p;
    while(!messages.empty()){
        delete messages.front();
        messages.pop();
    }
}

std::string RegisteredClient::getEmail() const
{
    return eMail;
}

unsigned int RegisteredClient::getID() const
{
    return ID;
}

std::vector<Payment *> RegisteredClient::getPaymentMethods() const
{
    return paymentMethods;
}

void RegisteredClient::setEMail(const std::string& value)
{
    eMail = value;
}

void RegisteredClient::setPaymentMethods(const std::vector<Payment *>& value)
{
    paymentMethods = value;
}

void RegisteredClient::addPaymentMethod(Payment * p)
{
    for(Payment * _p: paymentMethods){
        if(paymentComparator(_p,p))
            throw PaymentMethodAlreadyExists();
    }
    paymentMethods.push_back(p);
}

bool RegisteredClient::operator==(const RegisteredClient& c2) const
{
    return ID == c2.ID;
}

bool RegisteredClient::paymentMethodsNotEmpty() const {
    for (auto payment:paymentMethods) {
        if (dynamic_cast<MBWay *>(payment) != nullptr || dynamic_cast<CreditCard *>(payment) != nullptr)
            return true;
    }
    return false;
}

bool paymentComparator(Payment * p1,Payment * p2){
    if (dynamic_cast<MBWay*>(p1)!= nullptr && dynamic_cast<MBWay*>(p2)!= nullptr)
        return dynamic_cast<MBWay*>(p1)->getPhoneNumber()==dynamic_cast<MBWay*>(p2)->getPhoneNumber();
    else if (dynamic_cast<CreditCard*>(p1)!= nullptr && dynamic_cast<CreditCard*>(p2)!= nullptr)
        return dynamic_cast<CreditCard*>(p1)->getCardNumber()==dynamic_cast<CreditCard*>(p2)->getCardNumber() && dynamic_cast<CreditCard*>(p1)->getCVV()==dynamic_cast<CreditCard*>(p2)->getCVV() && dynamic_cast<CreditCard*>(p1)->getCardValidity()==dynamic_cast<CreditCard*>(p2)->getCardValidity();
    return false;
}

void RegisteredClient::addMessage(Message * msg) {
    messages.push(msg);
}

Message * RegisteredClient::getLastMessage() {
    return messages.back();
}

std::queue<Message *> RegisteredClient::getMessages() const {
    return messages;
}

bool RegisteredClient::noMessages() const {
    return messages.empty();
}

void RegisteredClient::showMessages() const {
    std::queue<Message *> temp = messages;
    Message * last;
    if(temp.empty()){
        std::cout << "Hi! What do you want to tell us?" << std::endl;
    }
    std::cout << "(quote '_BACK_' to back to the client menu)" << std::endl;
    bool first = true;
    while(!temp.empty()){
        if(first){ temp.front()->printMessage(first); first = false; }
        else temp.front()->printMessage(last->messageType() != temp.front()->messageType() || !(last->getDate() == temp.front()->getDate()));
        last = temp.front();
        temp.pop();
    }
}

void RegisteredClient::removeMessage() {
    messages.pop();
}

void RegisteredClient::writeChat(std::ostream & out){
    while(!messages.empty()){
        messages.front()->writeMessageInFile(out);
        messages.pop();
    }
}

Message * RegisteredClient::getMessage(size_t index){
    std::queue<Message *> temp = messages;
    while(index){
        index--;
        temp.pop();
    }
    return temp.front();
}

void RegisteredClient::processLast(){
    auto temp = dynamic_cast<ClientMessage *>(messages.back());
    if(temp != nullptr){
        temp->processMessage();
    }
}