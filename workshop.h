#pragma once
#include <queue>
#include <string>
#include "date.h"

using namespace std;



enum car_brand { Mercedes, Man, Ford, Volvo, Iveco, Scania, Volkswagen, Mitsubishi}; /// Enum representing the possibile Workshop's specialization

class Workshop {
private:
    string name; /// Workshop's name
    car_brand brand; /// Workshop's brand specialization
    unsigned unavailability; // Unavailability duration in days
    
public:
    Workshop(string n, car_brand b, unsigned unavailability);
};