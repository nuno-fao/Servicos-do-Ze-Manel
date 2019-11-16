#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "client.h"
#include "truck.h"
#include "company.h"
#include "service.h"


#define min(a,b) (((a) < (b)) ? (a) : (b))
using namespace std;

class Client;
class Truck;
class Company;
class Service;
class Address;
/**
*
* Clears the console, works both in windows and linux
*
*/
void clearScreen();
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

unsigned chooseOptionNumber(unsigned minimum, unsigned maximum, string Message, unsigned maxPerPage=0,vector<string> *more_options=nullptr);

void checkIfOut(string &temp);

int binaryCustomfind(vector<Client*> *vetor, unsigned val);

void printClassVector(vector<string> *t);

/**
*
*
* Prompts the user to input a newline so that he has time to read whatever is on the screen
*
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

long askForId(string classToAsk, string what_to_do, string identifier);

template<class T> bool cmp_classes(T *a,T *b);

bool cmpOnQueue(Service *a,Service *b);

bool cmpOnTransit(Service *a,Service *b);
