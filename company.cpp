#include "company.h"

Company::Company(){
    //load trucks

    //load clients

    //load services
    Service::loadFromFile(&services_finished,&services_on_transit,&services_on_queue);


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
