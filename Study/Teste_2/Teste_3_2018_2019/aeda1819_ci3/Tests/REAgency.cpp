#include "REAgency.h"
#include <algorithm>

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    vector<PropertyTypeItem> temp;
    for(auto elem:properties){
        PropertyTypeItem x(elem->getAddress(), elem->getPostalCode(), elem->getTypology(), elem->getPrice());
        auto it = find(temp.begin(), temp.end(), x);
        if(it == temp.end()){ x.setItems({elem}); temp.push_back(x);}
        else{
            vector<Property *> p = it->getItems();
            p.push_back(elem);
            it->setItems(p);
        }
    }
    for(auto elem: temp){
        catalogItems.insert(elem);
    }
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	PropertyTypeItem x(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
    BSTItrLevel<PropertyTypeItem> it(catalogItems);
    while(!it.isAtEnd()){
        if(it.retrieve() == x){
            for(auto elem:it.retrieve().getItems()){
                if(get<1>(elem->getReservation()) == 0)
                    temp.push_back(elem);
            }
        }
        it.advance();
    }
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    PropertyTypeItem x(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
    BSTItrLevel<PropertyTypeItem> it(catalogItems);
    while(!it.isAtEnd()){
        if(it.retrieve() == x){
            for(auto &elem: it.retrieve().getItems()){
                if(get<1>(elem->getReservation()) == 0){
                    elem->setReservation(make_tuple(client, property->getPrice() - property->getPrice() * percentage / 100));
                    client->addVisiting(property->getAddress(), property->getPostalCode(), property->getTypology(), to_string(property->getPrice()));
                    return true;
                }
            }
        }
        it.advance();
    }
	return false;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    listingRecords.insert(client);
}

void REAgency::deleteClients() {
	for(auto elem: listingRecords){
	    if(elem.getClientPointer()->getVisitedProperties().empty()) listingRecords.erase(elem);
	}
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
	for(auto elem: candidates){
	    int counter = 0;
	    for(auto p:properties){
	        if(elem.getEMail() == get<0>(p->getReservation())->getEMail()){
	            counter++;
	        }
	    }
        if (float(counter) / elem.getVisitedProperties().size() > float(min))
            clientProfiles.push(elem);
	}

}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
    priority_queue<Client> temp = clientProfiles;
    int i = 0;
    while(!temp.empty()){
        i++;
        tempProperties.resize(i);
        Client temporary = temp.top();
        if(get<1>(temporary.getVisiting()).empty()) { temp.pop(); continue; };

        int postal = stoi(get<1>(temporary.getVisiting()));
        Property * x;
        bool first = true;
        for(auto elem:properties){
            if(first)
                if(get<1>(elem->getReservation()) == 0 && stoi(elem->getPostalCode()) != postal) {
                    x = elem;
                    first = false;
                }
            else{
                if(get<1>(elem->getReservation()) == 0 &&  stoi(elem->getPostalCode()) != postal)
                    if(stoi(elem->getPostalCode()) - postal < stoi(x->getPostalCode()) - postal)
                        x = elem;
            }
        }
        tempProperties[i - 1] = x;
        temp.pop();
    }
	return tempProperties;
}
