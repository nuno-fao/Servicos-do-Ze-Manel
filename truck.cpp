#include "truck.h"


float HazardousMat::pricePerKG;
float Congelation::pricePerKG;
float Normal::pricePerKG;
float Animal::pricePerKG;

Truck::Truck(string license) {
	this->license=license;
	availabe = true;
	registered = false;
}

Congelation::Congelation(string license) : Truck(license) {

}
HazardousMat::HazardousMat(string license) : Truck(license) {

}
Animal::Animal(string license) : Truck(license) {

}
Normal::Normal(string license) : Truck(license) {

}

unsigned short Truck::getcapacity() const {
	return capacity;
}

bool Truck::getavailable() const {
	return availabe;
}

bool Truck::getregistered() const{
	return registered;
}

string Truck::getlicense() const {
	return license;
}

unsigned short Truck::get_cargo() const {
	return cargo;
}

float HazardousMat::getprice(Service *service) const {
    return service->getMultiplier()*service->getDistance()*HazardousMat::pricePerKG;
}

float Congelation::getprice(Service *service) const {
    return service->getMultiplier()*service->getDistance()*Congelation::pricePerKG;
}

float Animal::getprice(Service *service) const {
    return Animal::pricePerKG*service->getDistance();
}

float Normal::getprice(Service *service) const {
    return service->getDistance()*Normal::pricePerKG;
}


void Truck::setavailable(bool foo) {
	availabe = foo;
}

void Truck::setregistered(bool foo) {
	registered = foo;
}

void Congelation::setprice(float newval) {
	pricePerKG = newval;
}
void HazardousMat::setprice(float newval) {
	pricePerKG = newval;
}
void Animal::setprice(float newval) {
	pricePerKG = newval;
}
void Normal::setprice(float newval) {
	pricePerKG = newval;
}

void Truck::add_service(Service* service) {
	assignedServices.push_back(service);
}

void Truck::remove_service(unsigned int id) {
	short index = -1;
	for (auto it:assignedServices) {
		index++;
		if (it->getId() == id) {
			assignedServices.erase(assignedServices.begin()+index);
		}
	}
}

void Truck::start_transport(unsigned short cargo) {
	availabe = false;
	this->cargo = cargo;
}
