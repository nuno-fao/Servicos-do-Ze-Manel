#include "client.h"

// TODO: excecoes, verificacoes, hipotese de cancelar com !q, usar enter_to_exit() nos menus
// Confirmar alteracoes do cliente com Y/N?

Client::Client() {}

Client::Client(Client const &x){
    this->nif=x.getNif();
    this->name=x.getName();
}

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

vector<Service *> *Client::getServicesVector() { return &services; }

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

void Client::addClient(vector<Client *> *clientsVector) {


    clearScreen();
    string tempName;
    string tempNif;
    bool variable_error=true;
    while (variable_error) {
        cout<<"Enter the Name"<<endl;

        getline(cin,tempName);
        checkIfOut(tempName);
        clearScreen();
        if(strIsChar(tempName))
            variable_error=false;
        else{
            variable_error=true;
            cout<<"Name Input not acceptable, please try again"<<endl;
        }

    }
    variable_error=true;
    while (variable_error) {
        cout<<"Enter the Nif"<<endl;

        getline(cin,tempNif);
        checkIfOut(tempNif);
        clearScreen();
        if(strIsNumber(tempNif) && tempNif.size()==9)
            variable_error=false;
        else{
            variable_error=true;
            cout<<"Nif Input not acceptable, please try again"<<endl;
        }
    }
    Client *tempClient = new Client(tempName,unsigned(stoi(tempNif)));
    clientsVector->push_back(tempClient);

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

    string clientsNameFile = "./files/clients.txt"; // File containing clients
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
                Client *temp=new Client(client);
                clientsVector.push_back(temp);
                i = 0;
            }
        }
    }
    clientsFile.close();
}

void Client::saveToFile(vector<Client*>& clientsVector){
	string clientsNameFile = "./files/clients.txt"; // File containing clients
	ofstream clientsFile;
	clientsFile.open(clientsNameFile);
	if (clientsFile.fail()){
		throw CantOpenClientFile("Could not open associated clients.txt file");
	}
	else{
		for (auto it = clientsVector.begin(); it != clientsVector.end(); it++)
		{
			clientsFile << (*it)->getName() << endl;
			clientsFile << (*it)->getNif() << endl;
			clientsFile << "::::::::::::::::::::::::::::" << endl;
		}
	}
	clientsFile.close();
}


// OPERATOR OVERLOADING

bool Client::operator==(const Client& client1) const {
    return nif == client1.nif;
}

bool Client::operator<(const Client &a) const{
    return nif < a.getNif();
}

ostream& operator<<(ostream& out, const Client& client) {
    out << "Name:" << client.name << endl;
    out << "NIF: " << client.nif << endl; 
	out << "*********************************" << endl;

    return out;
}


ClientInVector::~ClientInVector(){
}

CantOpenClientFile::~CantOpenClientFile(){

}
NotAClient::~NotAClient(){

}

float Client::getMoneySpent() const{
    return money_spent;
}

void Client::calcMoneySpent(){
    money_spent=0;
    for(auto i:services){
        money_spent+=i->getTotalPrice();
    }
}


// ----------------------- //

// Options for Client Management in the User Interface

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
