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

queue<pair<Truck*, Date*>> *Workshop::getWaitingLine()
{
    return &waiting_line;
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


            while (!(workshopLine->top()->getWaitingLine()->empty()))
			{
                workshopFile << workshopLine->top()->getWaitingLine()->front().first->getlicense() << ";";
                workshopFile << workshopLine->top()->getWaitingLine()->front().second->getDate() << ";";

                workshopLine->top()->getWaitingLine()->pop();
			}

			workshopFile << endl << discarded << endl;

			workshopLine->pop();
		}
		catch (...) {
			continue;
		}
	}
	workshopFile.close();
}

void Workshop::addWorkshop(priority_queue<Workshop*>* workshop_line)
{
	clearScreen();
	clearBuffer();
	string name, temp_brand;
	string confirmstr;
	car_brand brand;
	unsigned int unavailability = 0;
	queue<pair<Truck*, Date*>> *standard_queue = new queue<pair<Truck*, Date*>>();
	bool invalidInput;

	do {
		invalidInput = false;
		cout << "Please input the new Workshop's name: " << endl; 
		getline(cin, name);
		if (name == "!q"){
			clearScreen();
			return;
		}

		// Verifies if workshop already exists.
		if (!checkWorkshopName(name)) {
			invalidInput = true;
			clearScreen();
		}
	} while (invalidInput);

	clearScreen();

	do {
		invalidInput = false;
		cout << "Please input the new Workshop's name: " << name << endl;
		cout << "Please input the new Workshop's brand: " << endl;
		getline(cin, temp_brand);
		if (temp_brand == "!q"){
			clearScreen();
			return;
		}

		// Verifies if brand if valid
		if (!verifyBrand(temp_brand)) {
			invalidInput = true;
			clearScreen();
		}
		else
			brand = selectBrand(temp_brand);
	} while (invalidInput);

	// Confirmation screen

	do {
		clearScreen();
		cout << "You're about to add a Workshop with the following characteristics: " << endl;
		cout << "Name: " << name << endl;
		cout << "Brand: " << printBrand(brand) << endl;
		cout << "Do you wish proceed (Y/N)? ";
		cin >> confirmstr;
		clearBuffer();
	} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n" && confirmstr != "!q");	// Confirmation
	
	if (confirmstr == "Y" || confirmstr == "y") {
		Workshop* workshop_to_add = new Workshop(name, brand, unavailability, *standard_queue);
		workshop_line->push(workshop_to_add);
		cout << "Workshop " << name << " added successfully!" << endl;
		enter_to_exit();
	}
	else {
		cout << "Operation cancelled!" << endl;
		enter_to_exit();
	}
	clearScreen();
}



unsigned int Workshop::calculateUnavailability(Date d1)
{
	Date now_date;
	return (d1 - now_date) / 1440;
}

void Workshop::addService(Truck* truck, Date* date)
{
	getWaitingLine()->push(make_pair(truck, date));
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
