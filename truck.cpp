#include "truck.h"

unordered_map<Hazard_enum, float> HazardousMat::hazardMul;
unordered_map<Temperature_enum, float> Congelation::tempMul;
float HazardousMat::pricePerKG;
float Congelation::pricePerKG;
float Normal::pricePerKG;
float Animal::pricePerKG;

Truck::~Truck(){

};

float Truck::getprice(Service* service) const{
    return service->getMultiplier()*0;
}

Truck::Truck(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo) {
    this->license=license;
    this->availabe = available;
    this->registered = registered;
    this->capacity = capacity;
    this->cargo = cargo;
}

Congelation::Congelation(string license_c, bool available_c, bool registered_c, unsigned short capacity_c, unsigned short cargo_c) : Truck(license_c,available_c,registered_c, capacity_c, cargo_c) {

}
HazardousMat::HazardousMat(string license_h, bool available_h, bool registered_h, unsigned short capacity_h, unsigned short cargo_h) : Truck(license_h, available_h, registered_h, capacity_h, cargo_h) {

}
Animal::Animal(string license_a, bool available_a, bool registered_a, unsigned short capacity_a, unsigned short cargo_a) : Truck(license_a,available_a,registered_a, capacity_a, cargo_a) {

}
Normal::Normal(string license_n, bool available_n, bool registered_n, unsigned short capacity_n, unsigned short cargo_n) : Truck(license_n,available_n,registered_n, capacity_n, cargo_n) {

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

void Truck::info() {
    cout << "License: " << license << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Available: ";
    (availabe) ? cout << "true" << endl : cout << "false" << endl << "\tCurrently transporting " << cargo << "KG of cargo" << endl;
    cout << "Registered: ";
    (registered) ? cout << "true" << endl : cout << "false" << endl;
    if (registered) {
        cout << "\tTo service(s) with ID:";
        for (auto it : assignedServices) {
            cout<<" "<<it->getId();
        }
        cout << endl;
    }
}

void Congelation::info() {
    Truck::info();
    cout << "Type: Congelation" << endl;
}
void HazardousMat::info() {
    Truck::info();
    cout << "Type: Hazardous Material" << endl;
}
void Animal::info() {
    Truck::info();
    cout << "Type: Animal" << endl;
}
void Normal::info() {
    Truck::info();
    cout << "Type: Normal" << endl;
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
    char type='\0';
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
    while (getline(truckfile, aux)) {
        getline(truckfile, lic);
        getline(truckfile, aux);
        aux == "1" ? avai = true : avai = false;
        getline(truckfile, aux);
        aux == "1" ? regist = true : regist = false;
        getline(truckfile, aux);
        cap = date_u_short(stoi(aux));
        getline(truckfile, aux);
        carg = date_u_short(stoi(aux));
        getline(truckfile, aux);
        type = aux[0];
        switch (type) {
        case 'A':{

            Truck *temp= new Animal(lic, avai, regist, cap, carg);
            trucks->push_back(temp);
            break;
        }
        case 'C':{
            Truck *temp = new Congelation(lic, avai, regist, cap, carg);
            trucks->push_back(temp);
            break;
        }
        case 'H':{
            Truck *temp = new HazardousMat(lic, avai, regist, cap, carg);
            trucks->push_back(temp);
            break;
        }
        case 'N':{
            Truck *temp = new HazardousMat(lic, avai, regist, cap, carg);
            trucks->push_back(temp);
            break;
        }
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

bool operator<(Truck &a,Truck &b) {
    return a.getlicense()<b.getlicense();
}

void Truck::createTruck(vector<Truck*>* trucks) {
    clearScreen();
    string license, aux, confirmstr;
    char type = '\0';
    int capacity = 0;
    bool invalidInput;

    do {
        invalidInput = false;
        cout <<"What's the license of the new truck (XX-YY-ZZ)? "; getline(cin, license);
        if (license == "!q") return;

        //verifies if the license is valid or if it already exists.
        if (!checkLicense(license,trucks)) {
            invalidInput = true;
            clearScreen();
        }
    } while (invalidInput);

    clearScreen();

    do {
        invalidInput = false;
        cout << "What's the license of the new truck (XX-YY-ZZ)? " << license << endl;
        cout << "What's the capacity of the new truck? "; getline(cin, aux);
        if (aux == "!q") return;

        //verifies if the capacity is valid.
        if (!strIsNumber(aux)) {
            invalidInput = true;
            clearScreen();
        }
        else if(stoi(aux)<=0){
            invalidInput = true;
            clearScreen();
        }
        else {
            capacity = stoi(aux);
        }
    } while (invalidInput);

    clearScreen();

    do {
        invalidInput = false;
        cout << "What's the license of the new truck (XX-YY-ZZ)? " << license << endl;
        cout << "What's the capacity of the new truck?" << capacity << endl;
        cout << "What's the truck type (A/N/C/H)? "; getline(cin, aux);
        if (aux == "!q") return;

        //verifies if the capacity is valid.
        if (aux.size()!=1) {
            invalidInput = true;
            cout << "Invalid input!!!\nInput either one of N, A, H, C without extra characters.";
            enter_to_exit();
            clearScreen();
        }
        else {
            if (aux == "C" || aux == "c") {
                type = 'C';
                aux = "Congelation";
            }
            else if (aux == "A" || aux == "a") {
                type = 'A';
                aux = "Animal";
            }
            else if (aux == "N" || aux == "n") {
                type = 'N';
                aux = "Normal";
            }
            else if (aux == "H" || aux == "h") {
                type = 'H';
                aux = "Hazardous Materials";
            }
            else {
                invalidInput = true;
                cout << "Invalid input!!!\nInput either one of N, A, H, C without extra characters.";
                enter_to_exit();
                clearScreen();
            }
        }
    } while (invalidInput);

    do {
        clearScreen();
        cout << "You're about to add a truck with the following characteristics to this business: " << endl;
        cout << "License: " << license << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Type: " << aux << endl;
        cout << "Do you wish proceed (Y/N)? ";
        cin >> confirmstr;
        clearBuffer();
    } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n" && confirmstr!="!q");	//confirmation
    if (confirmstr == "Y" || confirmstr == "y") {
        switch (type) {
        case('C'):{
            Truck* newTruck = new Congelation(license, true, false, date_u_short(capacity), 0);
            trucks->push_back(newTruck);
            break;
        }
        case('A'):{
            Truck* newTruck = new Animal(license, true, false, date_u_short(capacity), 0);
            trucks->push_back(newTruck);
            break;
        }
        case('N'):{
            Truck* newTruck = new Normal(license, true, false, date_u_short(capacity), 0);
            trucks->push_back(newTruck);
            break;
        }
        case('H'):{
            Truck* newTruck = new HazardousMat(license, true, false, date_u_short(capacity), 0);
            trucks->push_back(newTruck);
            break;
        }
        }
		cout << "Truck with license " << license << " removed successfully!" << endl;
		enter_to_exit();
    }
	else {
		cout << "Operation cancelled!" << endl;
		enter_to_exit();
	}
	clearScreen();
}

void Truck::removeTruck(vector<Truck*>* trucks) {
    
    string license, confirmstr;
	bool invalidInput, found=false;
    vector<string> auxVec;
	do {
		clearScreen();
		invalidInput = false;
		cout << "What's the license of the truck you wish to remove (XX-YY-ZZ)? "; getline(cin, license);
		if (license == "!q") return;

		//verifies if the license is valid or if it already exists.
		if (!checkLicenseV2(license)) {
			invalidInput = true;
		}
		else {
			for (vector<Truck*>::iterator it = trucks->begin(); it != trucks->end();it++) {
				if ((*it)->getlicense() == license) {
					found = true;
					if ((*it)->getavailable() && !((*it)->getregistered())) {
						do {
							clearScreen();
							cout << "Truck found!!!" << endl;
							(*it)->info();
							cout << "Do you wish to proceed with the removal of this truck (Y/N)? ";
							cin >> confirmstr;
							clearBuffer();
						} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n" && confirmstr != "!q");	//confirmation
						if (confirmstr == "Y" || confirmstr == "y") {
							clearScreen();
							delete *it;
							trucks->erase(it);
							cout << "Truck with license " << license << " removed successfully!" << endl;
							enter_to_exit();
						}
						else{
							cout << "Operation cancelled!" << endl;
							enter_to_exit();
							clearScreen();
							return;
						}
					}
					else {
						cout << "The truck with license " << license << " cannot be removed because it either on transit or registered to a future service" << endl;
						enter_to_exit();
					}
					break;
				}
			}
			if (!found) {
				invalidInput = true;
				cout<< "Truck with license " << license << " is not a part of the company's database" << endl;
				enter_to_exit();
			}
		}
	} while (invalidInput);
	clearScreen();

}

void Truck::showTruck(vector<Truck*>* trucks) {
	string license;
	bool invalidInput;
	vector<string> auxVec;
	do {
		clearScreen();
		invalidInput = false;
		cout << "What's the license of the truck you wish to see (XX-YY-ZZ)? "; getline(cin, license);
		if (license == "!q") return;

		//verifies if the license is valid or if it already exists.
		if (!checkLicenseV2(license)) {
			invalidInput = true;
		}
		else {
			for (vector<Truck*>::iterator it = trucks->begin(); it != trucks->end(); it++) {
				if ((*it)->getlicense() == license) {
					clearScreen();
					cout << "Truck found!!!" << endl;
					(*it)->info();
					enter_to_exit();
					return;
				}
			}
			invalidInput = true;
			cout << "Truck with license " << license << " is not a part of the company's database" << endl;
			enter_to_exit();
		}
	} while (invalidInput);
	clearScreen();
}
