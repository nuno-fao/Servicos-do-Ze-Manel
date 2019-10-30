#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "service.h"
#include "company.h"
using namespace std;

class Service;
class Client;
enum class Temperature_enum;
enum class Hazard_enum;


class Truck
{
protected:
	string license; //format XX-YY-ZZ
	bool availabe;	//is the truck available right now?
	bool registered;	//is the truck registered to a service in the future?
	vector<Service*> assignedServices;	//services the truck is registered to
	unsigned short capacity; //in KG
	unsigned short cargo; //if in transit this holds the weight it transports, if not it is 0 

public:
    Truck(string license, bool available,bool registered,unsigned short capacity, unsigned short cargo);
    virtual ~Truck(){}
	//get methods
	virtual float getprice(Service* service) const = 0;
	unsigned short getcapacity() const;
	bool getavailable() const;
	string getlicense() const;
	bool getregistered() const;
	unsigned short getcargo() const;
	//set methods
	virtual void setprice(float newval) = 0;
	void setregistered(bool foo);
	void setavailable(bool foo);
	//load and save to file
	static void loadFromFile(vector<Truck*> *trucks);
	static void saveToFile(vector<Truck*> *trucks);
	//other
	void add_service(Service* service); //adds to the vector the service which the truck is assigned to
	void remove_service(unsigned int id); //removes an assigned service when it is finished, searches by id
	void start_transport(unsigned short cargo); //sets the needed variables so the truck is in transport
};

class Congelation : public Truck
{
public:
    Congelation(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
	~Congelation() {}

	float getprice(Service* service) const;
	void setprice(float newval);
    static unordered_map<Temperature_enum, float> tempMul;


private:
	static float pricePerKG;
};

class HazardousMat : public Truck
{
public:
    HazardousMat(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
	~HazardousMat(){}


    float getprice(Service* service)const;
	void setprice(float newval);
	static unordered_map<Hazard_enum, float> hazardMul;
private:
    static float pricePerKG;
};

class Animal : public Truck
{
public:
    Animal(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
    ~Animal(){}

	float getprice(Service* service)const;
	void setprice(float newval);

private:
	static float pricePerKG;
};

class Normal : public Truck
{
public:
    Normal(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
    ~Normal(){}

	float getprice(Service* service)const;
	void setprice(float newval);

private:
	static float pricePerKG;
};

class FailedToOpenTrucks {
public:
    FailedToOpenTrucks() {}
};

class TruckDoNotExist{
public:
    string erro;
    string license;
    TruckDoNotExist(string erro,string license):erro(erro),license(license){}
};

class NotATruck{
public:
    string erro;
    string license;
    NotATruck(string erro,string license):erro(erro),license(license){}
};
