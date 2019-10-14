#pragma once
#include <string>
#include <vector>

#include "truck.h"

using namespace std;

enum type {
    red, green, blue
};

enum state {
    on_queue,onTransit,finished
};

class Service
{
public:
    Service(string origin,string destination,double time,unsigned distance,type type, state state);
    ~Service();
    static unsigned int lastId;

    //get methods
    string getOrigin() const;
    string getDestination() const;
    double getTime() const;
    unsigned getDistance() const;
    type getType() const;
    unsigned int getId() const;
    state getState();

    //set methods
    void setOrigin(string origin);
    void setDestination(string destination);
    void setTime(double time);
    void setDistance(unsigned distance);
    void setType(type type);
    void setState(state state);

    void addTruck(Truck *truck);

private:
    string origin;
    string destination;
    double time;
    unsigned distance;
    type type;
    unsigned int id;
    vector<Truck*> trucks;
    //static unsigned int lastId;
    state state;

};

unsigned int Service::lastId=0;
