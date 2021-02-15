#include "packagingMachine.h"
#include <sstream>
#include <algorithm>

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
        else    temp.push_back(*it);

    }
    objs = temp;
    return objects.size();
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {
	Box b;
	vector<Box> temp;
	while(!boxes.empty()){
	    if(boxes.top().getFree() >= obj.getWeight()){
	        b = boxes.top(); boxes.pop();
	        break;
	    }
	    temp.push_back(boxes.top());
	    boxes.pop();
	}
	for(Box bx: temp){
	    boxes.push(bx);
	}
	return b;
}

// TODO
unsigned PackagingMachine::packObjects() {
    int counter;
    while(!objects.empty()){
        Object temp_o(objects.top()); objects.pop();
        Box temp_b = searchBox(temp_o);
        if(temp_b.getSize() == 0) counter++;
        temp_b.addObject(temp_o);
        boxes.push(temp_b);
    }
	return counter;
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
    if(objects.size() == 0)
        return "No objects!\n";
    string result = "";
    HeapObj temp = objects;
    while(!temp.empty()){
        result += 'O' + to_string(temp.top().getID()) + ':' + to_string(temp.top().getWeight()) + '\n';
        temp.pop();
    }
    return result;
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
	if(boxes.empty()) throw MachineWithoutBoxes();
    Box b;
	HeapBox temp = boxes;
	while(!temp.empty()){
	    if(temp.top().getSize() >= b.getSize()) b = temp.top();
	    temp.pop();
	}
	return b;
}
