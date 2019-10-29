#pragma once
#include <string>
#include <vector>

#include "client.h"
#include "service.h"
#include "truck.h"

using namespace std;

class Company
{
public:
    static Company *getCompany();
    ~Company();
    bool services_finished_changed=false,services_on_transit_changed=false,services_on_queue_changed=false;
    bool clients_changed=false;
    bool trucks_changed=false;
    vector<Service*> *getVectorServicesFinished();
    vector<Service*> *getVectorServicesOnTransit();
    vector<Service*> *getVectorServicesOnQueue();
    vector<Client*> *getVectorClients();
    vector<Truck*> *getVectorTrucks();


private:
    static Company *company;
    Company();
    int generalRevenue; // lucro geral
    int dangerousRevenue; //lucro caminhao perigoso
    int freezeRevenue; //
    vector<Service*> services_finished,services_on_transit,services_on_queue;
    vector<Client*> clients;
    vector<Truck*> trucks;


};
