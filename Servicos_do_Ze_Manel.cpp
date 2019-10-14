// Serviços do Zé Manel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;


/*
This function receives a name and returns true if it is valid
*/

bool verifyName(const string &name) {
	bool valid = true;

	for (unsigned int i = 0; i < name.size(); i++){	
		if (!(stoi(name[i]).isdigit())) {
			valid = false;
			break;
		}
	}

	return valid;
}


int main()
{
    std::cout << "Hello World!\n";

	return 0;
}
