#include "client.h"

// Destrutor


unsigned int Client::lastId=0;

Client::Client(string name, unsigned int nif, vector<Service*> *services): name(name), id(lastId), nif(nif){
    if(services==nullptr)
        services=new vector<Service*>;
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
//void getServicesVector(vector<Service*> *services) const;

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


void Client::loadClients(const string &clientsNameFile, vector<Client> &clientsVector) {

	string clientsText;
	ifstream clientsFile;
	Client client;

	int i = 0;
	clientsFile.open(clientsNameFile);
	if (clientsFile.fail())
	{
		CantOpenClientFile cocf("Could not open associated clients.txt file");
		throw cocf;
	}

	else
	{
		while (getline(clientsFile, clientsText))
		{
			vector<int> temporary;
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
//void Client::removeClient(vector<Client>& clientsVector) {
//	Client client;
//
//	int last_pos = clientsVector.size() - 1;
//	for (int i = 0; i < clientsVector.size(); i++)
//	{
//		client = clientsVector[i];
//		if (*this == client) {
//			clientsVector[i] = clientsVector[last_pos];
//			clientsVector.pop_back();
//			break;
//		}
//	}
//}

// Returns true if number has 9 digits and is a valid int
//bool Client::checknif() const
//{
//	bool valid = true;
//
//	if (nif < 100000000 || nif > 999999999) // The number has to be 9 digits long    
//		valid = false;
//
//	return valid;
//}

//Prints client to the screen
//void Client::showClient() const
//{
//	cout << "*********************************" << endl;
//	cout << "Name:" << name << endl;
//	cout << "NIF: " << nif << endl;
//	cout << "Family Size: " << familySize << endl;
//	cout << "Address: " << endl;
//	address.showAddress();
//	cout << "TravelPacks: " << travelPacksToString(travelPackIds) << endl;
//	cout << "Total Value: " << totalPurchased << endl;
//	cout << "*********************************" << endl;
//}

/*
ostream& operator<<(ostream& out, const Client& client) {
	out << "*********************************" << endl;
	out << "Name:" << client.name << endl;
	out << "NIF: " << client.nif << endl;
	//auto it = services.begin();
	//for (it; it != services.end(); it++)
	//{
	//	out << 
	//}
	return out;
}


// Returns true if clients are the same
bool Client::operator==(const Client& client1, const Client& client2) {
	return client1.getName() == client2.getName() && client1.getnif() == client2.getnif() && client1.getServicesVector() == client2.getServicesVector();
}
*/

