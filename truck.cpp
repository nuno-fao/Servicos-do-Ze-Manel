#include "truck.h"


float HazardousMat::pricePerKG;
float Congelation::pricePerKG;
float Normal::pricePerKG;
float Animal::pricePerKG;

Truck::Truck(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo) {
	this->license=license;
	this->availabe = available;
	this->registered = registered;
	this->capacity = capacity;
	this->cargo = cargo;
}

Truck::~Truck(){

}

Congelation::Congelation(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo) : Truck(license,available,registered, capacity, cargo) {

}
HazardousMat::HazardousMat(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo) : Truck(license, available, registered, capacity, cargo) {

}
Animal::Animal(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo) : Truck(license,available,registered, capacity, cargo) {

}
Normal::Normal(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo) : Truck(license,available,registered, capacity, cargo) {

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
	for (vector<Service*>::iterator it = assignedServices.begin(); it != assignedServices.end();it++) {
		if ((*it)->getId() == id) {
			assignedServices.erase(assignedServices.begin()+index);
			return;
		}
	}
}

void Truck::start_transport(unsigned short cargo) {
	availabe = false;
	this->cargo = cargo;
}

void Truck::loadFromFile(vector<Truck*>* trucks) {
	ifstream truckfile;
	string aux;
	string separator = "; ";
	string lic;
	char type;
	bool avai, regist;
	unsigned short cap, carg;
	vector<string> auxVec;
	truckfile.open("files//trucks.txt");
	if (!truckfile.is_open()) { throw FailedToOpenTrucks(); }
	//load hazard multipliers for hazardous cargo trucks
	getline(truckfile, aux);
	auxVec = vectorString(aux, separator);
	HazardousMat::hazardMul[explosives] = stoi(auxVec[0]);
	HazardousMat::hazardMul[gases] = stoi(auxVec[1]);
	HazardousMat::hazardMul[flammableliq] = stoi(auxVec[2]);
	HazardousMat::hazardMul[flammablesolid] = stoi(auxVec[3]);
	HazardousMat::hazardMul[oxidizer] = stoi(auxVec[4]);
	HazardousMat::hazardMul[poisons] = stoi(auxVec[5]);
	HazardousMat::hazardMul[radioactive] = stoi(auxVec[6]);
	HazardousMat::hazardMul[corrosives] = stoi(auxVec[7]);
	HazardousMat::hazardMul[other] = stoi(auxVec[8]);
	//load temperature multipliers for congelation trucks
	getline(truckfile, aux);
	auxVec = vectorString(aux, separator);
	Congelation::tempMul[_100] = stoi(auxVec[0]);
	Congelation::tempMul[_200] = stoi(auxVec[1]);
	Congelation::tempMul[_300] = stoi(auxVec[2]);
	Congelation::tempMul[_400] = stoi(auxVec[3]);
	while (getline(truckfile, aux)) {	//reads all trucks
		getline(truckfile, lic);
		getline(truckfile, aux);
		aux == "1" ? avai = true : avai = false;
		getline(truckfile, aux);
		aux == "1" ? regist = true : regist = false;
		getline(truckfile, aux);
		cap = stoi(aux);
		getline(truckfile, aux);
		carg = stoi(aux);
		getline(truckfile, aux);
		type = aux[0];
		switch (type) {
			case 'A':
				Truck* temp = new Animal(lic,avai,regist,cap,carg);
				trucks->push_back(temp);
				break;
			case 'C':
				Truck * temp = new Congelation(lic, avai, regist, cap, carg);
				trucks->push_back(temp);
				break;
			case 'H':
				Truck * temp = new HazardousMat(lic, avai, regist, cap, carg);
				trucks->push_back(temp);
				break;
			case 'N':
				Truck * temp = new HazardousMat(lic, avai, regist, cap, carg);
				trucks->push_back(temp);
				break;
		}

	}

}
