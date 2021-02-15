/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	Expertize temp(expertizeAvailable, cost);
	auto it = expertizes.find(temp);
	if(it.getName().empty() && it.getCost() == 0){
	    temp.addConsultant(student);
	    expertizes.insert(temp);
	}else{
	    temp.setConsultants(it.getConsultants());
	    expertizes.remove(it);
	    temp.addConsultant(student);
	    expertizes.insert(temp);
	}

}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	Expertize x(project->getExpertize(), project->getCost());
	auto it = expertizes.find(x);
	if(!it.getName().empty() && it.getCost() != 0) {
	    for(auto elem:it.getConsultants()){
	        if(elem->getCurrentProject().empty()) temp.push_back(elem);
	    }
	}
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	if(project->getConsultant()) return false;
	if(!student->getCurrentProject().empty()) return false;
	Expertize temp(project->getExpertize(), project->getCost());
	auto v = getCandidateStudents(project);
	for(auto s:v){
	    if(s == student){
	        student->addProject(project->getTitle());
	        project->setConsultant(student);
	        return true;
	    }
	}
	return false;
}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
    students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	for(auto elem:students){
	    if(student->getEMail() == elem.getEMail()){
	        students.erase(elem);
	        student->setEMail(newEMail);
	        students.insert(student);
	    }
	}

}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
    for(auto elem:candidates){
        if(elem.getPastProjects().size() >= min)
            activeStudents.push(elem);
    }
}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    if(activeStudents.empty()) return 0;
    Student temp = activeStudents.top();
    activeStudents.pop();
    if(activeStudents.top().getPastProjects().size() == temp.getPastProjects().size()){activeStudents.push(temp); return 0;}
	studentMaximus = temp;
	activeStudents.push(temp);
	return activeStudents.size();

}





















