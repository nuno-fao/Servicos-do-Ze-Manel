#include "client.h"

// Destrutor


unsigned int Client::lastId=0;

Client::Client(string name, unsigned int nif, vector<Service*> *services): name(name), id(lastId), nif(nif){
    if(services==nullptr)
        services=new vector<Service*>;
	lastId++;
}


Client::~Client(){
	for (size_t i = 0; i < services.size(); i++)
	{
		services.at(i)->~Service();
	}
}

//get methods
string Client::getName() const { return name; }

unsigned Client::getNif() const { return nif; }

vector<Service*> Client::getServicesVector() const { return services; }

//set methods
void Client::setName(string name){
    this->name=name;
}
void Client::setNif(unsigned nif){
    this->nif=nif;
}

//add methods	
void Client::addService(Service *service){
	services.push_back(service);
}

void Client::addClient(vector<Client>& clientsVector) {
	
	for (vector<Client>::iterator it = clientsVector.begin(); it != clientsVector.end(); it++) {
		if (it->nif == this->nif) {
			throw ClientInVector(nif, "Client is already exists in the database");
		}
	}
	
	clientsVector.push_back(*this);
}


// OTHER METHODS


void Client::loadClients(const string &clientsNameFile, vector<Client> &clientsVector){

	string clientsText;
	ifstream clientsFile;
	Client client;

	int i = 0;

	clientsFile.open(clientsNameFile);
	if (clientsFile.fail())
	{
		throw CantOpenClientFile("Could not open associated clients.txt file");
	}

	else
	{
		while (getline(clientsFile, clientsText))
		{
			switch (i)
			{
			case 0:
				client.setName(clientsText);
				break;
			case 1:
				client.setNif(stoi(clientsText));
				break;
			case 2:
				// Add service id 
			default:
				break;
			}
			i++;
		}
	}

	clientsVector.push_back(client);
	clientsFile.close();
}

// Removes client from the vector
void Client::removeClient(vector<Client>& clientsVector) {
	Client client;

	int last_pos = clientsVector.size() - 1;
	for (int i = 0; i < clientsVector.size(); i++)
	{
		client = clientsVector[i];
		if (*this == client) {
			clientsVector[i] = clientsVector[last_pos];
			clientsVector.pop_back();
			break;
		}
	}
}


// Returns true if number has 9 digits and is a valid int
bool Client::checknif() const
{
	if (nif < 100000000 || nif > 999999999) // The number has to be 9 digits long    
		return false;
	return true;
}


// OPERATOR OVERLOADING


 // Returns true if clients are the same
bool Client::operator==(const Client& client1) const {
	return nif == client1.nif;
}

// Prints clients
ostream& operator<<(ostream& out, const Client& client) {
	out << "*********************************" << endl;
	out << "Name:" << client.name << endl;
	out << "NIF: " << client.nif << endl;
	// Print services
	out << "*********************************" << endl;

	return out;
}
