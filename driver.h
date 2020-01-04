#pragma once
#include <string>
#include <fstream>

#include "company.h"
#include "bst.h"
using namespace std;

class Company;
class Driver
{
public:
/**
 * @brief Constructor with all data necessary
 *
 * Receives all the data it needs to construct a driver properly
 * It is the most used constructor of the three
 *
 * @param nif - Identification number of the driver
 * @param name - Name of the driver
 * @param serviceHours - driver's number of hours of service
 */
    Driver(int nif,string name, float serviceHours);
/**
* Default Constructor
*/
    Driver(){
        Driver(1,"0",0);
    }

/**
* @brief Gets the Driver's NIF
*
* @return Returns an int representing the driver's NIF
*/
    int getNif() const;
/**
* @brief Gets the Driver's name
*
* @return Returns the driver's name
*/
    string getName() const;
/**
* @brief Gets the Driver's number of hours of service
*
* @return Returns a float representinf the number of hours of service
*/
    float getServiceHours() const;
/**
* @brief Gets the Driver's status
*
* @return Returns true if the driver is active
*/
    bool getDriverActiv() const;
/**
 * @brief Sets a Driver's NIF
 *
 * Updates the Driver's NIF
 *
 * @param nif - int contaning NIF to be set
 * @return Returns nothing
 */
    void setNif(int nif);
/**
* @brief Sets a Driver's name
*
* Updates the Driver's name
*
* @param name - String containing the Driver's name to be updated
* @return Returns nothing
*/
    void setName(string name);

/**
* @brief Sets a Driver's service hours
*
* Updates the Driver's number of hours of service
*
* @param ServiceHours - float with number of hours to be set
* @return Returns nothing
*/
    void setServiceHours(float ServiceHours);

    /**
* @brief loads drivers info and loads the binary tree
*
* Loads drivers info and loads the binary tree
*
* @return Returns nothing
*/
    static void loadFromFile();
        /**
* @brief saves drivers info into the file
*
* Saves drivers info into the file
*
* @return Returns nothing
*/
    static void saveToFile();
            /**
* @brief adds a driver to the binary tree
*
* Adds a driver to the binary tree
*
* @return Returns nothing
*/
    static void addDriver();
     /**
* @brief toogles driver active status
*
* if the driver is active, it turn non active, if it is inactive it turn active
*
* @return Returns nothing
*/
    void toogleDriverActiv();

private:
    int nif; /// Driver's NIF
    string name; /// Driver's name
    float service_hours; /// Driver's number of hours of service
    bool active=0; /// true if active
};

/**
* @brief overloads de < operator too define drivers priority in the binary tree
*
* overloads de < operator too define drivers priority in the binary tree
*
* @param a - driver a
* @param b - driver b
* @return returns if a driver a is smaller than a driver b
*/
bool operator <(const Driver &a,const Driver &b);

/**
* @brief Operator << overloading
*
* Overload of << operator to allow a Driver's information to be printed
*
* @param os - ostream to allow the chain of ostreams
* @param a - Driver Object containing the data to be printed
* @return Returns the ostream containing the information to be printed
*/
ostream& operator <<(ostream& os, const Driver &a);

