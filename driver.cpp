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
    ifstream driverFile;
    driverFile.open("./files/drivers.txt");
    string nif;
    string name;
    string serviceHours;
    int nif_tmp;
    float service_h;
    BST<Driver> *tmp_vect=Company::getCompany()->getDrivers();
    while(getline(driverFile,nif)){
        getline(driverFile,name);
        getline(driverFile,serviceHours);
        try {
            nif_tmp=stoi(nif);
            service_h=stof(serviceHours);
            Driver *tmp;
            tmp=new Driver(nif_tmp,name,service_h);
            tmp_vect->insert(*tmp);
        } catch (...) {
            continue;
        }
    }
}

void Driver::saveToFile(){
    ofstream driverFile;
    driverFile.open("./files/drivers.txt");
    BST<Driver> *tmp=Company::getCompany()->getDrivers();
    BSTItrLevel<Driver> i(*tmp);

    while(!i.isAtEnd()){
        driverFile<<i.retrieve().getNif()<<endl;
        driverFile<<i.retrieve().getName()<<endl;
        driverFile<<i.retrieve().getServiceHours()<<endl;
        i.advance();
        driverFile<<"::::::::::"<<endl;
    }
}


bool operator <( const Driver &a, const Driver &b){
    return a.getNif()<b.getNif();
}
