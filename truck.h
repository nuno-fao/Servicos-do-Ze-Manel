#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "service.h"
#include "company.h"
using namespace std;

class Service;
class Client;
enum class Temperature_enum;
enum class Hazard_enum;
enum class type;


class Truck
{
protected:
    string license; ///format XX-YY-ZZ
    bool available;	///is the truck available right now?
    bool registered;	///is the truck registered to a service in the future?
    vector<Service*> assignedServices;	///services the truck is registered to
    unsigned capacity; //in KG
    float cargo; ///if in transit this holds the weight it transports, if not it is 0

public:
	/**
* @brief Constructor with data
*
* Constructs the object by receiving all the necessary information
*
* @param license - license
* @param available - whether it is available or not
* @param registered - whether it is registereds to a service or not
* @param capacity - truck's maximum capacity
* @param cargo - if it is on transit, how much it is transporting
*/
    Truck(string license, bool available,bool registered,unsigned short capacity, unsigned short cargo);
	/**
*
* Default destructor
*
*/
    virtual ~Truck();
    //get methods
	/**
* @brief Gets capacity
*
* Returns maximum capacity of the truck
*
* @return Returns the maximum capacity of the truck
*/
    unsigned getcapacity() const;
	/**
* @brief Gets availability
*
* Returns if the truck is available
*
* @return Returns whether the truck is available or not
*/
    bool getavailable() const;
	/**
* @brief Gets the license
*
* Returns the truck's license
*
* @return Returns a string with the license
*/
    string getlicense() const;
	/**
* @brief Gets registered
*
* Returns if the truck is registered to a service
*
* @return Returns if it is registered to a service or not in a bool
*/
    bool getregistered() const;
	/**
* @brief Gets cargo
*
* Returns the cargo it transports, if it isnt transporting any it returns 0
*
* @return Returns the cargo it transports, default 0
*/
    float getcargo() const;
	/**
* @brief Gets services
*
* Returns the services the truck is registered to
*
* @return Returns a vector that holds the services the truck is registered to
*/
    vector<Service*> *getServices();
    //set methods

    virtual void setprice(float newval){available=(bool(newval) && available);}
	/**
* @brief Sets cargo
*
*
* @param cargo - the new value of the truck's cargo
* @return Returns nothing
*/
    void setCargo(float cargo);
	/**
* @brief Sets cargo
*
*
* @param foo - true if still registered to a service, false otherwise
* @return Returns nothing
*/
    void setregistered(bool foo);
	/**
* @brief Sets available
*
*
* @param foo - true if it is available, false otherwise
* @return Returns nothing
*/
    void setavailable(bool foo);
    //load and save to file
		/**
* @brief loads trucks and price multipliers from file trucks.txt with the specified format
*
*
* @param trucks - pointer to the vector that will hold the loaded trucks
* @return Returns nothing
*/
    static void loadFromFile(vector<Truck*> *trucks);
	/**
* @brief saves trucks and price multipliers to file trucks.txt with the specified format
*
*
* @param trucks - pointer to the vector that holds all the trucks
* @return Returns nothing
*/
    static void saveToFile(vector<Truck*> *trucks);
    //other
		/**
* @brief Prints basic information about a truck
*
* @return Returns nothing
*/
    virtual void info();
	/**
* @brief adds a service to services vector
*
*
* @param service - pointer to the service that will be pushed back onto the services vector
* @return Returns nothing
*/
    void add_service(Service* service);
	/**
* @brief removes a service from services vector
*
*
* @param id - id of the service to remove
* @return Returns nothing
*/
    void remove_service(unsigned int id);
	/**
* @brief updates data members so that the truck is now on transit
* sets available to false and updates cargo
*
* @param cargo - new value of cargo data member
* @return Returns nothing
*/
    void start_transport(unsigned short cargo);
	/**
* @brief creates a new truck
*
*
* @param trucks - pointer to the vector to which the created truck will be pushed onto
* @return Returns nothing
*/
    static void createTruck(vector<Truck*>* trucks); 
	/**
* @brief removes a truck from the given vector
* only works if the truck has no registered
*
* @param trucks - pointer to the vector from which we will delete the truck
* @return Returns nothing
*/
    static void removeTruck(vector<Truck*>* trucks);
	/**
* @brief return type of truck
*
*
* @return Returns type of truck
*/
    virtual enum type getType();
};
/**
* @brief compares truck by license in ascending order
*
* @return Returns true or false

*/
bool operator<(Truck &a,Truck &b);

class Congelation : public Truck
{
public:
	/**
* @brief constructor for this subclass that calls the one from superclass
*
* @return Returns nothing
*/
    Congelation(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);

	/**
* @brief Default destructor
*
* @return Returns nothing
*/
    ~Congelation() {}
	/**
* @brief Prints more specific information about this truck's subclass
*
* @return Returns nothing
*/
    void info();
    static unordered_map<Temperature_enum, float> tempMul;/*!< will hold price multipliers depending on the service*/
    static map<unsigned , unsigned > CapDist; /*!< holds how many trucks of this have x capacity being that the latter is the key*/
    static float pricePerKG;
    type getType();
};

class HazardousMat : public Truck
{
public:
	/**
* @brief constructor for this subclass that calls the one from superclass
*
* @return Returns nothing
*/
    HazardousMat(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
	/**
* @brief Default destructor
*
* @return Returns nothing
*/
    ~HazardousMat(){}

	/**
* @brief Prints more specific information about this truck's subclass
*
* @return Returns nothing
*/
    void info();
    static float pricePerKG;
    type getType();
    static unordered_map<Hazard_enum, float> hazardMul;	/*!< will hold price multipliers depending on the service*/
    static map<unsigned , unsigned > CapDist; /*!< holds how many trucks of this have x capacity being that the latter is the key*/

};

class Animal : public Truck
{
public:
	/**
* @brief constructor for this subclass that calls the one from superclass
*
* @return Returns nothing
*/
    Animal(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
	/**
* @brief Default destructor
*
* @return Returns nothing
*/
    ~Animal(){}
	/**
* @brief Prints more specific information about this truck's subclass
*
* @return Returns nothing
*/
    void info();
    static float pricePerKG;
    type getType();
    static map<unsigned , unsigned > CapDist; /*!< holds how many trucks of this have x capacity being that the latter is the key*/
};

class Normal : public Truck
{
public:
	/**
* @brief constructor for this subclass that calls the one from superclass
*
* @return Returns nothing
*/
    Normal(string license, bool available, bool registered, unsigned short capacity, unsigned short cargo);
	/**
* @brief Default destructor
*
* @return Returns nothing
*/
    ~Normal(){}
	/**
* @brief Prints more specific information about this truck's subclass
*
* @return Returns nothing
*/
    void info();
    static float pricePerKG;
    type getType();
    static map<unsigned , unsigned > CapDist; /*!< holds how many trucks of this have x capacity being that the latter is the key*/

};

class FailedToOpenTrucks {
public:
	/**
* @brief Constructor with all data necessary
*
* This exception is thrown if the program is unable to open the associated file containing the trucks
*
*/
    FailedToOpenTrucks() {}
};

class TruckDoNotExist{
public:
    string erro;
    string license;
	/**
* @brief Constructor with all data necessary
*
* This exception is thrown if the program is unable to find the truck
*
* @param erro - Message describing error
* @param license - license that was not found
*/
    TruckDoNotExist(string erro,string license):erro(erro),license(license){}
};

class NotATruck{
public:
    string erro;
    string license;
	/**
* @brief Constructor with all data necessary
*
* This exception is thrown if the truck is not valid
*
* @param erro - Message describing error
* @param license - license that isn't valid
*/
    NotATruck(string erro,string license):erro(erro),license(license){}
};
