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
    string license; ///format XX-YY-ZZ
    bool availabe;	///is the truck available right now?
    bool registered;	///is the truck registered to a service in the future?
    vector<Service*> assignedServices;	///services the truck is registered to
    unsigned short capacity; ///in KG
    unsigned short cargo; ///if in transit this holds the weight it transports, if not it is 0

public:
    Truck(string license, bool available,bool registered,unsigned short capacity, unsigned short cargo);
    virtual ~Truck();
	//get methods
    virtual float getprice(Service* service) const;
    unsigned short getcapacity() const;
    bool getavailable() const;
    string getlicense() const;
    bool getregistered() const;
    unsigned short getcargo() const;
	//set methods
    virtual void setprice(float newval){availabe=(bool(newval) && availabe);}
    void setregistered(bool foo);
    void setavailable(bool foo);
	//load and save to file
	static void loadFromFile(vector<Truck*> *trucks);
	static void saveToFile(vector<Truck*> *trucks);
	//other
	virtual void info();	//prints basic info of the truck
	void add_service(Service* service); //adds to the vector the service which the truck is assigned to
	void remove_service(unsigned int id); //removes an assigned service when it is finished, searches by id
	void start_transport(unsigned short cargo); //sets the needed variables so the truck is in transport
	static void createTruck(vector<Truck*>* trucks); //creates a new truck from scratch and adds to the vector
	static void removeTruck(vector<Truck*>* trucks); //removes a truck, searches by license. iterative
	static void showTruck(vector<Truck*>* trucks); //searches truck by license and prints its info
};

bool operator<(Truck &a,Truck &b);

class Congelation : public Truck
{
public:
    Congelation(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
	~Congelation() {}

	void info();
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


	void info();
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

	void info();
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

	void info();
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
