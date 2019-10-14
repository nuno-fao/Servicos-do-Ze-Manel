#pragma once
#include <string>
#include <vector>

#include "service.h"
using namespace std;

class client
{
public:
	client();
	~client();

	//get methods
	string getName() const;
	unsigned getNif() const;
	void getServicesVector(vector<service*>* services) const;

	//set methods
	void setName(string name);
	void setNif(unsigned nif);
	
	//add methods
	void addService(service* service);

private:
	string name;
	const unsigned int id;
	unsigned int nif;
	vector<service*> services;
	static int last_id = 0;
};