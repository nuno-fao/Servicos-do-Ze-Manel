#include "client.h"

Client::Client(string name, unsigned int id, unsigned int nif, vector<Service*> services): name(name), nif(nif), services(services) {
	//if (!verifyName(const string & name))
	//	throw exception;


	this->id = last_ id + 1;
	last_id++;
}



~Client();

//get methods
string getName() const;
unsigned getNif() const;
void getServicesVector(vector<Service*>* services) const;

//set methods
void setName(string name);
void setNif(unsigned nif);

//add methods
void addService(Service* service);


