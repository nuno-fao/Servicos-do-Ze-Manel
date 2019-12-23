#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <fstream>
#include <set>

#include "truck.h"
#include "date.h"
#include "misc.h"
#include "client.h"
#include "company.h"
#include "Address.h"

using namespace std;

class Service;
class Client;
class Truck;
class TemperatureService;
class HazardousService;
class Date;
class Company;
class Address;

enum class Hazard_enum {explosives=0, gases=1, flammableliq=2, flammablesolid=3, oxidizer=4, poisons=5, radioactive=6, corrosives=7, other=8}; //categories for the diferent dangers
enum class Temperature_enum{p1_20=0, n20_0=1,n50_n21=2,n100_n51=3};

enum class type {ordinary=0,hazardous=1,animal=2,lowTemperature=3};

enum state {
    on_queue=0,on_transit=1,finished=2
};

class Service
{
public:
	/**
* Default destructor
*/
    virtual ~Service();
	/**
* Default constructor
*/
	Service();
    //get methods
		/**
* @brief Gets origin
*
* Returns the origin of the service
*
* @return Returns the origin of the service as Address data type
*/
    Address getOrigin() const; 
	/**
* @brief Gets destiny
*
* Returns the destiny of the service
*
* @return Returns the destiny of the service as Address data type
*/
    Address getDestination() const;
	/**
* @brief Gets distance
*
* Returns the distance from origin to destiny
*
* @return Returns the distance from origin to destiny
*/
    unsigned getDistance() const;
	/**
* @brief Gets type
*
* Returns the type of service
*
* @return Returns the type of service
*/
    type getType() const;
	/**
* @brief Gets id
*
* Returns the id of service
*
* @return Returns the id of service
*/
    unsigned int getId() const;
	/**
* @brief Gets state
*
* Returns the state of service
*
* @return Returns the state of service as a state data type
*/
    state getState() const;
	/**
* @brief Gets starting date
*
* Returns the starting date of service
*
* @return Returns the starting date of the service
*/
    Date *getIDate() const;
	/**
* @brief Gets arrival date
*
* Returns the arrival date of service
*
* @return Returns the arrival date of the service
*/
    Date *getADate() const;
	/**
* @brief Gets the client that bought the service
*
*
* @return Returns a pointer to the client that bought the service
*/
    Client *getClient() const;
	/**
* @brief Gets the trucks associated to the service and respective cargo in a map
*
*
* @return Returns a map to the trucks associated to the service and respective cargo
*/
    map<Truck *, float> *getTrucks();
	/**
* @brief Gets full price of the service
*
*
* @return Returns full price of the service
*/
    float getTotalPrice() const;
	/**
* @brief Gets quantity of the material to transport
* Gets quantity of the material to transport
*
* @return Returns quantity of the material to transport
*/
    float getQuantity() const;
	
    float getMultiplier(){return  1;}
	/**
* @brief Gets  material to transport
* Gets material to transport
*
* @return Returns a string with the material to transport
*/
    string getMaterial() const;

    //set methods
	/**
* @brief Sets service origin
*
* Sets service origin to parameter given
* @param origin - Address data type that will be the service's new origin
* @return Returns nothing
*/
    void setOrigin(Address origin);
	/**
* @brief Sets service destination
*
* Sets service destination to parameter given
* @param destination - Address data type that will be the service's new destination
* @return Returns nothing
*/
    void setDestination(Address destination);
	/**
* @brief Sets service time
*
* Sets service duration to parameter given
* @param time - will be new value of the service's time
* @return Returns nothing
*/
    void setTime(double time);
	/**
* @brief Sets service travel distance
*
* Sets service's distance member to be equal to the parameter given
* @param distance - will be new value of the service's distance
* @return Returns nothing
*/
    void setDistance(unsigned distance);
	/**
* @brief Sets service's type
*
* Sets service's ser_type member to be equal to the parameter given
* @param type - will be new value of the service's ser_type
* @return Returns nothing
*/
    void setType(type type);
	/**
* @brief Sets service travel state
*
* Sets service's state member to be equal to the parameter given
* @param state - will be new value of the service's state
* @return Returns nothing
*/
    void setState(state state);
	/**
* @brief Sets service initial date
*
* Sets service's starting date
* @param date - will be new value of the service's initialDate
* @return Returns nothing
*/
    void setIDate(Date *date);
	/**
* @brief Sets service arrival date
*
* Sets service's arrival date
* @param date - will be new value of the service's arrivalDate
* @return Returns nothing
*/
    void setADate(Date *date);
	/**
* @brief Sets service's client
*
* Sets service's client. (Important to know who actually bought it)
* @param client - pointer to the service's owner
* @return Returns nothing
*/
    void setClient(Client *client);
	/**
* @brief Sets service material quantity
*
* Sets service's material quantity
* @param quantity - how much material there is in kg
* @return Returns nothing
*/
    void setQuantity(float quantity);
	/**
* @brief Sets service material
*
* Sets service's material
* @param string - material description
* @return Returns nothing
*/
    void setMaterial(string material);

	/**
* @brief Adds truck and respective load to trucks map
*
* Adds truck and respective load to trucks map member
* @param truck - truck that will be part in this service execution
* @param cargo - how much material it will transport in kg
* @return Returns nothing
*/
    void addTruck(Truck *truck,float cargo);

    //file methods
	 /**
 * @brief Saves the services
 *
 * Saves the services into the program by writing them to the according file (whether they are finished,on queue or on transit) in the specified format
 *
 * @param services_on_transit - Vector where the pointers to the in progress services are stored
 * @param services_finished - Vector where the pointers to the finished services are stored
 * @param services_on_queue - Vector where the pointers to the on hold services are stored
 * @return Returns nothing
 */
    static void saveToFile(list<Service*>*services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
	/**
 * @brief Loads the services
 *
 * Loads the services into the program by pushing them to a vector
 *
 * @param services_on_transit - Vector where the pointers to the in progress services are stored
 * @param services_finished - Vector where the pointers to the finished services are stored
 * @param services_on_queue - Vector where the pointers to the on hold services are stored
 * @return Returns nothing
 */
    static void loadFromFile(list<Service *> *services_finished, vector<Service *> *services_on_transit, vector<Service *> *services_on_queue);
	/**
 * @brief Creates new service
 *
 * Creates new service, handles wrong inputs and pushes it to both the service on queue and the client that bought it. 
 *
 * @param services - Vector where the pointers to the on queue services are stored
 * @param client - CLient that is buying this new service
 * @return Returns the service itself
 */
    static Service *addService(vector<Service *> *services, Client *client=nullptr);
	/**
 * @brief Edit new service
 *
 * Edits service, only partially implemented as of writing this
 *
 * @return Returns nothing
 */
    void editService();
	/**
 * @brief Removes a service
 *
 * Can only remove on queue services. Only partially implemented as of writing this because it can already remove the service but does not update the status of the trucks associaeted with it
 *
 * @param services - Vector where the pointers to the on queue services are stored
 * @param id - id of the service to remove
 * @return Returns true or false whether it was successfull or not
 */
    static bool removeService(vector<Service *> *services,unsigned id);
	/**
 * @brief Overloads operator << for services
 *
 * Overloads operator << for services so that we can print a service's full info more easily
 *
 * @param os - ostream
 * @param a - service to 'print' the info
 * @return Returns nothing
 */

    virtual string getSpecificType(){return "non correct";}
    friend ostream& operator<<(ostream& os, Service *a);

    static set<unsigned> idList;

protected:
    Service(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity);
    Service(string material, string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date, Client *client, float quantity, float total_price,unsigned id);
    Address *origin; /**< stores the origin of the Service */
    Address *destination;
    string material;
    Date *arrivalDate;
    unsigned distance;
    float quantity;
    type ser_type;
    unsigned int id;
    map<Truck*,float> trucks;
    state ser_state;
    Date *initialDate;
    Client *client;
    float total_price;
	/**
 * @brief Caculates what and how many trucks of the appropriate type are needed
 *
 * Caculates what and how many trucks of the appropriate type are needed for the service with it's material quantity
 *
 * @return Returns the remaining material quantity after calculations (positive if NOT POSSIBLE, otherwise possible)
 */
    int autoAddTrucks();



};

class HazardousService: public Service
{
public:
    ~HazardousService();
    HazardousService(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Hazard_enum hazard);
    HazardousService(string material,string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Hazard_enum hazard,float total_price,unsigned id);
    Hazard_enum type;
    string getSpecificType();
};

class TemperatureService: public Service
{
public:
    ~TemperatureService();
    TemperatureService(string material,Address origin, Address destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date,Client *client,float quantity,Temperature_enum temp);
    TemperatureService(string material, string origin, string destination, Date *arrivalDate, unsigned distance, type type, state state, Date *date, Client *client, float quantity, Temperature_enum temp, float total_price, unsigned id_s);
    Temperature_enum type;
    string getSpecificType();
};

class ServiceDoNotExist//: public Service
{
public:
    string erro;
	/**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the program is unable to find a service
 *
 * @param erro - Message describing error
 */
    ServiceDoNotExist(string erro):erro(erro){}
};

class ServiceFinishedFileError//: public Service
{
public:
	/**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the program is unable to open the associated file containing the finished services
 *
 */
    ServiceFinishedFileError(){}
};

class ServiceOnQueueFileError//: public Service
{
public:
	/**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the program is unable to open the associated file containing the on queue services
 *
 */
    ServiceOnQueueFileError(){}

};
class ServiceOnTransitFileError//: public Service
{
public:
	/**
 * @brief Constructor with all data necessary
 *
 * This exception is thrown if the program is unable to open the associated file containing the on transit services
 *
 */
    ServiceOnTransitFileError(){}

};

