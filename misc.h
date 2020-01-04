#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <queue>

#include "client.h"
#include "truck.h"
#include "date.h"
#include "company.h"
#include "service.h"
#include "date.h"

#define min2(a, b) ((a) < (b) ? (a) : (b))
using namespace std;

enum class car_brand;

class Client;
class Truck;
class Company;
class Service;
class Address;
class Date;
/**
*
* Clears the console, works both in windows and linux
*
*/
void clearScreen();
/**
*
* Deletes all outputs
*
*/
void clearScreen_2_0();
/**
*
* Split the string into a vector on every substring thats equal to the separator param
*
* @param separator - where to split the string
* @param stringToVectorize - string to split
* @return Returns the resulting vector
*/
vector<string> vectorString(string stringToVectorize, string separator);
/**
*
* Cleans input buffer, needed so we can use both the operator >> and getline func
*
*/
void clearBuffer(void);
/**
*
* Checks if a string contains only digit characters
*
* @param str - string to process
* @return Returns true or false if the string only contains digit characters
*/
bool strIsNumber(string str);
/**
* 
* @brief Checks if string only contains alphabetic characters
*
* It can cont the characters like '.' and  ' ' but must have at least 1 alphabetic character
*
* @param str - string to process
* @return Returns true or false
*/
bool strIsChar(string str);

/**
*
* @brief Checks if user wants to leave
*
* Checks if user input is !q and verifies if user wants to leave
* Throws an exception if the input thereafter is 'y' or '\n'
*
* @param temp - string to process
* @return Returns nothing
*/
void checkIfOut(string &temp);

/**
*
* @brief Binary search
*
* Searches for a Client by using the binary search algorithm
*
* @param vetor - pointer to a vector containing pointers to Clients
* @param val - identification code to search for the Client
* @return Returns the index of the Client or -1 if not found
*/
int binaryCustomfind(vector<Client*> *vetor, unsigned val);
/**
*
* @brief Prints Service
*
* Prints the Service as its information gets added
*
* @param t - pointer to the vector of strings to be printed
* @return Returns nothing
*/
void printClassVector(vector<string> *t);

/**
*
*
* Prompts the user to input a newline so that he has time to read whatever is on the screen
*
* @return Returns nothing
*/
void enter_to_exit();

/**
*
* Checks if a given integer is a valid nif number
*
* @param int - integer to process
* @return Returns true or false
*/
bool checkNif(int nif);

/**
*
* Checks if a string is a valid license and if it already exists or not
*
*
* @param license - license to verify
* @param trucks - vector that holds existing trucks
* @return Returns true or false
*/
bool checkLicense(string license, vector<Truck*>* trucks);
/**
*
* Checks if a string is a valid license but not if it already exists or not
*
*
* @param license - license to verify
* @return Returns true or false
*/
bool checkLicenseV2(string license);
/**
*
* Checks if the name given is valid and if Workshop with that name already exists
*
*
* @param name - name to verify
* @return Returns true if name given is valid and doesn't exist yet
*/
bool checkWorkshopName(string name);

/**
*
* @brief Asks for the ID
* Prompts the user for the ID by giving exact instructions
* This function is versatile and is used to get different kinds of info from the user
*
* @param classToAsk - Type of information to be asked for
* @param what_to_do - Input instructions
* @param identifier - Idemtifier of the information to be retrieved
* @return Returns the ID as a long int
*/
long askForId(string classToAsk, string what_to_do, string identifier);

/**
*
* @brief Operator<-overload-type of function
* Returns true if a < b, using the template Class' operator< overload function
*
* @param a - A template Class Object
* @param b - A template Class Object
* @return Returns true if a < b
*/
template<class T> bool cmp_classes(T *a,T *b){
    return *a<*b;
}

/**
*
* @brief Operator<-overload-type of function
* Returns true if a's IDate < b's IDate
*
* @param a - A pointer to a Service
* @param b - A pointer to a Service
* @return Returns true if a's IDate < b's IDate
*/
bool cmpOnQueue(Service *a,Service *b);

/**
*
* @brief Operator<-overload-type of function
* Returns true if b's IDate < a's IDate
*
* @param a - A pointer to a Service
* @param b - A pointer to a Service
* @return Returns true if b's IDate < a's IDate
*/
bool cmpOnTransit(Service *a,Service *b);

/**
*
* @brief checks if it has passed a year since the date given has an argument
* Returns true if has, false otherwise
*
* @param date - the date to analyse
* @return Returns true if it has passed a year since the date given has an argument, false otherwise
*/
bool overAYear(Date date);
/**
*
* @brief Verifies if given string is a valid brand
*
* @param temp_brand - string containing brand to verify
* @return Returns true if string can represent a brand, false otherwise
*/
bool verifyBrand(string temp_brand);
/**
*
* @brief Transforms string into a car brand
*
* @param temp_brand - brand as a string to be converted
* @return Returns a car_brand type corresponding to the string passed
*/
car_brand selectBrand(string temp_brand);
/**
*
* @brief Transforms car brand type into a string
*
* @param brand - car brand type to be transformed
* @return Returns a string representing a car brand
*/
string printBrand(car_brand brand);
/**
*
* @brief Searches the latest date
* Retrieves the latest date in the given queue
*
* @param queue_to_check - pointer to a queue of pairs of pointers to Trucks and pointers to Dates to be checked
* @return Returns the pointer to the latest date as a Date objects
*/
Date findMaxDate(queue<pair<Truck*, Date*>> queue_to_check);
