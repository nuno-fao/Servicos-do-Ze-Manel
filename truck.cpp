#include "truck.h"

unordered_map<Hazard_enum, float> HazardousMat::hazardMul;
unordered_map<Temperature_enum, float> Congelation::tempMul;
float HazardousMat::pricePerKG;
float Congelation::pricePerKG;
float Normal::pricePerKG;
float Animal::pricePerKG;
map<unsigned,unsigned> HazardousMat::CapDist;
map<unsigned,unsigned> Congelation::CapDist;
map<unsigned,unsigned> Normal::CapDist;
map<unsigned,unsigned> Animal::CapDist;

type Normal::getType(){
    return type::ordinary;
}

type Animal::getType(){
    return type::animal;
}
type HazardousMat::getType(){
    return type::hazardous;
}
type Congelation::getType(){
    return type::lowTemperature;
}
type Truck::getType(){
    return type::ordinary;
}

Truck::~Truck(){

};


Truck::Truck(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo, car_brand brand) {
    this->license=license;
    this->available = available;
    this->registered = registered;
    this->capacity = capacity;
    this->cargo = cargo;
    this->brand = brand;
}

Congelation::Congelation(string license_c, bool available_c, bool registered_c, unsigned short capacity_c, unsigned short cargo_c, car_brand brand_c) : Truck(license_c,available_c,registered_c, capacity_c, cargo_c, brand_c) {

}
HazardousMat::HazardousMat(string license_h, bool available_h, bool registered_h, unsigned short capacity_h, unsigned short cargo_h, car_brand brand_h) : Truck(license_h, available_h, registered_h, capacity_h, cargo_h, brand_h) {

}
Animal::Animal(string license_a, bool available_a, bool registered_a, unsigned short capacity_a, unsigned short cargo_a, car_brand brand_a) : Truck(license_a,available_a,registered_a, capacity_a, cargo_a, brand_a) {

}
Normal::Normal(string license_n, bool available_n, bool registered_n, unsigned short capacity_n, unsigned short cargo_n, car_brand brand_n) : Truck(license_n,available_n,registered_n, capacity_n, cargo_n, brand_n) {

}

unsigned Truck::getcapacity() const {
    return capacity;
}

bool Truck::getavailable() const {
    return available;
}

bool Truck::getregistered() const{
    return registered;
}

string Truck::getlicense() const {
    return license;
}

car_brand Truck::getbrand() const
{
    return brand;
}

float Truck::getcargo() const {
    return cargo;
}

void Truck::setCargo(float cargo){
    this->cargo=cargo;
}

vector<Service*> *Truck::getServices(){
    return &assignedServices;
}


void Truck::setavailable(bool foo) {
    available = foo;
}

void Truck::setregistered(bool foo) {
    registered = foo;
}

void Truck::info() {
    cout << "License: " << license << endl;
    cout << "Brand: " << printBrand(brand) << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Available: ";
    (available) ? cout << "true" << endl : cout << "false" << endl << "\tCurrently transporting " << cargo << "KG of cargo" << endl;
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
    for (vector<Service*>::iterator it = assignedServices.begin(); it != assignedServices.end();it++) {
        if ((*it)->getId() == id) {
            assignedServices.erase(it);
            return;
        }
    }
}

void Truck::start_transport(unsigned short cargo) {
    available = false;
    this->cargo = cargo;
}

void Truck::loadFromFile(vector<Truck*>* trucks) {
    ifstream truckfile;
    string aux;
    string separator = "; ";
    string lic;
    string brand_string;
    car_brand br;
    char type='\0';
    bool avai, regist;
    unsigned short cap, carg;
    vector<string> auxVec;
    truckfile.open("files//trucks.txt");
    if (!truckfile.is_open()) { throw FailedToOpenTrucks(); }
    //load hazard multipliers for hazardous cargo trucks
    getline(truckfile, aux);
    auxVec = vectorString(aux, separator);
    HazardousMat::hazardMul[Hazard_enum::explosives] = stof(auxVec[0]);
    HazardousMat::hazardMul[Hazard_enum::gases] = stof(auxVec[1]);
    HazardousMat::hazardMul[Hazard_enum::flammableliq] = stof(auxVec[2]);
    HazardousMat::hazardMul[Hazard_enum::flammablesolid] = stof(auxVec[3]);
    HazardousMat::hazardMul[Hazard_enum::oxidizer] = stof(auxVec[4]);
    HazardousMat::hazardMul[Hazard_enum::poisons] = stof(auxVec[5]);
    HazardousMat::hazardMul[Hazard_enum::radioactive] = stof(auxVec[6]);
    HazardousMat::hazardMul[Hazard_enum::corrosives] = stof(auxVec[7]);
    HazardousMat::hazardMul[Hazard_enum::other] = stof(auxVec[8]);
    //load temperature multipliers for congelation trucks
    getline(truckfile, aux);
    auxVec = vectorString(aux, separator);
    Congelation::tempMul[Temperature_enum::p1_20] = stof(auxVec[0]);
    Congelation::tempMul[Temperature_enum::n20_0] = stof(auxVec[1]);
    Congelation::tempMul[Temperature_enum::n50_n21] = stof(auxVec[2]);
    Congelation::tempMul[Temperature_enum::n100_n51] = stof(auxVec[3]);
    //load price per KG of each truck
    getline(truckfile, aux);
    auxVec = vectorString(aux, separator);
    Congelation::pricePerKG = stof(auxVec[0]);
    HazardousMat::pricePerKG = stof(auxVec[1]);
    Animal::pricePerKG = stof(auxVec[2]);
    Normal::pricePerKG = stof(auxVec[3]);
    while (getline(truckfile, aux)) {
        getline(truckfile, lic);
        getline(truckfile, brand_string);
        br = selectBrand(brand_string);
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

            Truck *temp= new Animal(lic, avai, regist, cap, carg, br);
            trucks->push_back(temp);
            (Animal::CapDist.count(cap)) ? Animal::CapDist[cap] == 1 : Animal::CapDist[cap] += 1;
            break;
        }
        case 'C':{
            Truck *temp = new Congelation(lic, avai, regist, cap, carg, br);
            trucks->push_back(temp);
            (Congelation::CapDist.count(cap)) ? Congelation::CapDist[cap] == 1 : Congelation::CapDist[cap] += 1;
            break;
        }
        case 'H':{
            Truck *temp = new HazardousMat(lic, avai, regist, cap, carg, br);
            trucks->push_back(temp);
            (HazardousMat::CapDist.count(cap)) ? HazardousMat::CapDist[cap] == 1 : HazardousMat::CapDist[cap] += 1;
            break;
        }
        case 'N':{
            Truck *temp = new Normal(lic, avai, regist, cap, carg, br);
            trucks->push_back(temp);
            (Normal::CapDist.count(cap)) ? Normal::CapDist[cap] == 1 : Normal::CapDist[cap] += 1;
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
    truckfile << Congelation::tempMul[Temperature_enum::p1_20] << "; ";
    truckfile << Congelation::tempMul[Temperature_enum::n20_0] << "; ";
    truckfile << Congelation::tempMul[Temperature_enum::n50_n21] << "; ";
    truckfile << Congelation::tempMul[Temperature_enum::n100_n51] << endl;
    truckfile << Congelation::pricePerKG << "; ";
    truckfile << HazardousMat::pricePerKG << "; ";
    truckfile << Animal::pricePerKG << "; ";
    truckfile << Normal::pricePerKG << endl;
    for (auto it : *trucks) {
        truckfile << "::::::::::::::::::::::::::::" << endl;
        truckfile << it->getlicense() << endl;
        truckfile << printBrand(it->getbrand()) << endl;
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
    string brand_string;
    car_brand brand;
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
        cout << "What's the brand of the new truck? "; getline(cin, brand_string);
        if (brand_string == "!q") 
            return;

        //verifies if the string is valid
        if (!strIsChar(brand_string)) {
            invalidInput = true;
            clearScreen();
        }
    } while (invalidInput);

    brand = selectBrand(brand_string);

    clearScreen();

    do {
        invalidInput = false;
        cout << "What's the license of the new truck (XX-YY-ZZ)? " << license << endl;
        cout << "What's the brand of the new truck? " << brand_string << endl;
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
        cout << "What's the brand of the new truck? " << brand_string << endl;
        cout << "What's the capacity of the new truck? " << capacity << endl;
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
        cout << "Brand: " << brand_string << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Type: " << aux << endl;
        cout << "Do you wish proceed (Y/N)? ";
        cin >> confirmstr;
        clearBuffer();
    } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n" && confirmstr!="!q");	//confirmation
    if (confirmstr == "Y" || confirmstr == "y") {
        switch (type) {
        case('C'):{
            Truck* newTruck = new Congelation(license, true, false, date_u_short(capacity), 0, brand);
            trucks->push_back(newTruck);
	    Congelation::CapDist[capacity]=1;
            break;
        }
        case('A'):{
            Truck* newTruck = new Animal(license, true, false, date_u_short(capacity), 0, brand);
            trucks->push_back(newTruck);
	    Animal::CapDist[capacity]=1;
            break;
        }
        case('N'):{
            Truck* newTruck = new Normal(license, true, false, date_u_short(capacity), 0, brand);
            trucks->push_back(newTruck);
	    Normal::CapDist[capacity]=1;
            break;
        }
        case('H'):{
            Truck* newTruck = new HazardousMat(license, true, false, date_u_short(capacity), 0, brand);
            trucks->push_back(newTruck);
   	    HazardousMat::CapDist[capacity]=1;
            break;
        }
        }
        cout << "Truck with license " << license << " added successfully!" << endl;
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

