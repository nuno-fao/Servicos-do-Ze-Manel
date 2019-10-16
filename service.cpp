#include "service.h"
#include <fstream>


unsigned int Service::lastId=0;

Service::Service(string origin, string destination, double time, unsigned distance, enum type type, enum state state, Date date, Client *client)
    : origin(origin),destination(destination), time(time), distance(distance),ser_type(type), ser_state(state)
{
    id=lastId++;
    setDate(date);
    setClient(client);

}

Service::~Service(){

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
    return ser_type;
}
unsigned int Service::getId() const{
    return id;
}
state Service::getState(){
    return ser_state;
}
Date Service::getDate(){
    return initialDate;
}

Client *Service::getClient(){
    return client;
}

vector<Truck*> *Service::getTrucks(){
    return &trucks;
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
    this->ser_type=type;
}
void Service::setState(enum state state){
    this->ser_state=state;
}
void Service::setDate(Date date){
    initialDate=Date(date);
}
void Service::setClient(Client *client){
    this->client=client;
}

void Service::addTruck(Truck *truck){
    this->trucks.push_back(truck);
}

void Service::saveToFile(vector<Service*>*services){
    ofstream servicesFile;
    servicesFile.open ("services.txt");
    for(auto x:*services){
         servicesFile << x->getOrigin()<<endl;
         servicesFile << x->getDestination()<<endl;
         servicesFile << to_string(x->getTime())<<endl;
         servicesFile << to_string(x->getDistance())<<endl;
         servicesFile << to_string(x->getType())<<endl;
         servicesFile << to_string(x->getId())<<endl;
         for(auto i: *x->getTrucks()){
             //servicesFile << i->getId() <<";";
         }
         servicesFile << endl << to_string(x->getState())<<endl;
         servicesFile << x->getDate().getDate() <<endl;
         servicesFile << x->getClient()->getNif() << endl;
         servicesFile << ":::::::::::"<<endl;
    }
}
