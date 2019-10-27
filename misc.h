#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

void clearScreen();
vector<string> vectorString(string stringToVectorize, string separator);
void clearBuffer(void);
bool strIsNumber(string str);
bool strIsChar(string str);
unsigned chooseOptionNumber(unsigned minimum, unsigned maximum, string Message, unsigned maxPerPage=0);
