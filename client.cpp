#include "client.h"

// TODO: excecoes, verificacoes, hipotese de cancelar com !q, usar enter_to_exit() nos menus
// Confirmar alteracoes do cliente com Y/N?
// Descomentar misc 126


Client::Client() {}

Client::Client(string name, unsigned int nif, vector<Service*> *services): name(name), nif(nif){
    if(services==nullptr)
        services=new vector<Service*>;

	//if (!checkNif(nif))
		//throw BadNif(nif, "NIF not allowed!");
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

//other methods	
void Client::addService(Service *service){
    services.push_back(service);
}

void Client::addClient(vector<Client>& clientsVector) {

    for (vector<Client>::iterator it = clientsVector.begin(); it != clientsVector.end(); it++) {
        if (it->nif == this->nif) {
            throw ClientInVector(nif, "Client is already in the database!");
        }
    }

    clientsVector.push_back(*this);
}

// Removes client from the vector
void Client::removeClient(vector<Client*>& clientsVector) {
    Client *client;

    size_t last_pos = clientsVector.size() - 1;
    for (size_t i = 0; i < clientsVector.size(); i++)
    {
        client = clientsVector[i];
        if (*this == *client) {
            clientsVector[i] = clientsVector[last_pos];
            clientsVector.pop_back();
            break;
        }
    }
}


void Client::loadClients(vector<Client*>& clientsVector) {

	string clientsNameFile = "clients.txt"; // File containing clients
	string clientsText; // String containing contents of clients.txt
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
				client.setNif(unsigned(stoi(clientsText)));
				break;
			default:
				break;
			}
			i++;
			if (i == 3) {
				clientsVector.push_back(&client);
				i = 0;
			}
		}
	}

	clientsVector.push_back(&client);
	clientsFile.close();
}

void Client::saveToFile(vector<Client*>& clientsVector)
{
}


// OPERATOR OVERLOADING

bool Client::operator==(const Client& client1) const {
    return nif == client1.nif;
}

bool Client::operator<(const Client &a) const{
    return nif < a.getNif();
}

ostream& operator<<(ostream& out, const Client& client) {
    out << "*********************************" << endl;
    out << "Name:" << client.name << endl;
    out << "NIF: " << client.nif << endl;
    // Print services
    out << "*********************************" << endl;

    return out;
}


ClientInVector::~ClientInVector(){
}

CantOpenClientFile::~CantOpenClientFile(){

}
NotAClient::~NotAClient(){

}


// ----------------------- //

// Options for Client Management in the User Interface

//Prints the menu and asks the user what option to choose

//void runClientsMenu(vector<Client>& clientsVector) {
//	int option;
//
//	cout << "Welcome to the Clients Menu! Please choose what you want to do: ";
//	cout << endl << endl;
//	cout << "0. Go back" << endl;
//	cout << "1. Create a new client." << endl;
//	cout << "2. Change a client information." << endl;
//	cout << "3. Remove a client" << endl;
//	cout << "4. See information from all clients. " << endl;
//	cout << "5. See information from a specific client. " << endl;
//	// Eventually add more functions
//	cout << "Insert the number correspondent to your option: ";
//	cin >> option;
//
//	while (cin.fail() || option < 0 || option > 8)
//	{
//		cout << "Invalid option, please insert the option again: ";
//		clearBuffer();
//		cin >> option;
//	}
//
//	clearBuffer();
//
//	if (option == 0) { /*Correr Menu inicial*/ }
//	if (option == 1) { createClientOption(clientsVector); }
//	if (option == 2) { modifyClientOption(clientsVector); }
//	if (option == 3) { removeClientOption(clientsVector); }
//	if (option == 4) { showAllClients(clientsVector); }
//	if (option == 5) { showClientOption(clientsVector); }
//
//	// Correr menu inicial de novo (quando acaba a operacao escolhida)
//}
//
////Asks for client information and returns a client
//Client askForClientsInformation(vector<Client> clientsVector) {
//	Client client;
//
//	string name;
//	int zeroIfNotInFile = 0;
//	int nif;
//	int familyNumber;
//	bool inDatabase = false;
//	string addressText;
//	vector<int> touristicPacksBought;
//	touristicPacksBought.push_back(0);
//
//	cout << "Name: ";
//	getline(cin, name);
//
//	cout << "NIF: ";
//	cin >> nif;
//	checkNif(nif);
//	cin.clear();
//	cin.ignore(10000, '\n');
//
//	for (int i = 0; i < clientsVector.size(); i++) {
//		if (clientsVector[i].getNif() == nif) {
//			inDatabase = true;
//			break;
//		}
//	}
//
//	while (inDatabase) // DEVO FAZER ESTA VERIFICACAO AO ADICIONAR O CLIENTE OU AQUI???
//		// fazer exceptions em qualquer um dos casos
//	{
//		cout << "NIF is already in the database, please insert again: ";
//		cin >> nif;
//		checkNif(nif);
//		cin.clear();
//		cin.ignore(10000, '\n');
//
//		for (int i = 0; i < clientsVector.size(); i++)
//		{
//			zeroIfNotInFile = 0;
//			if (clientsVector[i].getNif() == nif) {
//				zeroIfNotInFile += 1;
//				break;
//			}
//		}
//		if (zeroIfNotInFile == 0)
//			inDatabase = false;
//	}
//
//	client.setName(name);
//	client.setNif(nif);
//	// set services
//	return client;
//}
//
//
////Asks the user for data and adds a new client to clientsvector
//void createClientOption(vector<Client>& clientsVector) {
//	Client client;
//
//	cout << "Please insert the data of your new client" << endl << endl;
//
//	client = askForClientsInformation(clientsVector);
//	client.addClient(clientsVector);
//
//	cout << endl << endl << "Client created successfully!";
//	menuSeparator();
//}
