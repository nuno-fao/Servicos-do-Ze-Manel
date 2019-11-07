#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

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

// Verifies a client's NIF
bool checkNif(int nif);

// Verifies if the name is valid (POTENCIALMENTE VOU CAGAR NISTO COMO ESTOU A RETIRAR O NOME COM GETLINE)
bool verifyName(const string& name)