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



/*
This function receives a name and returns true if it is valid
*/

bool verifyName(const string &name) {

    for (unsigned int i = 0; i < name.size(); i++){
        if (!isdigit(name.at(i))) {
            return  false;
        }
    }

    return true;
}

bool cmp(const Service *a, const Service *b){
    if(a->getDate()<b->getDate())
        return true;
    else
        return false;
}


Company *Company::company = nullptr;
int main()
{

    Company *Ze_Manel = nullptr;
    Ze_Manel->getCompany();
    Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());
    unsigned opt=1;
    string temp;
    while (opt!=0) {
        cout<<"[1] see services"<<endl;
        cout<<"[2] add service"<<endl;
        cout<<"[3] remove service"<<endl;
        cout<<Ze_Manel->services_on_queue_changed<<endl;
        if(cin>>opt && opt<=3)
            switch (opt) {
            case 0:
                break;
            case 1:{
                clearBuffer();
                clearScreen();
                for(auto i=Ze_Manel->getVectorServicesOnQueue()->begin();i!=Ze_Manel->getVectorServicesOnQueue()->end();i++)
                    cout<<*i;
                if(!Ze_Manel->getVectorServicesOnQueue()->size())
                    cout<<"There are no info to show"<<endl;
                getline(cin,temp);
                clearScreen();
                break;
            }
            case 2:{
                Client *a=nullptr;
                clearScreen();
                clearBuffer();
                a =new Client("Margarida Cruz",121212121);
                Service::addService(Ze_Manel->getVectorServicesOnQueue(),a);
                break;
            }

            case 3:{
                clearScreen();
                clearBuffer();
                for(auto i:*Ze_Manel->getVectorServicesOnQueue()){
                    cout<<i->getMaterial()<<", id: "<<i->getId()<<endl;
                }
                if(Ze_Manel->getVectorServicesOnQueue()->size()){
                    cout<<endl;
                    cout<<"Which Service you want to remove ( write service's id ):"<<endl;
                    unsigned id;
                    cin>>id;
                    Service::removeService(Ze_Manel->getVectorServicesOnQueue(),id);
                    clearScreen();
                }
                else
                    cout<<"There are no services that can be removed"<<endl;
                    string temp;
                    getline(cin,temp);
                    clearScreen();
                break;
            }
            default:
                opt=1;

            }
        else{
            clearBuffer();
            clearScreen();
            cout<<"Non valid option, please try again"<<endl;
        }
    }
    delete Ze_Manel;
    return 0;
}
