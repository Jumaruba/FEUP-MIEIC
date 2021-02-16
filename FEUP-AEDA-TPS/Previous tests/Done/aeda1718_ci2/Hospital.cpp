/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    int total = 0;
	for (auto& c: doctors){
	    total += c.getPatients().size();
	}
	return total;

}

void Hospital::sortDoctors() {
	doctors.sort([](Doctor d1, Doctor d2){
	    if (d1.getPatients().size() < d2.getPatients().size()) return true;
	    else if(d1.getPatients().size() > d2.getPatients().size()) return false;
	    else if (d1.getMedicalSpecialty() < d2.getMedicalSpecialty()) return true;
	    else if (d1.getMedicalSpecialty() > d2.getMedicalSpecialty()) return false;
	    else if (d1.getCode() < d2.getCode()) return true;
	    return false;
	});

}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	// TODO
	return true;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	// TODO
	queue<Patient> p1;
	return p1;

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	// TODO
	return true;

}



void Hospital::processPatient(unsigned codM1) {
	// TODO

}


unsigned Hospital::removePatients(unsigned codP1) {
	// TODO
	return 0;

}



