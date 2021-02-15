#include "CinemaFinder.h"

void test_a1() {
	Cinema c1("NS",0,5);

	Film *f1 = new Film("The Last Witch Hunter");
	Film *f2 = new Film("Bridge of Spie");
	Film *f3 = new Film("Hotel Transylvania");
	Film *f4 = new Film("The Good Dinosaur");

	Film *f0=NULL;
	unsigned hf = 20;

	Film *f = c1.filmAtHour(hf);
	std::cout << f0 << '/' << f << std::endl;

	c1.addFilmTime(FilmTime(20,f1,1));

	f = c1.filmAtHour(hf);
	std::cout << f1<< '/' << f << std::endl;
	hf=19;
	f = c1.filmAtHour(hf);
	std::cout << f0 << '/' << f << std::endl;

	c1.addFilmTime(FilmTime(22,f2,1));
	c1.addFilmTime(FilmTime(18,f3,1));
	c1.addFilmTime(FilmTime(15,f4,1));

	hf=18;
	f = c1.filmAtHour(hf);
	std::cout << f3<< '/' << f << std::endl;
	std::cout << 18<< '/' << hf<< std::endl;

	hf=23;
	f = c1.filmAtHour(hf);
	std::cout << f2<< '/' << f<<std::endl;
	std::cout << 22<< '/' << hf << std::endl;

	hf=11;
	f = c1.filmAtHour(hf);
	std::cout << f0<< '/' << f << std::endl;
}


void test_a2() {
	Cinema c1("NS",0,5);

	Film *f1 = new Film("The Last Witch Hunter");
	Film *f2 = new Film("Bridge of Spie");
	Film *f3 = new Film("Hotel Transylvania");
	Film *f4 = new Film("The Good Dinosaur");

	bool res = c1.modifyHour(15,3,20);
	std::cout << false << '/' << res << std::endl;

	c1.addFilmTime(FilmTime(15,f1,3));
	c1.addFilmTime(FilmTime(20,f3,3));
	c1.addFilmTime(FilmTime(15,f2,2));
	c1.addFilmTime(FilmTime(18,f4,3));

	res = c1.modifyHour(15,3,20);
	std::cout << false << '/' << res << std::endl;

	res = c1.modifyHour(10,3,12);
	std::cout << false << '/' << res << std::endl;

	BST<FilmTime> timet1 = c1.getTimetable();
	FilmTime ft1 = timet1.findMin();
	std::cout << f2 << '/' << ft1.getFilm() << std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f1 << '/' << ft1.getFilm() <<std::endl;

	res = c1.modifyHour(15,3,19);
	std::cout << true << '/' << res << std::endl;

	timet1 = c1.getTimetable();
	ft1 = timet1.findMin();
	std::cout << f2<< '/' << ft1.getFilm() <<std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f4 << '/' << ft1.getFilm() << std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f1<< '/' << ft1.getFilm() << std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f3<< '/' << ft1.getFilm() << std::endl;
	timet1.remove(ft1);
	std::cout << true << '/' << timet1.isEmpty() << std::endl;
}


void test_a3() {
	Cinema c1("NS",0,3);

	Film *f1 = new Film("The Last Witch Hunter");
	Film *f2 = new Film("Bridge of Spie");
	Film *f3 = new Film("Hotel Transylvania");
	Film *f4 = new Film("The Good Dinosaur");

	unsigned room1 = c1.addFilm(f2,15);
	std::cout << 1<< '/' << room1<<std::endl;

	room1 = c1.addFilm(f2,10);
	std::cout << 1<< '/' << room1<<std::endl;

	room1 = c1.addFilm(f1,18);
	std::cout << 1<< '/' << room1 << std::endl;

	room1 = c1.addFilm(f3,10);
	std::cout << 2<< '/' << room1 << std::endl;

	room1 = c1.addFilm(f4,10);
	std::cout << 3<< '/' << room1 << std::endl;

	room1 = c1.addFilm(f1,10);
	std::cout << 0<< '/' << room1 << std::endl;

	BST<FilmTime> timet1 = c1.getTimetable();
	FilmTime ft1 = timet1.findMin();
	std::cout << f2<< '/' << ft1.getFilm() << std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f3<< '/' << ft1.getFilm()<<std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f4<< '/' << ft1.getFilm()<<std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f2<< '/' << ft1.getFilm()<<std::endl;
	timet1.remove(ft1);
	ft1 = timet1.findMin();
	std::cout << f1<< '/' << ft1.getFilm()<<std::endl;
	timet1.remove(ft1);
	std::cout << true<< '/' << timet1.isEmpty()<<std::endl;
}


void test_b1() {
	CinemaFinder cf1;

	list<string> actors1;
	actors1.push_back("Vin Diesel"); actors1.push_back("Rose Leslie"); actors1.push_back("Elijah Wood");
	list<string> actors2;
	actors2.push_back("Tom Hanks"); actors2.push_back("Mark Rylance"); actors2.push_back("Scott Shepherd");
	actors2.push_back("Amy Ryan"); actors2.push_back("Sebastian Koch"); actors2.push_back("Alan Alda");
	list<string> actors3;
	actors3.push_back("Amy Ryan");

	Film *f1 = new Film("The Last Witch Hunter", actors1);
	Film *f2 = new Film("Bridge of Spie", actors2);
	Film *f3 = new Film("Hotel Transylvania", actors3);
	Film *f4 = new Film("The Good Dinosaur");

	list<string> res;

	res = cf1.filmsWithActor("Vin Diesel");
	std::cout << 0<< '/' << res.size()<<std::endl;

	cf1.addFilm(f1);
	cf1.addFilm(f2);
	cf1.addFilm(f3);
	cf1.addFilm(f4);

	res = cf1.filmsWithActor("Tom Hanks");
	std::cout << 1 << '/' <<res.size() << std::endl;
	std::cout << "Bridge of Spie" << '/' <<res.front() << std::endl;

	res = cf1.filmsWithActor("Amy Ryan");
	std::cout << 2<< '/' << res.size() << std::endl;

	string s1,s2;
	if (res.front()=="Bridge of Spie") { s1=res.front(); s2=res.back(); }
	else { s1=res.back(); s2=res.front(); }
	std::cout << "Bridge of Spie"<< '/' << s1 << std::endl;
	std::cout << "Hotel Transylvania"<< '/' << s2 << std::endl;

	res=cf1.filmsWithActor("Daniel Craig");
	std::cout << 0<< '/' << res.size() << std::endl;
}


void test_b2() {
	CinemaFinder cf1;

	list<string> actors1;
	actors1.push_back("Vin Diesel"); actors1.push_back("Rose Leslie"); actors1.push_back("Elijah Wood");
	list<string> actors2;
	actors2.push_back("Tom Hanks"); actors2.push_back("Mark Rylance"); actors2.push_back("Scott Shepherd");
	actors2.push_back("Amy Ryan"); actors2.push_back("Sebastian Koch"); actors2.push_back("Alan Alda");

	Film *f2 = new Film("Bridge of Spie", actors2);
	Film *f4 = new Film("The Good Dinosaur");


	cf1.addActor("Hotel Transylvania", "Daniel Craig");
	std::cout << 1<< '/' <<cf1.getFilms().size()<< std::endl;

	cf1.addFilm(f2);
	cf1.addFilm(f4);
	std::cout << 3<< '/' <<cf1.getFilms().size() << std::endl;

	cf1.addActor("Bridge of Spie", "Daniel Craig");
	std::cout << 3 << '/' << cf1.getFilms().size() << std::endl;

	FilmPtr fxPtr;
	fxPtr.film=f2;
	tabHFilm tabf = cf1.getFilms();
	std::cout << 7<< '/' << tabf.find(fxPtr)->film->getActors().size() << std::endl;
}


void test_c1() {
	CinemaFinder cf1;

	std::cout << ""<< '/' << cf1.nearestCinema("estacionamento") << std::endl;

	Cinema c1("NS", 20, 4);
	c1.addService("estacionamento");
	c1.addService("restaura��o");
	c1.addService("comercio");

	Cinema c2("Arrabida", 10, 4);
	c2.addService("estacionamento");

	Cinema c3("PN", 20, 4);
	c3.addService("estacionamento");
	c3.addService("restaura��o");

	Cinema c4("GS", 8, 4);

	cf1.addCinema(c1);
	cf1.addCinema(c2);
	cf1.addCinema(c3);
	cf1.addCinema(c4);

	std::cout << "Arrabida"<< '/' << cf1.nearestCinema("estacionamento")<< std::endl;
	std::cout << 4<< '/' << cf1.getCinemas().size()<< std::endl;

	std::cout << "NS"<< '/' << cf1.nearestCinema("comercio")<< std::endl;
	std::cout << 4<< '/' << cf1.getCinemas().size()<< std::endl;
}


void test_c2() {
	CinemaFinder cf1;

	try {
        cf1.addServiceToNearestCinema("diversao", 10);
    }catch(CinemaFinder::CinemaNotFound & e){
	    std::cout << "CATCH" << std::endl;
	}

	Cinema c1("NS", 20, 4);
	c1.addService("estacionamento");
	c1.addService("restaura��o");
	c1.addService("comercio");

	Cinema c2("Arrabida", 12, 4);
	c2.addService("estacionamento");

	Cinema c3("PN", 20, 4);
	c3.addService("estacionamento");
	c3.addService("restaura��o");

	Cinema c4("GS", 8, 4);

	cf1.addCinema(c1);
	cf1.addCinema(c2);
	cf1.addCinema(c3);
	cf1.addCinema(c4);

	cf1.addServiceToNearestCinema("diversao",10);
	std::cout << 4 << '/' << cf1.getCinemas().size() << std::endl;
	c1= cf1.getCinemas().top();
	std::cout << "GS" << '/' << c1.getName() << std::endl;
	std::cout << 1 << '/' << c1.getServices().size() << std::endl;

	try{
	    cf1.addServiceToNearestCinema("diversao",4);
	}catch(CinemaFinder::CinemaNotFound & e){
    std::cout << "CATCH" << std::endl;
    }

    std::cout << 4 << '/' << cf1.getCinemas().size() << std::endl;
}


int main(){
    test_c2();
    return 0;
}



