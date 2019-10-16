#pragma once
#include <string>
#include <vector>

#include "truck.h"
#include "date.h"
#include "client.h"

using namespace std;

class Service;
class Client;
class Truck;

enum type {
    ordinary=0,hazardous=1,animal=2,lowTemperature=3
};

enum state {
    on_queue,onTransit,finished
};

class Service
{
public:
    Service(string origin, string destination, double time, unsigned distance, type type, state state, Date date,Client *client);
    ~Service();

    //get methods
    string getOrigin() const;
    string getDestination() const;
    double getTime() const;
    unsigned getDistance() const;
    type getType() const;
    unsigned int getId() const;
    state getState();
    Date getDate();
    Client *getClient();
    vector<Truck*> *getTrucks();

    //set methods
    void setOrigin(string origin);
    void setDestination(string destination);
    void setTime(double time);
    void setDistance(unsigned distance);
    void setType(type type);
    void setState(state state);
    void setDate(Date date);
    void setClient(Client *client);

    void addTruck(Truck *truck);

    //file methods
    static void saveToFile(vector<Service*>*services);
    static void loadFromFile(vector<Service *> *services);

private:
    string origin;
    string destination;
    double time;
    unsigned distance;
    type ser_type;
    unsigned int id;
    vector<Truck*> trucks;
    //static unsigned int lastId;
    state ser_state;
    Date initialDate;
    Client *client;
    static unsigned int lastId;



};
