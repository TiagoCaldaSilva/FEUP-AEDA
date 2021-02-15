#include "Van.h"

Van::Van(std::string& plate, unsigned int totalCapacity, unsigned int remainingCapacity) : plate(plate), totalCapacity(totalCapacity), remainingCapacity(remainingCapacity)
{
    currentLoad = totalCapacity - remainingCapacity;
}

std::string Van::getVanPlate() const { return plate; }
unsigned int Van::getTotalCapacity() const { return totalCapacity; }
unsigned int Van::getRemainingCapacity() const { return remainingCapacity; }
unsigned int Van::getCurrentLoad() const { return currentLoad; }

void Van::loadOrder(unsigned int orderCapacity) {
    // throws an exception whenever the order exceeds the van's capacity
    if (remainingCapacity + orderCapacity > totalCapacity)
        throw VanAlreadyFull();

    remainingCapacity -= orderCapacity;
    currentLoad += orderCapacity;
}

void Van::removeOrder(unsigned int orderCapacity) {
    if (currentLoad - orderCapacity < 0)
        throw VanAlreadyEmpty();

    remainingCapacity += orderCapacity;
    currentLoad -= orderCapacity;
}

void Van::sendVan(bool forcedSent) {
    if (forcedSent) {
		remainingCapacity = totalCapacity;
		currentLoad = 0;
    } else {
        if ((double) currentLoad / totalCapacity >= 0.9) {
			remainingCapacity = totalCapacity;
			currentLoad = 0;
		}

        // Must not send with less than 90% occupation
        else
            throw VanNotReady((int)((currentLoad / totalCapacity) * 100));
    }
}


bool Van::operator==(const Van& vanCompared) const {

    return plate == vanCompared.plate;
}

bool Van::operator<(const Van& vanCompared) const {
    if (remainingCapacity == vanCompared.remainingCapacity) {

        if (currentLoad == vanCompared.currentLoad) {

            if (totalCapacity == vanCompared.totalCapacity)
                return plate < vanCompared.plate;

            return totalCapacity < vanCompared.totalCapacity;
        }
        return currentLoad < vanCompared.currentLoad;
    }
    return remainingCapacity > vanCompared.remainingCapacity;
}
