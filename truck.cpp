#include "truck.h"


float HazardousMat::pricePerKG;
float Congelation::pricePerKG;
float Normal::pricePerKG;
float Animal::pricePerKG;

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

float HazardousMat::getprice(Service *service) {
    return service->getMultiplier()*service->getDistance()*HazardousMat::pricePerKG;
}

float Congelation::getprice(Service *service) {
    return service->getMultiplier()*service->getDistance()*Congelation::pricePerKG;
}

float Animal::getprice(Service *service) {
    return Animal::pricePerKG*service->getDistance();
}

float Normal::getprice(Service *service) {
    return service->getDistance()*Normal::pricePerKG;
}


