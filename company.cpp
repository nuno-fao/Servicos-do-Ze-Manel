#include "company.h"


Company *Company::getCompany(){
    if (company==nullptr)
        company = new Company();
    return company;
}

Company::Company(){}

Company::~Company(){
    cout<<getCompany()->services_on_queue_changed<<endl;
    if(getCompany()->services_on_queue_changed){
        Service::saveToFile(&services_finished,&services_on_transit,&services_on_queue);
    }
}

vector<Service*> *Company::getVectorServicesFinished(){
    return &services_finished;
}
vector<Service*> *Company::getVectorServicesOnTransit(){
    return &services_on_transit;
}
vector<Service*> *Company::getVectorServicesOnQueue(){
    return &services_on_queue;
}

vector<Client*> *Company::getVectorClients(){
    return &clients;
}
vector<Truck*> *Company::getVectorTrucks(){
    return &trucks;
}

Client *Company::getClient(unsigned nif){
    for(auto i: clients){
        if(i->getNif()==nif)
            return i;
    }
    throw NotAClient(nif,"Couldn't find the client");
}
Truck *Company::getTruck(string license){
    for(auto i: trucks){
        if(i->getlicense()==license)
            return i;
    }
    throw TruckDoNotExist("Couldn't find the client",license);
}
