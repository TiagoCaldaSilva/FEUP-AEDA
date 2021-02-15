#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    sort(obj.begin(), obj.end());
    while(obj.size()){
        addObject(obj[0]);
        obj.erase(obj.begin());
    }
    return objects.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
     Object obj("dummy", maxSize), temp;
     bool done = false;
     int s = objects.size();
     for(int i = 0; i < s; i++)
     {
         temp = objects.front();
         if(!done && temp.getSize() <= maxSize) {
             obj = temp;
             objects.pop();
             done = 1;
         }
         else{
             objects.pop();
             objects.push(temp);
         }
     }
     return obj;
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for(ThinTallBox b:boV)
        boxes.push(b);
    return boxes.size();
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    int s = boxes.size();
    for(int i = 0; i < s; i++)
    {
        ThinTallBox temp = boxes.front();
        boxes.pop();
        if(temp.getContentSize() == temp.getCapacity()) {
            res.push_back(temp);
            continue;
        }
        else{
            Object obj = RemoveObjectQueue((temp.getCapacity() - temp.getContentSize()));
            if(obj.getName() == "dummy")
                obj.setSize(0);
            temp.insert(obj);
        }
        if(!temp.getDays()){
            res.push_back(temp);
            continue;
        }
        temp.setDaysToSend(temp.getDays() - 1);
        boxes.push(temp);
    }
    return res;
}

