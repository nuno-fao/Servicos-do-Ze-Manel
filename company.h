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
    static Company &getCompany();
    ~Company();
    vector<Service*> *getVectorServicesFinished();
    vector<Service*> *getVectorServicesOnTransit();
    vector<Service*> *getVectorServicesOnQueue();
    vector<Client*> *getVectorClients();


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
