// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends There.
//

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <map>

#include "client.h"
#include "truck.h"
#include "service.h"
#include "company.h"
#include "misc.h"
#include "driver.h"
#include "workshop.h"

using namespace std;


void manage_client(Client *client);
void menu_services();
void menu_editprices();
void mainMenu();
void menu_clients();
void menu_trucks();
void information();
void clientsInformation();
void trucksInformation();
void infoEveryServices(),infoOnQueueServices(),infoOnTransitServices(),infoFinishedServices();
void servicesInformation();
void moneyInformation();
void menu_inactive_clients();


/*
This function receives a name and returns true if it is valid
*/


Company *Company::company = nullptr;
int main()
{
    clearScreen();
    Company *Ze_Manel = nullptr;
    Ze_Manel=Company::getCompany();

    try{
        Truck::loadFromFile(Ze_Manel->getVectorTrucks());
    }
    catch(const FailedToOpenTrucks &){
        cout<<"Can't open trucks.txt, program is ending with error"<<endl;
    }

    try{
        Client::loadClients(*Ze_Manel->getVectorClients());
    }
    catch(const CantOpenClientFile &){
        ofstream r;
        r.open("./files/clients.txt");
        r.close();
        Client::loadClients(*Ze_Manel->getVectorClients());
    }
    Ze_Manel->loadStats();

    sort(((*Ze_Manel).getVectorTrucks())->begin(),((*Ze_Manel).getVectorTrucks())->end(),cmp_classes<Truck>);
    sort(((*Ze_Manel).getVectorClients())->begin(),((*Ze_Manel).getVectorClients())->end(),cmp_classes<Client>);
    sort(((*Ze_Manel).getVectorServicesOnQueue())->begin(),((*Ze_Manel).getVectorServicesOnQueue())->end(),cmpOnQueue);
    sort(((*Ze_Manel).getVectorServicesOnTransit())->begin(),((*Ze_Manel).getVectorServicesOnTransit())->end(),cmpOnTransit);


    try{
        Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());
    }
    catch(const ServiceOnQueueFileError){
        ofstream r;
        r.open("./files/on_queue_services.txt");
        r.close();
        Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());

    }
    catch(const ServiceOnTransitFileError){
        ofstream r;
        r.open("./files/on_transit_services.txt");
        r.close();
        Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());

    }
    catch(const ServiceFinishedFileError){
        ofstream r;
        r.open("./files/finished_services.txt");
        r.close();
        Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());

    }

    //Service::test();
    mainMenu();

    delete Ze_Manel;


    return 0;
}

void mainMenu(){
    unsigned opt=1;
    while (opt != 0) {
        cout << "****************************" << endl;
        cout << "TRANSPORTES SML" << endl;
        cout << "****************************" << endl;
        cout<<"[0] Exit program"<<endl;
        cout<<"[1] Clients"<<endl;
        cout<<"[2] Trucks"<<endl;
        cout<<"[3] Services"<<endl;
        cout<<"[4] Information"<<endl;
        cout << "[5] Testing section" << endl;

        if(cin>>opt && opt<=5)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1:{
                menu_clients();
                break;
            }
            case 2:{
                menu_trucks();
                break;
            }

            case 3:{
                menu_services();
                break;
            }
            case 4:{
                information();
                break;
            }
            case 5: {
                Workshop::loadFromFile();
                priority_queue<Workshop*>* temp_priority_queue = Company::getCompany()->getWorkshopLine();
                
                while (!temp_priority_queue->empty()) {
                    temp_priority_queue->top()->info();
                }

                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void menu_clients(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Add Client"<<endl;
        cout<<"[2] Manage Client"<<endl;
        cout<<"[0] Return to Main Menu"<<endl;
        if(cin>>opt && opt<=2)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1:{
                try {
                    clearBuffer();
                    Client::addClient(Company::getCompany()->getVectorClients());
                }
                catch(const ClientInVector &e){
                    clearScreen();
                    clearBuffer();
                    cout << e.erro << endl;
                    enter_to_exit();
                }
                catch(...){

                }

                break;
            }
            case 2:{
                long nif=0;
                Client *temp_client;
                do{
                    for(auto i: *Company::getCompany()->getVectorClients()){
                        cout<<*i;
                    }
                }while((nif=askForId("Client","manage","Nif"))==-2);

                if(nif>0){
                    try {
                        temp_client=Company::getCompany()->getClient(unsigned(nif));
                        manage_client(temp_client);

                    } catch (const NotAClient &e) {
                        clearScreen();
                        clearBuffer();
                        cout << e.erro << endl;
                        enter_to_exit();
                    }
                }
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void menu_trucks() {
    unsigned opt = 1;
    while (opt != 0) {
        clearScreen();
        cout << "[1] Add Truck" << endl;
        cout << "[2] Edit Truck Prices" << endl;
        cout << "[3] Remove Truck" << endl;
        cout << "[0] Return to Main Menu" << endl;
        if (cin >> opt && opt <= 3)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1: {
                clearBuffer();
                Truck::createTruck(Company::getCompany()->getVectorTrucks());
                break;
            }
            case 2: {
                clearBuffer();
                menu_editprices();
                break;
            }
            case 3: {
                clearBuffer();
                Truck::removeTruck(Company::getCompany()->getVectorTrucks());
                break;
            }

            default:
                opt = 1;
            }
        }
        else {
            opt = 1;
            clearBuffer();
            clearScreen();
            cout << "Not a valid option, please try again" << endl;
        }
    }
}

void menu_services(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Add Service"<<endl;
        cout<<"[2] Edit Service"<<endl;
        cout<<"[3] Remove Service"<<endl;
        cout<<"[0] Return to Main Menu"<<endl;
        if(cin>>opt && opt<=3)
        {
            clearScreen();
            switch (opt) {
            case 2:{

                long id=long(0);
                if(Company::getCompany()->getVectorServicesOnQueue()->size()){
                    Service *temp_client = nullptr;
                    do{
                        for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                            cout<<"("<<i->getId()<<") "<<i->getMaterial()<<"   "<<i->getIDate()->getYear()<<"/"<<i->getIDate()->getMonth()<<"/"<<i->getIDate()->getDay()<<", "<<i->getIDate()->getHour()<<":"<<i->getIDate()->getMinute()<<endl;
                        }
                    }while((id=askForId("Service","Edit","Id"))==-2);
                    clearScreen();
                    for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getId()==long(id)){
                            temp_client=i;
                            break;
                        }
                    }
                    if(temp_client==nullptr){
                        cout<<"couldn't find the specified service"<<endl;
                        clearBuffer();
                        enter_to_exit();
                    }
                    else{

                        temp_client->editService();
                        cout<<"Successfully Edited"<<endl;
                    }
                }
                else{
                    cout<<"No Service can be Edited"<<endl;
                    clearBuffer();
                    enter_to_exit();
                }
                break;

            }
            case 3:{

                long id=long(0);
                if(Company::getCompany()->getVectorServicesOnQueue()->size()){
                    Service *temp_client = nullptr;
                    do{
                        for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                            cout<<"("<<i->getId()<<") "<<i->getMaterial()<<"   "<<i->getIDate()->getYear()<<"/"<<i->getIDate()->getMonth()<<"/"<<i->getIDate()->getDay()<<", "<<i->getIDate()->getHour()<<":"<<i->getIDate()->getMinute()<<endl;
                        }
                    }while((id=askForId("Service","Remove","Id"))==-2);
                    clearScreen();
                    for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getId()==long(id)){
                            temp_client=i;
                            break;
                        }
                    }
                    if(temp_client==nullptr){
                        cout<<"couldn't find the specified service"<<endl;
                    }
                    else{
                        try{
                            Service::removeService(Company::getCompany()->getVectorServicesOnQueue(),unsigned(id));

                            cout<<"Successfully Removed"<<endl;
                        }
                        catch(ServiceDoNotExist e){
                            cout<<e.erro<<endl;
                        }
                    }
                }
                else{
                    cout<<"No Service can be Canceled"<<endl;
                    clearBuffer();
                }
                enter_to_exit();
                break;

            }
            case 0:
                break;
            case 1:{
                clearScreen();
                for(auto i:*Company::getCompany()->getVectorClients()){
                    cout<<*i;
                }
                try{
                    int temp=int(askForId("Client","add a Service","Nif"));
                    if(temp==-1)
                        break;
                    Client *tempClient= Company::getCompany()->getClient(unsigned(temp));
                    clearBuffer();
                    clearScreen();
                    Service::addService(Company::getCompany()->getVectorServicesOnQueue(),tempClient);
                    tempClient->getLastReservation()->~Date();
                    tempClient->setLastReservation(new Date());
                    Company::getCompany()->eraseClientFromHash(tempClient->getNif());
                }
                catch(const NotAClient &e){
                    clearBuffer();
                    cout<<e.erro<<endl;
                    enter_to_exit();
                }
                catch(const ServiceDoNotExist &e){
                    cout<<e.erro<<endl;
                    enter_to_exit();
                }
                catch(...){
                    //clearBuffer();
                    cout << "Stopped operation! Couldn't assign Enough Trucks" << endl;
                    enter_to_exit();
                }

                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void information(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Clients"<<endl;
        cout<<"[2] Services"<<endl;
        cout<<"[3] Trucks"<<endl;
        cout<<"[4] Revenue"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=4)
        {
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:
                clientsInformation();
                break;
            case 2:{
                servicesInformation();
                break;
            }
            case 3:
                trucksInformation();
                break;

            case 4:{
                moneyInformation();
                break;
            }
            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

inline  bool cpm_clientsSpent(Client *a,Client *b){
    return a->getMoneySpent()<b->getMoneySpent();
}
void clientsInformation(){
    unsigned opt=1;
    clearScreen();
    while (opt!=0) {
        cout<<"[1] Order by Nif"<<endl;
        cout<<"[2] Order by money Spent(low to high)"<<endl;
        cout<<"[3] Order by money Spent(high to low)"<<endl; // Não funciona
        cout<<"[4] Order by number of Services"<<endl;
        cout<<"[5] Show Clients with Services on queue"<<endl;
        cout<<"[6] Show Clients with Services on Transit"<<endl;
        cout<<"[7] Show Specific Client"<<endl;
        cout << "[8] Inactive Client Menu" << endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=8)
        {
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:
                if(Company::getCompany()->getVectorClients()->size())
                    for(auto i: *Company::getCompany()->getVectorClients()){
                        cout<<*i;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            case 2:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(),temp.end(),cpm_clientsSpent);
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                        cout<<i->getMoneySpent()<<endl;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 3:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(), temp.end(), cpm_clientsSpent);
                if (temp.size())
                    for (auto it = temp.rbegin(); it != temp.rend(); it++) {
                        cout << *(*it);
                        cout << (*it)->getMoneySpent() << endl;
                    }
                else
                    cout << "There is no Information to show" << endl;

                clearBuffer();
                enter_to_exit();
                break;

            }
            case 4:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(),temp.end(),[](Client *a, Client *b)
                {
                    return (a->getServicesVector()->size() < b->getServicesVector()->size());
                }
                );
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                        cout<<i->getServicesVector()->size()<<endl;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 5:{
                map<Client*, int>::iterator it;
                map<Client*, int> temp_ocurre;
                for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                    it = temp_ocurre.find(i->getClient());
                    if(it != temp_ocurre.end()){
                        it->second++;
                    }
                    else {
                        temp_ocurre[i->getClient()]=0;
                    }
                }
                if(temp_ocurre.size())
                    for(auto i: temp_ocurre){
                        cout<<*i.first;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 6:{
                map<Client*, int>::iterator it;
                map<Client*, int> temp_ocurre;
                for(auto i: *Company::getCompany()->getVectorServicesOnTransit()){
                    it = temp_ocurre.find(i->getClient());
                    if(it != temp_ocurre.end()){
                        it->second++;
                    }
                    else {
                        temp_ocurre[i->getClient()]=0;
                    }
                }
                if(temp_ocurre.size())
                    for(auto i: temp_ocurre){
                        cout<<*i.first;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 7:{
                long nif = 0;
                Client* temp_client;
                do {
                    clearScreen();
                    for (auto i : *Company::getCompany()->getVectorClients()) {
                        cout << *i;
                    }
                    if(nif==-2){
                        cout<<"Nif not Acceptable"<<endl;
                    }
                } while ((nif = askForId("Client", "manage", "Nif")) == -2);
                clearScreen();

                if (nif > 0) {
                    try {
                        temp_client = Company::getCompany()->getClient(unsigned(nif));

                        while(true){
                            cout << endl << *temp_client << endl;
                            cout<<"[1] See services"<<endl;
                            cout<<"[0] Return"<<endl;
                            unsigned temp_opt=3;
                            if(cin>>temp_opt){
                                if(temp_opt==1){
                                    clearScreen();
                                    cout << "Services: " << endl;
                                    for(auto it = temp_client->getServicesVector()->begin(); it != temp_client->getServicesVector()->end(); it++)
                                    {
                                        cout << (*it) << endl;
                                    }
                                    clearBuffer();
                                    enter_to_exit();
                                    clearScreen();
                                    break;
                                }
                                else if (temp_opt==0) {
                                    clearBuffer();
                                    clearScreen();
                                    break;
                                }
                                else{
                                    clearScreen();
                                    cout<<"Input not acceptable"<<endl;
                                    clearBuffer();
                                }
                            }
                            else{
                                clearScreen();
                                cout<<"Input not acceptable"<<endl;
                                clearBuffer();
                            }
                        }
                    }
                    catch (const NotAClient &e) {
                        cout << e.erro << endl;
                    }
                }
                break;
            }
			case 8:
                menu_inactive_clients();
				break;

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void trucksInformation() {
    unsigned opt = 1;
    clearScreen();
    while (opt != 0) {
        cout << "[1] See all" << endl;
        cout << "[2] See Congelation trucks" << endl;
        cout << "[3] See Hazardous Material trucks" << endl; // Não funciona
        cout << "[4] See Animal Material trucks" << endl;
        cout << "[5] See Normal Material trucks" << endl;
        cout << "[6] Show Trucks with Services on queue" << endl;
        cout << "[7] Show Trucks on Transit" << endl;
        cout << "[8] Show Specific Truck" << endl;
        cout << "[9] Show Multipliers and Standard Prices" << endl;
        cout << "[0] Return" << endl;
        if (cin >> opt && opt <= 9)
        {
            clearScreen();
            switch (opt) {
            case 0: {
                return;
            }
            case 1:{
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        i->info();
                        cout << endl;
                        nInfo=false;
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 2: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i)==typeid(Congelation)) {
                            i->info();
                            cout << endl;
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 3: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i) == typeid(HazardousMat)) {
                            i->info();
                            cout << endl;
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 4: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i) == typeid(Animal)) {
                            i->info();
                            cout << endl;
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 5: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (typeid(*i) == typeid(Normal)) {
                            i->info();
                            cout << endl;
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 6: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if ((!(i->getavailable()) && i->getServices()->size()>1) || (i->getavailable() && i->getregistered())) {
                            i->info();
                            cout << endl;
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 7: {
                bool nInfo=true;
                if (Company::getCompany()->getVectorTrucks()->size())
                    for (auto i : *Company::getCompany()->getVectorTrucks()) {
                        if (!(i->getavailable())) {
                            i->info();
                            cout << endl;
                            nInfo=false;
                        }
                    }
                if(nInfo)
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 8: {
                string license;
                bool invalidInput;
                vector<string> auxVec;
                if (Company::getCompany()->getVectorTrucks()->size()) {
                    clearBuffer();

                    do {
                        clearScreen();
                        invalidInput = false;
                        cout << "What's the license of the truck you wish to see (XX-YY-ZZ)? "; getline(cin, license);
                        if (license == "!q") break;

                        //verifies if the license is valid or if it already exists.
                        if (!checkLicenseV2(license)) {
                            invalidInput = true;
                        }
                        else {
                            invalidInput = true;
                            for (vector<Truck*>::iterator it = Company::getCompany()->getVectorTrucks()->begin(); it != Company::getCompany()->getVectorTrucks()->end(); it++) {
                                if ((*it)->getlicense() == license) {
                                    clearScreen();
                                    cout << "Truck found!!!" << endl;
                                    (*it)->info();
                                    invalidInput=false;
                                    break;
                                }
                            }
                            if(invalidInput){
                                cout << "Truck with license " << license << " is not a part of the company's database" << endl;
                                enter_to_exit();
                            }
                        }
                    } while (invalidInput);
                }
                else
                    cout << "There is no Information to show" << endl;
                enter_to_exit();
                break;
            }

            case 9:
                clearScreen();
                clearBuffer();
                cout << "---Hazards---" << endl;
                cout << "Explosives multiplier: " << HazardousMat::hazardMul[Hazard_enum::explosives] << endl;
                cout << "Flammable liquid multiplier: " << HazardousMat::hazardMul[Hazard_enum::flammableliq] << endl;
                cout << "Flammable solid multiplier: " << HazardousMat::hazardMul[Hazard_enum::flammablesolid] << endl;
                cout << "Gases multiplier: " << HazardousMat::hazardMul[Hazard_enum::gases] << endl;
                cout << "Oxidizer multiplier: " << HazardousMat::hazardMul[Hazard_enum::oxidizer] << endl;
                cout << "Poisons multiplier: " << HazardousMat::hazardMul[Hazard_enum::poisons] << endl;
                cout << "Corrosives multiplier: " << HazardousMat::hazardMul[Hazard_enum::corrosives] << endl;
                cout << "Radioactive multiplier: " << HazardousMat::hazardMul[Hazard_enum::radioactive] << endl;
                cout << "'Other' multiplier: " << HazardousMat::hazardMul[Hazard_enum::other] << endl;
                cout <<endl<< "---Congelation---" << endl;
                cout << "[1,20] multiplier: " << Congelation::tempMul[Temperature_enum::p1_20] << endl;
                cout << "[-20,0] multiplier: " << Congelation::tempMul[Temperature_enum::n20_0] << endl;
                cout << "[-50,-21] multiplier: " << Congelation::tempMul[Temperature_enum::n50_n21] << endl;
                cout << "[-100,-51] multiplier: " << Congelation::tempMul[Temperature_enum::n100_n51] << endl;
                cout <<endl<< "---STD Prices---" << endl;
                cout << "Congelation price per KG: " << Congelation::pricePerKG << endl;
                cout << "Hazard price per KG: " << HazardousMat::pricePerKG << endl;
                cout << "Animal price per KG: " << Animal::pricePerKG << endl;
                cout << "Normal price per KG: " << Normal::pricePerKG << endl;
                enter_to_exit();
                break;

            default:
                opt = 1;
            }
        }
        else {
            opt = 1;
            clearBuffer();
            clearScreen();
            cout << "Not a valid option, please try again" << endl;
        }
    }
}

void menu_editprices() {
    unsigned opt = 1;
    while (opt != 0) {
        clearScreen();
        cout << "[1] Temperature Price Multipliers" << endl;
        cout << "[2] Hazard Multipliers" << endl;
        cout << "[3] Standard price per KG" << endl;
        cout << "[0] Return to Main Menu" << endl;
        if (cin >> opt && opt <= 3)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 2: {
                clearBuffer();
                unsigned opt1 = 1;
                string aux;
                while (opt1 != 0) {
                    clearScreen();
                    cout << "[1] Edit Explosives" << endl;
                    cout << "[2] Edit Gases" << endl;
                    cout << "[3] Edit Flammable Liquid" << endl;
                    cout << "[4] Edit Flammable Solid" << endl;
                    cout << "[5] Edit Oxidizer" << endl;
                    cout << "[6] Edit Poison" << endl;
                    cout << "[7] Edit Radioactive" << endl;
                    cout << "[8] Edit Corrosives" << endl;
                    cout << "[9] Edit 'Other'" << endl;
                    cout << "[0] Return to Main Menu" << endl;
                    if (cin >> opt1 && opt1 <= 9)
                    {
                        clearScreen();
                        switch (opt1) {
                        case 0:
                            break;
                        case 1: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for explosives is: " << HazardousMat::hazardMul[Hazard_enum::explosives] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::explosives] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 2: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for gases is: " << HazardousMat::hazardMul[Hazard_enum::gases] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::gases] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 3: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for flammable liquid is: " << HazardousMat::hazardMul[Hazard_enum::flammableliq] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::flammableliq] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 4: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for flammable solid is: " << HazardousMat::hazardMul[Hazard_enum::flammablesolid] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::flammablesolid] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 5: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for oxidizer is: " << HazardousMat::hazardMul[Hazard_enum::oxidizer] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::oxidizer] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 6: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for poisons is: " << HazardousMat::hazardMul[Hazard_enum::poisons] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::poisons] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 7: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for radioactive is: " << HazardousMat::hazardMul[Hazard_enum::radioactive] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::radioactive] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 8: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for corrosive is: " << HazardousMat::hazardMul[Hazard_enum::corrosives] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::corrosives] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 9: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for 'other' is: " << HazardousMat::hazardMul[Hazard_enum::other] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::hazardMul[Hazard_enum::other] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }

                        default:
                            opt1 = 1;
                        }
                    }
                    else {
                        opt = 1;
                        clearBuffer();
                        clearScreen();
                        cout << "Not a valid option, please try again" << endl;
                    }
                }
                break;
            }
            case 1: {
                clearBuffer();
                unsigned opt1 = 1;
                string aux;
                while (opt1 != 0) {
                    clearScreen();
                    cout << "[1] Edit [1,20]" << endl;
                    cout << "[2] Edit [-20,0]" << endl;
                    cout << "[3] Edit [-50,-21]" << endl;
                    cout << "[4] Edit [-100,-51]" << endl;
                    cout << "[0] Return to Main Menu" << endl;
                    if (cin >> opt1 && opt1 <= 4)
                    {
                        clearScreen();
                        switch (opt1) {
                        case 0:
                            break;
                        case 1: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for [1,20] is: " << Congelation::tempMul[Temperature_enum::p1_20] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::p1_20] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 2: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for [-20,0] is: " << Congelation::tempMul[Temperature_enum::n20_0] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::n20_0] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 3: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for [-50,-21] is: " << Congelation::tempMul[Temperature_enum::n50_n21] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::n50_n21] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 4: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current multiplier for [-100,-51] is: " << Congelation::tempMul[Temperature_enum::n100_n51] << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::tempMul[Temperature_enum::n100_n51] = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }

                        default:
                            opt1 = 1;
                        }
                    }
                    else {
                        opt = 1;
                        clearBuffer();
                        clearScreen();
                        cout << "Not a valid option, please try again" << endl;
                    }
                }
                break;
            }
            case 3: {
                clearBuffer();
                unsigned opt1 = 1;
                string aux;
                while (opt1 != 0) {
                    clearScreen();
                    cout << "[1] Edit congelation trucks' price per KG" << endl;
                    cout << "[2] Edit hazardous material trucks' price per KG" << endl;
                    cout << "[3] Edit animal trucks' price per KG" << endl;
                    cout << "[4] Edit normal trucks' price per KG" << endl;
                    cout << "[0] Return to Main Menu" << endl;
                    if (cin >> opt1 && opt1 <= 4)
                    {
                        clearScreen();
                        switch (opt1) {
                        case 0:
                            break;
                        case 1: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current congelation trucks' price per KG: " << Congelation::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Congelation::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 2: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current hazardous material trucks' price per KG is: " << HazardousMat::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    HazardousMat::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 3: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current animal trucks' price per KG is: " << Animal::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Animal::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }
                        case 4: {
                            clearBuffer();
                            clearScreen();
                            cout << "Current normal trucks' price per KG is: " << Normal::pricePerKG << endl;
                            cout << "What will be the new value? "; cin >> aux;
                            clearBuffer();
                            if (strIsNumber(aux)) {
                                if (stof(aux) > 0) {
                                    Normal::pricePerKG = stof(aux);
                                    cout << "Multiplier changed successfully!!!" << endl;
                                    enter_to_exit();
                                }
                                else {
                                    cout << endl << "The multiplier must be a positive number." << endl;
                                    enter_to_exit();
                                }
                            }
                            else {
                                cout << endl << "The multiplier must be a positive number." << endl;
                                enter_to_exit();
                            }
                            break;
                        }

                        default:
                            opt1 = 1;
                        }
                    }
                    else {
                        opt = 1;
                        clearBuffer();
                        clearScreen();
                        cout << "Not a valid option, please try again" << endl;
                    }
                }
                break;
            }

            default:
                opt = 1;
            }
        }
        else {
            opt = 1;
            clearBuffer();
            clearScreen();
            cout << "Not a valid option, please try again" << endl;
        }
    }
}
void servicesInformation(){
    unsigned opt=1;
    clearScreen();
    while (opt!=0) {
        cout<<"[1] Every Service"<<endl;
        cout<<"[2] Services On Queue"<<endl;
        cout<<"[3] Services On Transit"<<endl; // Não funciona
        cout<<"[4] Services Finished"<<endl;
        cout<<"[5] Services From Specific Location"<<endl;
        cout<<"[6] Services To Specific Location"<<endl;
        cout<<"[7] Services Between Two Dates"<<endl;
        cout<<"[8] Animal Services"<<endl;
        cout<<"[9] Normal Services"<<endl;
        cout<<"[10] Congelation Services"<<endl;
        cout<<"[11] Hazardous Services"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=12)
        {
            clearScreen();
            clearBuffer();
            try {
                switch (opt) {
                case 8:{
                    string temp_origin;
                    bool print=false;
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getType()==type::animal){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(i->getType()==type::animal){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(i->getType()==type::animal){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print)
                        enter_to_exit();
                    clearScreen();
                    break;
                }
                case 9:{
                    string temp_origin;
                    bool print=false;
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getType()==type::ordinary){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(i->getType()==type::ordinary){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(i->getType()==type::ordinary){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print)
                        enter_to_exit();
                    clearScreen();
                    break;
                }
                case 10:{
                    string temp_origin;
                    bool print=false;
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getType()==type::lowTemperature){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(i->getType()==type::lowTemperature){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(i->getType()==type::lowTemperature){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print)
                        enter_to_exit();
                    clearScreen();
                    break;
                }
                case 11:{
                    string temp_origin;
                    bool print=false;
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getType()==type::hazardous){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(i->getType()==type::hazardous){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(i->getType()==type::hazardous){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print)
                        enter_to_exit();
                    clearScreen();
                    break;
                }
                case 7:{
                    bool variable_error=true;
                    string tempString;
                    vector<string> tempVector;
                    while (variable_error) {
                        try {
                            cout<<"Enter the departure date(yy mm dd)"<<endl;
                            if(getline(cin,tempString)){
                                clearScreen();
                                checkIfOut(tempString);
                                tempVector = vectorString(tempString," ");
                                for(auto p:tempVector){
                                    if(!strIsNumber(p)){
                                        tempVector.clear();
                                        variable_error=true;
                                        clearScreen();
                                        cout<<"Date Input not Aceptable, please try again"<<endl;
                                        break;
                                    }
                                }
                                if(tempVector.size()==3){
                                    Date i(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),23,59);
                                    variable_error=false;
                                }
                                else{
                                    variable_error=true;
                                    clearScreen();
                                    cout<<"Date Input not Aceptable, please try again"<<endl;
                                }
                            }
                            else{
                                variable_error=true;
                                clearScreen();
                                cout<<"minute Input not Aceptable, please try again"<<endl;
                            }
                        } catch (DateInvalid i) {
                            clearScreen();
                            cout<<i.error<<endl;
                        }
                    }
                    variable_error=true;
                    vector<string> tempVector_h;
                    while (variable_error) {
                        try {
                            cout<<"Enter the departure hours(hh mm)"<<endl;
                            if(getline(cin,tempString)){
                                clearScreen();
                                checkIfOut(tempString);
                                tempVector_h = vectorString(tempString," ");
                                for(auto p:tempVector_h){
                                    if(!strIsNumber(p)){
                                        tempVector_h.clear();
                                        variable_error=true;
                                        clearScreen();
                                        cout<<"minute Input not Aceptable, please try again"<<endl;
                                        break;
                                    }
                                }
                                if(tempVector_h.size()==2){
                                    Date i(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));
                                    variable_error=false;
                                }
                                else{
                                    variable_error=true;
                                    clearScreen();
                                    cout<<"minute Input not Aceptable, please try again"<<endl;
                                }
                            }
                            else{
                                variable_error=true;
                                clearScreen();
                                cout<<"minute Input not Aceptable, please try again"<<endl;
                            }
                        } catch (DateInvalid i) {
                            clearScreen();
                            cout<<i.error<<endl;
                        }
                    }
                    Date temp_date=Date(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));

                    //set arrival date
                    clearScreen();
                    variable_error=true;
                    tempVector.clear();
                    while (variable_error) {
                        try {
                            cout<<"Enter the date of arrival(yy mm dd)"<<endl;
                            if(getline(cin,tempString)){
                                clearScreen();
                                checkIfOut(tempString);
                                tempVector = vectorString(tempString," ");
                                for(auto p:tempVector){
                                    if(!strIsNumber(p)){
                                        tempVector.clear();
                                        variable_error=true;
                                        clearScreen();
                                        cout<<"Date Input not Aceptable, please try again"<<endl;
                                        break;
                                    }
                                }
                                if(tempVector.size()==3){
                                    Date i(unsigned(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),23,59);
                                    if(i<temp_date){
                                        variable_error=true;
                                        clearScreen();
                                        cout<<"Date Input not Aceptable, should not be prior to initial date, please try again"<<endl;
                                    }
                                    else
                                        variable_error=false;
                                }
                                else{
                                    variable_error=true;
                                    clearScreen();
                                    cout<<"Date Input not Aceptable, please try again"<<endl;
                                }
                            }
                            else{
                                variable_error=true;
                                clearScreen();
                                cout<<"Date Input not Aceptable, please try again"<<endl;
                            }
                        } catch (DateInvalid i) {
                            clearScreen();
                            cout<<i.error<<endl;
                        }
                    }
                    variable_error=true;
                    tempVector_h.clear();
                    while (variable_error) {
                        try {
                            cout<<"Enter the hours of Arrival(hh mm)"<<endl;
                            if(getline(cin,tempString)){
                                clearScreen();
                                checkIfOut(tempString);
                                tempVector_h = vectorString(tempString," ");
                                for(auto p:tempVector_h){
                                    if(!strIsNumber(p)){
                                        tempVector_h.clear();
                                        variable_error=true;
                                        clearScreen();
                                        cout<<"minute Input not Aceptable, please try again"<<endl;
                                        break;
                                    }
                                }
                                if(tempVector_h.size()==2){
                                    Date i(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));
                                    if(i<temp_date){
                                        variable_error=true;
                                        clearScreen();
                                        cout<<"Input not Aceptable, should not be prior to current date, please try again"<<endl;
                                    }
                                    else
                                        variable_error=false;
                                }
                                else{
                                    variable_error=true;
                                    clearScreen();
                                    cout<<"minute Input not Aceptable, please try again"<<endl;
                                }
                            }
                            else{
                                variable_error=true;
                                clearScreen();
                                cout<<"minute Input not Aceptable, please try again"<<endl;
                            }
                        } catch (DateInvalid i) {
                            clearScreen();
                            cout<<i.error<<endl;
                        }
                    }
                    Date temp_date_arrival=Date(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));

                    bool print=false;
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(temp_date<*i->getIDate() && *i->getADate()<temp_date_arrival){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(temp_date<*i->getIDate() && *i->getADate()<temp_date_arrival){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(temp_date<*i->getIDate() && *i->getADate()<temp_date_arrival){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print){
                        enter_to_exit();
                    }
                    clearScreen();
                    break;
                }
                case 5:{
                    string temp_origin;
                    cout<<"Enter Origin Location (i.e. Porto): "<<endl;
                    getline(cin,temp_origin);
                    bool print=false;
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getOrigin().getLocation()==temp_origin){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(i->getOrigin().getLocation()==temp_origin){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(i->getOrigin().getLocation()==temp_origin){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print)
                        enter_to_exit();
                    clearScreen();
                    break;
                }
                case 6:{
                    bool print=false;
                    string temp_origin;
                    cout<<"Enter Destination Location (i.e. Porto): "<<endl;
                    getline(cin,temp_origin);
                    for(auto i:*Company::getCompany()->getVectorServicesOnQueue()){
                        if(i->getDestination().getLocation()==temp_origin){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesOnTransit()){
                        if(i->getDestination().getLocation()==temp_origin){
                            cout<<i;
                            print=true;
                        }
                    }
                    for(auto i:*Company::getCompany()->getVectorServicesFinished()){
                        if(i->getDestination().getLocation()==temp_origin){
                            cout<<i;
                            print=true;
                        }
                    }
                    if(print)
                        enter_to_exit();
                    clearScreen();
                    break;
                }
                case 0:{
                    return;
                }
                case 1:
                    infoEveryServices();
                    enter_to_exit();
                    break;
                case 2:{
                    infoOnQueueServices();
                    enter_to_exit();
                    break;
                }
                case 3:{
                    infoOnTransitServices();
                    enter_to_exit();
                    break;
                }
                case 4:{
                    infoFinishedServices();
                    enter_to_exit();
                    break;
                }


                default:
                    opt=1;
                }
            }
            catch(...){

            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}

void infoEveryServices(){

    cout << "---On Queue---" << endl;
    infoOnQueueServices();
    cout << "---On Transit---" << endl;
    infoOnTransitServices();
    cout << "---Finished---" << endl;
    infoFinishedServices();
}
void infoOnQueueServices(){
    bool nInfo = true;
    if (Company::getCompany()->getVectorServicesOnQueue()->size()) {
        for (auto i : *Company::getCompany()->getVectorServicesOnQueue()) {
            cout<<i;
            cout << endl;
            nInfo = false;
        }
    }
    if (nInfo)
        cout << "There is no queued service" << endl;

}
void infoOnTransitServices(){
    bool nInfo = true;
    if (Company::getCompany()->getVectorServicesOnTransit()->size()) {
        for (auto i : *Company::getCompany()->getVectorServicesOnTransit()) {
            cout << i;
            cout << endl;
            nInfo = false;
        }
    }
    if (nInfo)
        cout << "There is no service on transit" << endl;
}
void infoFinishedServices(){
    bool nInfo = true;
    if (Company::getCompany()->getVectorServicesFinished()->size()) {
        for (auto i : *Company::getCompany()->getVectorServicesFinished()) {
            cout << i;
            cout << endl;
            nInfo = false;
        }
    }
    if (nInfo)
        cout << "There is no finished service" << endl;
}
void manage_client(Client *client){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout <<*client<<endl;
        cout<<"[1] Edit Client"<<endl;
        cout<<"[2] Remove Client"<<endl;
        cout<<"[3] See Service"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=3)
        {
            clearScreen();
            switch (opt) {
            case 1: {
                clearBuffer();
                client->editClient();
                break;
            }
            case 2:{
                try {
                    clearBuffer();
                    Company::getCompany()->removeClientFromHash(client->getNif());
                    client->removeClient(*Company::getCompany()->getVectorClients());
                    
                }
                catch (const ClientNotInVector &e) {
                    clearScreen();
                    clearBuffer();
                    cout << e.erro << endl;
                    enter_to_exit();
                }
                return;
            }
            case 0:{
                return;
            }


            case 3:{
                clearBuffer();
                cout << "Services: " << endl;
                for (auto it = client->getServicesVector()->begin(); it != client->getServicesVector()->end(); it++)
                {
                    cout << (*it) << endl;
                }
                enter_to_exit();
                break;
            }

            default:
                opt=1;
            }
        }
        else{
            opt=1;
            clearBuffer();
            clearScreen();
            cout<<"Not a valid option, please try again"<<endl;
        }
    }
}
void moneyInformation(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] View General Financial Reports"<<endl;
        cout<<"[2] View Low Temperature Trucks Financial Reports"<<endl;
        cout<<"[3] View Hazardous Trucks Financial Reports"<<endl;
        cout<<"[4] View Normal Temperature Trucks Financial Reports"<<endl;
        cout<<"[5] View Animal Temperature Trucks Financial Reports"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=5)
        {
            clearBuffer();
            clearScreen();
            switch (opt) {
            case 0:{
                return;
            }
            case 1:{
                for (unsigned i = 0; i < Company::getCompany()->getStatCong().size(); i++) {
                    cout << ":::::::::::::::::::" << endl;
                    cout << "Month/Year: " << (Company::getCompany()->getStatCong()[i].first % 12) <<"/"<<int(Company::getCompany()->getStatCong()[i].first/12)  << endl;
                    cout << "Total rev: "<< Company::getCompany()->getStatHaz()[i].second + Company::getCompany()->getStatCong()[i].second + Company::getCompany()->getStatNorm()[i].second + Company::getCompany()->getStatAnim()[i].second << endl;
                }
                enter_to_exit();
                break;
            }
            case 2:{
                for (unsigned i = 0; i < Company::getCompany()->getStatCong().size(); i++) {
                    cout << ":::::::::::::::::::" << endl;
                    cout << "Month/Year: " << (Company::getCompany()->getStatCong()[i].first % 12) << "/" << int(Company::getCompany()->getStatCong()[i].first / 12) << endl;
                    cout << "Low temperature transport rev: " << Company::getCompany()->getStatCong()[i].second << endl;
                }
                enter_to_exit();
                break;
            }
            case 3:{
                for (unsigned i = 0; i < Company::getCompany()->getStatHaz().size(); i++) {
                    cout << ":::::::::::::::::::" << endl;
                    cout << "Month/Year: " << (Company::getCompany()->getStatHaz()[i].first % 12) << "/" << int(Company::getCompany()->getStatHaz()[i].first / 12) << endl;
                    cout << "Hazard transport rev: " << Company::getCompany()->getStatHaz()[i].second << endl;
                }
                enter_to_exit();
                break;
            }
            case 4:{
                for (unsigned i = 0; i < Company::getCompany()->getStatNorm().size(); i++) {
                    cout << ":::::::::::::::::::" << endl;
                    cout << "Month/Year: " << (Company::getCompany()->getStatNorm()[i].first % 12) << "/" << int(Company::getCompany()->getStatNorm()[i].first / 12) << endl;
                    cout << "Normal transport rev: " << Company::getCompany()->getStatNorm()[i].second << endl;
                }
                enter_to_exit();
                break;
            }
            case 5:{
                for (unsigned i = 0; i < Company::getCompany()->getStatAnim().size(); i++) {
                    cout << ":::::::::::::::::::" << endl;
                    cout << "Month/Year: " << (Company::getCompany()->getStatAnim()[i].first % 12) << "/" << int(Company::getCompany()->getStatAnim()[i].first / 12) << endl;
                    cout << "Animal transport rev: " << Company::getCompany()->getStatAnim()[i].second << endl;
                }
                enter_to_exit();
                break;
            }
            }
        }
    }
}

void menu_inactive_clients() {
	unsigned opt = 1;
	clearScreen();
    while (opt != 0) {
        cout << "[1] Show All Inactive Clients" << endl;
        cout << "[2] Show a Specific Inactive Client" << endl;
        cout << "[0] Return" << endl;
        if (cin >> opt && opt <= 2)
        {
            clearScreen();
            switch (opt) {
            case 0: {
                return;
            }
            case 1:
                if (Company::getCompany()->clientHash.size())
                    for (auto i : Company::getCompany()->clientHash) {
                        cout << *i << endl;
                    }
                else {
                    cout << "There is no Information to show" << endl;
                }
                clearBuffer();
                enter_to_exit();
                break;
            case 2: {
				bool variable_error = true;
				string tempNif;
                clearBuffer();
				while (variable_error) {
					cout << "Enter the Nif" << endl;

					getline(cin, tempNif);
					checkIfOut(tempNif);
					clearScreen();
					if (strIsNumber(tempNif) && tempNif.size() == 9)
						variable_error = false;
					else {
						variable_error = true;
						cout << "Nif Input not acceptable, please try again" << endl;
					}
				}
                clearBuffer();
                int auxnif = stoi(tempNif);
                if (Company::getCompany()->clientHash.size()) {
                    for (auto i : Company::getCompany()->clientHash) {
                        if (i->getNif() == auxnif) {
                            cout << *i;
                            clearBuffer();
                            enter_to_exit();
                            return;
                        }

                    }
                    cout << "Either there is no client with that NIF or the client simply isn't on the inactive list";
                }
                else
                    cout << "There is no Information to show" << endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            }
        }
    }
}