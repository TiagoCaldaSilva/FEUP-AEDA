/*
 * Cinema.cpp
 */
#include "Cinema.h"

Cinema::Cinema(string nm, unsigned d, unsigned nr): name(nm), distance(d),
		numberOfRooms(nr),timetable(FilmTime(0,NULL, 0))
{}

Cinema::Cinema(string nm, unsigned d, unsigned nr, list<string> ls): name(nm), distance(d),
		numberOfRooms(nr),services(ls), timetable(FilmTime(0,NULL,0))
{}

Cinema::~Cinema() { }

string Cinema::getName() const
{ return name; }

unsigned Cinema::getDistance() const
{ return distance; }

list<string> Cinema::getServices() const
{ return services; }

BST<FilmTime> Cinema::getTimetable() const
{ return timetable; }

void Cinema::addService(string service1)
{ services.push_back(service1); }

void Cinema::addFilmTime(const FilmTime &ft1)
{ timetable.insert(ft1); }


// TODO

bool Cinema::operator<(const Cinema & cr) const
{
    if(distance == cr.distance){
        return services.size() < services.size();
    }return distance > cr.distance;
}


//a1
Film *Cinema::filmAtHour(unsigned &h1) const {
	Film *res = NULL;
	BSTItrIn<FilmTime> it(timetable);
	if(timetable.isEmpty()) return res;
	res = it.retrieve().getFilm();
	if(it.retrieve().getHour() > h1) return res;
	while(!it.isAtEnd()){
        if(it.retrieve().getHour() == h1){
            return it.retrieve().getFilm();
        }
        else if(it.retrieve().getHour() > h1){
            return res;
        }
        else
            res = it.retrieve().getFilm();
        it.advance();
	}
	return res;
}


//a2
bool Cinema::modifyHour(unsigned h1, unsigned room1, unsigned h2) {
	bool res = false;
	BSTItrIn<FilmTime> _it(timetable);
	if(timetable.isEmpty()) return false;
	if(_it.retrieve().getHour() > h1) return false;
	while(!_it.isAtEnd()){
	    if(room1 == _it.retrieve().getRoomID() && h2 == _it.retrieve().getHour())
	        return false;
	    _it.advance();
	}
    BSTItrIn<FilmTime> it(timetable);
	while(it.retrieve().getHour() <= h1 && !it.isAtEnd()){
	    if(it.retrieve().getHour() == h1 && room1 == it.retrieve().getRoomID()) {
            FilmTime temp(h2, it.retrieve().getFilm(), it.retrieve().getRoomID());
            timetable.remove(it.retrieve());
            timetable.insert(temp);
            return true;
        }
	    it.advance();
	}
	return res;
}


//a3
unsigned Cinema::addFilm(Film *f1, unsigned h1) {
	unsigned roomToUse = 0;
	BSTItrIn<FilmTime> it(timetable);
	while(!it.isAtEnd() && roomToUse <= numberOfRooms){
	    if(it.retrieve().getHour() == h1)
	        roomToUse++;
	    it.advance();
	}
	if(roomToUse >= numberOfRooms) return 0;
	FilmTime temp(h1, f1, roomToUse + 1);
    timetable.insert(temp);
	return roomToUse+1;
}






