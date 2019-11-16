#pragma once
#include <string>
#include <vector>
#include <algorithm>

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
    Client(Client const &x);
    /**
 * Default Constructor
 */
    Client();
    /**
 * @brief Constructor with all data necessary
 *
 * Receives all the data it needs to construct a client properly
 * It is the most used constructor of the three
 *
 * @param name - Name of the client
 * @param nif - Identification number of the client
 * @param services - Pointer to the vector of pointers to Services that the client has bought (none by default)
 */
    Client(string name, unsigned int nif,float money_spent, vector<Service*> *services = nullptr);
    /**
 * Default Destructor
 */
    virtual ~Client();
    /**
 * @brief Loads the clients
 *
 * Loads the clients into the program by pushing them to a vector
 *
 * @param clientsVector - Vector where the pointers to the Clients are stored
 * @return Returns nothing
 */
    static void loadClients(vector<Client*>& clientsVector);
    /**
 * @brief Saves the clients
 *
 * Saves the clients the user has added by writing to the clients.txt file in the specified format
 *
 * @param clientsVector - Vector where the pointers to the Clients are stored
 * @return Returns nothing
 */
    static void saveToFile(vector<Client*>& clientsVector);
    /**
 * @brief Edits the information of a client
 *
 * Edits the information of a client by asking
 *
 * @return Returns nothing
 */
    void editClient();
    /**
 * @brief Removes a client
 *
 * Removes a client from the vector of Clients if the client has no services bought
 * Throws an exception if the specified client is not found in the vector
 *
 * @param clientsVector - Vector where the pointers to the Clients are stored
 * @return Returns nothing
 */
    void removeClient(vector<Client *> &clientsVector);

    // GET METHODS

    /**
 * @brief Gets the Client's name
 *
 * @return Returns a string containing the Client's name
 */
    string getName() const;
    /**
 * @brief Gets the money spent in services
 *
 * @return Returns a float representing the money spent in services by the client
 */
    float getMoneySpent() const;
    /**
 * @brief Gets the Client's identification number
 *
 * @return Returns an unsigned 9-digit integer containing the Client's identification number
 */
    unsigned getNif() const;
    /**
 * @brief Gets the Client's bought services
 *
 * @return Returns an a vector containing pointers to the Client's bought services
 */
    vector<Service*> *getServicesVector();

    // SET METHODS

    /**
 * @brief Sets a Client's name
 *
 * Updates the Client's name
 *
 * @param name - String containing the Client's name to be updated
 * @return Returns nothing
 */
    void setName(string name);
    /**
 * @brief Sets a Client's identification number
 *
 * Updates the Client's identification number
 *
 * @param nif - an unsigned integer containing the Client's identification number to be updated
 * @return Returns nothing
 */
    void setNif(unsigned nif);
    /**
 * @brief Calculates the Client's money spent
 *
 * Computes the money spent by a Client in services and updates it
 *
 * @return Returns nothing
 */
    void calcMoneySpent();

    // ADD METHODS

/**
 * @brief Adds a Service bought by a Client
 *
 * Adds a Service bought by a Client to the vector of Services
 *
 * @param service - Pointer to the Service to he added to the vector of Services
 * @return Returns nothing
 */
    void addService(Service *service);
   /**
 * @brief Adds a Client
 *
 * Adds a Client to the vector of Clients
 *
 * @param clientsVector - Pointer to the vector of pointers to Clients
 * @return Returns nothing
 */
    static void addClient(vector<Client*> *clientsVector);
	/**
* @brief Removes a service
*
* Removes a bought service from a Client
*
* @param service - Pointer to the service to be removed
* @return Returns nothing
*/
    void removeService(Service *service);

    /**
 * @brief Operator << overloading
 *
 * Overload of << operator to allow a Client's information to be printed
 *
 * @param out - ostream to allow the chain of ostreams
 * @param client - Client Object containing the data to be printed
 * @return Returns the ostream containing the information to be printed
 */
    friend ostream& operator<<(ostream& out, const Client& client);
    /**	
* @brief Operator < overloading
*
* Overload of < operator for comparisons. A Client is < if his identification number is smaller (as a normal, decimal interpretation)
*
* @param a - Client Object containing the nif to be compared
* @return Returns true if the Client has a smaller nif
*/
    bool operator<(const Client &a) const;


    /**
* @brief Operator == overloading
*
* Overload of == operator for comparisons. A Client is == if his identification number is the same
*
* @param client1 - Client Object containing the nif to be compared
* @return Returns true if the Client has an equal nif
*/
    bool operator== (const Client& client1) const;

protected:
    float money_spent=0; /*!< Total money spent in services*/
    string name;
    unsigned int nif; /*!< Client's Identification - used whenever comparing and verifying clients */
    vector<Service*> services;/*!< Client's vector of bought Services */

};

class NotAClient: public Client{
public:
    /**
* Default destructor
*/
    ~NotAClient();
    string erro; /*!< Message describing error */
    /**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if a given nif belongs to no client
 *
 * @param nif_n - Identification number of the client
 * @param erro - Message describing error
 */
    NotAClient(unsigned nif_n, string erro): erro(erro){
        this->nif=nif_n;
    }
    /**
 * @brief Gets identification number
 *
 * Returns identification number of the client searched
 *
 * @return Returns an unsigned integer containing the identification number
 */
    unsigned int getNif() const {
        return nif;
    }
};

class ClientInVector: public Client{
public:
    /**
* Default destructor
*/
    ~ClientInVector();
    string erro; /*!< Message describing error */
    unsigned nif;
    /**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the Client being searched for is already in the Clients vector
 *
 * @param nif_n - Identification number of the client
 * @param erro - Message describing error
 */
    ClientInVector(unsigned nif_n, string erro): erro(erro) {
        this->nif = nif_n;
    }
    /**
 * @brief Gets identification number
 *
 * Returns identification number of the client
 *
 * @return Returns an unsigned integer containing the identification number
 */
    unsigned int getNif() const {
        return nif;
    }
};

class ClientNotInVector : public Client{
public:
    /**
* Default destructor
*/
    ~ClientNotInVector();
    string erro; /*!< Message describing error */
    /**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the Client being searched for is not in the Clients vector
 *
 * @param nif_n - Identification number of the client
 * @param erro - Message describing error
 */
    ClientNotInVector(unsigned nif_n, string erro) : erro(erro) {
        this->nif = nif_n;
    }
    /**
 * @brief Gets identification number
 *
 * Returns identification number of the client searched
 *
 * @return Returns an unsigned integer containing the identification number
 */
    unsigned int getNif() const {
        return nif;
    }
};



class CantOpenClientFile : public Client{
public:
    /**
* Default destructor
*/
    ~CantOpenClientFile();
    string erro; /*!< Message describing error */
    /**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the program is unable to open the associated file containing the clients
 *
 * @param erro - Message describing error
 */
    CantOpenClientFile(string erro): erro(erro) {}
};
