#include "driver.h"
Driver::Driver(int nif,string name,float serviceHours)
    :nif(nif),
      name(name),
      service_hours(serviceHours)
{

}
int Driver::getNif() const{
    return nif;
}
string Driver::getName() const{
    return name;
}
float Driver::getServiceHours() const{
    return service_hours;
}

void Driver::setNif(int nif){
    this->nif=nif;
}
void Driver::setName(string name){
    this->name=name;
}
void Driver::setServiceHours(float ServiceHours){
    this->service_hours=ServiceHours;
}

void Driver::loadFromFile(){

}

void Driver::saveToFile(){
    ofstream driverFile;
    driverFile.open("./files/drivers.txt");
    for(auto i:*(Company::getCompany()->getDrivers())){
        cout<<"okk"<<endl;
    }
}
