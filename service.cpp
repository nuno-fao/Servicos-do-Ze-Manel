#include "service.h"
unsigned int Service::lastId=0;

Service::Service(string origin, string destination, double time, unsigned distance, enum type type, enum state state, Date date, Client *client,float quantity)
    : origin(origin),destination(destination), time(time), distance(distance), quantity(quantity), ser_type(type), ser_state(state)
{
    
    id=lastId++;
    setDate(date);
    setClient(client);
    calcPrice();
    
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
state Service::getState() const{
    return ser_state;
}
Date Service::getDate() const{
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

void Service::calcPrice(){
    total_price=0;
    for(auto i:trucks)
        total_price+=i->getprice(this);
}

void Service::saveToFile(vector<Service*>*services_finished,vector<Service*>*services_on_transit,vector<Service*>*services_on_queue){
    ofstream servicesFile;
    servicesFile.open ("services.txt");
    for(auto x:*services_finished){
        servicesFile << x->getOrigin()<<endl;
        servicesFile << x->getDestination()<<endl;
        servicesFile << (x->getTime())<<endl;
        servicesFile << (x->getDistance())<<endl;
        servicesFile << (x->getType())<<endl;
        servicesFile << (x->getId())<<endl;
        for(auto i: *x->getTrucks()){
            servicesFile << i->getlicense() <<";";
        }
        servicesFile << endl << (x->getState())<<endl;
        servicesFile << x->getDate().getDate() <<endl;
        servicesFile << x->getClient()->getNif() << endl;
        servicesFile << x->getTotalPrice() <<endl;
        servicesFile << ":::::::::::"<<endl;
    }
    for(auto x:*services_on_queue){
        servicesFile << x->getOrigin()<<endl;
        servicesFile << x->getDestination()<<endl;
        servicesFile << (x->getTime())<<endl;
        servicesFile << (x->getDistance())<<endl;
        servicesFile << (x->getType())<<endl;
        servicesFile << (x->getId())<<endl;
        for(auto i: *x->getTrucks()){
            servicesFile << i->getlicense() <<";";
        }
        servicesFile << endl << (x->getState())<<endl;
        servicesFile << x->getDate().getDate() <<endl;
        servicesFile << x->getClient()->getNif() << endl;
        servicesFile << x->getTotalPrice() <<endl;
        servicesFile << ":::::::::::"<<endl;
    }
    for(auto x:*services_on_transit){
        servicesFile << x->getOrigin()<<endl;
        servicesFile << x->getDestination()<<endl;
        servicesFile << (x->getTime())<<endl;
        servicesFile << (x->getDistance())<<endl;
        servicesFile << (x->getType())<<endl;
        servicesFile << (x->getId())<<endl;
        for(auto i: *x->getTrucks()){
            servicesFile << i->getlicense() <<";";
        }
        servicesFile << endl << (x->getState())<<endl;
        servicesFile << x->getDate().getDate() <<endl;
        servicesFile << x->getClient()->getNif() << endl;
        servicesFile << x->getTotalPrice() <<endl;
        servicesFile << ":::::::::::"<<endl;
    }
}

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

Client *findClient(int nif){
    vector<Service *> t;
    Client *temp=new Client("ola",unsigned(nif),&t);
    return temp;
}

void Service::loadFromFile(vector<Service*> *services_finished,vector<Service*> *services_on_transit,vector<Service*> *services_on_queue){
    ifstream servicesFile;
    servicesFile.open("services.txt");
    string tempOrigin;
    string tempDestination;
    double tempTime;
    double tempDistance;
    type tempType;
    string vector;
    state tempState;
    string tempDate;
    string tempNif;
    string tempGeneral;

    while(getline(servicesFile,tempOrigin)){
        getline(servicesFile,tempDestination);
        
        getline(servicesFile,tempGeneral);
        tempTime=stod(tempGeneral);
        
        getline(servicesFile,tempGeneral);
        tempDistance=stoi(tempGeneral);
        
        getline(servicesFile,tempGeneral);
        tempType=intToType(stoi(tempGeneral));
        
        getline(servicesFile,tempGeneral);
        
        getline(servicesFile,vector);
        
        getline(servicesFile,tempGeneral);
        tempState=intToState(stoi(tempGeneral));
        
        getline(servicesFile,tempDate);
        
        getline(servicesFile,tempNif);
        Service *temp;
        if(tempType==3)
            temp= new TemperatureService(tempOrigin,tempDestination,tempTime,unsigned(tempDistance),tempType,tempState,Date(tempDate),findClient(22200),8989,_200);
        if(tempType==1)
            temp= new HazardousService(tempOrigin,tempDestination,tempTime,unsigned(tempDistance),tempType,tempState,Date(tempDate),findClient(22200),8989,corrosives);
        else
            temp= new Service(tempOrigin,tempDestination,tempTime,unsigned(tempDistance),tempType,tempState,Date(tempDate),findClient(22200),8989);
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
        getline(servicesFile,tempGeneral);
    }
    
    
    
    
    
}

HazardousService::HazardousService(string origin_h, string destination_h, double time_h, unsigned distance_h, enum type type_h, enum state state_h, Date date_h, Client *client_h,float quantity_h,Hazard_enum type)
    : Service(origin_h,destination_h,time_h,distance_h,type_h,state_h,date_h,client_h,quantity_h),type(type)
{
    id=lastId++;
    setDate(date_h);
    setClient(client_h);
    calcPrice();
    
}

TemperatureService::TemperatureService(string origin_s, string destination_s, double time_s, unsigned distance_s, enum type type_s, enum state state_s, Date date_s, Client *client_s,float quantity_s,Temperature_enum type)
    : Service(origin_s,destination_s,time_s,distance_s,type_s,state_s,date_s,client_s,quantity_s) ,type(type)
{
    id=lastId++;
    setDate(date_s);
    setClient(client_s);
    calcPrice();
    
    
}

Service *Service::addService(vector<Service *> *services,Client *client){
    string tempOrigin,tempDestination;
    unsigned short tempType = 0,month=1,day=1,hour=0,minute=0;
    unsigned temp_quantity=0;
    unsigned year=0;
    bool variable_error=true;
    time_t rawtime;struct tm *now;std::time( &rawtime );now = localtime( &rawtime );
    // set origin
    while (variable_error) {
        cout<<"Enter the Origin"<<endl;

        getline(cin,tempOrigin);
        clearScreen();
        if(strIsChar(tempOrigin))
            variable_error=false;
        else{
            variable_error=true;
            cout<<"ORigin Input not acceptable, please try again"<<endl;
        }
        
    }

    //set destination
    variable_error=true;
    while (variable_error) {
        cout<<"Enter the Destination"<<endl;
        getline(cin,tempDestination);
        clearScreen();
        if(strIsChar(tempDestination))
            variable_error=false;
        else{
            variable_error=true;
            cout<<"Destination Input not acceptable, please try again"<<endl;
        }
        
    }

    // set type of service
    variable_error=true;
    while (variable_error) {
        cout<<"Please choose a type of service:"<<endl;
        cout<<endl;
        cout<<"[0] Ordinary"<<endl;
        cout<<"[1] Hazardous"<<endl;
        cout<<"[2] Animal"<<endl;
        cout<<"[3] Low Temperature"<<endl;
        if(cin>>tempType && tempType<4){
            clearScreen();

            variable_error=false;
        }
        else{
            clearScreen();
            variable_error=true;
            cout<<"Invalid Type number, please Try Again"<<endl;

            
        }
        clearBuffer();
    }
    
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
    }
    Date temp_date(year,month,day,hour,minute);
    clearScreen();
    //set quantity
    variable_error=true;
    while (variable_error) {
        cout<<"Enter the quntity to transport"<<endl;
        if(cin>>temp_quantity){
            clearScreen();
            variable_error=false;
        }
        else
        {
            clearScreen();
            cout<<"Quantity not acceptable, please try again"<<endl;
        }
    }
    clearBuffer();
    Service *temp_service;
    switch (tempType) {
    case hazardous:
        temp_service=new  HazardousService(tempOrigin,tempDestination,0,0,intToType(tempType),on_queue,temp_date,client,temp_quantity,explosives);
        break;
    case lowTemperature:
        temp_service=new TemperatureService(tempOrigin,tempDestination,0,0,intToType(tempType),on_queue,temp_date,client,temp_quantity,_200);
        break;
    default:
        temp_service=new Service(tempOrigin,tempDestination,0,0,intToType(tempType),on_queue,temp_date,client,temp_quantity);
    }
    services->push_back(temp_service);
    return temp_service;
}

ostream& operator <<(ostream& os,Service &a){
    os<<"__________________________________________________"<<endl;
    os<<"Client: "+a.getClient()->getName()<<endl;
    os<<endl;
    os<<"Origin: "+a.getOrigin()<<endl;
    os<<"Destination: "+a.getDestination()<<endl;
    os<<endl;
    os<<"Initial Date: "+a.getDate().getDate()<<endl;
    os<<endl;
    os<<"Type of Transport: "+to_string(a.getType())<<endl;
    os<<"Quantity: "+to_string(a.getQuantity())<<endl;
    os<<endl;
    return os;
}

