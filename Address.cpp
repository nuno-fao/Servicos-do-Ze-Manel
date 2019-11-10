#include "Address.h"


//Class constructors

Address::Address(){
	street = postalCode = location = "unknown";
	doorNumber = 0;
}

Address::Address(string street, unsigned short doorNumber, string postalCode, string location): street(street), doorNumber(doorNumber), postalCode(postalCode), location(location){

}

Address::Address(string fullAddress){

        vector<string> addressVector=vectorString(fullAddress,"/");
        for (size_t i=0;i<addressVector.size();i++) {
            if(addressVector.at(i).at(0)==' '){
                addressVector.at(i)=addressVector.at(i).substr(1,addressVector.at(i).size());
            }
            if(addressVector.at(i).at(addressVector.at(i).size()-1)==' '){
                addressVector.at(i)=addressVector.at(i).substr(0,addressVector.at(i).size()-1);
            }
        }
        if(addressVector[2].size()==0){
            addressVector[2]=" - ";
        }
        this->street=addressVector[0];
        this->doorNumber= ((stoi(addressVector[1])));
        postalCode=addressVector[2];
        location=addressVector[3];
        }
  // metodos GET


string Address::getStreet() const{

	return street;
}

unsigned short Address::getDoorNumber() const{

	return doorNumber;
}


string Address::getPostalCode() const{

	return postalCode;
}

string Address::getLocation() const{

	return location;
}


string Address::getFullAdress() const{
    return getStreet()+" / "+std::to_string(getDoorNumber())+" / "+getPostalCode()+" / "+getLocation();

}


  // metodos SET

void Address::setStreet(string street){

	this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber){

	this->doorNumber = doorNumber;
}


void Address::setPostalCode(string postalCode){

	this->postalCode = postalCode;
}

void Address::setLocation(string  location){

	this->location = location;
}

ostream& operator <<(ostream& os,Address *a){
    os << a->getFullAdress();
    return os;
}

