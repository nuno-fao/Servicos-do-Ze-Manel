#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "misc.h"

using namespace std;

class Address{
 private:
	  string street; // street name
	  unsigned short doorNumber; // door number
	  string postalCode; // postal code
	  string location; // site

 public:
/**
*
* Default constructor
*/
	Address();
/**
* @brief Constructor with all the data necessary
*
* Constructor where all the information is passed
*
* @param street - Address's street
* @param doorNumber - Address's doorNumber
* @param postalCode - Address's postalCode
* @param location - Address's location
*/
	Address(string street, unsigned short doorNumber, string postalCode, string location);
	  /**
* @brief Constructor with data as a string
*
* Constructor the string passed gets parsed and the fields get initialized
*
* @param fullAddress - complete Address as a string in the format "Street / Door Number/ Postal-Code / Location"
*/
	Address(string fullAddress);

  // GET METHODS

/**
* @brief Gets street
*
* Returns the Address's street
*
* @return Returns the Address' street
*/
	string getStreet() const;
/**
* @brief Gets doornumber
*
* Returns the Address's doornumber
*

* @return Returns the Address' doornumber
*/
	unsigned short getDoorNumber() const;
	  /**
* @brief Gets postal-code
*
* Returns the Address's postal-code
*
* @return Returns the Address' postal-code
*/
	string getPostalCode() const;
/**
* @brief Gets location
*
* Returns the Address's location
*

* @return Returns the Address' location
*/
	string getLocation() const;
/**
* @brief Gets the full Address
*
* Returns the Address in the format "Street / Door Number/ Postal-Code / Location"
*
* @return Returns the full address as a string
*/
	string getFullAdress() const;
  
// SET METHODS

/**
* @brief Sets the street
*
* Sets the Address's street
*
* @param street - Address's street
* @return Returns nothing
*/
	void setStreet(string street);

/**
* @brief Sets the doornumber
*
* Sets the Address's doornumber
*
* @param doorNumber - Address's doornumber
* @return Returns nothing
*/
	void setDoorNumber(unsigned short doorNumber);
/**
* @brief Sets the postalcode
*
* Sets the Address's postalcode
*
* @param postalCode - Address's postalcode
* @return Returns nothing
*/
	void setPostalCode(string postalCode);
/**
* @brief Sets the location
*
* Sets the Address's location
*
* @param location - Address's location
* @return Returns nothing
*/
	void setLocation(string location);

// OTHER METHODS

/**
 * @brief Operator << overloading
 *
 * Overload of << operator to allow an Adress's information to be printed
 *
 * @param os - ostream to allow the chain of ostreams
 * @param a - Service Object containing the data to be printed
 * @return Returns the ostream containing the information to be printed
 */
	friend ostream& operator<<(ostream& os, Service *a);
};



