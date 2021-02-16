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
	BSTItrIn<Expertize>it(expertizes);
	while(!it.isAtEnd()){
	    if (it.retrieve().getCost() == cost && it.retrieve().getName() == expertizeAvailable) {
            it.retrieve().addConsultant(student);
            return;
        }
	    it.advance();
	}
	Expertize m(expertizeAvailable, cost);
	m.addConsultant(student);
	expertizes.insert(m);



}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	BSTItrIn<Expertize>it(expertizes);
	while(!it.isAtEnd()){
	    if (it.retrieve().getName() == project->getExpertize() && project->getCost() == it.retrieve().getCost()){
	        for (auto const & i: it.retrieve().getConsultants()){
	            if (i->getCurrentProject().empty()) temp.push_back(i);
	        }
	    }
	    it.advance();
	}
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
    BSTItrIn<Expertize>it(expertizes);
    //estudante tem de estar interessado
    if (project->getConsultant() != nullptr) return false;
    while(!it.isAtEnd()){
        auto consults = it.retrieve().getConsultants();
        if (it.retrieve().getCost() == project->getCost() && it.retrieve().getName() == project->getExpertize()) {
            for (auto const &i: consults) {
                if(i == student && i->getCurrentProject().empty()) {
                    student->addProject(project->getTitle());
                    project->setConsultant(student);
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

void FEUPConsulting::addStudent(Student* student) {
	students.insert(student);

}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
    auto it = students.begin();
	while(it != students.end()){
	    if (it->getStudent() == student) student->setEMail(newEMail);
	    it++;
	}


}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for (auto const& std: candidates){
	    if (std.getPastProjects().size() >= min) activeStudents.push(std);
	}

}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
    if (activeStudents.empty()) return 0;

	Student max_student = activeStudents.top();
	activeStudents.pop();
	if (activeStudents.top().getPastProjects().size() == max_student.getPastProjects().size()){
	    activeStudents.push(max_student);
	    return 0;
	}
	activeStudents.push(max_student);
	studentMaximus = max_student;
	return activeStudents.size();

}





















