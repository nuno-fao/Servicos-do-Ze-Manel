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
    Client c1("Miguel Pinto",252496960,cv1);
    Service s1("porto","braga",4.1,300,hazardous,on_queue,Date(2018,2,25),&c1);
    Service s2("porto","braga",4.1,300,hazardous,on_queue,Date(2018,2,25),&c1);
    cout<<s1.getState()<<endl;
    cout<<s1.getClient()->getName()<<endl;
    cout<<s1.getId()<<endl<<endl;
    cout<<s2.getState()<<endl;
    cout<<s2.getClient()->getName()<<endl;
    cout<<s2.getId()<<endl;

	return 0;
}
