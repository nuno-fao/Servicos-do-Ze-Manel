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
/**
* @brief Gets Company
*
* Retrieves the Company instance
*
* @return Returns a pointer to the company
*/
    static Company *getCompany();
/**
*
* Default Destructor
*/
    ~Company();
    bool services_finished_changed=false,services_on_transit_changed=false,services_on_queue_changed=false;
    bool clients_changed=false;
    bool trucks_changed=false;
/**
* @brief Gets list containing finished services
*
* Returns a pointer to the list containing finished services
*
* @return Returns a pointer to the list containing pointers to finished services
*/
    list<Service*> *getVectorServicesFinished();
/**
* @brief Gets vector containing services on transit
*
* Returns a pointer to the vector containing services on transit
*
* @return Returns a pointer to the vector containing services on transit
*/
    vector<Service*> *getVectorServicesOnTransit();
/**
* @brief Gets vector containing services on queue
*
* Returns a pointer to the vector containing services on queue
*
* @return Returns a pointer to the vector containing services on queue
*/
    vector<Service*> *getVectorServicesOnQueue();
/**
* @brief Gets the vector containing the clients
*
* Returns a vector of pointers to clients
*
* @return Returns a pointer to the vector containing pointers to clients
*/
    vector<Client*> *getVectorClients();
	/**
* @brief Gets the vector containing the trucks
*
* Returns a vector of pointers to trucks
*
* @return Returns a pointer to the vector containing pointers to trucks
*/
    vector<Truck*> *getVectorTrucks();
/**
* @brief Gets the client
*
* Returns a Client that posesses the passed identification number
*
* @return Returns a pointer to the Client
*/
    Client *getClient(unsigned nif);
/**
* @brief Gets the truck
*
* Returns a Truck that posesses the passed license
*
* @return Returns a pointer to a Truck
*/
    Truck *getTruck(string license);
/**
* @brief Gets the service
*
* Returns a Service that posesses the passed identification number
*
* @return Returns a pointer to a Service
*/
    Service *getService(unsigned id);
/**
* @brief Updates the truck's state
*
* Updates the truck's state depending on the current, real time
*
* @return Returns nothing
*/
    void updateTruckSituation();
/**
* @brief Updates the services' state
*
* Updates the services' state depending on the current, real time
*
* @return Returns nothing
*/
    void updateServicesSituation();
/**
* @brief Loads the statistics
*
* Reads the statistics from the associated text file
*
* @return Returns nothing
*/
    void loadStats();
/**
* @brief Saves the statistics
*
* Writes the statistics to the associated text file
*
* @return Returns nothing
*/
    void saveStats();
/**
* @brief Gets the statistics from congelated trucks
*
* Retrieves the statistics of congelated-type trucks
*
* @return Returns a vector containing pairs that represents the number of trucks of that type that have a determined capacity
*/
	vector<pair<int, double>> getStatCong() { return statCong; }
/**
* @brief Gets the statistics from hazardous trucks
*
* Retrieves the statistics of hazardous-type trucks
*
* @return Returns a vector containing pairs that represents the number of trucks of that type that have a determined capacity
*/
	vector<pair<int, double>> getStatHaz() { return statHaz; }
/**
* @brief Gets the statistics from animal-carrying trucks
*
* Retrieves the statistics of animal-carrying-type trucks
*
* @return Returns a vector containing pairs that represents the number of trucks of that type that have a determined capacity
*/
	vector<pair<int, double>> getStatAnim() { return statAnim; }
/**
* @brief Gets the statistics from normal trucks
*
* Retrieves the statistics of normal-type trucks
*
* @return Returns a vector containing pairs that represents the number of trucks of that type that have a determined capacity
*/
	vector<pair<int, double>> getStatNorm() { return statNorm; }

private:
    static Company *company;
/**
*
* Default Constructor
*/
    Company();
    list<Service*> services_finished;
    vector<Service*> services_on_transit,services_on_queue;
    vector<Client*> clients;
    vector<Truck*> trucks;
    vector<pair<int, double>> statCong;
    vector<pair<int, double>> statHaz;
    vector<pair<int, double>> statNorm;
    vector<pair<int, double>> statAnim;
    priority_queue<Truck*> workshop_line;
};
