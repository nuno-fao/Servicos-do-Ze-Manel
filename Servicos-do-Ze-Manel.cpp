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

using namespace std;


void manage_client(Client *client){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout <<*client<<endl;
        cout<<"[1] Edit Client"<<endl;
		cout<<"[2] Remove Client"<<endl;
        cout<<"[3] Edit Services"<<endl;
        cout<<"[4] Cancel Service"<<endl;
        cout<<"[5] See Service"<<endl;
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=5)
        {
            clearScreen();
            switch (opt) {
            case 1:
				clearBuffer();
				client->editClient();
                break;
            case 2:{
				clearBuffer();
				client->removeClient(*Company::getCompany()->getVectorClients());
                break;
            }
            case 0:{
                return;
            }

            case 3:{

                long id=long(0);
                Service *temp_client = nullptr;
                do{
                    for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                        cout<<i;
                    }
                }while((id=askForId("Service","Edit","Id"))==-2);
                clearScreen();
                for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                    if(i->getId()==long(id)){
                        temp_client=i;
                        break;
                    }
                }
                temp_client->editService();
                break;

            }
            case 4:{

                long id=long(0);
                Service *temp_client = nullptr;
                do{
                    for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                        cout<<i;
                    }
                }while((id=askForId("Service","Remove","Id"))==-2);
                clearScreen();
                for(auto i: *Company::getCompany()->getVectorServicesOnQueue()){
                    if(i->getId()==long(id)){
                        temp_client=i;
                        break;
                    }
                }
                Service::removeService(Company::getCompany()->getVectorServicesOnQueue(),unsigned(id));
                string temp;
                clearBuffer();
                getline(cin,temp);
                break;

            }
            case 5:{
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

void menu_services();
void mainMenu();
void menu_clients();
void information();
void clientsInformation();


/*
This function receives a name and returns true if it is valid
*/

template<class T> bool cmp_classes(T *a,T *b){
    return *a<*b;
}

Company *Company::company = nullptr;
int main()
{
    clearScreen();
    Company *Ze_Manel = nullptr;
    Ze_Manel=Company::getCompany();
    Truck::loadFromFile(Ze_Manel->getVectorTrucks());
    Client::loadClients(*Ze_Manel->getVectorClients());
    sort(((*Ze_Manel).getVectorTrucks())->begin(),((*Ze_Manel).getVectorTrucks())->end(),cmp_classes<Truck>);
    sort(((*Ze_Manel).getVectorClients())->begin(),((*Ze_Manel).getVectorClients())->end(),cmp_classes<Client>);
    sort(((*Ze_Manel).getVectorServicesOnQueue())->begin(),((*Ze_Manel).getVectorServicesOnQueue())->end(),cmpOnQueue);
    sort(((*Ze_Manel).getVectorServicesOnTransit())->begin(),((*Ze_Manel).getVectorServicesOnTransit())->end(),cmpOnTransit);
    Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());

    //vector<Truck*> a(*Ze_Manel->getVectorTrucks());
    string temp;
    mainMenu();
	Client::saveToFile(*Ze_Manel->getVectorClients());
    delete Ze_Manel;


    return 0;
}

void mainMenu(){
    unsigned opt=1;
	while (opt != 0) {
		cout<<"[0] Exit program"<<endl;
		cout<<"[1] Clients"<<endl;
        cout<<"[2] Trucks"<<endl;
        cout<<"[3] Services"<<endl;
        cout<<"[4] Information"<<endl;
        if(cin>>opt && opt<=4)
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
				clearBuffer();
				Client::addClient(Company::getCompany()->getVectorClients());
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

                    } catch (NotAClient *e) {
                        cout << e->erro << endl;
                    }
                }
                //clearBuffer(); Tem de estar comentado senão não apresenta o menu no ecrã
                string temp;
                getline(cin,temp);
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

void menu_services(){
    unsigned opt=1;
    while (opt!=0) {
        clearScreen();
        cout<<"[1] Add Service"<<endl;
        cout<<"[2] Manage Service"<<endl;
        cout<<"[0] Return to Main Menu"<<endl;
        if(cin>>opt && opt<=2)
        {
            clearScreen();
            switch (opt) {
            case 0:
                break;
            case 1:{
                clearScreen();
                for(auto i:*Company::getCompany()->getVectorClients()){
                    cout<<*i;
                }
                Client *tempClient= Company::getCompany()->getClient(unsigned(askForId("Client","add a Service","Nif")));
                clearBuffer();
                clearScreen();
                Service::addService(Company::getCompany()->getVectorServicesOnQueue(),tempClient);
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

                    } catch (NotAClient *e) {
                        cout << e->erro << endl;
                    }
                }
                //clearBuffer(); Tem de estar comentado senão não apresenta o menu no ecrã
                string temp;
                getline(cin,temp);
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
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=3)
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
                //Client::removeClient();
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
        cout<<"[0] Return"<<endl;
        if(cin>>opt && opt<=7)
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
                sort(temp.begin(),temp.end(),cmp_classes<Client>);
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
                clearBuffer();
                enter_to_exit();
                break;
            }
            case 3:{
                vector<Client*> temp(*Company::getCompany()->getVectorClients());
                sort(temp.begin(),temp.end(),[](Client *a, Client *b)
                {
                    return !(a->getMoneySpent() < b->getMoneySpent());
                }
                );
                if(temp.size())
                    for(auto i: temp){
                        cout<<*i;
                    }
                else
                    cout<<"There is no Information to show"<<endl;
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
					for (auto i : *Company::getCompany()->getVectorClients()) {
						cout << *i;
					}
				} while ((nif = askForId("Client", "manage", "Nif")) == -2);

				if (nif > 0) {
					try {
						temp_client = Company::getCompany()->getClient(unsigned(nif));
						cout << endl << *temp_client << endl;
						cout << "Services: " << endl;
						for(auto it = temp_client->getServicesVector()->begin(); it != temp_client->getServicesVector()->end(); it++)
						{
							cout << (*it) << endl;
						}
					}
					catch (NotAClient * e) {
						cout << e->erro << endl;
					}
				}
				//clearBuffer(); Tem de estar comentado senão não apresenta o menu no ecrã
				string temp;
				getline(cin, temp);
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



