#pragma once
#include <string>
#include <vector>

#include "service.h"
#include "misc.h"

using namespace std;

class Service;
class Truck;

class Client
{
public:
/**
 * Constructor with a Client Object as parameter
 * @param x Client data that is used to initialize the Client Object
 */
    Client(Client const &);
/**
 * Default Constructor
 */
	Client();
/**
 * @brief Constructor with all data necessary
 *
 * Receives all the data it needs to construct a client properly
 * It is the most used constructor of the three
 * The vector pointer that is passed 
 *
 * @param name Name of the client
 * @param nif Identification number of the client
 * @param services - Pointer to the vector of Services the client has bought (none by default)

 */
	Client(string name, unsigned int nif, vector<Service*> *services = nullptr);
/**
 * Default Destructor
 */
    virtual ~Client();
/**
 * @brief Loads the clients
 *
 * Loads the clients into the program by pushing them to a vector
 * It does this by going line by line in the clients.txt (which is formatted) and  
 * @param name Name of the client
 * @param nif Identification number of the client
 * @param services - Pointer to the vector of Services the client has bought (none by default)

 */
  	static void loadClients(vector<Client*>& clientsVector);
	static void saveToFile(vector<Client*>& clientsVector);

	void editClient();
	void removeClient(vector<Client *> &clientsVector);
	
    //get methods
    string getName() const;
    float getMoneySpent() const;
    unsigned getNif() const;
    vector<Service*> *getServicesVector();

    //set methods
    void setName(string name);
    void setNif(unsigned nif);
    void calcMoneySpent();

    //add methods
    void addService(Service *service);
    static void addClient(vector<Client*> *clientsVector);


    friend ostream& operator<<(ostream& out, const Client& client);

    bool operator<(const Client &a) const;
    bool operator== (const Client& client1) const;
protected:
    float money_spent=0; /*!< Total money spent in services - used  */
    string name;
    unsigned int nif; /*!< Client's Identification - used whenever comparing and verifying clients */
    vector<Service*> services;

};

class NotAClient: public Client{
public:
    ~NotAClient();
    string erro;
    NotAClient(unsigned nif_n, string erro): erro(erro){
        this->nif=nif_n;
    }
	unsigned int getNif() const {
		return nif;
	}
};

class ClientInVector{
public:
    ~ClientInVector();
	string erro;
    unsigned nif;
    ClientInVector(unsigned nif_n, string erro): erro(erro) {
		this->nif = nif_n;
	}
	unsigned int getNif() const {
		return nif;
	}
};

class ClientNotInVector {
public:
	~ClientNotInVector();
	string erro;
	unsigned nif;
	ClientNotInVector(unsigned nif_n, string erro) : erro(erro) {
		this->nif = nif_n;
	}
	unsigned int getNif() const {
		return nif;
	}
};



class CantOpenClientFile{
public:
    ~CantOpenClientFile();
	string erro;
    CantOpenClientFile(string erro): erro(erro) {}
};