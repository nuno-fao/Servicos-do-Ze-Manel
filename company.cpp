#include "company.h"


Company *Company::getCompany(){
    if (company==nullptr)
        company = new Company();
    return company;
}

Company::Company(){}

Company::~Company(){
    if(getCompany()->services_on_queue_changed){
        Service::saveToFile(&services_finished,&services_on_transit,&services_on_queue);
    }
    Client::saveToFile(clients);
    Truck::saveToFile(&trucks);
	saveStats();
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
				//adicionar á lista
				switch ((*it)->getType()) {
				case type::ordinary:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12) == unsigned(statNorm.back().first)) {
                        statNorm.back().second += double((*it)->getTotalPrice());
					}
					else {
						statNorm.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, (*it)->getTotalPrice()));
						statHaz.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statAnim.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statCong.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
					}
					break;
				case type::hazardous:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear()*12) == unsigned(statHaz.back().first)) {
                        statHaz.back().second += double((*it)->getTotalPrice());
					}
					else {
						statNorm.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statHaz.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, (*it)->getTotalPrice()));
						statAnim.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statCong.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
					}
					break;
				case type::animal:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12) == unsigned(statAnim.back().first)) {
                        statAnim.back().second += double((*it)->getTotalPrice());
                    }
					else {
						statNorm.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statHaz.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statAnim.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, (*it)->getTotalPrice()));
						statCong.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
					}
					break;
				case type::lowTemperature:
                    if (((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12) == unsigned(statHaz.back().first)) {
                        statCong.back().second += double((*it)->getTotalPrice());
					}
					else {
						statNorm.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statHaz.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statAnim.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, 0));
						statCong.push_back(make_pair((*it)->getADate()->getMonth() + (*it)->getADate()->getYear() * 12, (*it)->getTotalPrice()));
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
                Company::getCompany()->services_on_queue_changed=true;
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
