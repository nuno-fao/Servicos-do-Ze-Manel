#include "workshop.h"

Workshop::Workshop(string n, car_brand b, unsigned ua, queue<pair<Truck*, Date*>> wl)
{
	name = n;
	brand = b;
	unavailability = ua;
	waiting_line = wl;
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

queue<pair<Truck*, Date*>> Workshop::getWaitingLine() const
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

void Workshop::setWaitingLine(queue<pair<Truck*, Date*>> wl)
{
	waiting_line = wl;
}

void Workshop::loadFromFile()
{
	ifstream workshopFile;
	workshopFile.open("./files/workshops.txt");

	string temp_string_pair;
	string temp_brand;
	string temp_unavailability;
	vector<string> vectored_pairs;

	string name;
	car_brand brand;
	unsigned int unavailability;
	queue<pair<Truck*, Date*>> waiting_line;
	priority_queue<Workshop*>* temp_wait_line = Company::getCompany()->getWorkshopLine();

	while (!workshopFile.eof()) {
		getline(workshopFile, name);
		getline(workshopFile, temp_brand);
		getline(workshopFile, temp_unavailability);
		getline(workshopFile, temp_string_pair);
		try {
			brand = selectBrand(temp_brand);
			unavailability = stoi(temp_unavailability);
			vectored_pairs = vectorString(temp_string_pair, ";");
			
			//for (size_t i = 0; i < vectored_pairs.size() - 1; i++)
			//{
			//	pair<>
			//}
			//waiting_line.push


			//Workshop * temp_workshop = new Workshop(name, brand, unavailability, waiting_line);

			//Driver* tmp;
			//tmp = new Driver(nif_tmp, name, service_h);
			//tmp_vect->push_back(tmp);
		}
		catch (...) {
			continue;
		}
	}
	workshopFile.close();
}

void Workshop::saveToFile()
{
}

bool Workshop::operator<(Workshop w1)
{
	if (unavailability < w1.unavailability)
		return true;
	return false;
}
