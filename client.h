#pragma once
#include <string>
#include <vector>

#include "service.h"
using namespace std;

class Client
{
public:
	Client();
	~Client();

	//get methods
	string getName() const;
	unsigned getNif() const;
	void getServicesVector(vector<Service*> *services) const;

	//set methods
	void setName(string name);
	void setNif(unsigned nif);
	
	//add methods
	void addService(Service *service);


	ostream& operator<<(ostream& out, const Client& client) const; 

	bool operator== (const Client& client1, const Client& client2) const;

private:
	string name;
	const unsigned int id;
	unsigned int nif;
	vector<Service*> services;
	static int last_id = 0;
};