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
    throw TruckDoNotExist("Couldn't find the Truck",license);
}

Truck *Company::binarySearch(vector<Truck*> vect, string license)
{
    size_t l=0;
    string t;
    size_t r=vect.size()-1;
    while (l <= r) {
        size_t m = l + (r - l) / 2;
        t=vect.at(m)->getlicense();
        // Check if x is present at mid
        if (vect[m]->getlicense() == license)
            return vect.at(m);

        // If x greater, ignore left half
        if (vect[m]->getlicense() < license)
            l = m + 1;

        // If x is smaller, ignore right half
        else
            r = m - 1;
    }


    // We reach here when element is not
    // present in array
    throw TruckDoNotExist("Couldn't find the Truck",license);
}
