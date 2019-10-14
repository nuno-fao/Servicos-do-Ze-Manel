#include "client.h"

Client::client(string name, unsigned int id, unsigned int nif, vector<service*> services): name(name), nif(nif), services(services) {
	//if (!verifyName(const string & name))
	//	throw exception;


	this->id = last_ id + 1;
	last_id++;
}



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


