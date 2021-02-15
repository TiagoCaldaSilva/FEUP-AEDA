/*
 * CinemaFinder.cpp
 */

#include "CinemaFinder.h"
#include "Cinema.h"
#include "Film.h"
#include <algorithm>

CinemaFinder::CinemaFinder() { }

CinemaFinder::~CinemaFinder() { }

void CinemaFinder::addFilm(Film *f1) {
	FilmPtr fp1;
	fp1.film = f1;
	films.insert(fp1);
}

void CinemaFinder::addCinema(const Cinema &c1)
{ cinemas.push(c1); }

tabHFilm CinemaFinder::getFilms() const
{ return films; }

priority_queue<Cinema> CinemaFinder::getCinemas() const
{ return cinemas; }


// TODO


//b1
list<string> CinemaFinder::filmsWithActor(string actorName) const {
	list<string> res;
	for(auto elem:films){
	    if(elem.film->getActors().empty()) continue;
	    for(auto x:elem.film->getActors())
	        if(x == actorName)
	            res.push_back(elem.film->getTitle());
	}
	return res;
}


//b2
void CinemaFinder::addActor(string filmTitle, string actorName) {
    for(auto elem:films){
        if(elem.film->getTitle() == filmTitle){
            Film * temp = new Film(elem.film->getTitle(), elem.film->getActors());
            temp->addActor(actorName);
            films.erase(elem);
            FilmPtr x{temp};
            films.insert(x);
            return;
        }
    }
    list<string> temporary_list;
    temporary_list.push_back(actorName);
    Film * z = new Film(filmTitle, temporary_list);
    FilmPtr y{z};
    films.insert(y);
}


//c1
string CinemaFinder::nearestCinema(string service1) const {
	string cName="";
	if(cinemas.empty()) return cName;
	priority_queue<Cinema> temp=cinemas;
	while(!temp.empty()){
	    Cinema temporary = temp.top();
	    for(auto elem:temporary.getServices()){
	        if(elem == service1)
	            return temporary.getName();
	    }
	    temp.pop();
	}
	return cName;
}


//c2
void CinemaFinder::addServiceToNearestCinema(string service1, unsigned maxDistance) {
    if(cinemas.empty()) throw CinemaNotFound();
    if(cinemas.top().getDistance() > maxDistance) throw CinemaNotFound();
    Cinema temp = cinemas.top();
    cinemas.pop();
    temp.addService(service1);
    cinemas.push(temp);
}
