#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "client.h"

using namespace std;

class Client;

void clearScreen();
vector<string> vectorString(string stringToVectorize, string separator);
void clearBuffer(void);
bool strIsNumber(string str);
bool strIsChar(string str);
unsigned chooseOptionNumber(unsigned minimum, unsigned maximum, string Message, unsigned maxPerPage=0,vector<string> *more_options=nullptr);
void checkIfOut(string &temp);
int binaryCustomfind(vector<Client*> *vetor, unsigned val);
void printClassVector(vector<string> *t);

//so that the user can read the stuff before doing anything else
void enter_to_exit();

// Verifies a client's NIF
bool checkNif(int nif);

// Verifies a trucks license
bool checkLicense(string license, vector<Truck*>* trucks);