#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    vector<Object> temp;
	for(auto it = objs.begin(); it != objs.end(); it++){
	    if(it->getWeight() <= boxCapacity) {
            objects.push(*it);
        }
	    else
	        temp.push_back(*it);
	}
	objs = temp;
    return objects.size();
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {
	Box b;
	vector<Box> temp;
	while(!boxes.empty()) {
        if (boxes.top().getFree() >= obj.getWeight()) {
            b = boxes.top();
            boxes.pop();
            break;
        }
        temp.push_back(boxes.top());
        boxes.pop();
    }
	for(auto value:temp){
	    boxes.push(value);
	}
	return b;
}

// TODO
unsigned PackagingMachine::packObjects() {
    while(!objects.empty()){
        Object obj = objects.top(); objects.pop();
        Box b = searchBox(obj);
        b.addObject(obj);
        boxes.push(b);
    }
	return boxes.size();
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
    string result = "";
    if(objects.empty()) return "No objects!\n";
    HeapObj temp = objects;
    while(!temp.empty()){
        Object x = temp.top();
        temp.pop();
        result += 'O' + to_string(x.getID()) + ':' + to_string(x.getWeight()) + '\n';
    }
	return result;
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
    if(boxes.empty()) throw MachineWithoutBoxes();
    Box b;
	HeapBox temp = boxes;
	while(!temp.empty()){
	    if(temp.top().getSize() > b.getSize())
	        b = temp.top();
	    temp.pop();
	}
	return b;
}