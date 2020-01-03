#include "workshop.h"

Workshop::Workshop(string n, car_brand b, int ua, queue<pair<Truck*, Date*>> wl,Date date)
{
    name = n;
    brand = b;
    unavailability = ua;
    waiting_line = wl;
    last_date=new Date(date);
}


Date *Workshop::getLastDate(){
    return last_date;
}

string Workshop::getName() const
{
    return name;
}

car_brand Workshop::getBrand() const
{
    return brand;
}

int Workshop::getUnavailability() const
{
    Date d1=*last_date;
    Date d2;
    if(d2<d1){
        float x=d1-d2;
        x/=1440;
        return x;
    }
    return 0;
}

queue<pair<Truck*, Date*>>* Workshop::getWaitingLine()
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

void Workshop::setUnavailability(int ua)
{
    unavailability = ua;
}

void Workshop::setWaitingLine(queue<pair<Truck*, Date*>> wl)
{
    waiting_line = wl;
}

void Workshop::loadFromFile(priority_queue<Workshop>* workshopLine)
{
    ifstream workshopFile;
    workshopFile.open("./files/workshops.txt");

    string temp_string_pair;
    string temp_brand;
    string temp_unavailability;
    string discarded;
    vector<string> vectored_pairs;
    string name;

    while (getline(workshopFile,name)) {
        car_brand brand;
        int unavailability;
        queue<pair<Truck*, Date*>>waiting_line;
        string date_s;
        Date date;
        getline(workshopFile, temp_brand);
        getline(workshopFile, temp_unavailability);
        getline(workshopFile, temp_string_pair);
        getline(workshopFile, date_s);
        getline(workshopFile, discarded);
        try{
            brand = selectBrand(temp_brand);
            unavailability = stoi(temp_unavailability);
            vectored_pairs = vectorString(temp_string_pair, ";");
            try{
                for (size_t i = 0; i < vectored_pairs.size() - 1; i += 2)
                {
                    Truck* new_truck = Company::getCompany()->getTruck(vectored_pairs.at(i));
                    Date* new_date = new Date(vectored_pairs.at(i + 1));
                    waiting_line.push(make_pair(new_truck, new_date));
                }
            }
            catch(...){

            }
            try{
                date=Date(date_s);
            }
            catch(...){
                cout<<date_s<<endl;
            }
            workshopLine->push(Workshop(name, brand, unavailability, waiting_line,date));
        }
        catch(...){

        }



    }
    workshopFile.close();
}

void Workshop::saveToFile(priority_queue<Workshop>* workshopLine)
{
    ofstream workshopFile;
    workshopFile.open("./files/workshops.txt");

    string discarded = "::::::::::::::::::::::::::::";


    while (!workshopLine->empty()) {

        try {
            workshopFile << workshopLine->top().getName() << endl;
            workshopFile << printBrand(workshopLine->top().getBrand()) << endl;
            workshopFile << workshopLine->top().getUnavailability() << endl;

            Workshop tmp=workshopLine->top();
            while (!(tmp.getWaitingLine()->empty()))
            {
                workshopFile << tmp.getWaitingLine()->front().first->getlicense() << ";";
                workshopFile << tmp.getWaitingLine()->front().second->getDate() << ";";

                tmp.getWaitingLine()->pop();
            }

            workshopFile<<endl << workshopLine->top().last_date->getDate();
            workshopFile << endl << discarded;
            workshopLine->pop();

            if (!workshopLine->empty())
                workshopFile << endl;
        }
        catch (...) {
            continue;
        }
    }
    workshopFile.close();
}

void Workshop::addWorkshop(priority_queue<Workshop>* workshop_line)
{
    clearScreen();
    string name, temp_brand;
    string confirmstr;
    car_brand brand;
    int unavailability = 0;
    queue<pair<Truck*, Date*>>* standard_queue = new queue<pair<Truck*, Date*>>();
    bool invalidInput;

    do {
        invalidInput = false;
        cout << "Please input the new Workshop's name: " << endl;
        getline(cin, name);
        if (name == "!q") {
            clearScreen();
            return;
        }

        // Verifies if workshop already exists.
        if (!checkWorkshopName(name)) {
            invalidInput = true;
            clearScreen();
            cout<<"Name already on the database, please try again"<<endl;
        }
    } while (invalidInput);

    clearScreen();

    do {
        invalidInput = false;
        cout << "Please input the new Workshop's name: " << name << endl<<endl;
        cout << "Mercedes, Man, Ford, Volvo, Iveco, Scania, Volkswagen, Mitsubishi"<<endl;
        cout << "Please input the new Workshop's brand: " << endl;
        getline(cin, temp_brand);
        if (temp_brand == "!q") {
            clearScreen();
            //clearBuffer();
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
        workshop_line->push(Workshop(name, brand, unavailability, *standard_queue,Date()));
        cout << "Workshop " << name << " added successfully!" << endl;
        enter_to_exit();
    }
    else {
        cout << "Operation cancelled!" << endl;
        enter_to_exit();
    }
    clearScreen();
}

void Workshop::editWorkshop(priority_queue<Workshop>* workshop_line)
{
    clearScreen();
    string name, temp_brand, name_to_change, brand_to_change_string;
    string confirmstr;
    car_brand brand_to_change;
    bool invalidInput;

    do {
        invalidInput = false;
        cout << "Please input the Workshop's name to edit: " << endl;
        getline(cin, name);
        if (name == "!q") {
            clearScreen();
            return;
        }

        // Verifies if name given is valid
        if (!strIsChar(name)) {
            invalidInput = true;
            clearScreen();
        }
    } while (invalidInput);

    clearScreen();

    Workshop to_edit = getWorkshop(name);


    if (to_edit.getName() == "nanana") {
        cout << "Workshop not found" << endl;
        enter_to_exit();
        clearScreen();
        return;
    }

    do {
        invalidInput = false;
        cout << "Please input the Workshop's new name: " << endl;
        getline(cin, name_to_change);
        if (name_to_change == "!q") {
            clearScreen();
            //clearBuffer();
            return;
        }

        // Verifies if name already exists
        if (!checkWorkshopName(name_to_change)) {
            invalidInput = true;
            clearScreen();
        }
    } while (invalidInput);

    clearScreen();

    do {
        invalidInput = false;
        cout << "Please input the new Workshop's name: " << name_to_change << endl;
        cout << "Please input the new Workshop's brand: " << endl;
        getline(cin, brand_to_change_string);
        if (brand_to_change_string == "!q") {
            clearScreen();
            //clearBuffer();
            return;
        }

        // Verifies if brand if valid
        if (!verifyBrand(brand_to_change_string)) {
            invalidInput = true;
            clearScreen();
        }
        else
            brand_to_change = selectBrand(brand_to_change_string);
    } while (invalidInput);

    // Confirmation screen

    do {
        clearScreen();
        cout << "You're about to add a Workshop with the following characteristics: " << endl;
        cout << "Name: " << name_to_change << endl;
        cout << "Brand: " << printBrand(brand_to_change) << endl;
        cout << "Do you wish proceed (Y/N)? ";
        cin >> confirmstr;
        clearBuffer();
    } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n" && confirmstr != "!q");	// Confirmation

    if (confirmstr == "Y" || confirmstr == "y") {
        to_edit.setName(name_to_change);
        to_edit.setBrand(brand_to_change);
        workshop_line->push(to_edit);
        cout << "Workshop changed successfully!" << endl;
        enter_to_exit();
    }
    else {
        cout << "Operation cancelled!" << endl;
        enter_to_exit();
    }
    clearScreen();
}

void Workshop::deleteWorkshop(priority_queue<Workshop>* workshop_line)
{
    // Copying

    priority_queue<Workshop> to_replace = *workshop_line;

    clearScreen();
    string name;
    string confirmstr;
    bool invalidInput;

    do {
        invalidInput = false;
        cout << "Please input the Workshop's name to delete: " << endl;
        getline(cin, name);
        if (name == "!q") {
            clearScreen();
            return;
        }

        // Verifies if name is valid
        if (!strIsChar(name)) {
            invalidInput = true;
            clearScreen();
        }
    } while (invalidInput);

    clearScreen();


    Workshop to_delete = getWorkshop(name);

    if (!to_delete.getWaitingLine()->empty()) {
        cout << "The workshop has active services and cannot be deleted" << endl;
        enter_to_exit();
        clearScreen();
        return;
    }

    if (to_delete.getName() == "nanana") {
        cout << "Workshop not found" << endl;
        enter_to_exit();
        clearScreen();
        return;
    }

    // Confirmation screen

    do {
        clearScreen();
        cout << "You're about to delete a Workshop with the following characteristics: " << endl;
        cout << "Name: " << name << endl;
        cout << "Brand: " << printBrand(to_delete.getBrand()) << endl;
        cout << "Do you wish proceed (Y/N)? ";
        cin >> confirmstr;
        clearBuffer();
    } while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n" && confirmstr != "!q");	// Confirmation

    if (confirmstr == "Y" || confirmstr == "y") {

        // Empty the workshop_line

        while (!workshop_line->empty()) {
            workshop_line->pop();
        }

        while (!to_replace.empty()) {
            if (to_replace.top().getName() != to_delete.getName())
                workshop_line->push(to_replace.top());

            to_replace.pop();
        }

        cout << "Workshop " << name << " deleted successfully!" << endl;
        enter_to_exit();
    }
    else {
        cout << "Operation cancelled!" << endl;
        enter_to_exit();
    }
    clearScreen();
}

int Workshop::calculateUnavailability(Date d1)
{
    Date now_date;
    return (d1 - now_date) / 1440;
}

void Workshop::addService(Truck* truck, Date date)
{
    Date maxDate;

    waiting_line.push(make_pair(truck, new Date(date)));
    *last_date=date;
    Date tmp;
    cout<<date-tmp<<endl;
    enter_to_exit();
    setUnavailability(getUnavailability());

}


bool operator<(const Workshop &w1,const Workshop &w2)
{
    if (w1.getUnavailability() > w2.getUnavailability())
        return true;
    return false;
}

bool Workshop::notInWorkshop(Truck* truck)
{
    priority_queue<Workshop> temp = *Company::getCompany()->getWorkshopLine();

    while (!temp.empty()) {

        Workshop tmp=temp.top();
        while (!tmp.getWaitingLine()->empty()) {
            if (tmp.getWaitingLine()->front().first->getlicense() == truck->getlicense())
                return false;

            tmp.getWaitingLine()->pop();
        }
        temp.pop();
    }

    return true;
}

void Workshop::info() {
    cout << "Name: " << name << endl;
    cout << "Brand: " << printBrand(brand) << endl;
    cout << "Unavailability: " << getUnavailability() << endl;

    queue<pair<Truck*, Date*>> temp_queue = waiting_line;

    while (!temp_queue.empty()) {
        cout << "Truck: " << temp_queue.front().first->getlicense() << endl;
        cout << "Date: ";
        temp_queue.front().second->show();
        temp_queue.pop();
    }
    cout << "::::::::::::::::::::::::::::" << endl;
}

Workshop Workshop::getWorkshop(string name)
{
    // Copying
    priority_queue<Workshop> temp_priority_queue = *Company::getCompany()->getWorkshopLine();
    vector<Workshop> tmp_vect;
    while (!temp_priority_queue.empty()) {

        if (temp_priority_queue.top().getName() == name){
            Workshop tmp=temp_priority_queue.top();
            temp_priority_queue.pop();
            for(auto i:tmp_vect){
                temp_priority_queue.push(i);
            }
            *Company::getCompany()->getWorkshopLine()=temp_priority_queue;
            return  tmp;
        }
        tmp_vect.push_back(temp_priority_queue.top());
        temp_priority_queue.pop();
    }

    return Workshop("nanana",car_brand::None,0,queue<pair<Truck*,Date*>>(),Date());
}
