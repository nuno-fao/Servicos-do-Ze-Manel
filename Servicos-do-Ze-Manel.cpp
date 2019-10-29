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

bool verifyName(const string &name) { // TIRAR ISTO E POR NO MISC?

    for (unsigned int i = 0; i < name.size(); i++){
        if (!isdigit(name.at(i))) {
            return false;
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


Company *Company::company = nullptr;
int main()
{
    Company *Ze_Manel = nullptr;
    Ze_Manel->getCompany();
    Truck::loadFromFile(Ze_Manel->getVectorTrucks());
    Service::loadFromFile(Ze_Manel->getVectorServicesFinished(),Ze_Manel->getVectorServicesOnTransit(),Ze_Manel->getVectorServicesOnQueue());
    unsigned opt=1;
    string temp;
    while (opt!=0) {
        cout<<"[1] See services"<<endl;
        cout<<"[2] Add service"<<endl;
        cout<<"[3] Remove service"<<endl;
        cout<<Ze_Manel->services_on_queue_changed<<endl;
        if(cin>>opt && opt<=3)
            switch (opt) {
            case 0:
                break;
            case 1:{
                clearBuffer();
                clearScreen();
                for(auto i=Ze_Manel->getVectorServicesOnQueue()->begin();i!=Ze_Manel->getVectorServicesOnQueue()->end();i++)
                    cout<<*i;
                if(!Ze_Manel->getVectorServicesOnQueue()->size())
                    cout<<"There are no info to show"<<endl;
                getline(cin,temp);
                clearScreen();
                break;
            }
            case 2:{
                Client *a=nullptr;
                clearScreen();
                clearBuffer();
                a =new Client("Margarida Cruz",121212121);
                Service::addService(Ze_Manel->getVectorServicesOnQueue(),a);
                break;
            }

            case 3:{
                clearScreen();
                clearBuffer();
                for(auto i:*Ze_Manel->getVectorServicesOnQueue()){
                    cout<<i->getMaterial()<<", id: "<<i->getId()<<endl;
                }
                if(Ze_Manel->getVectorServicesOnQueue()->size()){
                    cout<<endl;
                    cout<<"Which Service you want to remove ( write service's id ):"<<endl;
                    unsigned id;
                    cin>>id;
                    Service::removeService(Ze_Manel->getVectorServicesOnQueue(),id);
                    clearScreen();
                }
                else
                    cout<<"There are no services that can be removed"<<endl;
                    string temp;
                    getline(cin,temp);
                    clearScreen();
                break;
            }
            case 4:{

            }

            default:
                opt=1;
            }
        else{
            clearBuffer();
            clearScreen();
            cout<<"Non valid option, please try again"<<endl;
        }
    }
    delete Ze_Manel;


    return 0;
}

// ----------------------- //

// Options for Client Management in the User Interface

//Prints the menu and asks the user what option to choose
void runClientsMenu(vector<Client>& clientsVector) {
	int option;

	cout << "Welcome to the Clients Menu! Please choose what you want to do: ";
	cout << endl << endl;
	cout << "0. Go back" << endl;
	cout << "1. Create a new client." << endl;
	cout << "2. Change a client information." << endl;
	cout << "3. Remove a client" << endl;
	cout << "4. See information from all clients. " << endl;
	cout << "5. See information from a specific client. " << endl;
	cout << "6. See all packs bought by a specific client. " << endl;
	cout << "7. See all packs bought by all clients. " << endl;
	cout << "8. Buy a touristic pack for a client" << endl << endl;
	cout << "Insert the number correspondent to your option: ";
	cin >> option;

	while (cin.fail() || option < 0 || option > 8)
	{
		cout << "Invalid option, please insert the option again: ";
		cin.clear();
		cin.ignore(10000, '\n');
		cin >> option;
	}

	cin.clear();
	cin.ignore(10000, '\n');

	if (option == 0) { /*Correr Menu inicial*/ }
	if (option == 1) { createClientOption(clientsVector); }
	if (option == 2) { modifyClientOption(clientsVector); }
	if (option == 3) { removeClientOption(clientsVector); }
	if (option == 4) { showAllClients(clientsVector); }
	if (option == 5) { showClientOption(clientsVector); }
	if (option == 6) { showPacksClient(clientsVector, travelPacksVector); }
	if (option == 7) { showPacksAllClient(clientsVector, travelPacksVector); }
	if (option == 8) { buyTravelPack(clientsVector, travelPacksVector); }

	// Correr menu inicial de novo (quando acaba a operacao escolhida)
}

//Asks for client information and returns a client
Client askForClientsInformation(vector<Client> clientsVector) {
	Client client;
	string name;
	int zeroIfNotInFile = 0;
	int nif;
	int familyNumber;
	bool inDatabase = false;
	string addressText;
	vector<int> touristicPacksBought;
	touristicPacksBought.push_back(0);

	cout << "Name: ";
	getline(cin, name);

	cout << "NIF: ";
	cin >> nif;
	validNif(nif);
	cin.clear();
	cin.ignore(10000, '\n');

	for (int i = 0; i < clientsVector.size(); i++) {
		if (clientsVector[i].getnif() == nif) {
			inDatabase = true;
			break;
		}
	}

	while (inDatabase)
	{
		cout << "NIF is already in the database, please insert again: ";
		cin >> nif;
		validNif(nif);
		cin.clear();
		cin.ignore(10000, '\n');
		for (int i = 0; i < clientsVector.size(); i++)
		{
			zeroIfNotInFile = 0;
			if (clientsVector[i].getnif() == nif) {
				zeroIfNotInFile += 1;
				break;
			}
		}
		if (zeroIfNotInFile == 0)
			inDatabase = false;
	}



	cout << "Number of people in the family: ";
	cin >> familyNumber;
	validCin(familyNumber);
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Address (Street / Door Number / Floor Number / Postal Code / Locality): ";
	getline(cin, addressText);

	while (!Address::validAddressText(addressText) || addressText == "////")
	{
		cout << "Invalid address, please insert again: ";
		getline(cin, addressText);
	}


	client.setName(name);
	client.setNif(nif);
	client.setFamilySize(familyNumber);
	client.setAddress(Address::addressTextConverter(addressText));
	client.setTravelPackIds(touristicPacksBought);
	return client;
}


//Asks the user for data and adds a new client to clientsvector
void createClientOption(vector<Client>& clientsVector) {
	Client client;
	cout << "Please insert the data of your new client" << endl << endl;
	client = askForClientsInformation(clientsVector);
	client.addClient(clientsVector);
	cout << endl << endl << "Client created successfully!";
	menuSeparator();
}