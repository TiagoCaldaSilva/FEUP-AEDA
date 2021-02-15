#include "Payment.h"

// Class Payment Implementation

Payment::Payment() = default;

Payment::~Payment() = default;

std::ostream& operator<<(std::ostream& out, const Payment& paymentToPrint)
{
    out << paymentToPrint.printPayment(); return out;
}

// Class MBWay Implementation

MBWay::MBWay(unsigned long int phoneNumber) : Payment(), phoneNumber(phoneNumber)
{
    if (!this->verifyPayment()) throw InvalidPayment(MBW_ERROR);
}
MBWay::~MBWay() = default;

unsigned long int MBWay::getPhoneNumber() const{
    return phoneNumber;
}

std::string MBWay::printPayment() const
{
    std::string paymentMethodInfo, phoneStr = std::to_string(phoneNumber);

    // Data Privacy 101
    for (unsigned int index = 2; index < phoneStr.length() - 4; index++)
        phoneStr[index] = '*';
    paymentMethodInfo = "MBWay - " + phoneStr;
    return paymentMethodInfo;
}

bool MBWay::verifyPayment() const
{
    std::string phoneNumberStr = std::to_string(phoneNumber);
    bool validDigit;
    switch(phoneNumberStr[1]) {
        case '1':
        case '2':
        case '3':
        case '6':
            validDigit = true; break;
        default:
            validDigit = false;
    }
    return (phoneNumberStr[0] == std::to_string(FIRST_DIGIT_FROM_PHONE_NUMBER)[0] && validDigit && phoneNumberStr.length() == NUM_DIGITS_IN_PHONE_NUMBER);
}

std::string MBWay::writeToFile() const {
    return "MW " + std::to_string(phoneNumber);
}

// Class MultiBanco Implementation

MultiBanco::MultiBanco() : Payment() { reference = generateReference(); }

MultiBanco::MultiBanco(unsigned long int reference) : Payment(), reference(reference)
{
    if (!this->verifyPayment()) throw InvalidPayment(MB_ERROR);
}

MultiBanco::~MultiBanco() = default;

unsigned long int MultiBanco::generateReference()
{
    reference = 0;
    for (unsigned int digit = 0; digit < NUM_DIGITS_IN_REFERENCE; digit++)
        reference += rand() % 10 * pow(10, digit);

    return reference;
}
unsigned long int MultiBanco::getReference() const { return reference; }

std::string MultiBanco::printPayment() const { return "MB - " + std::to_string(reference); }

bool MultiBanco::verifyPayment() const { return std::to_string(reference).length() == NUM_DIGITS_IN_REFERENCE; }

std::string MultiBanco::writeToFile() const{
    return "MB " + std::to_string(reference);
}

// Class CreditCard Implementation

CreditCard::CreditCard(long long cardNumber, unsigned short int CVV, const Date& validity) : Payment(), cardNumber(cardNumber), CVV(CVV), validity(validity)
{
    if (!this->verifyPayment()) throw InvalidPayment(CC_ERROR);
}

const Date& CreditCard::getCardValidity() const {
    return validity;
}

long long CreditCard::getCardNumber() const {
    return cardNumber;
}

unsigned short int CreditCard::getCVV() const {
    return CVV;
}

CreditCard::~CreditCard() = default;

std::string CreditCard::printPayment() const
{
    std::string paymentMethodInfo, CCNumberStr = std::to_string(cardNumber);

    // Data Privacy 101
    for (unsigned int index = 3; index < CCNumberStr.length() - 4; index++)
        CCNumberStr[index] = '*';
    paymentMethodInfo = "Credit Card - " + validity.printDate(false) + ' ' + CCNumberStr + ' ' + std::to_string(CVV);
    return paymentMethodInfo;
}
bool CreditCard::verifyPayment() const
{
    return std::to_string(cardNumber).length() == NUM_DIGITS_CARD_NUMBER && std::to_string(CVV).length() == NUM_DIGITS_CVV;
}

std::string CreditCard::writeToFile() const {
    std::string result = "CC ", month = std::to_string(validity.getMonth()), year = std::to_string(validity.getYear());
    return "CC " + std::string(2 - month.size(), '0') + month + '/' + std::string(4 - year.size(), '0') + year + ' ' + std::to_string(cardNumber) + ' ' + std::to_string(CVV);
}