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
	Company();
	~Company();



private:
	int generalRevenue; // lucro geral
	int dangerousRevenue; //lucro caminhao perigoso
	int freezeRevenue; //
    vector<Service*> servicesOrigin,servicesDestination,servicesId,servicesInitialDate;
    size_t SOOn_queue,SOOnTransit,SOFinished;
    size_t SDOn_queue,SDOnTransit,SDFinished;
    size_t SIOn_queue,SIOnTransit,SIFinished;
    size_t SIDOn_queue,SIDOnTransit,SIDFinished;

    vector<Client*> clients;
    vector<Truck*> trucks;


};
