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

int binaryCustomfind(vector<Client*> *vetor, unsigned val);
