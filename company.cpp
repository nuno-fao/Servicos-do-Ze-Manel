#include "company.h"



Company *Company::company=nullptr;

Company &Company::getCompany(){
    if (company==nullptr)
        company = new Company();
    return *company;
}

Company::Company(){}

Company::~Company(){
    Service::saveToFile(&services_finished,&services_on_transit,&services_on_queue);
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
