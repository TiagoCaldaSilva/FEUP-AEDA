#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>
#include <algorithm>

class NoSuchFloorException{
private:
    int floor;
public:
    NoSuchFloorException(int f){floor = f;}
    int getFloor() const {return floor;}
};

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if(chambers.size() == maxCapacity)
        return 0;
    for(Chamber * c:chambers)
    {
        if(*c == *chamber)
            return 0;
    }
    chambers.push_back(chamber);
    return 1;
}

//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    for (unsigned int p = 1; p < chambers.size(); p++)
    {
        Chamber * tmp = chambers[p];
        int j;
        for (j = p; j > 0 && tmp->getCode() <= chambers[j-1]->getCode(); j--) {
            if ((tmp->getCode() == chambers[j - 1]->getCode()) && (tmp->getFloor() > chambers[j - 1]->getFloor()))
                chambers[j] = chambers[j - 1];
            else if (tmp->getCode() != chambers[j - 1]->getCode())
                chambers[j] = chambers[j - 1];
        }
        chambers[j] = tmp;
    }

    //Ver como ordenar pointer mais facilmente:
/*   sort(chambers.begin(),chambers.end(),[](Chamber* chamber1, Chamber* chamber2)
    {return (*chamber1)<(*chamber2);});*/
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {
    Chamber *c_ = new Chamber(code, floor);
    for (int i = 0; i < chambers.size(); i++) {
        if (*chambers[i] == *c_) {
            c_ = chambers[i];
            chambers.erase(chambers.begin() + i);
            return c_;
        }
    }

    throw NoSuchChamberException();
}

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    float total;
    int nChamber = 0;
    for(Chamber * c:chambers)
    {
        if(c->getFloor() == floor) {
            total += c->getArea();
            nChamber++;
        }
    }
    if(!nChamber)
        throw NoSuchFloorException(floor);
    return total / nChamber;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){

    Chamber* _find = new Chamber(code, floor);
    for(Chamber * c:chambers)
        if(*c == *_find){
            if(c->getReservation())
                return 0;
            c->setReservation(1);
            reservationsDone.push_back(*c);
            return 1;
        }

    return false;
}

//TODO
template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> res;
    for(Chamber *c:chambers)
        if(find(reservationsDone.begin(), reservationsDone.end(), *c) == reservationsDone.end())
            res.push_back(*c);
    return res;
}


#endif /* SRC_HOTEL_H_ */
