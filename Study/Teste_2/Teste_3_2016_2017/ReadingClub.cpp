/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
    for(auto elem:books){
        BookCatalogItem temp(elem->getTitle(), elem->getAuthor(), elem->getYear());
        auto it = catalogItems.find(temp);
        if(it.getAuthor().empty() && it.getTitle().empty()) {
            temp.addItems(elem);
            catalogItems.insert(temp);
        }
        else{
            temp = it;
            temp.addItems(elem);
            catalogItems.remove(it);
            catalogItems.insert(temp);
        }
    }
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	BookCatalogItem x(book->getTitle(), book->getAuthor(), 0);
	auto it = catalogItems.find(x);
	if(it.getAuthor().empty() && it.getTitle().empty()) return temp;

	for(auto elem:it.getItems()){
	    if(elem->getReader())
            continue;
	    else
	        temp.push_back(elem);
	}
	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	BookCatalogItem temp(book->getTitle(), book->getAuthor(), 0);
	auto it = catalogItems.find(temp);
	if(it.getAuthor().empty() && it.getTitle().empty()) return false;
	for(auto elem:it.getItems()){
	    if(elem->getReader()) continue;
	    else{
	        elem->setReader(reader);
	        reader->addReading(elem->getTitle(), elem->getAuthor());
	        return true;
	    }
	}
	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
    userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	for(auto elem: userRecords){
	    if(elem.getEMail() == user->getEMail())
	        user->setEMail(newEMail);
	        UserRecord x(user);
	        userRecords.erase(elem);
	        userRecords.insert(x);
	        return;
	}
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	for(auto elem:candidates){
	    int total = (elem.getReading().first.empty()) ? elem.getReadings().size():(elem.getReadings().size() + 1);
	    if(total >= min)
            readerCandidates.push(elem);
	}
}

int ReadingClub::awardReaderChampion(User& champion) {
	if(readerCandidates.empty()) return 0;
	User temp = readerCandidates.top();
    int total_temp = (temp.getReading().first.empty()) ? temp.getReadings().size():(temp.getReadings().size() + 1);
    readerCandidates.pop();
    readerCandidates.push(temp);
    int total_2 = (readerCandidates.top().getReading().first.empty()) ? readerCandidates.top().getReadings().size():(readerCandidates.top().getReadings().size() + 1);
    if(total_temp == total_2){ return 0;}
    champion = temp;
	return readerCandidates.size();
}
























