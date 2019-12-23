#pragma once
#include <queue>
#include <string>
#include "date.h"
#include "truck.h"
#include "company.h"

class Truck;
class Date;

using namespace std;

enum class car_brand { Mercedes, Man, Ford, Volvo, Iveco, Scania, Volkswagen, Mitsubishi, None}; /// Enum representing the possibile Workshop's specialization

typedef queue<pair<Truck*, Date>> wait_queue;

// TODO: falta comentar as funcoes e fazer as funcoes de pesquisa com static



class Workshop {
private:
    string name; /// Workshop's name
    car_brand brand; /// Workshop's brand specialization
    unsigned int unavailability; /// Unavailability duration in days
    wait_queue waiting_line; /// Queue of pointers to Trucks assigned to the given Workshop (ordered by FIFO)
public:
    Workshop(string n, car_brand b, unsigned unavailability);
    Workshop(string n);
    
    string getName() const;
    car_brand getBrand() const;
    unsigned int getUnavailability() const;
    wait_queue getWaitingLine() const;
    
    void setName(string n);
    void setBrand(car_brand b);
    void setUnavailability(unsigned int ua);
    void setWaitingLine(wait_queue wl);


};