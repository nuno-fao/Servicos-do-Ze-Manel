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
    Service(string origin, string destination, double time, unsigned distance, type type, state state, Date date,Client *client,float quantity);
    ~Service();

    //get methods
    string getOrigin() const;
    string getDestination() const;
    double getTime() const;
    unsigned getDistance() const;
    type getType() const;
    unsigned int getId() const;
    state getState() const;
    Date getDate() const;
    Client *getClient() const;
    vector<Truck*> *getTrucks();
    float getTotalPrice() const;
    float getQuantity() const;

    //set methods
    void setOrigin(string origin);
    void setDestination(string destination);
    void setTime(double time);
    void setDistance(unsigned distance);
    void setType(type type);
    void setState(state state);
    void setDate(Date date);
    void setClient(Client *client);
    void setQuantity(float quantity);

    void addTruck(Truck *truck);
    void calcPrice();

    //file methods
    static void saveToFile(vector<Service*>*services);
    static void loadFromFile(vector<Service *> *services);

private:
    string origin;
    string destination;
    double time;
    unsigned distance;
    float quantity;
    type ser_type;
    unsigned int id;
    vector<Truck*> trucks;
    //static unsigned int lastId;
    state ser_state;
    Date initialDate;
    Client *client;
    float total_price;
    static unsigned int lastId;



};
