#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include <sstream>
#include "Exceptions.h"

#define MONTH_ERROR "Invalid Month Value."
#define DAY_ERROR "Invalid Day Value."

/**
 * @class Date
 */
class Date {
private:
    unsigned short int day;
    unsigned short int month;
    unsigned int year;
public:
  /**
   * @brief Class Constructor
   * @param day For the day attribute
   * @param month For the month attribute
   * @param year For the year attribute
   * @throw InvalidDate If Date is somehow invalid
   */
  explicit Date(unsigned short int day = 1, unsigned short int month = 1, unsigned int year = 2020);
  /**
   * @brief Class Constructor
   * @param dateValue String in format dd/mm/yyyy
   * @throw InvalidDate If Date is somehow invalid
   */
  explicit Date(const std::string& dateValue);
  /**
   * @brief Default Destructor
   */
  virtual ~Date();
  /**
   * @brief Specific method to intercept invalid Dates
   * @param checkMonth If true verifies if month is a valid input
   * @throw InvalidDate If date is in some way invalid
   */
  void dateHandler(bool checkMonth) const;
  /**
   * @brief Prints the Date object
   * @param printDay If true, prints the day of the Date Object
   * @return String with the Date in one of the following format (dd/mm/yyyy) or (mm/yyyy)
   */
  std::string printDate(bool printDay = true) const;
  /**
   * @return Bool true if rhsDate is more recent than this->Date
   * @param  rhsDate Date to be compared
   */
  bool operator<(const Date& rhsDate) const;
  /**
   * @return Bool true if rhsDate and this->Date are the same
   * @param  rhsDate Date to be compared
   */
  bool operator==(const Date& rhsDate) const;
  /**
   * @brief Increments the value of the date by one day
   * @return This Date with the value changed (pre-fix notation)
   * @throw InvalidDate If somehow the operation does not occur correctly
   */
  Date& operator++();
  /**
   * @brief Decrements the value of the date by one day
   * @return This Date with the value changed (pre-fix notation)
   * @throw InvalidDate If somehow the operation does not occur correctly
   */
  Date& operator--();
  /**
   * @brief Set the value of day
   * @param newValueDay The new value of day
   * @throw InvalidDate If day is invalid
   */
  void setDay(unsigned short newValueDay);
  /**
   * @brief Get the value of day
   * @return The value of day
   */
  unsigned short int getDay() const;
  /**
   * @brief Set the value of month
   * @param newValueMonth The new value of month
   * @throw InvalidDate If month is invalid
   */
  void setMonth(unsigned short int newValueMonth);
  /**
   * @brief Get the value of month
   * @return The value of month
   */
  unsigned short int getMonth() const;
  /**
   * @brief Set the value of year
   * @param newValueYear The new value of year
   * @throw InvalidDate If year is invalid
   */
  void setYear(unsigned int newValueYear);
  /**
   * @brief Get the value of year
   * @return The value of year
   */
  unsigned int getYear() const;
  /**
   * @brief Determines if a given year is a leap year or not
   * @return True if leap year, false otherwise
   */
  bool isLeapYear() const;
  /**
   * @brief Writes the date to out
   * @param out Ostream to be writen the date
   * @param date Date that should be used
   * @return Param out with the date inside
   */
  friend std::ostream& operator<<(std::ostream& out, const Date& date);
};

#endif // DATE_H
