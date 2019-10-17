#include "truck.h"


Truck::Truck(string license) {
	this->license = license;
	availabe = true;
	registered = false;
}

unsigned short Truck::getcapacity() {
	return capacity;
}

bool Truck::getavailable() {
	return availabe;
}

bool Truck::getregistered() {
	return registered;
}

string Truck::getlicense() {
	return license;
}

void Truck::setavailable(bool foo) {
	availabe = foo;
}

void Truck::setregistered(bool foo) {
	registered = foo;
}