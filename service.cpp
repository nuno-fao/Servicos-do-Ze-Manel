#include "service.h"

unsigned int Service::lastId=0;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SERVICE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//constructors
Service::Service(string material, Address origin, Address destination, Date *arrivalDate, unsigned distance, enum type type, enum state state, Date *date, Client *client, float quantity)
    : material(material), distance(distance), quantity(quantity), ser_type(type), ser_state(state)
{
    
    id=lastId++;
    setIDate(date);
    setADate(arrivalDate);
    setOrigin(Address(origin));
    setDestination(Address(destination));
    setClient(client);
    calcPrice();
    
}

Service::Service(string material, string origin, string destination, Date *arrivalDate, unsigned distance, enum type type, enum state state, Date *date, Client *client, float quantity, float total_price, unsigned id)
    : material(material), distance(distance), quantity(quantity),  ser_type(type),id(id), ser_state(state),total_price(total_price)
{
    lastId++;
    setIDate(date);
    setADate(arrivalDate);
    setOrigin(Address(origin));
    setDestination(Address(destination));
    setClient(client);

}
//destructor
Service::~Service(){
    initialDate->~Date();
    if(ser_state==on_queue)
        for(auto i=Company::getCompany()->getVectorServicesOnQueue()->begin();i!=Company::getCompany()->getVectorServicesOnQueue()->end();i++){
            if((*i)->getId()==id){
                Company::getCompany()->getVectorServicesOnQueue()->erase(i);
            }
        }

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
vector<Truck*> *Service::getTrucks(){
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
void Service::addTruck(Truck *truck){
    this->trucks.push_back(truck);
}
void Service::calcPrice(){
    total_price=0;
    for(auto i:trucks)
        total_price+=i->getprice(this);
}



//help methods
type intToType(int a){
    switch (a) {
    case 0: return ordinary;
    case 1: return hazardous;
    case 2: return animal;
    case 3: return lowTemperature;
    default: return ordinary;
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
    case ordinary:
        return "ordinary";
    case hazardous:
        return "hazardous";
    case animal:
        return "animal";
    case lowTemperature:
        return "Low Temperature";
    }
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
    servicesFile.open("./files/on_queue_services.txt");
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
    unsigned tempId;
    vector<string> tempVectorTruckS;

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

            if(tempType==3)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,temp_client,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==1)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,temp_client,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,temp_client,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    Truck *temp_truck=Company::getCompany()->getTruck(i);
                    temp->addTruck(temp_truck);
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
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
            if(tempType==3)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,tempC,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==1)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,tempC,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempI,tempC,tempQuantity,tempPrice,tempId);


            for(auto i:tempVectorTruckS){
                try{
                    Truck *temp_truck=Company::getCompany()->getTruck(i);
                    temp->addTruck(temp_truck);
                    temp_truck->add_service(temp);

                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
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
        Date *tempD=new Date(tempIDate);
        Date *tempA=new Date(tempADate);
        try {
            if(tempNif.size()!=9)
                throw NotAClient(unsigned(stoi(tempNif)),"Not a valid NIF");
            Client *temp_client=Company::getCompany()->getClient(unsigned(stoi(tempNif)));
            if(tempType==3)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==1)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    Truck *temp_truck=Company::getCompany()->getTruck(i);
                    temp->addTruck(temp_truck);
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
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
            if(tempType==3)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==1)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    Truck *temp_truck=Company::getCompany()->getTruck(i);
                    temp->addTruck(temp_truck);
                    temp_truck->add_service(temp);
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
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
            if(tempType==3)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==1)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,temp_client,tempQuantity,tempPrice,tempId);


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
            cout<<e.erro<<" "<<to_string(e.getNif())<<endl;
            string temp_error;
            Client *tempC= new NotAClient(e);
            //getline(cin,temp_error);
            if(tempType==3)
                temp= new TemperatureService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Temperature_enum::_200,tempPrice,tempId);
            if(tempType==1)
                temp= new HazardousService(tempMaterial, tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,Hazard_enum::corrosives,tempPrice,tempId);
            else
                temp= new Service(tempMaterial,tempOrigin,tempDestination,tempA,unsigned(tempDistance),tempType,tempState,tempD,tempC,tempQuantity,tempPrice,tempId);

            for(auto i:tempVectorTruckS){
                try{
                    temp->addTruck(Company::getCompany()->getTruck(i));
                }
                catch(TruckDoNotExist e){
                    cout<<e.erro+" "<<e.license<<endl;
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
        servicesFile << (x->getType())<<endl;

        servicesFile << endl << (x->getState())<<endl;
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
        servicesFile << (x->getType())<<endl;

        for(auto i: *x->getTrucks()){
            servicesFile << i->getlicense() <<";";
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
        servicesFile << (x->getType())<<endl;

        for(auto i: *x->getTrucks()){
            servicesFile << i->getlicense() <<";";
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
    string tempType ,month,day,hour,minute;
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

    print.push_back(tempMaterial);
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
                    cin>>postal_code;
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
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
                    cin>>postal_code;
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
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
            cout<<"ORigin Input not acceptable, please try again"<<endl;
        }

    }

    clearScreen();
    clearBuffer();
    print.push_back(tempOrigin);
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
                    cin>>postal_code;
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
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
                    cin>>postal_code;
                    vector<string> temp_postal_code= vectorString(postal_code,"-");
                    if(temp_postal_code.size()==2 && strIsNumber(temp_postal_code.at(0)) && strIsNumber(temp_postal_code.at(1)) && temp_postal_code.at(0).size()==4 && temp_postal_code.at(1).size()==3){
                        origin=Address("",0,postal_code,temp_address_no_pc.at(0));

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
    print.push_back(tempDestination);
    //set yy/mm/dd



    clearBuffer();
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
                    if((f-i)<0){
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
                    if((f-i)<0){
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
    print.push_back(temp_date->getDateWHour());









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
                    int t=now->tm_year;
                    Date i(unsigned(stoi(tempVector.at(0))),date_u_short(stoi(tempVector.at(1))),date_u_short(stoi(tempVector.at(2))),23,59);
                    if((*temp_date-i)<0){
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
                    int t=now->tm_year;
                    Date f(unsigned(t-100),1+date_u_short(now->tm_mon),date_u_short(now->tm_mday),date_u_short(now->tm_hour),date_u_short(now->tm_min));
                    if((*temp_date-i)<0){
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
    print.push_back(temp_date_arrival->getDateWHour());

    //set distance
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

    print.push_back(tempDistance);
    // set type of service
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
    print.push_back(tempType);
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
    variable_error=true;
    while (variable_error) {
        printClassVector(&print);
        cout<<"Enter the quantity to transport"<<endl;
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

    print.push_back(temp_quantity);
    printClassVector(&print);

    string t="p";
    while(t!="y" && t!="n"){
        cout<<"Are u sure you want to Add Service?"<<endl;
        cin>>t;
        if(t!="y"){
            clearScreen();
            throw exception();
        }
    }

    clearBuffer();
    Service *temp_service;
    switch (stoi(tempType)) {
    case hazardous:
        temp_service=new  HazardousService(tempMaterial,origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),on_queue,temp_date,client,stoi(temp_quantity),Hazard_enum::explosives);
        break;
    case lowTemperature:
        temp_service=new TemperatureService(tempMaterial, origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),on_queue,temp_date,client,stoi(temp_quantity),Temperature_enum::_200);
        break;
    default:
        temp_service=new Service(tempMaterial,origin,destination,temp_date_arrival,unsigned(stoi(tempDistance)),intToType(stoi(tempType)),intToState(0),temp_date,client,stoi(temp_quantity));
    }
    services->push_back(temp_service);
    Company::getCompany()->services_on_queue_changed=true;
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
                cout<<"[1] edit Origin"<<endl;
                cout<<"[2] edit destination"<<endl;
                cout<<"[3] edit Quantity"<<endl;
                if(cin>>opt && opt<=3){
                    clearScreen();
                    variable_error=false;
                    string temp;

                    switch (opt) {
                    case 1: {
                        variable_error=true;
                        clearScreen();
                        clearBuffer();
                        while (variable_error) {
                            cout<<"Enter the Origin"<<endl;
                            getline(cin,temp);
                            if(temp=="")
                                break;
                            checkIfOut(temp);
                            clearScreen();
                            if(strIsChar(temp)){
                                variable_error=false;
                                setOrigin(temp);
                                Company::getCompany()->services_on_queue_changed=true;
                            }
                            else{
                                variable_error=true;
                                cout<<"ORigin Input not acceptable, please try again"<<endl;
                            }

                        }
                        break;
                    }
                    case 2:{
                        //set destination
                        variable_error=true;
                        clearBuffer();
                        while (variable_error) {
                            cout<<"Enter the Destination"<<endl;
                            getline(cin,temp);
                            if(temp=="")
                                break;
                            checkIfOut(temp);
                            clearScreen();
                            if(strIsChar(temp)){
                                variable_error=false;
                                setDestination(temp);
                                Company::getCompany()->services_on_queue_changed=true;
                            }
                            else{
                                variable_error=true;
                                cout<<"Destination Input not acceptable, please try again"<<endl;
                            }

                        }

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
                                variable_error=false;
                                try {
                                    setQuantity(stof(temp_quantity));
                                } catch (...) {
                                    variable_error=true;
                                    clearScreen();
                                    cout<<"Quantity not acceptable, please try again"<<endl;
                                }
                                Company::getCompany()->services_on_queue_changed=true;
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
        if((*i)->getId()==id && (*i)->getState()==on_queue){
            (*i)->~Service();
            services->erase(i);
            return  true;
        }
        else if((*i)->getState()!=on_queue){
            cout<<"couldn't remove service, already finished or or route"<<endl;
            return  false;
        }
    }
    throw ServiceDoNotExist("Couldn't find Service");
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Hazardous
//constructor
HazardousService::HazardousService(string material_h, Address origin_h, Address destination_h, Date *arrivalDate_h, unsigned distance_h, enum type type_h, enum state state_h, Date *date_h, Client *client_h,float quantity_h,Hazard_enum type): Service(material_h,origin_h,destination_h,arrivalDate_h,distance_h,type_h,state_h,date_h,client_h,quantity_h),type(type)
{
    calcPrice();
    
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
    calcPrice();
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
    os<<"Time :"<<*a->getIDate()-*a->getADate()<<" h"<<endl;
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
        os<<i->getlicense()<<" ";
    }
    os<<endl<<endl;
    os<<"Quantity: "<<setprecision(prec_q)<<fixed<<x<<endl;
    float y=a->getTotalPrice();
    os<<"Price : "<<setprecision(prec_p)<<fixed<<y<<endl;
    os<<endl;
    return os;
}
