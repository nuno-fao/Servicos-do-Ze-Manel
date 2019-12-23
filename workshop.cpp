#include "workshop.h"

Workshop::Workshop(string n = "unknown", car_brand b = car_brand::None, unsigned ua = 0, wait_queue wl)
{
	name = n;
	brand = b;
	unavailability = ua;
	waiting_line = wl;
}

Workshop::Workshop(string n)
{
	name = n;
	brand = car_brand::None;
	unavailability = 0;

	Truck* default_truck = NULL;
	Date default_date;
	pair<Truck*, Date> default_pair(default_truck, default_date);
	waiting_line.push(default_pair);
}

string Workshop::getName() const
{
	return name;
}

car_brand Workshop::getBrand() const
{
	return brand;
}

unsigned int Workshop::getUnavailability() const
{
	return unavailability;
}

queue<pair<Truck*, Date>> Workshop::getWaitingLine() const
{
	return waiting_line;
}

void Workshop::setName(string n)
{
	name = n;
}

void Workshop::setBrand(car_brand b)
{
	brand = b;
}

void Workshop::setUnavailability(unsigned int ua)
{
	unavailability = ua;
}

void Workshop::setWaitingLine(wait_queue wl)
{
	waiting_line = wl;
}

void Workshop::loadFromFile()
{
	string nif;
	string name;
	string serviceHours;
	int nif_tmp;
	float service_h;
	BST<Driver*>* tmp_vect = Company::getCompany()->getDrivers();
	while (getline(driverFile, nif)) {
		getline(driverFile, name);
		getline(driverFile, serviceHours);
		try {
			nif_tmp = stoi(nif);
			service_h = stof(serviceHours);
			Driver* tmp;
			tmp = new Driver(nif_tmp, name, service_h);
			tmp_vect->push_back(tmp);
		}
		catch (...) {
			continue;
		}
	}



	ifstream workshopFile;
	workshopFile.open("./files/workshops.txt");

	string name;
	car_brand brand;
	unsigned int unavailability;
	wait_queue waiting_line;
	priority_queue<Workshop*> temp_wait_line = Company::getCompany()->

	while (getline(workshopFile, name)) {
		getline(driverFile, name);
		getline(driverFile, serviceHours);
		try {
			nif_tmp = stoi(nif);
			service_h = stof(serviceHours);
			Driver* tmp;
			tmp = new Driver(nif_tmp, name, service_h);
			tmp_vect->push_back(tmp);
		}
		catch (...) {
			continue;
		}
	}

}

void Workshop::saveToFile()
{
}
