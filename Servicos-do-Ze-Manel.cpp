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
#include "company.h"

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
    Company Ze_Manel;
    Client ac("Miguel Pinto",121263630);
    Service as(*Service::addService(Ze_Manel.getVectorServicesOnQueue(),&ac));
    Ze_Manel.getVectorServicesOnQueue()->push_back(&as);
    for(auto i=Ze_Manel.getVectorServicesOnQueue()->begin();i!=Ze_Manel.getVectorServicesOnQueue()->end();i++)
        cout<<**i<<endl;
    return 0;
}
