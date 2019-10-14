#pragma once
#include <string>
#include <vector>
#include "service.h"
using namespace std;

class Truck
{
protected:
	string license;
	bool availabe;
	bool registered;
	vector<Service*> assignedServices;
public:
	Truck();
	~Truck();

};

class Congelation : public Truck
{
public:
	Congelation();
	~Congelation();

private:
	float pricePerKG;
	unsigned short capacity; //in KG
	short temp;  //in Celsius
};

class HazardousMat : public Truck
{
public:
	HazardousMat();
	HazardousMat();

private:
	float pricePerKG;
	unsigned short capacity; //in KG
	//make a type for the various hazards
};

class Animal : public Truck
{
public:
	Animal();
	~Animal();

private:
	float pricePerKG;
	unsigned short capacity; //in KG
	//make a type for the various hazards
};