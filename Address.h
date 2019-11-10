
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
	  Address();
	  Address(string street, unsigned short doorNumber, string postalCode, string location);
          Address(string fullAddress);
  // metodos GET
	  string getStreet() const;
	  unsigned short getDoorNumber() const;
	  string getPostalCode() const;
	  string getLocation() const;
      	  string getFullAdress() const;
  
// metodos SET
	  void setStreet(string street);
	  void setDoorNumber(unsigned short doorNumber);
	  void setPostalCode(string postalCode);
	  void setLocation(string  location);

// outros */
      friend ostream& operator<<(ostream& os, Service *a);
};



