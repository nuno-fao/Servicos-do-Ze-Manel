#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <list>

#include "client.h"
#include "service.h"
#include "truck.h"


class Truck;
class Service;
class Client;
using namespace std;

class Company
{
public:
    static Company *getCompany();
    ~Company();
    bool services_finished_changed=false,services_on_transit_changed=false,services_on_queue_changed=false;
    bool clients_changed=false;
    bool trucks_changed=false;
    list<Service*> *getVectorServicesFinished();
    vector<Service*> *getVectorServicesOnTransit();
    vector<Service*> *getVectorServicesOnQueue();
    vector<Client*> *getVectorClients();
    vector<Truck*> *getVectorTrucks();
    Client *getClient(unsigned nif);
    Truck *getTruck(string license);
    Service *getService(unsigned id);
    void updateTruckSituation();


private:
    static Company *company;
    Company();
    int generalRevenue; // lucro geral
    int dangerousRevenue; //lucro caminhao perigoso
    int freezeRevenue; //
    list<Service*> services_finished;
    vector<Service*> services_on_transit,services_on_queue;
    vector<Client*> clients;
    vector<Truck*> trucks;


};
