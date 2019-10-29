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

unsigned short Truck::getcargo() const {
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
	HazardousMat::hazardMul[Hazard_enum::explosives] = stoi(auxVec[0]);
	HazardousMat::hazardMul[Hazard_enum::gases] = stoi(auxVec[1]);
	HazardousMat::hazardMul[Hazard_enum::flammableliq] = stoi(auxVec[2]);
	HazardousMat::hazardMul[Hazard_enum::flammablesolid] = stoi(auxVec[3]);
	HazardousMat::hazardMul[Hazard_enum::oxidizer] = stoi(auxVec[4]);
	HazardousMat::hazardMul[Hazard_enum::poisons] = stoi(auxVec[5]);
	HazardousMat::hazardMul[Hazard_enum::radioactive] = stoi(auxVec[6]);
	HazardousMat::hazardMul[Hazard_enum::corrosives] = stoi(auxVec[7]);
	HazardousMat::hazardMul[Hazard_enum::other] = stoi(auxVec[8]);
	//load temperature multipliers for congelation trucks
	getline(truckfile, aux);
	auxVec = vectorString(aux, separator);
	Congelation::tempMul[Temperature_enum::_100] = stoi(auxVec[0]);
	Congelation::tempMul[Temperature_enum::_200] = stoi(auxVec[1]);
	Congelation::tempMul[Temperature_enum::_300] = stoi(auxVec[2]);
	Congelation::tempMul[Temperature_enum::_400] = stoi(auxVec[3]);
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
		Truck* temp;
		switch (type) {
			case 'A':
				temp = new Animal(lic,avai,regist,cap,carg);
				trucks->push_back(temp);
				break;
			case 'C':
				temp = new Congelation(lic, avai, regist, cap, carg);
				trucks->push_back(temp);
				break;
			case 'H':
				temp = new HazardousMat(lic, avai, regist, cap, carg);
				trucks->push_back(temp);
				break;
			case 'N':
				temp = new HazardousMat(lic, avai, regist, cap, carg);
				trucks->push_back(temp);
				break;
		}

	}
	truckfile.close();

}

void Truck::saveToFile(vector<Truck*>* trucks) {
	ofstream truckfile;
	truckfile.open("files//trucks.txt");
	if (!truckfile.is_open()) { throw FailedToOpenTrucks(); }
	truckfile << HazardousMat::hazardMul[Hazard_enum::explosives] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::gases] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::flammableliq] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::flammablesolid] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::oxidizer] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::poisons] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::radioactive] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::corrosives] << "; ";
	truckfile << HazardousMat::hazardMul[Hazard_enum::other] << endl;
	truckfile << Congelation::tempMul[Temperature_enum::_100] << "; ";
	truckfile << Congelation::tempMul[Temperature_enum::_200] << "; ";
	truckfile << Congelation::tempMul[Temperature_enum::_300] << "; ";
	truckfile << Congelation::tempMul[Temperature_enum::_400] << endl;
	for (auto it : *trucks) {
		truckfile << "::::::::::::::::::::::::::::" << endl;
		truckfile << it->getlicense() << endl;
		truckfile << it->getavailable() << endl;
		truckfile << it->getregistered() << endl;
		truckfile << it->getcapacity() << endl;
		truckfile << it->getcargo() << endl;
		if (typeid(*it) == typeid(HazardousMat)) {
			truckfile << 'H' << endl;
		}
		else if (typeid(*it) == typeid(Animal)) {
			truckfile << 'A' << endl;
		}
		else if (typeid(*it) == typeid(Congelation)) {
			truckfile << 'C' << endl;
		}
		else if (typeid(*it) == typeid(Normal)) {
			truckfile << 'N' << endl;
		}
	}
	truckfile.close();
}
