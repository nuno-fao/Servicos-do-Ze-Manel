// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>

#include "client.h"
#include "truck.h"
#include "service.h"
#include "company.h"

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
                //client->editClient();
                break;
            case 2:{
                //Client::removeClient();
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

void mainMenu();
void menu_clients();


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
    Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());

    //vector<Truck*> a(*Ze_Manel->getVectorTrucks());
    string temp;
    mainMenu();
    delete Ze_Manel;


    return 0;
}

void mainMenu(){
    unsigned opt=1;
    while (opt!=0) {
        cout<<"[1] Clients"<<endl;
        cout<<"[2] Trucks"<<endl;
        cout<<"[3] Services"<<endl;
        cout<<"[4] Information"<<endl;
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

                break;
            }

            case 3:{

                break;
            }
            case 4:{

                break;
            }
            case 5:{

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
                menu_clients();
                break;
            }
            case 2:{
                int nif=0;
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

                    } catch (NotAClient e) {
                        cout << e.erro << endl;
                    }
                }
                clearBuffer();
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




