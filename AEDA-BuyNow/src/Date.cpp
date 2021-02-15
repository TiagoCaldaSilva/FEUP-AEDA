#include "Date.h"

// Date Class Implementation

Date::Date(unsigned short int day, unsigned short int month, unsigned int year) : day(day), month(month), year(year)
{
    try { dateHandler(true); }
    catch (const InvalidDate& invalidInput) { throw; }
}

Date::Date(const std::string& dateValue) {
    std::stringstream input(dateValue);
    char slash;
    input >> day >> slash >> month >> slash >> year;
    try { dateHandler(true); }
    catch (const InvalidDate& invalidInput) { throw; }
}

Date::~Date() = default;

std::string Date::printDate(bool printDay) const
{
    std::string res;
    if (printDay)
    {
        if (day < 10) res += '0' + std::to_string(day) + '/';
        else res += std::to_string(day) + '/';
    }
    if (month < 10) res += '0' + std::to_string(month) + '/';
    else res += std::to_string(month) + '/';

    return res += std::string(4 - std::to_string(year).size(), '0') + std::to_string(year);
}

void Date::setDay(unsigned short int newValueDay) {  day = newValueDay; dateHandler(false);}

unsigned short int Date::getDay() const { return day; }

void Date::setMonth(unsigned short newValueMonth) {month = newValueMonth; dateHandler(true); }

unsigned short int Date::getMonth() const { return month; }

void Date::setYear(unsigned int newValueYear) { year = newValueYear; }

unsigned int Date::getYear() const { return year; }

bool Date::isLeapYear() const
{
    if (year % 4 == 0)
    {
        if (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0)) return true;
        else return false;
    }
    return false;
}

void Date::dateHandler(bool checkMonth) const
{
    if (checkMonth && (month == 0 || month > 12))
        throw InvalidDate(MONTH_ERROR);
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (day == 0 || day > 31) throw InvalidDate(DAY_ERROR);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day == 0 || day > 30) throw InvalidDate(DAY_ERROR);
            break;
        case 2:
            if ((isLeapYear() && (day == 0 || day > 29)) || (day == 0 || day > 28)) throw InvalidDate(DAY_ERROR);
            break;
        default:
            throw InvalidDate(MONTH_ERROR);
    }
}

bool Date::operator<(const Date& rhsDate) const
{
    if (year < rhsDate.year) return true;
    if (year == rhsDate.year)
    {
        if (month < rhsDate.month) return true;
        if (month == rhsDate.month && day < rhsDate.day) return true;
    }
    return false;
}

bool Date::operator==(const Date &rhsDate) const
{
    return (year == rhsDate.year && month == rhsDate.month && day == rhsDate.day);
}

Date& Date::operator++()
{
    if (day < 28) { day++; return *this; }
    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            if (day == 31) { day = 1; month++; }
            else day++; break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (day == 30) { day = 1; month++; }
            else day++; break;
        case 12:
            if (day == 31) { day = 1; month = 1; year++; }
            else day++; break;
        case 2:
            if (this->isLeapYear())
            {
                if (day == 29) { day = 1; month = 3; }
                else day++;
            } else {
                if (day == 28) { day = 1; month = 3; }
                else day++;
            }
        default:
            throw InvalidDate(DAY_ERROR);
    }
    return *this;
}

Date& Date::operator--()
{
    if (day > 1) day--;
    else
    {
        switch(month) {
            case 4:
            case 6:
            case 8:
            case 9:
            case 11:
                day = 31; month--;
                break;
            case 5:
            case 7:
            case 10:
            case 12:
                day = 30; month--;
                break;
            case 1:
                day = 1; month = 12; year--;
                break;
            case 3:
                if (this->isLeapYear()) day = 29;
                else day = 28;
                month--; break;
            default:
                throw InvalidDate(DAY_ERROR);
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Date& date) { out << date.printDate(); return out; }
