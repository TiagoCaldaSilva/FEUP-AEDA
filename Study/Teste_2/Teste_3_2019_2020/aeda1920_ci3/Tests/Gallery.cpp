#include "Gallery.h"
#include <ostream>
using namespace std;
#include <algorithm>

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO
vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    while(!it.isAtEnd()){
        if(it.retrieve().getAuthor() == a){
            tmp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    return tmp;
}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    BSTItrIn<PaintCatalogItem> it(catalog);
    while(!it.isAtEnd()){
        if(it.retrieve().getYear() >= y1 && it.retrieve().getYear() <= y2){
            tmp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    PaintCatalogItem x(p);
    auto it = catalog.find(x);
    if(it.getAuthor().empty() && it.getTitle().empty()) return false;
    catalog.remove(it);
    Paint *temp = new Paint(it.getAuthor(), tnew, it.getYear(), it.getPrice());
    PaintCatalogItem new_(temp);
    catalog.insert(new_);
    return true;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for(auto elem:collection){
        if(authorRecords.find(elem->getAuthor()) != authorRecords.end()){
            auto it = authorRecords.find(elem->getAuthor());
            AuthorRecord temp(it->getAuthor(), it->getAvailablePaints() + 1, it->getTotalSells());
            authorRecords.erase(it);
            authorRecords.insert(temp);
        }
        else
            authorRecords.insert(elem->getAuthor());
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    double total = 0;
    for(auto elem:authorRecords){
        total += elem.getTotalSells();
    }
    return total;
}

//TODO
double Gallery::sellPaint(string a, string t) {
    double value = 0;
    for(auto it = collection.begin(); it != collection.end(); it++){
        if((*it)->getAuthor() == a && (*it)->getTitle() == t) {
            value = (*it)->getPrice();
            collection.erase(it);
            break;
        }
    }
    if(value == 0) return value;
    auto it = authorRecords.find(AuthorRecord(a, 0, 0));
    AuthorRecord temp(a, it->getAvailablePaints() - 1, it->getTotalSells() + value);
    authorRecords.erase(it);
    authorRecords.insert(temp);
    return value;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmp;
    priority_queue<ExhibitionItem> temp;
    int counter = 0, current_year = paintsToShow.top().getYear();
    while(!paintsToShow.empty()){
        ExhibitionItem x = paintsToShow.top();
        if(counter == maxPerYear && current_year == x.getYear()){
            temp.push(x);
        }
        else{
            if(current_year != x.getYear()){
                counter = 1;
                current_year = x.getYear();
            }else counter++;
            tmp.push_back(x.getPaint());
        }
        paintsToShow.pop();
        if(tmp.size() == n) break;
    }
    while(!temp.empty()){
        paintsToShow.push(temp.top());
        temp.pop();
    }
    return tmp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    priority_queue<ExhibitionItem> temp = paintsToShow;
    int order = 1;
    while(!temp.empty()){
        if(temp.top().getAuthor() == a && temp.top().getTitle() == t)
            return order;
        temp.pop();
        order++;
    }
    return 0;
}

