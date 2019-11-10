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
    Client(Client const &);
    Client();
	Client(string name, unsigned int nif, vector<Service*> *services = nullptr);
    virtual ~Client();

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
    //tive q comentar para testar!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    //Client(){};
    float money_spent=0;
    string name;
    unsigned int nif;
    vector<Service*> services;

};

class NotAClient: public Client{
public:
    ~NotAClient();
    string erro;
    NotAClient(unsigned nif_n, string erro): Client(), erro(erro){
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



class CantOpenClientFile{
public:
    ~CantOpenClientFile();
	string erro;
    CantOpenClientFile(string erro): erro(erro) {}
};

//class BadNif {
//public:
//	~BadNif;
//	string erro;
//	CantOpenClientFile(string erro) : erro(erro) {}
//};
