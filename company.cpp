#include "company.h"


Company *Company::getCompany(){
    if (company==nullptr)
        company = new Company();
    return company;
}

Company::Company(){

}

Company::~Company(){
    Service::saveToFile(&services_finished,&services_on_transit,&services_on_queue);
    Client::saveToFile(clients);
    Truck::saveToFile(&trucks);
    Driver::saveToFile();
	saveStats();
    Workshop::saveToFile(&workshop_line);
    for(auto i:clients){
        i->~Client();
    }
    for(auto i:trucks){
        i->~Truck();
    }
    cout<<"Salvo com sucesso"<<endl;
}

list<Service*> *Company::getVectorServicesFinished(){
    return &services_finished;
}
vector<Service*> *Company::getVectorServicesOnTransit(){
    return &services_on_transit;
}
vector<Service*> *Company::getVectorServicesOnQueue(){
    return &services_on_queue;
}

vector<Client*> *Company::getVectorClients(){
    return &clients;
}
vector<Truck*> *Company::getVectorTrucks(){
    return &trucks;
}

Client *Company::getClient(unsigned nif){
    size_t l=0;
    vector<Client*> *temp(Company::getCompany()->getVectorClients());
    if(!temp->size())
        throw NotAClient(nif,"Couldn't find the client");
    size_t r=(*temp).size()-1;
    while (l <= r) {
        size_t m = l + (r - l) / 2;
        if (temp->at(m)->getNif() == nif)
            return Company::getCompany()->getVectorClients()->at(m);
        if (temp->at(m)->getNif() < nif)
            l = m + 1;
        else if(m>0)
            r = m - 1;
        else
            break;
    }
    throw NotAClient(nif,"Couldn't find the client");
}
Truck *Company::getTruck(string license){
    size_t l=0;
    string t;
    vector<Truck*> *vect(Company::getCompany()->getVectorTrucks());
    if(!vect->size())
        throw TruckDoNotExist("Couldn't find the Truck",license);
    size_t r=vect->size()-1;
    while (l <= r) {
        size_t m = l + (r - l) / 2;
        t=vect->at(m)->getlicense();
        if (vect->at(m)->getlicense() == license)
            return vect->at(m);
        if (vect->at(m)->getlicense() < license)
            l = m + 1;
        else if(m>0)
            r = m - 1;
        else
            break;
    }
    throw TruckDoNotExist("Couldn't find the Truck",license);
}


//Service *getService(unsigned id){
//
//
//}

void Company::updateTruckSituation(){
    time_t rawtime;
    struct tm *now;
    time( &rawtime );
    now = localtime( &rawtime );
    Date f(unsigned(now->tm_year-100),1+date_u_short(now->tm_mon),date_u_short(now->tm_mday),date_u_short(now->tm_hour),date_u_short(now->tm_min));

    if(services_on_transit.size()){
		auto it = services_on_transit.begin();
        while(it!= services_on_transit.end()){
            if(*(*it)->getADate()<f){

                for(auto x =(*it)->getTrucks()->begin();x!=(*it)->getTrucks()->end();x++)
                {
                    x->first->setavailable(true);
					auto o = x->first->getServices()->begin();
                    while(o!=x->first->getServices()->end()){
                        if((*o)->getId()==(*it)->getId()){
                            o=x->first->getServices()->erase(o);
                            break;
                        }
						else {
							o++;
							continue;
						}
                    }
                    if(!x->first->getServices()->size()){
                        x->first->setregistered(false);
                    }
                }
                //adicionar à lista
				switch ((*it)->getType()) {
				case type::ordinary:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1) == unsigned(statNorm.begin()->first)) {
                        statNorm.begin()->second += double((*it)->getTotalPrice());
					}
					else {
                        statNorm.insert(statNorm.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, (*it)->getTotalPrice()));
                        statHaz.insert(statHaz.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statAnim.insert(statAnim.begin(), make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statCong.insert(statCong.begin(), make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                    }
					break;
				case type::hazardous:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear()*12-1) == unsigned(statHaz.begin()->first)) {
                        statHaz.begin()->second += double((*it)->getTotalPrice());
					}
					else {
                        statNorm.insert(statNorm.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statHaz.insert(statHaz.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, (*it)->getTotalPrice()));
                        statAnim.insert(statAnim.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statCong.insert(statCong.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
					}
					break;
				case type::animal:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1) == unsigned(statAnim.begin()->first)) {
                        statAnim.begin()->second += double((*it)->getTotalPrice());
                    }
					else {
                        statNorm.insert(statNorm.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statHaz.insert(statHaz.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statAnim.insert(statAnim.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, (*it)->getTotalPrice()));
                        statCong.insert(statCong.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
					}
					break;
				case type::lowTemperature:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1) == unsigned(statHaz.begin()->first)) {
                        statCong.begin()->second += double((*it)->getTotalPrice());
					}
					else {
                        statNorm.insert(statNorm.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statHaz.insert(statHaz.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statAnim.insert(statAnim.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, 0));
                        statCong.insert(statCong.begin(),make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12-1, (*it)->getTotalPrice()));
					}
					break;
				}
                services_finished.push_back(*it);
                it=services_on_transit.erase(it);
                Company::getCompany()->services_on_queue_changed=true;
            }
            else{
				it++;
                continue;
            }
        }
    }
    if(services_on_queue.size()){
		auto it = services_on_queue.begin();
        while(it!= services_on_queue.end()){
            if(*(*it)->getIDate()<f){

                for(auto x:*(*it)->getTrucks())
                {
                    x.first->setavailable(false);
                    x.first->setCargo(x.second);
                }
                services_on_transit.push_back(*it);
                it=services_on_queue.erase(it);
                Company::getCompany()->services_on_queue_changed=true;
            }
            else{
				it++;
                continue;
            }
        }
    }
    sort(services_on_queue.begin(),services_on_queue.end(),cmpOnQueue);
    sort(services_on_transit.begin(),services_on_transit.end(),cmpOnTransit);


}

void Company::updateServicesSituation(){
    time_t rawtime;struct tm *now;std::time( &rawtime );now = localtime( &rawtime );
    Date f(unsigned(now->tm_year-100),1+date_u_short(now->tm_mon),date_u_short(now->tm_mday),date_u_short(now->tm_hour),date_u_short(now->tm_min));
    if(services_on_transit.size()){
        for(auto it=services_on_transit.begin(); it!= services_on_transit.end();it++){
            if(*(*it)->getADate()<f){
                (*it)->setState(finished);
                Date a=*(*it)->getADate();
                int min=*(*it)->getADate()-*(*it)->getIDate();
                int hours=min/60;
                cout<<"min: "<<min<<endl;
                cout<<"hour: "<<hours<<endl;
                Company::getCompany()->services_on_queue_changed=true;
                for(auto i:(*it)->drivers){
                    Company::getCompany()->driver_queue.push(pair<int,float>(i.first,i.second));
                    Driver tmp=drivers.find(Driver(i.first,"",i.second));
                    if(tmp.getNif()==0){
                        BSTItrIn<Driver> it(*Company::getCompany()->getDrivers());
                        try {
                            while (!it.isAtEnd()) {
                                if(it.retrieve().getNif()==i.first){
                                    tmp=it.retrieve();
                                    break;
                                }
                                it.advance();
                            }
                        } catch (...) {
                        }
                    }
                    drivers.remove(tmp);
                    if(min%60!=0){
                        hours++;
                    }
                    cout<<"hour after: "<<hours<<endl;
                    cout<<"plus: "<<tmp.getServiceHours()+float(hours)<<endl;

                    tmp.setServiceHours(tmp.getServiceHours()+float(hours));
                    cin>>hours;
                    drivers.insert(tmp);
                }
            }
            else{
                continue;
            }
        }
    }

    if(services_on_queue.size()){
        for(auto it=services_on_queue.begin(); it!= services_on_queue.end();it++){
            if(*(*it)->getIDate()<f){
                (*it)->setState(on_transit);
                for(size_t i=0;i<(*it)->getTrucks()->size();i++){
                    (*it)->drivers.push_back((Company::getCompany()->driver_queue.front()));
                    Company::getCompany()->driver_queue.pop();
                }
                Company::getCompany()->services_on_queue_changed=true;
            }
            else{
                continue;
            }
        }
    }


}

void Company::loadStats() {
	ifstream statfile;
	string aux, separator = "; ";
	int ano_mes;
	vector<string> auxVec;
	statfile.open("files//stats.txt");
	while (getline(statfile, aux)) {
		getline(statfile, aux);
        ano_mes = stoi(aux);
		getline(statfile, aux);
		auxVec = vectorString(aux,separator);
		statHaz.push_back(make_pair(ano_mes,stod(auxVec[0])));
		statCong.push_back(make_pair(ano_mes, stod(auxVec[1])));
		statAnim.push_back(make_pair(ano_mes, stod(auxVec[2])));
		statNorm.push_back(make_pair(ano_mes, stod(auxVec[3])));
	}
}

BST<Driver> *Company::getDrivers(){
    return &drivers;
}

priority_queue<Workshop*>* Company::getWorkshopLine()
{
    return &workshop_line;
}

void Company::saveStats() {
	ofstream statfile;
    string aux, separator = "; ";
	vector<string> auxVec;
	statfile.open("files//stats.txt");
	for (unsigned i = 0; i < statCong.size(); i++) {
		statfile << ":::::::::::::::::::" << endl;
		statfile << statHaz[i].first << endl;
		statfile << statHaz[i].second << "; " << statCong[i].second << "; " << statAnim[i].second << "; " << statNorm[i].second << endl;
	}
	statfile.close();
}

int clientActiviyHash::operator() (const Client* cr) const
{
	return cr->getNif() % 1000 + cr->getName().size();
}

bool clientActiviyHash::operator() (const Client* cr1, const Client* cr2) const
{
	return cr1->getNif() == cr2->getNif();
}

void Company::removeClientFromHash(unsigned nif) {
    auto it = clientHash.begin();
    for (it; it != clientHash.end(); it++) {
        if ((*it)->getNif()==nif && (*it)->getServicesVector()->size()==0) {
            clientHash.erase(it);
            return;
        }
    }
}

void Company::eraseClientFromHash(unsigned nif) {
	auto it = clientHash.begin();
	for (it; it != clientHash.end(); it++) {
		if ((*it)->getNif() == nif) {
			clientHash.erase(it);
			return;
		}
	}
}
