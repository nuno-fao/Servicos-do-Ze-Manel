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

void Workshop::loadFromFile(priority_queue<Workshop*>* workshopLine)
{
	ifstream workshopFile;
	workshopFile.open("./files/workshops.txt");

	string temp_string_pair;
	string temp_brand;
	string temp_unavailability;
	string discarded;
	vector<string> vectored_pairs;

	while (!workshopFile.eof()) {
		
		string name;
		car_brand brand;
		unsigned int unavailability;	
		queue<pair<Truck*, Date*>>* waiting_line = new queue<pair<Truck*, Date*>>();
		
		getline(workshopFile, name);
		getline(workshopFile, temp_brand);
		getline(workshopFile, temp_unavailability);
		getline(workshopFile, temp_string_pair);
		getline(workshopFile, discarded);
		try {
			brand = selectBrand(temp_brand);
			unavailability = stoi(temp_unavailability);
			vectored_pairs = vectorString(temp_string_pair, ";");
			
			for (int i = 0; i < vectored_pairs.size() - 1; i+=2)
			{				
				Truck* new_truck = Company::getCompany()->getTruck(vectored_pairs.at(i));
				Date* new_date = new Date(vectored_pairs.at(i+1));
				waiting_line->push(make_pair(new_truck, new_date));
			}

			Workshop* new_workshop = new Workshop(name, brand, unavailability, *waiting_line);

			workshopLine->push(new_workshop);
		}
		catch (...) {
			continue;
		}
	}
	workshopFile.close();
}

void Workshop::saveToFile(priority_queue<Workshop*>* workshopLine)
{
	ofstream workshopFile;
	workshopFile.open("./files/workshops.txt");

	string discarded = "::::::::::::::::::::::::::::";


	while(!workshopLine->empty()) {
	
		try {
			workshopFile << workshopLine->top()->getName() << endl;
			workshopFile << printBrand(workshopLine->top()->getBrand()) << endl;
			workshopFile << workshopLine->top()->getUnavailability() << endl;


			while (!(workshopLine->top()->getWaitingLine().empty()))
			{
				workshopFile << workshopLine->top()->getWaitingLine().front().first->getlicense() << ";";
				workshopFile << workshopLine->top()->getWaitingLine().front().second->getDate() << ";";

				// Pop() not working, no clue why
				workshopLine->top()->getWaitingLine().pop();
			}

			workshopFile << endl << discarded;

			workshopLine->pop();
		}
		catch (...) {
			continue;
		}
	}
	workshopFile.close();
}

bool Workshop::operator<(Workshop w1)
{
	if (unavailability < w1.unavailability)
		return true;
	return false;
}

void Workshop::info() {
	cout << "Name: " << name << endl;
	cout << "Brand: " << printBrand(brand) << endl;
	cout << "Unavailability: " << to_string(unavailability) << endl;
	
	queue<pair<Truck*, Date*>> temp_queue = waiting_line;

	while (!temp_queue.empty()) {
		cout << "Truck: " << temp_queue.front().first->getlicense() << endl;
		cout << "Date: ";
		temp_queue.front().second->show();
		temp_queue.pop();
	}
	cout << "::::::::::::::::::::::::::::" << endl;
}
