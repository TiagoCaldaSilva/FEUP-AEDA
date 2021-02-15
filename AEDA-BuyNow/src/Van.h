#ifndef AEDA_BUYNOW_VAN_H
#define AEDA_BUYNOW_VAN_H

#include "Date.h"
#include <fstream>

/**
 * @class Van
 */
class Van {
private:
    std::string plate;
    unsigned int totalCapacity;
    unsigned int remainingCapacity;
    unsigned int currentLoad;

public:

    // Should plate id be unique or not???
    /**
     * @brief Van's Constructor
     * @param plate String Identifying the Van
     * @param totalCapacity Value of the Van's total Capacity
     */
    Van(std::string& plate, unsigned int totalCapacity, unsigned int remainingCapacity);

    /**
     * @brief Get the Van's Plate
     * @return Van's Plate as a string
     */
    std::string getVanPlate() const;
    /**
     * @brief Get Total Capacity Value
     * @return Total Capacity Value
     */
    unsigned int getTotalCapacity() const;
    /**
     * @brief Get Remaining Capacity Value
     * @return Remaining Capacity Value
     */
    unsigned int getRemainingCapacity() const;
	/**
	 * @brief Get Current Load Value
	 * @return Current Load Value
	 */
    unsigned int getCurrentLoad() const;
    /**
     * @brief Loads an Order to a given Van
     * @param orderCapacity Volume occupied by the Order
     * @throw VanAlreadyFull if the van is full
     */
    void loadOrder(unsigned int orderCapacity);
    /**
     * @brief Removes an Order to a given Van
     * @param orderCapacity Volume occupied by the Order
     * @throw VanAlreadyEmpty if the orderCapacity passed as argument is greater the the currentLoad
     */
    void removeOrder(unsigned int orderCapacity);

    /**
     * @brief Sends a Van to deliver its corresponding Orders
     * @param forcedSent True whether or not is was forced sent by the Admin
     */
    void sendVan(bool forcedSent);

    /**
     * @param vanCompared Van to be compared
     * @return True if the compared vans are equal, otherwise false
     */
    bool operator==(const Van& vanCompared) const;
    /**
     * @param vanCompared Van to be compared
     * @return True if the remainingCapacity of this is bigger than remainingCapacity of vanCompared, else false
     */
    bool operator<(const Van& vanCompared) const;
};

#endif //AEDA_BUYNOW_VAN_H
