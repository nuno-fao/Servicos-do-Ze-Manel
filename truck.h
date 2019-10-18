#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "service.h"
using namespace std;

class Service;
class Client;
class Truck;

enum Hazard {explosives, gases, flammableliq, flammablesolid, oxidizer, poisons, radioactive, corrosives, other}; //categories for the diferent dangers

class Truck
{
protected:
	string license; //format XX-YY-ZZ
	bool availabe;	//is the truck available right now?
	bool registered;	//is the truck registered to a service in the future?
	vector<Service*> assignedServices;	//pretty self-explanatory I'd say
	unsigned short capacity; //in KG
	unsigned short cargo; //if in transit this holds the weight it transports

public:
    Truck(string license);
    virtual ~Truck()=0;
	//get methods
	virtual float getprice() = 0;
	unsigned short getcapacity();
	bool getavailable();
	string getlicense();
	bool getregistered();
	//set methods
	virtual void setprice(float newval) = 0;
	void setregistered(bool foo);
	void setavailable(bool foo);
	//other
	void add_service(Service service); //adds to the vector the service which the truck is assigned to
	void start_transport(unsigned short cargo); //sets the needed variables so the truck is in transport
};

class Congelation : public Truck
{
public:
	Congelation();
	~Congelation();

	short gettemp();
    float getprice();
	unsigned short getcapacity();

	void setprice(float newval);


private:
	//static unordered_map<Hazard, int> table;
	static float pricePerKG;
	short temp;  //in Celsius
};

class HazardousMat : public Truck
{
public:
	HazardousMat();
    ~HazardousMat();


    float getprice(Hazard type);
    //using Truck::getprice;

	void setprice(float newval);

private:
    static float pricePerKG;
};

class Animal : public Truck
{
public:
	Animal();
	~Animal();
	float getprice();
	void setprice(float newval);

private:
	static float pricePerKG;
};

class Normal : public Truck
{
public:
	Normal();
	~Normal();
	float getprice();
	void setprice(float newval);

private:
	static float pricePerKG;
};
