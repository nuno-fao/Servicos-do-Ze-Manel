#include "client.h"

Client::client() {};
Client::client(string name, unsigned int id, unsigned int nif) {
	name = 
	
	id = last_id + 1;
	last_id = id;
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