#pragma once
#include <string>
#include <fstream>

#include "company.h"
#include "bst.h"
using namespace std;

class Company;
class Driver
{
public:
    Driver(int nif,string name,float serviceHours);
    int getNif() const;
    string getName() const;
    float getServiceHours() const;

    void setNif(int nif);
    void setName(string name);
    void setServiceHours(float ServiceHours);

    static void loadFromFile();
    static void saveToFile();
private:
    int nif;
    string name;
    float service_hours;
};