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
    unsigned opt=1;
    string temp;
    while (opt!=0) {
        cout<<"[1] see services"<<endl;
        cout<<"[2] add service"<<endl;
        if(cin>>opt && opt<=2)
            switch (opt) {
            case 1:
                clearBuffer();
                clearScreen();
                for(auto i=Ze_Manel.getVectorServicesOnQueue()->begin();i!=Ze_Manel.getVectorServicesOnQueue()->end();i++)
                    cout<<*i;
                if(!Ze_Manel.getVectorServicesOnQueue()->size())
                    cout<<"There are no info to show"<<endl;
                getline(cin,temp);
                clearScreen();
                break;
            case 2:
                clearScreen();
                clearBuffer();
                Client *a =new Client("Margarida Cruz",121212121);
                Service::addService(Ze_Manel.getVectorServicesOnQueue(),a);
                break;

            }
        else{
            clearBuffer();
            clearScreen();
            cout<<"Non valid option, please try again"<<endl;
        }
    }
    return 0;
}
