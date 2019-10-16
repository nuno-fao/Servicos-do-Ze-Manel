// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cctype>

#include "client.h"
#include "truck.h"
#include "service.h"

using namespace std;


/*
This function receives a name and returns true if it is valid
*/

bool verifyName(const string &name) {

	for (unsigned int i = 0; i < name.size(); i++){	
        if (!isdigit(name.at(i))) {
            return  false;
		}
	}

    return true;
}


int main()
{
    vector<Service*> cv1;
    Service::loadFromFile(&cv1);
    for(auto x:cv1){
        cout<<x->getTime()<<endl;
    }
	return 0;
}
