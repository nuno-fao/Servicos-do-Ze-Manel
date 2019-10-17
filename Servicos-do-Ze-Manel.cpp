// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>

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

bool cmp(const Service *a, const Service *b){
    if(a->getDate()<b->getDate())
        return true;
    else
        return false;
}
int main()
{
    vector<Service*> cv1;
    Service::loadFromFile(&cv1);
    //for(auto x:cv1){
        //cout<<x->getTime()<<endl;
    //}
    time_t before=time(0);
    char* dt = ctime(&before);
    sort(cv1.begin(),cv1.end(),cmp);
    time_t now=time(0);
    char* dn = ctime(&now);
    cout<<dn<<endl<<dt<<endl<<dn-dt<<endl;
    cout<<cv1.size();
	return 0;
}
