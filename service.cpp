#include "service.h"

service::service(string origin,string destination,double time,unsigned distance,enum type type, enum state state)
    : origin(origin),destination(destination), time(time), distance(distance),type(type), state(state)
{
    id=lastId++;
}

string service::getOrigin() const{
    return origin;
}
string service::getDestination() const{
    return destination;
}
double service::getTime() const{
    return time;
}
unsigned service::getDistance() const{
    return distance;
}
type service::getType() const{
    return type;
}
unsigned int service::getId() const{
    return id;
}
state service::getState(){
    return state;
}

//set methods
void service::setOrigin(string origin){
    this->origin=origin;
}
void service::setDestination(string destination){

}
void service::setTime(double time){

}
void service::setDistance(unsigned distance){

}
void service::setType(enum type type){

}
void service::setState(enum state state){

}

void service::addTruck(truck *truck){

}
#include "service.h"
