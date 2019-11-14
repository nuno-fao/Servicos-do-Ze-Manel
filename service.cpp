#include "service.h"

using namespace std;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SERVICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

set<unsigned> Service::idList={};
//constructors
Service::Service(string material, Address origin, Address destination, Date *arrivalDate, unsigned distance, enum type type, enum state state, Date *date, Client *client, float quantity)
    : material(material), distance(distance), quantity(quantity), ser_type(type), ser_state(state)
{
    
    for(unsigned x=0;;x++){
        if(idList.find(x)==idList.end()){
            this->id=x;
            break;
        }
    }
    setIDate(date);
    setADate(arrivalDate);
    setOrigin(Address(origin));
    setDestination(Address(destination));
    setClient(client);
    
}

Service::Service(string material, string origin, string destination, Date *arrivalDate, unsigned distance, enum type type, enum state state, Date *date, Client *client, float quantity, float total_price, unsigned id)
    : material(material), distance(distance), quantity(quantity),  ser_type(type),id(id), ser_state(state),total_price(total_price)
{

    idList.insert(id);
    this->id=id;
    setIDate(date);
    setADate(arrivalDate);
    setOrigin(Address(origin));
    setDestination(Address(destination));
    setClient(client);

}
//destructor
Service::~Service(){
    initialDate->~Date();
    arrivalDate->~Date();
    origin->~Address();
    destination->~Address();

}

//get methods
Address Service::getOrigin() const{
    return *origin;
}
Address Service::getDestination() const{
    return *destination;
}
Date *Service::getADate() const{
    return arrivalDate;
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
state Service::getState() const{
    return ser_state;
}
Date *Service::getIDate() const{
    return initialDate;
}
Client *Service::getClient() const{
    return client;
}
map<Truck*,float> *Service::getTrucks(){
    return &trucks;
}
float Service::getTotalPrice() const{
    return total_price;
}
float Service::getQuantity() const{
    return quantity;
}
string Service::getMaterial() const{
    return material;
}

//set methods
void Service::setOrigin(Address origin){
    Address *x=new Address(origin);
    this->origin=x;
}
void Service::setDestination(Address destination){
    Address *x=new Address(destination);
    this->destination=x;
}
void Service::setADate(Date *date){
    arrivalDate=date;
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
void Service::setIDate(Date *date){
    initialDate=date;
}
void Service::setClient(Client *client){
    this->client=client;
}
void Service::setMaterial(string material){
    this->material=material;
}
void Service::setQuantity(float quantity){
    this->quantity=quantity;
}

// other methods
void Service::addTruck(Truck *truck,float cargo){
    this->trucks[truck]=cargo;
}

//help methods
type intToType(int a){
    switch (a) {
    case 0: return type::ordinary;
    case 1: return type::hazardous;
    case 2: return type::animal;
    case 3: return type::lowTemperature;
    default: return type::ordinary;
    }
}
state intToState(int a){
    switch (a) {
    case 0: return on_queue;
    case 1: return on_transit;
    case 2: return finished;
    default: return finished;
    }
}

string typeToString(type a){
    switch (a) {
    case type::ordinary:
        return "ordinary";
    case type::hazardous:
        return "hazardous";
    case type::animal:
        return "animal";
    case type::lowTemperature:
        return "Low Temperature";
    }
    return "ordinary";
}
string stateToString(state a){
    return  to_string(a);
}
// atualizar!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Client *findClient(int nif){
    int index=binaryCustomfind(Company::getCompany()->getVectorClients(),unsigned(nif));
    if(index<0)
        throw NotAClient(unsigned(nif),"Couldn't find the Client");
    else
        return Company::getCompany()->getVectorClients()->at(size_t(index));
}

//adicionar hazardous type ou temp range!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// check if nif size==9!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void Service::loadFromFile(list<Service*> *services_finished,vector<Service*> *services_on_transit,vector<Service*> *services_on_queue){
    ifstream servicesFile;
    servicesFile.open("./files/on_transit_services.txt");
    if(!servicesFile.is_open()){throw ServiceOnTransitFileError();}
    servicesFile.close();

    servicesFile.open("./files/finished_services.txt");
    if(!servicesFile.is_open()){throw ServiceFinishedFileError();}
    servicesFile.close();


    servicesFile.open("./files/on_queue_services.txt");
    if(!servicesFile.is_open()){throw ServiceOnQueueFileError();}

    string tempOrigin;
    string tempDestination;
    string tempADate;
    double tempDistance;
    string tempMaterial;
    type tempType;
    string temptrucks;
    state tempState;
    string tempIDate;
    string tempNif;
    string tempGeneral;
    float tempQuantity;
    float tempPrice;
    unsigned tempId = 0;
    vector<string> tempVectorTruckS;

    while(getline(servicesFile,tempMaterial)){

        getline(servicesFile,tempGeneral);
        tempId=unsigned(stoi(tempGeneral));
        getline(servicesFile,tempOrigin);
        getline(servicesFile,tempDestination);
        
        getline(servicesFile,tempADate);
        
        getline(servicesFile,tempGeneral);
        tempDistance=stoi(tempGeneral);

        //
        getline(servicesFile,tempGeneral);
        tempType=intToType(stoi(tempGeneral));

        getline(servicesFile,temptrucks);
        tempVectorTruckS=vectorString(temptrucks,";");
        
        getline(servicesFile,tempGeneral);
        tempState=intToState(stoi(tempGeneral));
        
        getline(servicesFile,tempIDate);
        
        getline(servicesFile,tempNif);

        getline(servicesFile,tempGeneral);
        tempQuantity=(stof(tempGeneral));

        getline(servicesFile,tempGeneral);
        tempPrice=(stof(tempGeneral));
        Service *temp;
        Date *tempI=new Date(tempIDate);
        Date *tempA=new Date(tempADate);
        try {
            if(tempNif.size()!=9)
                throw NotAClient(unsigned(stoi(tempNif)),"Not a valid NIF");
            Client *temp_client=Company::getCompany()->getClient(unsigned(stoi(tempNif)));

            if(tempType==type::lowTemperature)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,temp_client,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==type::hazardous)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,temp_client,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,temp_client,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_truck=Company::getCompany()->getTruck(tempTruckMap.at(0));
                    temp->addTruck(temp_truck,stof(tempTruckMap.at(1)));
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
                }
                catch(...)
                {
                    cout<<"Someone Messed with the files..."<<endl;
                }
            }

            switch (tempState) {
            case on_transit:
                services_on_transit->push_back(temp);
                break;
            case on_queue:
                services_on_queue->push_back(temp);
                break;
            case finished:
                services_finished->push_back(temp);
                break;
            }
            temp_client->addService(temp);

        } catch (NotAClient &e) {
            cout<<e.erro+to_string(e.getNif())<<endl;
            string temp_error;
            Client *tempC= new NotAClient(e);
            //getline(cin,temp_error);
            if(tempType==type::lowTemperature)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,tempC,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==type::hazardous)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,tempC,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,tempC,tempQuantity,tempPrice,tempId);


            for(auto i:tempVectorTruckS){
                try{
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_truck=Company::getCompany()->getTruck(tempTruckMap.at(0));
                    temp->addTruck(temp_truck,stof(tempTruckMap.at(1)));
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
                }
                catch(...)
                {
                    cout<<"Someone Messed with the files..."<<endl;
                }
            }



            switch (tempState) {
            case on_transit:
                services_on_transit->push_back(temp);
                break;
            case on_queue:
                services_on_queue->push_back(temp);
                break;
            case finished:
                services_finished->push_back(temp);
                break;
            }
        }
        catch(...){
            cout<<"Not a valid Nif "+tempNif<<endl;
        }
        getline(servicesFile,tempGeneral);
    }

    servicesFile.close();
    servicesFile.open("./files/on_transit_services.txt");
    while(getline(servicesFile,tempMaterial)){

        getline(servicesFile,tempGeneral);
        tempId=unsigned(stoi(tempGeneral));
        getline(servicesFile,tempOrigin);
        getline(servicesFile,tempDestination);

        getline(servicesFile,tempADate);

        getline(servicesFile,tempGeneral);
        tempDistance=stoi(tempGeneral);

        getline(servicesFile,tempGeneral);
        tempType=intToType(stoi(tempGeneral));

        getline(servicesFile,tempGeneral);
        tempState=intToState(stoi(tempGeneral));

        getline(servicesFile,temptrucks);
        tempVectorTruckS=vectorString(temptrucks,";");

        getline(servicesFile,tempIDate);

        getline(servicesFile,tempNif);

        getline(servicesFile,tempGeneral);
        tempQuantity=(stof(tempGeneral));

        getline(servicesFile,tempGeneral);
        tempPrice=(stof(tempGeneral));
        Service *temp;
        Date *tempD=new Date(tempIDate);
        Date *tempA=new Date(tempADate);
        try {
            if(tempNif.size()!=9)
                throw NotAClient(unsigned(stoi(tempNif)),"Not a valid NIF");
            Client *temp_client=Company::getCompany()->getClient(unsigned(stoi(tempNif)));
            if(tempType==type::lowTemperature)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==type::hazardous)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_truck=Company::getCompany()->getTruck(tempTruckMap.at(0));
                    temp->addTruck(temp_truck,stof(tempTruckMap.at(1)));
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
                }
                catch(...)
                {
                    cout<<"Someone Messed with the files..."<<endl;
                }
            }

            switch (tempState) {
            case on_transit:
                services_on_transit->push_back(temp);
                break;
            case on_queue:
                services_on_queue->push_back(temp);
                break;
            case finished:
                services_finished->push_back(temp);
                break;
            }

            temp_client->addService(temp);

        } catch (NotAClient &e) {
            cout<<e.erro+to_string(e.getNif())<<endl;
            string temp_error;
            Client *tempC= new NotAClient(e);
            //getline(cin,temp_error);
            if(tempType==type::lowTemperature)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==type::hazardous)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_truck=Company::getCompany()->getTruck(tempTruckMap.at(0));
                    temp->addTruck(temp_truck,stof(tempTruckMap.at(1)));
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
                }
                catch(...)
                {
                    cout<<"Someone Messed with the files..."<<endl;
                }
            }

            switch (tempState) {
            case on_transit:
                services_on_transit->push_back(temp);
                break;
            case on_queue:
                services_on_queue->push_back(temp);
                break;
            case finished:
                services_finished->push_back(temp);
                break;
            }
        }
        catch(...){
            cout<<"Not a valid Nif "+tempNif<<endl;
        }
        getline(servicesFile,tempGeneral);
    }

    servicesFile.close();
    servicesFile.open("./files/finished_services.txt");
    while(getline(servicesFile,tempMaterial)){

        getline(servicesFile,tempGeneral);
        tempId=unsigned(stoi(tempGeneral));
        getline(servicesFile,tempOrigin);
        getline(servicesFile,tempDestination);

        getline(servicesFile,tempADate);

        getline(servicesFile,tempGeneral);
        tempDistance=stoi(tempGeneral);

        getline(servicesFile,tempGeneral);
        tempType=intToType(stoi(tempGeneral));

        getline(servicesFile,tempGeneral);
        tempState=intToState(stoi(tempGeneral));

        getline(servicesFile,tempIDate);

        getline(servicesFile,tempNif);

        getline(servicesFile,tempGeneral);
        tempQuantity=(stof(tempGeneral));

        getline(servicesFile,tempGeneral);
        tempPrice=(stof(tempGeneral));
        Service *temp;
        Date *tempD=new Date(tempIDate);
        Date *tempA=new Date(tempADate);
        try {
            if(tempNif.size()!=9)
                throw NotAClient(unsigned(stoi(tempNif)),"Not a valid NIF");
            Client *temp_client=Company::getCompany()->getClient(unsigned(stoi(tempNif)));
            if(tempType==type::lowTemperature)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==type::hazardous)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_truck=Company::getCompany()->getTruck(tempTruckMap.at(0));
                    temp->addTruck(temp_truck,stof(tempTruckMap.at(1)));
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_t=new Truck(tempTruckMap.at(0),0,0,0,0);
                    temp->addTruck(temp_t,stof(tempTruckMap.at(1)));
                }
                catch(...)
                {
                    cout<<"Someone Messed with the files..."<<endl;
                }
            }

            switch (tempState) {
            case on_transit:
                services_on_transit->push_back(temp);
                temp_client->addService(temp);
                break;
            case on_queue:
                services_on_queue->push_back(temp);
                temp_client->addService(temp);
                break;
            case finished:
                services_finished->push_back(temp);
                break;
            }

        } catch (NotAClient &e) {
            cout<<e.erro<<" "<<to_string(e.getNif())<<endl;
            string temp_error;
            Client *tempC= new NotAClient(e);
            //getline(cin,temp_error);
            if(tempType==type::lowTemperature)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==type::hazardous)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,tempPrice,tempId);


            for(auto i:tempVectorTruckS){
                try{
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_truck=Company::getCompany()->getTruck(tempTruckMap.at(0));
                    temp->addTruck(temp_truck,stof(tempTruckMap.at(1)));
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    vector<string> tempTruckMap=vectorString(i,":");
                    Truck *temp_t=new Truck(tempTruckMap.at(0),0,0,0,0);
                    temp->addTruck(temp_t,stof(tempTruckMap.at(1)));
                }
                catch(...)
                {
                    cout<<"Someone Messed with the files..."<<endl;
                }
            }

            switch (tempState) {
            case on_transit:
                services_on_transit->push_back(temp);
                break;
            case on_queue:
                services_on_queue->push_back(temp);
                break;
            case finished:
                services_finished->push_back(temp);
                break;
            }
        }
        catch(...){
            cout<<"Not a valid Nif "+tempNif<<endl;
        }

        getline(servicesFile,tempGeneral);
    }
    servicesFile.close();
}
void Service::saveToFile(list<Service*> *services_finished,vector<Service*>*services_on_transit,vector<Service*>*services_on_queue){
    ofstream servicesFile;
    servicesFile.open("./files/finished_services.txt");
    for(auto x:*services_finished){
        servicesFile << x->getMaterial()<<endl;
        servicesFile << x->getId()<<endl;
        servicesFile << x->getOrigin().getFullAdress()<<endl;
        servicesFile << x->getDestination().getFullAdress()<<endl;
        servicesFile << (x->getADate()->getDate())<<endl;
        servicesFile << (x->getDistance())<<endl;
        switch (x->getType()) {
        case type::lowTemperature:{
            servicesFile<<3<<endl;
            break;
        }
        case type::ordinary:{
            servicesFile<<0<<endl;
            break;
        }
        case type::hazardous:{
            servicesFile<<1<<endl;
            break;
        }
        case type::animal:{
            servicesFile<<2<<endl;
            break;
        }
        }

        for(auto i: *x->getTrucks()){
            try{
                servicesFile << i.first->getlicense() <<":";
            }
            catch(...){
                servicesFile << "" <<":";
            }
            servicesFile << i.second <<";";
        }

        servicesFile << (x->getState())<<endl;
        servicesFile << x->getIDate()->getDate() <<endl;
        servicesFile << x->getClient()->getNif() << endl;
        servicesFile << x->getQuantity() <<endl;
        servicesFile << x->getTotalPrice() <<endl;
        servicesFile << ":::::::::::"<<endl;
    }
    servicesFile.close();
    servicesFile.open("./files/on_queue_services.txt");
    for(auto x:*services_on_queue){
        servicesFile << x->getMaterial()<<endl;
        servicesFile << x->getId()<<endl;
        servicesFile << x->getOrigin().getFullAdress() <<endl;
        servicesFile << x->getDestination().getFullAdress() <<endl;
        servicesFile << (x->getADate()->getDate())<<endl;
        servicesFile << (x->getDistance())<<endl;
        switch (x->getType()) {
        case type::lowTemperature:{
			servicesFile <<3<<endl;
            break;
        }
        case type::ordinary:{
			servicesFile <<0<<endl;
            break;
        }
        case type::hazardous:{
			servicesFile <<1<<endl;
            break;
        }
        case type::animal:{
			servicesFile <<2<<endl;
            break;
        }
        }

        for(auto i: *x->getTrucks()){
            try{
                servicesFile << i.first->getlicense() <<":";
            }
            catch(...){
                servicesFile << "" <<":";
            }
            servicesFile << i.second <<";";
        }

        servicesFile << endl << (x->getState())<<endl;
        servicesFile << x->getIDate()->getDate() <<endl;
        servicesFile << x->getClient()->getNif() << endl;
        servicesFile << x->getQuantity() <<endl;
        servicesFile << x->getTotalPrice() <<endl;
        servicesFile << ":::::::::::"<<endl;
    }
    servicesFile.close();
    servicesFile.open("./files/on_transit_services.txt");
    for(auto x:*services_on_transit){
        servicesFile << x->getMaterial()<<endl;
        servicesFile << x->getId()<<endl;
        servicesFile << x->getOrigin().getFullAdress() <<endl;
        servicesFile << x->getDestination().getFullAdress() <<endl;
        servicesFile << (x->getADate()->getDate())<<endl;
        servicesFile << (x->getDistance())<<endl;
        switch (x->getType()) {
        case type::lowTemperature:{
			servicesFile <<3<<endl;
            break;
        }
        case type::ordinary:{
			servicesFile <<0<<endl;
            break;
        }
        case type::hazardous:{
			servicesFile <<1<<endl;
            break;
        }
        case type::animal:{
			servicesFile <<2<<endl;
            break;
        }
        }

        for(auto i: *x->getTrucks()){
            try{
                servicesFile << i.first->getlicense() <<":";
            }
            catch(...){
                servicesFile << "" <<":";
            }
            servicesFile << i.second <<";";
        }

        servicesFile << endl << (x->getState())<<endl;
        servicesFile << x->getIDate()->getDate() <<endl;
        servicesFile << x->getClient()->getNif() << endl;
        servicesFile << x->getQuantity() <<endl;
        servicesFile << x->getTotalPrice() <<endl;
        servicesFile << ":::::::::::"<<endl;
    }
}

//adicionar hazardous type ou temp range!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Service *Service::addService(vector<Service *> *services,Client *client){
    string tempOrigin,tempDestination,tempMaterial;
    string tempType,tempSpecType,month,day,hour,minute;
    Temperature_enum temp_temperature=Temperature_enum::_100;
    Hazard_enum temp_hazard=Hazard_enum::other;
    string temp_quantity;
    string year;
    vector<string> print;
    string tempTime,tempDistance;
    bool variable_error=true;
    time_t rawtime;struct tm *now;std::time( &rawtime );now = localtime( &rawtime );
    Address origin,destination;

    //set material
    while (variable_error) {
        cout<<"What is the material to transport"<<endl;
        getline(cin,tempMaterial);
        checkIfOut(tempMaterial);
        if(tempMaterial.size())
            variable_error=false;
        else{
            clearScreen();
            cout<<"Material name not acceptable, please try again."<<endl;
        }
    }
    print.push_back("What: "+tempMaterial);

    // set origin
    variable_error=true;
    clearScreen();
    while (variable_error) {
        printClassVector(&print);
        cout<<"Enter the Origin (street / doorNumber / location) or (location)"<<endl;

        getline(cin,tempOrigin);
        vector<string> temp_address_no_pc=vectorString(tempOrigin,"/");
        checkIfOut(tempOrigin);
        if(temp_address_no_pc.size()==3){
            clearScreen();
            if(strIsChar(temp_address_no_pc.at(2)) && strIsNumber(temp_address_no_pc.at(1))){
                variable_error=false;
                cout<<"Enter the Origin postal code (xxxx-yyy)"<<endl;
                while(true){
                    string postal_code;
                    getline(cin,postal_code);
                    checkIfOut(postal_code);
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(postal_code==""){
                        origin=Address(temp_address_no_pc.at(0),date_u_short(stoi(temp_address_no_pc.at(1))),"0000-000",temp_address_no_pc.at(2));
                        variable_error=false;
                        break;
                    }
                    else if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                        origin=Address(temp_address_no_pc.at(0),date_u_short(stoi(temp_address_no_pc.at(1))),postal_code,temp_address_no_pc.at(2));
                        variable_error=false;
                        break;
                    }
                    else{
                        clearScreen();
                        cout<<"Postal code not acceptable\nEnter the Origin postal code (xxxx-yyy)"<<endl;
                    }

                }

            }
        }
        else if(temp_address_no_pc.size()==1 && strIsChar(temp_address_no_pc.at(0))){
            clearScreen();
            if(strIsChar(temp_address_no_pc.at(0))){
                cout<<"Enter the Origin postal code (xxxx-yyy)"<<endl;
                while(true){
                    string postal_code;
                    getline(cin,postal_code);
                    checkIfOut(postal_code);
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(postal_code==""){
                        origin=Address("",0,"0000-000",temp_address_no_pc.at(0));
                        variable_error=false;
                        break;
                    }
                    else if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                        origin=Address("",0,postal_code,temp_address_no_pc.at(0));
                        variable_error=false;
                        break;
                    }
                    else{
                        clearScreen();
                        cout<<"Postal code not acceptable\nEnter the Origin postal code (xxxx-yyy)"<<endl;
                    }

                }

            }

        }

        else{
            variable_error=true;
            cout<<"Origin Input not acceptable, please try again"<<endl;
        }

    }
    clearScreen();
    print.push_back("Origin: "+tempOrigin);

    //set destination
    variable_error=true;
    while (variable_error) {
        printClassVector(&print);
        cout<<"Enter the Destination (street / doorNumber / location) or (location)"<<endl;
        getline(cin,tempDestination);
        vector<string> temp_address_no_pc=vectorString(tempDestination,"/");
        checkIfOut(tempDestination);
        if(temp_address_no_pc.size()==3){
            clearScreen();
            if(strIsChar(temp_address_no_pc.at(2)) && strIsNumber(temp_address_no_pc.at(1))){
                cout<<"Enter the Destination postal code (xxxx-yyy)"<<endl;
                while(true){
                    string postal_code;
                    getline(cin,postal_code);
                    checkIfOut(postal_code);
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(postal_code==""){
                        destination=Address(temp_address_no_pc.at(0),date_u_short(stoi(temp_address_no_pc.at(1))),"0000-000",temp_address_no_pc.at(2));
                        variable_error=false;
                        break;
                    }
                    else if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                        destination=Address(temp_address_no_pc.at(0),date_u_short(stoi(temp_address_no_pc.at(1))),postal_code,temp_address_no_pc.at(2));
                        variable_error=false;
                        break;
                    }
                    else{
                        clearScreen();
                        cout<<"Postal code not acceptable\nEnter the Destination postal code (xxxx-yyy)"<<endl;
                    }

                }

            }
        }
        else if(temp_address_no_pc.size()==1 && strIsChar(temp_address_no_pc.at(0))){
            clearScreen();
            if(strIsChar(temp_address_no_pc.at(0))){
                cout<<"Enter the Destination postal code (xxxx-yyy)"<<endl;
                while(true){
                    string postal_code;
                    getline(cin,postal_code);
                    checkIfOut(postal_code);
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(postal_code==""){
                        destination=Address("",0,"0000-000",temp_address_no_pc.at(0));
                        variable_error=false;
                        break;
                    }
                    else if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                        destination=Address("",0,postal_code,temp_address_no_pc.at(0));

                        variable_error=false;
                        break;
                    }
                    else{
                        clearScreen();
                        cout<<"Postal code not acceptable\nEnter the Destination postal code (xxxx-yyy)"<<endl;
                    }

                }

            }

        }
        else{
            variable_error=true;
            cout<<"Destination Input not acceptable, please try again"<<endl;
        }
    }
    print.push_back("Destination: "+tempDestination);

    //set initial date
    clearScreen();
    variable_error=true;
    string tempString;
    vector<string> tempVector;
    while (variable_error) {
        printClassVector(&print);
        try {
            cout<<"Enter the departure date(yy mm dd)"<<endl;
            if(getline(cin,tempString)){
                clearScreen();
                checkIfOut(tempString);
                tempVector = vectorString(tempString," ");
                for(auto p:tempVector){
                    if(!strIsNumber(p)){
                        tempVector.clear();
                        variable_error=true;
                        clearScreen();
                        cout<<"Date Input not Aceptable, please try again"<<endl;
                        break;
                    }
                }
                if(tempVector.size()==3){
                    Date i(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),23,59);
                    int t=now->tm_year;
                    Date f(unsigned(t-100),1+date_u_short(now->tm_mon),date_u_short(now->tm_mday),date_u_short(now->tm_hour),date_u_short(now->tm_min));
                    if(i<f){
                        variable_error=true;
                        clearScreen();
                        cout<<"Date Input not Aceptable, should not be prior to current date, please try again"<<endl;
                    }
                    else
                        variable_error=false;
                }
                else{
                    variable_error=true;
                    clearScreen();
                    cout<<"Date Input not Aceptable, please try again"<<endl;
                }
            }
            else{
                variable_error=true;
                clearScreen();
                cout<<"minute Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }
    variable_error=true;
    vector<string> tempVector_h;
    while (variable_error) {
        printClassVector(&print);
        try {
            cout<<"Enter the departure hours(hh mm)"<<endl;
            if(getline(cin,tempString)){
                clearScreen();
                checkIfOut(tempString);
                tempVector_h = vectorString(tempString," ");
                for(auto p:tempVector_h){
                    if(!strIsNumber(p)){
                        tempVector_h.clear();
                        variable_error=true;
                        clearScreen();
                        cout<<"minute Input not Aceptable, please try again"<<endl;
                        break;
                    }
                }
                if(tempVector_h.size()==2){
                    Date i(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));
                    int t=now->tm_year;
                    Date f(unsigned(t-100),1+date_u_short(now->tm_mon),date_u_short(now->tm_mday),date_u_short(now->tm_hour),date_u_short(now->tm_min));
                    if(i<f){
                        variable_error=true;
                        clearScreen();
                        cout<<"Input not Aceptable, should not be prior to current date, please try again"<<endl;
                    }
                    else
                        variable_error=false;
                }
                else{
                    variable_error=true;
                    clearScreen();
                    cout<<"minute Input not Aceptable, please try again"<<endl;
                }
            }
            else{
                variable_error=true;
                clearScreen();
                cout<<"minute Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }
    Date *temp_date=new Date(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));
    print.push_back("Initial Date: "+temp_date->getDateWHour());

    //set arrival date
    clearScreen();
    variable_error=true;
    tempVector.clear();
    while (variable_error) {
        printClassVector(&print);
        try {
            cout<<"Enter the date of arrival(yy mm dd)"<<endl;
            if(getline(cin,tempString)){
                clearScreen();
                checkIfOut(tempString);
                tempVector = vectorString(tempString," ");
                for(auto p:tempVector){
                    if(!strIsNumber(p)){
                        tempVector.clear();
                        variable_error=true;
                        clearScreen();
                        cout<<"Date Input not Aceptable, please try again"<<endl;
                        break;
                    }
                }
                if(tempVector.size()==3){
                    Date i(unsigned(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),23,59);
                    if(i<*temp_date){
                        variable_error=true;
                        clearScreen();
                        cout<<"Date Input not Aceptable, should not be prior to initial date, please try again"<<endl;
                    }
                    else
                        variable_error=false;
                }
                else{
                    variable_error=true;
                    clearScreen();
                    cout<<"Date Input not Aceptable, please try again"<<endl;
                }
            }
            else{
                variable_error=true;
                clearScreen();
                cout<<"Date Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }
    variable_error=true;
    tempVector_h.clear();
    while (variable_error) {
        printClassVector(&print);
        try {
            cout<<"Enter the hours of Arrival(hh mm)"<<endl;
            if(getline(cin,tempString)){
                clearScreen();
                checkIfOut(tempString);
                tempVector_h = vectorString(tempString," ");
                for(auto p:tempVector_h){
                    if(!strIsNumber(p)){
                        tempVector_h.clear();
                        variable_error=true;
                        clearScreen();
                        cout<<"minute Input not Aceptable, please try again"<<endl;
                        break;
                    }
                }
                if(tempVector_h.size()==2){
                    Date i(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));
                    if(i<*temp_date){
                        variable_error=true;
                        clearScreen();
                        cout<<"Input not Aceptable, should not be prior to current date, please try again"<<endl;
                    }
                    else
                        variable_error=false;
                }
                else{
                    variable_error=true;
                    clearScreen();
                    cout<<"minute Input not Aceptable, please try again"<<endl;
                }
            }
            else{
                variable_error=true;
                clearScreen();
                cout<<"minute Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }
    Date *temp_date_arrival=new Date(date_u_short(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),date_u_short(stoi(tempVector_h.at(0))),date_u_short(stoi(tempVector_h.at(1))));
    print.push_back("Arrival Date: "+temp_date_arrival->getDateWHour());

    //set distance
    clearScreen();
    variable_error=true;
    while (variable_error) {
        printClassVector(&print);
        cout<<"Enter the distance to go"<<endl;
        if(cin>>tempDistance && strIsNumber(tempDistance)){
            clearScreen();
            variable_error=false;
        }
        else
        {
            checkIfOut(tempDistance);
            clearScreen();
            cout<<"Distance not acceptable, please try again"<<endl;
        }
    }
    print.push_back("Distance:"+tempDistance);

    // set type of service
    clearScreen();
    variable_error=true;
    while (variable_error) {
        printClassVector(&print);
        cout<<"Please choose a type of service:"<<endl;
        cout<<endl;
        cout<<"[0] Ordinary"<<endl;
        cout<<"[1] Hazardous"<<endl;
        cout<<"[2] Animal"<<endl;
        cout<<"[3] Low Temperature"<<endl;
        if(cin>>tempType && strIsNumber(tempType) && stoi(tempType)<4){
            clearScreen();
            variable_error=false;
        }
        else{
            clearScreen();
            checkIfOut(tempType);
            variable_error=true;
            cout<<"Invalid Type number, please Try Again"<<endl;


        }
        clearBuffer();
    }
    print.push_back("Type of Service:"+typeToString(intToType(stoi(tempType))));// set type of service

    if(stoi(tempType)==1){
        variable_error=true;
        while (variable_error) {
            printClassVector(&print);
            cout<<"Please choose a type of service:"<<endl;
            cout<<endl;
            cout<<"[0] Explosives"<<endl;
            cout<<"[1] Gases"<<endl;
            cout<<"[2] Flammable Liquid"<<endl;
            cout<<"[3] Flammable Solid"<<endl;
            cout<<"[4] Oxidizer"<<endl;
            cout<<"[5] Poisons"<<endl;
            cout<<"[6] Radioactive"<<endl;
            cout<<"[7] Corrosives"<<endl;
            cout<<"[8] Other"<<endl;

            if(cin>>tempSpecType && strIsNumber(tempSpecType) && stoi(tempSpecType)<9){
                clearScreen();
                temp_hazard=static_cast<Hazard_enum>(stoi(tempSpecType)) ;
                variable_error=false;
            }
            else{
                clearScreen();
                checkIfOut(tempSpecType);
                variable_error=true;
                cout<<"Invalid Type number, please Try Again"<<endl;


            }
            clearBuffer();
        }
    }
    else if(stoi(tempType)==3){
        variable_error=true;
        while (variable_error) {
            printClassVector(&print);
            cout<<"Please choose a type of service:"<<endl;
            cout<<endl;
            cout<<"[0] 100"<<endl;
            cout<<"[1] 200"<<endl;
            cout<<"[2] 300"<<endl;
            cout<<"[3] 400"<<endl;

            if(cin>>tempSpecType && strIsNumber(tempSpecType) && stoi(tempSpecType)<4){
                clearScreen();
                temp_temperature=static_cast<Temperature_enum>(stoi(tempSpecType)) ;
                variable_error=false;
            }
            else{
                clearScreen();
                checkIfOut(tempSpecType);
                variable_error=true;
                cout<<"Invalid Type number, please Try Again"<<endl;


            }
            clearBuffer();
        }
    }

    //set yy/mm/dd
    /*
    variable_error=true;
    while (variable_error) {
        try {
            cout<<"Enter the Year"<<endl;
            if(cin>>year){
                clearScreen();
                variable_error=false;
                Date(year,month,day,1,1);
            }
            else{
                clearBuffer();
                variable_error=true;
                clearScreen();
                cout<<"Year Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }

    clearBuffer();
    variable_error=true;
    while (variable_error) {
        try {
            cout<<"Enter the month"<<endl;
            if(cin>>month){
                clearScreen();
                Date(year,month,day,1,1);
                variable_error=false;
            }
            else{
                clearBuffer();
                variable_error=true;
                clearScreen();
                cout<<"Month Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }

    clearBuffer();
    variable_error=true;
    while (variable_error) {
        try {
            cout<<"Enter the day"<<endl;
            if(cin>>day){
                clearScreen();
                Date(year,month,day,1,1);
                variable_error=false;
            }
            else{
                clearBuffer();
                variable_error=true;
                clearScreen();
                cout<<"day Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }

    //set hour
    clearBuffer();
    variable_error=true;
    while (variable_error) {
        try {
            cout<<"Enter the hour an minutes (hh:mm)"<<endl;
            if(cin>>hour){
                clearScreen();
                Date(year,month,day,hour,1);
                variable_error=false;
            }
            else{
                clearBuffer();
                variable_error=true;
                clearScreen();
                cout<<"hour Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }

    //set min
    clearBuffer();
    variable_error=true;
    while (variable_error) {
        try {
            cout<<"Enter the minute"<<endl;
            if(cin>>minute){
                clearScreen();
                Date(year,month,day,hour,minute);
                variable_error=false;
            }
            else{
                clearBuffer();
                variable_error=true;
                clearScreen();
                cout<<"minute Input not Aceptable, please try again"<<endl;
            }
        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }
    */
    /*
    // set year
Year:
    variable_error=true;
    while (variable_error) {
        try {
            year=chooseOptionNumber(unsigned(now->tm_year+1900),2100,"Enter the year",10);
            cout<<year<<endl;
            Date(year,month,day,hour,minute);
            variable_error=false;

        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }


    //set month
Month:
    variable_error=true;
    while (variable_error) {
        try {
            vector<string> more_options;
            more_options.push_back("Get back to year");
            if(unsigned(now->tm_year+1900)==year){
                month=date_u_short(chooseOptionNumber(unsigned(now->tm_mon+1),13,"Enter the month",12,&more_options));
                if(month==13)
                    goto Year;
            }
            else{
                month=date_u_short(chooseOptionNumber(1,13,"Enter the month",12,&more_options));
                if(month==13)
                    goto Year;
            }
            cout<<month<<endl;
            Date(year,month,day,hour,minute);
            variable_error=false;

        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }

    //set day
Day:
    variable_error=true;
    while (variable_error) {
        try {
            vector<string> more_options;
            more_options.push_back("Get back to month");
            if(unsigned(now->tm_year+1900)==year && unsigned(now->tm_mon+1)==month){
                day=date_u_short(chooseOptionNumber(unsigned(now->tm_mday),total_days(year,month)+1,"Enter the Day",12,&more_options));
                if(day==total_days(year,month)+1)
                    goto Month;
            }
            else{
                day=date_u_short(chooseOptionNumber(1,total_days(year,month)+1,"Enter the Day",12,&more_options));
                if(day==total_days(year,month)+1)
                    goto Month;
            }
            cout<<day<<endl;
            Date(year,month,day,hour,minute);
            variable_error=false;

        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }
    //set hour
Hour:
    variable_error=true;
    while (variable_error) {
        try {
            vector<string> more_options;
            more_options.push_back("Get back to day");
            if(unsigned(now->tm_year+1900)==year && unsigned(now->tm_mon+1)==month && unsigned(now->tm_mday)==day){
                hour=date_u_short(chooseOptionNumber(unsigned(now->tm_hour+1),24,"Enter the Hour",12,&more_options));
                if(hour==24)
                    goto Day;
            }
            else{
                hour=date_u_short(chooseOptionNumber(0,24,"Enter the Hour",12,&more_options));
                if(hour==24)
                    goto Day;
            }
            cout<<hour<<endl;
            Date(year,month,day,hour,minute);
            variable_error=false;

        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }

    //set minutes
    variable_error=true;
    while (variable_error) {
        try {
            vector<string> more_options;
            more_options.push_back("Get back to hour");
            minute=date_u_short(chooseOptionNumber(0,60,"Enter the Minutes",20,&more_options));
            if(minute==60)
                goto Hour;
            cout<<minute<<endl;
            Date(year,month,day,hour,minute);
            variable_error=false;

        } catch (DateInvalid i) {
            clearScreen();
            cout<<i.error<<endl;
        }
    }*/
    clearScreen();

    //set quantity
    clearScreen();
    variable_error=true;
    while (variable_error) {
        printClassVector(&print);
        cout<<"Enter the quantity to transport (in kg)"<<endl;
        if(cin>>temp_quantity && strIsNumber(temp_quantity)){
            clearScreen();
            variable_error=false;
        }
        else
        {
            checkIfOut(temp_quantity);
            clearScreen();
            cout<<"Quantity not acceptable, please try again"<<endl;
        }
    }
    clearScreen();
    print.push_back("Quantity: "+temp_quantity);


    printClassVector(&print);
    Service *temp_service;
    switch (stoi(tempType)) {
    case 1:
        temp_service=new  HazardousService(tempMaterial,origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),on_queue,temp_date,client,stoi(temp_quantity),temp_hazard);
        temp_service->total_price=stoi(temp_quantity)*HazardousMat::pricePerKG*HazardousMat::hazardMul[temp_hazard]*temp_service->getDistance();
        break;
    case 3:
        temp_service=new TemperatureService(tempMaterial, origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),on_queue,temp_date,client,stoi(temp_quantity),temp_temperature);
        temp_service->total_price=stoi(temp_quantity)*Congelation::pricePerKG*Congelation::tempMul[temp_temperature]*temp_service->getDistance();
        break;
    case 2:
        temp_service=new Service(tempMaterial,origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),on_queue,temp_date,client,stoi(temp_quantity));
        temp_service->total_price=stoi(temp_quantity)*Animal::pricePerKG*temp_service->getDistance();
        break;
    default:
        temp_service=new Service(tempMaterial,origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),on_queue,temp_date,client,stoi(temp_quantity));
        temp_service->total_price=stoi(temp_quantity)*Normal::pricePerKG*temp_service->getDistance();
        break;
    }
    print.push_back("total Price: "+to_string(temp_service->getTotalPrice()));
    printClassVector(&print);

    string t="p";
    while(t!="y" && t!="n"){
        cout<<"Are u sure you want to Add Service? (y/n)"<<endl;
        cin>>t;
        if(t!="y"){
            clearScreen();
            delete temp_service;
            throw exception();
        }
        else
            break;
    }

    if(temp_service->autoAddTrucks()>0){
        cout<<"Couldn't assign enough truck to service"<<endl;
        throw exception();
    }
    else {
        cout<<"Service successfully created\n";
        enter_to_exit();
    }

    //clearBuffer();
    services->push_back(temp_service);
    client->addService(temp_service);
    Company::getCompany()->services_on_queue_changed=true;
    //enter_to_exit();
    return temp_service;
}

void Service::editService(){
    if(ser_state==on_queue){
        unsigned opt=1;
        clearScreen();
        while (opt!=0) {
            bool variable_error=true;
            while (variable_error) {
                cout<<this;
                cout<<"[1] Edit Origin"<<endl;
                cout<<"[2] Edit destination"<<endl;
                cout<<"[3] Edit Quantity"<<endl;
                cout<<"[0] Exit"<<endl;
                if(cin>>opt && opt<=3){
                    clearScreen();
                    variable_error=false;
                    string temp;
                    string tempOrigin;
                    Address temp_origin;
                    switch (opt) {
                    case 0:{
                        return;
                    }
                    case 1: {
                        clearBuffer();
                        variable_error=true;
                        clearScreen();
                        while (variable_error) {
                            cout<<"Enter the Origin (street / doorNumber / location) or (location)"<<endl;

                            getline(cin,tempOrigin);
                            vector<string> temp_address_no_pc=vectorString(tempOrigin,"/");
                            checkIfOut(tempOrigin);
                            if(temp_address_no_pc.size()==3){
                                clearScreen();
                                if(strIsChar(temp_address_no_pc.at(2)) && strIsNumber(temp_address_no_pc.at(1))){
                                    variable_error=false;
                                    cout<<"Enter the Origin postal code (xxxx-yyy)"<<endl;
                                    while(true){
                                        string postal_code;
                                        cin>>postal_code;
                                        vector<string> temp_postal_code= vectorString(postal_code,"-");
                                        if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                                            temp_origin=Address(temp_address_no_pc.at(0),date_u_short(stoi(temp_address_no_pc.at(1))),postal_code,temp_address_no_pc.at(2));
                                            variable_error=false;
                                            break;
                                        }
                                        else{
                                            clearScreen();
                                            cout<<"Postal code not acceptable\nEnter the Origin postal code (xxxx-yyy)"<<endl;
                                        }

                                    }

                                }
                            }
                            else if(temp_address_no_pc.size()==1 && strIsChar(temp_address_no_pc.at(0))){
                                clearScreen();
                                if(strIsChar(temp_address_no_pc.at(0))){
                                    cout<<"Enter the Origin postal code (xxxx-yyy)"<<endl;
                                    while(true){
                                        string postal_code;
                                        cin>>postal_code;
                                        vector<string> temp_postal_code= vectorString(postal_code,"-");
                                        if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                                            temp_origin=Address("",0,postal_code,temp_address_no_pc.at(0));
                                            variable_error=false;
                                            break;
                                        }
                                        else{
                                            clearScreen();
                                            cout<<"Postal code not acceptable\nEnter the Origin postal code (xxxx-yyy)"<<endl;
                                        }

                                    }

                                }

                            }

                            else{
                                checkIfOut(tempOrigin);
                                if(tempOrigin=="")
                                    break;
                                variable_error=true;
                                clearScreen();
                                cout<<"Origin Input not acceptable, please try again"<<endl;
                            }

                        }
                        if(tempOrigin!=""){
                            string tempDistance;
                            variable_error=true;
                            while (variable_error) {
                                cout<<"Enter the distance to go"<<endl;
                                if(cin>>tempDistance && strIsNumber(tempDistance)){
                                    clearScreen();
                                    variable_error=false;
                                }
                                else
                                {
                                    checkIfOut(tempDistance);
                                    clearScreen();
                                    cout<<"Distance not acceptable, please try again"<<endl;
                                }
                            }
                            string t="p";
                            while(t!="y" && t!="n"){
                                cout<<"Are u sure you want to Edit Service?"<<endl;
                                cin>>t;
                                if(t!="y"){
                                    clearScreen();
                                    throw exception();
                                }
                                total_price=total_price/distance;
                                total_price=total_price*stof(tempDistance);
                            }
                            Company::getCompany()->services_on_queue_changed=true;
                            this->setOrigin(temp_origin);
                            this->setDistance(unsigned(stoi(tempDistance)));
                            break;
                        }
                        break;
                    }


                    case 2:{
                        clearBuffer();
                        //set destination
                        variable_error=true;
                        clearScreen();
                        while (variable_error) {
                            cout<<"Enter the Destination (street / doorNumber / location) or (location)"<<endl;

                            getline(cin,tempOrigin);
                            vector<string> temp_address_no_pc=vectorString(tempOrigin,"/");
                            checkIfOut(tempOrigin);
                            if(temp_address_no_pc.size()==3){
                                clearScreen();
                                if(strIsChar(temp_address_no_pc.at(2)) && strIsNumber(temp_address_no_pc.at(1))){
                                    variable_error=false;
                                    cout<<"Enter the Destination postal code (xxxx-yyy)"<<endl;
                                    while(true){
                                        string postal_code;
                                        cin>>postal_code;
                                        vector<string> temp_postal_code= vectorString(postal_code,"-");
                                        if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                                            temp_origin=Address(temp_address_no_pc.at(0),date_u_short(stoi(temp_address_no_pc.at(1))),postal_code,temp_address_no_pc.at(2));
                                            variable_error=false;
                                            break;
                                        }
                                        else{
                                            clearScreen();
                                            cout<<"Postal code not acceptable\nEnter the Destination postal code (xxxx-yyy)"<<endl;
                                        }

                                    }

                                }
                            }
                            else if(temp_address_no_pc.size()==1 && strIsChar(temp_address_no_pc.at(0))){
                                clearScreen();
                                if(strIsChar(temp_address_no_pc.at(0))){
                                    cout<<"Enter the Destination postal code (xxxx-yyy)"<<endl;
                                    while(true){
                                        string postal_code;
                                        cin>>postal_code;
                                        vector<string> temp_postal_code= vectorString(postal_code,"-");
                                        if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                                            temp_origin=Address("",0,postal_code,temp_address_no_pc.at(0));
                                            variable_error=false;
                                            break;
                                        }
                                        else{
                                            clearScreen();
                                            cout<<"Postal code not acceptable\nEnter the Destination postal code (xxxx-yyy)"<<endl;
                                        }

                                    }

                                }

                            }

                            else{
                                clearScreen();
                                if(tempOrigin=="")
                                    break;
                                variable_error=true;
                                cout<<"ORigin Input not acceptable, please try again"<<endl;
                            }

                        }
                        string tempDistance;
                        variable_error=true;
                        while (variable_error) {
                            cout<<"Enter the distance to go"<<endl;
                            if(cin>>tempDistance && strIsNumber(tempDistance)){
                                clearScreen();
                                variable_error=false;
                            }
                            else
                            {
                                checkIfOut(tempDistance);
                                clearScreen();
                                cout<<"Distance not acceptable, please try again"<<endl;
                            }
                        }
                        string t="p";
                        while(t!="y" && t!="n"){
                            cout<<"Are u sure you want to Edit Service?"<<endl;
                            cin>>t;
                            if(t!="y"){
                                clearScreen();
                                throw exception();
                            }
                            total_price/=distance;
                            total_price*=stof(tempDistance);
                        }
                        Company::getCompany()->services_on_queue_changed=true;
                        this->setDestination(temp_origin);
                        setDistance(unsigned(stoi(tempDistance)));
                        break;
                    }
                    case 3:{
                        variable_error=true;
                        string temp_quantity;
                        clearBuffer();
                        while (variable_error) {
                            cout<<"Enter the quantity to transport"<<endl;
                            getline(cin,temp_quantity);
                            if(strIsNumber(temp_quantity)){
                                clearScreen();
                                for(auto i:trucks){
                                    i.first->remove_service(this->getId());
                                }
                                variable_error=false;
                                try {
                                    string t="p";
                                    while(t!="y" && t!="n"){
                                        cout<<"Are u sure you want to Edit Service?"<<endl;
                                        cin>>t;
                                        if(t!="y"){
                                            clearScreen();
                                            return;
                                        }
                                        total_price/=quantity;
                                        total_price*=stof(temp_quantity);
                                        quantity=stof(temp_quantity);
                                        if(autoAddTrucks()>0){
                                            clearScreen();
                                            cout<<"Quantity not acceptable, please try again"<<endl;
                                            enter_to_exit();
                                        }
                                    }
                                    Company::getCompany()->services_on_queue_changed=true;
                                } catch (...) {
                                    variable_error=true;
                                    clearScreen();
                                    cout<<"Quantity not acceptable, please try again"<<endl;
                                }
                            }
                            else
                            {
                                checkIfOut(temp_quantity);
                                if(temp_quantity=="")
                                    break;
                                clearScreen();
                                cout<<"Quantity not acceptable, please try again"<<endl;
                            }
                        }
                        break;
                    }
                    }
                }
                else{
                    clearScreen();
                    clearBuffer();
                    opt=1;
                    variable_error=true;
                    cout<<"Invalid Type number, please Try Again"<<endl;
                }
            }
        }
    }

}

bool Service::removeService(vector<Service *> *services, unsigned id){
    for(auto i=services->begin();i!=services->end();i++){
        clearBuffer();
        if((*i)->getId()==id && (*i)->getState()==on_queue){
            (*i)->~Service();
            (*i)->getClient()->removeService((*i));
            Company::getCompany()->services_on_queue_changed=true;
            return true;
        }
        else if((*i)->getState()!=on_queue){
            cout<<"couldn't remove service, already finished or on route"<<endl;
            return  false;
        }
    }
    throw ServiceDoNotExist("Couldn't find Service");
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Hazardous
//constructor
HazardousService::HazardousService(string material_h, Address origin_h, Address destination_h, Date *arrivalDate_h, unsigned distance_h, enum type type_h, enum state state_h, Date *date_h, Client *client_h,float quantity_h,Hazard_enum type): Service(material_h,origin_h,destination_h,arrivalDate_h,distance_h,type_h,state_h,date_h,client_h,quantity_h),type(type)
{
    
    
}
HazardousService::HazardousService(string material_h, string origin_h, string destination_h, Date *arrivalDate_h, unsigned distance_h, enum type type_h, enum state state_h, Date *date_h, Client *client_h,float quantity_h,Hazard_enum type,float total_price_h,unsigned id_h): Service(material_h,origin_h,destination_h,arrivalDate_h,distance_h,type_h,state_h,date_h,client_h,quantity_h,total_price_h,id_h),type(type)
{

}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Temperature
//constructor
TemperatureService::TemperatureService(string material_s, string origin_s, string destination_s, Date *arrivalDate_s, unsigned distance_s, enum type type_s, enum state state_s, Date *date_s, Client *client_s, float quantity_s, Temperature_enum type, float total_price_s,unsigned id_s): Service(material_s,origin_s,destination_s,arrivalDate_s,distance_s,type_s,state_s,date_s,client_s,quantity_s,total_price_s,id_s) ,type(type)
{

}
TemperatureService::TemperatureService(string material_s, Address origin_s, Address destination_s, Date *arrivalDate_s, unsigned distance_s, enum type type_s, enum state state_s, Date *date_s, Client *client_s,float quantity_s,Temperature_enum type): Service(material_s,origin_s,destination_s,arrivalDate_s,distance_s,type_s,state_s,date_s,client_s,quantity_s) ,type(type)
{
    
}



ostream& operator <<(ostream& os,Service *a){
    os<<"__________________________________________________"<<endl;
    os<<"Transporting "+a->getMaterial()+"("<<a->getId()<<")"<<endl;
    os<<endl;
    os<<"Client: "+a->getClient()->getName()<<endl;
    os<<endl;
    os<<"Origin: "+a->getOrigin().getFullAdress() <<endl;
    os<<"Destination: "+a->getDestination().getFullAdress() <<endl;
    os<<"Distance: "<<a->getDistance()<<endl;
    os<<endl;
    os<<"Initial Date: "+a->getIDate()->getDateWHour()<<endl;
    os<<"Arrival Date: "+a->getADate()->getDateWHour()<<endl;
    os<<"Time :"<<*a->getADate()-*a->getIDate()<<" min"<<endl;
    os<<endl;
    os<<"Type of Transport: "+typeToString(a->getType())<<endl;
    int prec_q=0,prec_p=0;
    if((a->getTotalPrice()-int(a->getTotalPrice())>0))
        prec_p=2;

    if((a->getQuantity()-int(a->getQuantity())>0))
        prec_q=2;
    float x=a->getQuantity();
    os<<endl<<"Trucks: ";
    for(auto i:a->trucks){
        os<<i.first->getlicense()<<": "<<i.second<<"kg"<<endl;
    }
    os<<endl<<endl;
    os<<"State: "<<a->getState()<<endl;
    os<<"Quantity: "<<setprecision(prec_q)<<fixed<<x<<endl;
    float y=a->getTotalPrice();
    os<<"Price : "<<setprecision(prec_p)<<fixed<<y<<endl;
    os<<endl;
    return os;
}

int Service::autoAddTrucks(){
    vector<Truck*> tempTruck;
    float remaining=quantity;
    bool notCompleted=true,forward=false;
    map<unsigned,unsigned> temp_map;
    switch (this->getType()) {
    case type::ordinary:{
        temp_map=Normal::CapDist;
        break;
    }
    case type::animal:{
        temp_map=Animal::CapDist;
        break;
    }
    case type::hazardous:{
        temp_map=HazardousMat::CapDist;
        break;
    }
    case type::lowTemperature:{
        temp_map=Congelation::CapDist;
        break;
    }

    }

    bool available_on_time=true;
    vector<Truck*> tempVectorIterate=*Company::getCompany()->getVectorTrucks();
    for(auto i= tempVectorIterate.begin();i!=tempVectorIterate.end();){
        if(ser_type==(*i)->getType()){
            for(auto c:*(*i)->getServices()){
                if(((*c->initialDate<*arrivalDate && *arrivalDate<*c->arrivalDate) || (*initialDate<*c->arrivalDate && *c->initialDate<*initialDate))){
                    available_on_time=false;
                    i=tempVectorIterate.erase(i);
                    break;
                }
            }
            if(available_on_time){
                temp_map.at((*i)->getcapacity())++;
                available_on_time=true;
                i++;
            }
        }
        else{
            i=tempVectorIterate.erase(i);
        }
    }

    auto r_it=temp_map.rbegin();
    auto it=temp_map.begin();
    enter_to_exit();
    unsigned maxTrucks;
    bool all=false;
    unsigned numb=unsigned(quantity/temp_map.rbegin()->first);
    if(temp_map.rbegin()->first*(numb)<quantity){
        numb++;
    }
    maxTrucks=numb;
    for(auto i=++temp_map.rbegin();i!=temp_map.rend();i++){
        unsigned numb=unsigned(quantity/i->first);
        if(i->first*numb<quantity){
            numb++;
        }
        if(numb<=maxTrucks  && numb<=i->second){
            r_it++;
            maxTrucks=numb;
            break;
        }
    }
    while(notCompleted){
        if(tempVectorIterate.size()==0 && remaining>0){
            //cout<<remaining<<endl;
            return int(remaining);
        }
        if(!forward && r_it!=temp_map.rend()){
            for(auto i= tempVectorIterate.begin();i!=tempVectorIterate.end();){
                if(r_it->first==(*i)->getcapacity()){
                    if(remaining-(*i)->getcapacity()>0){
                        remaining-=(*i)->getcapacity();
                        tempTruck.push_back((*i));
                        i=tempVectorIterate.erase(i);
                    }
                    else if(double(remaining-(*i)->getcapacity())==0.0){
                        tempTruck.push_back((*i));
                        i=tempVectorIterate.erase(i);
                        remaining=0;
                        notCompleted=false;
                        forward=true;
                        break;
                    }
                    else {
                        forward=true;
                        i++;
                        break;
                    }

                }
                else{
                    i++;
                }
                if(forward)
                    break;
            }
            r_it++;
        }
        else if(it!=temp_map.end()){
            for(auto i= tempVectorIterate.begin();i!=tempVectorIterate.end();){
                if(remaining-(*i)->getcapacity()<=0 && (*it).first==(*i)->getcapacity()){
                    remaining-=(*i)->getcapacity();
                    tempTruck.push_back((*i));
                    i=tempVectorIterate.erase(i);
                    notCompleted=false;
                    break;
                }
                else
                {
                    i++;
                }

            }
            it++;
        }
        else{
            if(all)
                break;
            else {
                r_it=temp_map.rbegin();
                it=temp_map.begin();
                all=false;
            }
        }
    }
    float cargo_capacity=0;
    for(auto i:tempTruck){
        cargo_capacity+=i->getcapacity();
    }

    float cargo_percentage= quantity/cargo_capacity;
    clearScreen();
    cout<<"Trucks Assigned"<<endl;
    for(auto i:tempTruck){
        trucks[i]=i->getcapacity()*cargo_percentage;
        i->add_service(this);
        i->setregistered(true);
        i->info();
        cout<<endl;
    }
    return  int(remaining);
}

void Service::test(){
    Date *x=new Date();
    Service i("pilas",Address(),Address(),x,300,type::ordinary,on_queue,x,Company::getCompany()->getVectorClients()->at(0),81000);
    i.autoAddTrucks();

}

/*
ServiceDoNotExist::ServiceDoNotExist(string erro): erro(erro){

};
ServiceFinishedFileError::ServiceFinishedFileError(){}


ServiceOnQueueFileError::ServiceOnQueueFileError(){}


ServiceOnTransitFileError::ServiceOnTransitFileError(){}
*/


