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
    Driver(int nif,string name,float serviceHours);
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

    static void loadFromFile();
    static void saveToFile();
    static void addDriver();
    void toogleDriverActiv();

private:
    int nif; /// Driver's NIF
    string name; /// Driver's name
    float service_hours; /// Driver's number of hours of service
    bool active; /// true if active
};

bool operator <(const Driver &a,const Driver &b);
ostream& operator <<(ostream& os, const Driver &a);

