#include "service.h"

Service::Service(string origin, string destination, double time, unsigned distance, enum type type, enum state state, Date date, Client client)
    : origin(origin),destination(destination), time(time), distance(distance),type(type), state(state)
{
    id=lastId++;
    setDate(date);

}

string Service::getOrigin() const{
    return origin;
}
string Service::getDestination() const{
    return destination;
}
double Service::getTime() const{
    return time;
}
unsigned Service::getDistance() const{
    return distance;
}
type Service::getType() const{
    return type;
}
unsigned int Service::getId() const{
    return id;
}
state Service::getState(){
    return state;
}
Date Service::getDate(){
    return initialDate;
}

Client *Service::getClient(){
    return client;
}

//set methods
void Service::setOrigin(string origin){
    this->origin=origin;
}
void Service::setDestination(string destination){
    this->destination=destination;
}
void Service::setTime(double time){
    this->time=time;
}
void Service::setDistance(unsigned distance){
    this->distance=distance;
}
void Service::setType(enum type type){
    this->type=type;
}
void Service::setState(enum state state){
    this->state=state;
}
void Service::setDate(Date date){
    initialDate=Date(date);
}
void Service::setClient(Client *client){
    *client=Client(*client);
}

void Service::addTruck(Truck *truck){
    this->trucks.push_back(truck);
}
