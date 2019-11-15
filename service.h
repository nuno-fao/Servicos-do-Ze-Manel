#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <fstream>
#include <set>

#include "truck.h"
#include "date.h"
#include "misc.h"
#include "client.h"
#include "company.h"
#include "Address.h"

using namespace std;

class Service;
class Client;
class Truck;
class TemperatureService;
class HazardousService;
class Date;
class Company;
class Address;

enum class Hazard_enum {explosives=0, gases=1, flammableliq=2, flammablesolid=3, oxidizer=4, poisons=5, radioactive=6, corrosives=7, other=8}; //categories for the diferent dangers
enum class Temperature_enum{p1_20=0, n20_0=1,n50_n21=2,n100_n51=3};

enum class type {ordinary=0,hazardous=1,animal=2,lowTemperature=3};

enum state {
    on_queue=0,on_transit=1,finished=2
};

class Service
{
public:
	/**
* Default destructor
*/
    ~Service();
	/**
* Default constructor
*/
    Service();
    //get methods
		/**
* @brief Gets origin
*
* Returns the origin of the service
*
* @return Returns the origin of the service as Address data type
*/
    Address getOrigin() const; 
	/**
* @brief Gets destiny
*
* Returns the destiny of the service
*
* @return Returns the destiny of the service as Address data type
*/
    Address getDestination() const;
	/**
* @brief Gets distance
*
* Returns the distance from origin to destiny
*
* @return Returns the distance from origin to destiny
*/
    unsigned getDistance() const;
	/**
* @brief Gets type
*
* Returns the type of service
*
* @return Returns the type of service
*/
    type getType() const;
	/**
* @brief Gets id
*
* Returns the id of service
*
* @return Returns the id of service
*/
    unsigned int getId() const;
	/**
* @brief Gets state
*
* Returns the state of service
*
* @return Returns the state of service as a state data type
*/
    state getState() const;
	/**
* @brief Gets starting date
*
* Returns the starting date of service
*
* @return Returns the starting date of the service
*/
    Date *getIDate() const;
	/**
* @brief Gets arrival date
*
* Returns the arrival date of service
*
* @return Returns the arrival date of the service
*/
    Date *getADate() const;
	/**
* @brief Gets the client that bought the service
*
*
* @return Returns a pointer to the client that bought the service
*/
    Client *getClient() const;
	/**
* @brief Gets the trucks associated to the service and respective cargo in a map
*
*
* @return Returns a map to the trucks associated to the service and respective cargo
*/
    map<Truck *, float> *getTrucks();
	/**
* @brief Gets full price of the service
*
*
* @return Returns full price of the service
*/
    float getTotalPrice() const;
	/**
* @brief Gets quantity of the material to transport
* Gets quantity of the material to transport
*
* @return Returns quantity of the material to transport
*/
    float getQuantity() const;
	
    float getMultiplier(){return  1;}
	/**
* @brief Gets  material to transport
* Gets material to transport
*
* @return Returns a string with the material to transport
*/
    string getMaterial() const;

    //set methods
    void setOrigin(Address origin);
    void setDestination(Address destination);
    void setTime(double time);
    void setDistance(unsigned distance);
    void setType(type type);
    void setState(state state);
    void setIDate(Date *date);
    void setADate(Date *date);
    void setClient(Client *client);
    void setQuantity(float quantity);
    void setMaterial(string material);

    void addTruck(Truck *truck,float cargo);

    //file methods
    static void saveToFile(list<Service*>*services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
    static void loadFromFile(list<Service *> *services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
    static Service *addService(vector<Service *> *services, Client *client=nullptr);
    void editService();
    static bool removeService(vector<Service *> *services,unsigned id);
    friend ostream& operator<<(ostream& os, Service *a);

    static void test();
    static set<unsigned> idList;

protected:
    Service(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity);
    Service(string material, string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date, Client *client, float quantity, float total_price,unsigned id);
    Address *origin; /**< stores the origin of the Service */
    Address *destination;
    string material;
    Date *arrivalDate;
    unsigned distance;
    float quantity;
    type ser_type;
    unsigned int id;
    map<Truck*,float> trucks;
    state ser_state;
    Date *initialDate;
    Client *client;
    float total_price;
    int autoAddTrucks();



};

class HazardousService: public Service
{
public:
    HazardousService(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Hazard_enum hazard);
    HazardousService(string material,string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Hazard_enum hazard,float total_price,unsigned id);
    Hazard_enum type;
};

class TemperatureService: public Service
{
public:
    TemperatureService(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Temperature_enum hazard);
    TemperatureService(string material, string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date, Client *client, float quantity, Temperature_enum hazard, float total_price, unsigned id_s);
    Temperature_enum type;
};

class ServiceDoNotExist//: public Service
{
public:
    string erro;
    ServiceDoNotExist(string erro):erro(erro){}
};

class ServiceFinishedFileError//: public Service
{
public:
    ServiceFinishedFileError(){}
};
class ServiceOnQueueFileError//: public Service
{
public:
    ServiceOnQueueFileError(){}

};
class ServiceOnTransitFileError//: public Service
{
public:
    ServiceOnTransitFileError(){}

};

