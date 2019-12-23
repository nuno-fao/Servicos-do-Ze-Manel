#include "misc.h"
#include <cmath>


#ifdef _WIN32
void clearScreen() {
    system("cls"); system("cls");
    Company::getCompany()->updateServicesSituation();
    Company::getCompany()->updateTruckSituation();
}
#endif

#ifdef linux
void clearScreen() {
    system("clear"); system("clear");
    Company::getCompany()->updateServicesSituation();
    Company::getCompany()->updateTruckSituation();
}
#endif

vector<string> vectorString(string stringToVectorize, string separador) {
    vector<string> ret;
    size_t startPos = 0, endPos = 0;
    while (endPos < stringToVectorize.length()) {
        endPos = stringToVectorize.find(separador, startPos);
        if (endPos == stringToVectorize.npos) {
            string t=stringToVectorize.substr(startPos);
            if(t.size() && t!=" ")
                ret.push_back(stringToVectorize.substr(startPos));
            break;
        }
        else {
            string t=stringToVectorize.substr(startPos, endPos - startPos);
            if(t.size() && t!=" ")
                ret.push_back(stringToVectorize.substr(startPos, endPos - startPos));
        }
        startPos = endPos + separador.length();
    }
    if (ret.size() >= 3) {
        if (ret[2].size() == 0) {
            ret[2] = "-";
        }
    }
    return ret;
}

void clearBuffer(void) {
    cin.clear();
    cin.ignore(1000, '\n');
}

bool strIsNumber(string str) {
    if (str.size() == 0) {
        return false;
    }
    for (unsigned i = 0; i < str.length(); i++) {
        if (!isdigit(str[i]) && str.at(i)!=' ') {
            if (str[i] != '.') {
                return false;
            }
        }
    }
    return true;
}

bool strIsChar(string str) {
    if (str.size() == 0) {
        return false;
    }
    unsigned non_alfa=0;
    for (unsigned i = 0; i < str.length(); i++) {
        if (!((str.at(i)<='z' && str.at(i)>='a') || (str.at(i)<='Z' && str.at(i)>='A')) && ((str.at(i)!='.') && (str.at(i)!=' '))) {
            return false;
        }
        if(str.at(i)=='.'||str.at(i)==' ')
            non_alfa++;
    }

    if((str.size())==non_alfa)
        return false;
    return true;

}

unsigned chooseOptionNumber(unsigned minimum, unsigned maximum, string Message, unsigned maxPerPage,vector<string> *more_options){
    clearScreen();
    size_t vector_size=0;
    if(more_options!=nullptr)
        vector_size=more_options->size();
    unsigned option;
    unsigned i=0;
    unsigned adder=0;
    while (true) {
        cout<<Message<<endl;
        unsigned last_i=i;
        stringstream out;

        //prints the number of number specified in maxPerPage
        for(;i+minimum<maximum && unsigned(abs(signed(i-last_i)))<maxPerPage;i++){
            out<<"["+to_string(unsigned(abs(signed(i-last_i)))%maxPerPage)+"] "+to_string(i+minimum)<<endl;
        }

        //verifica se chegou ao fim da sequencia, se sim imprime a opção go next page
        if(i+minimum<maximum){
            out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+1)+"] Go Next Page"<<endl;
            if(signed(i-maxPerPage)>=0)
                out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+2)+"] Go Last Page"<<endl;
        }
        else
            out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+2)+"] Go Last Page"<<endl;

        //verifica se exite mais opcoes a imprimir e imprime-as
        if(more_options!=nullptr)
            for(auto it:*more_options){
                out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+2+(++adder))+"] "+it<<endl;
            }

        adder=0;
        cout<<out.str();
        bool error=true;
        while (error) {
            if(cin>>option && signed(option-1-vector_size)<=signed(unsigned(abs(signed(i-last_i))))){
                if(option<unsigned(abs(signed(i-last_i)))){
                    return option+minimum+i-unsigned(abs(signed(i-last_i)));
                }
                else if(signed(i-(maxPerPage+unsigned(abs(signed(i-last_i)))))>=0 && option-1==unsigned(abs(signed(i-last_i))))
                    i-=maxPerPage+unsigned(abs(signed(i-last_i)));
                else if(signed(i-(maxPerPage+unsigned(abs(signed(i-last_i)))))<0 && option-1==unsigned(abs(signed(i-last_i))))
                    i=0;
                else if(option==unsigned(abs(signed(i-last_i))))
                    i=min(maximum-maxPerPage+1,i+minimum)-minimum;
                else if(option>(unsigned(abs(signed(i-last_i)))+1))
                    return maximum;
                error=false;
                clearScreen();
            }
            else{
                clearScreen();
                cout<<"Something went wrong, please try again"<<endl;
                cout<<Message<<endl;
                cout<<out.str();
            }
        }
    }
}


int binaryCustomfind(vector<Client*> *vetor, unsigned val){

    size_t inf = 0;     // limite inferior (o primeiro índice de vetor em C é zero          )
    size_t sup = vetor->size()-1; // limite superior (termina em um número a menos. 0 a 9 são 10 números)
    size_t meio;
    while ((inf <= sup) && vetor->size()>0)
    {
        meio = (inf + sup)/2;
        if (val == vetor->at(meio)->getNif())
            return int(meio);
        if (val < vetor->at(meio)->getNif())
            sup = meio-1;
        else
            inf = meio+1;
    }
    return -1;   // não encontrado
}


bool checkNif(int nif) {

    if (nif < 100000000 || nif > 999999999) // The number has to be 9 digits long
        return false;
    return true;
}

void checkIfOut(string &temp){
    if(temp=="!q"){
        string t;
        cout<<"Are u sure you want to exit? ((\"y\"/enter) to exit)"<<endl;
        int x=cin.get();
        if(x=='y'|| x=='\n'){
            clearScreen();
            throw exception();
        }
        clearScreen();
    }
}

void printClassVector(vector<string> *t){
    for(auto i:*t){
        cout<<i<<endl;
    }
}

void enter_to_exit()
{
    do
    {
        cout << '\n' << "Press enter to continue...";
    } while (cin.get() != '\n');
    clearScreen();
}

bool checkLicense(string license, vector<Truck*>* trucks) {
    vector<string> auxVec;
    if (license.size() == 8) {
        auxVec=vectorString(license, "-");
        if (auxVec.size() == 3) {
            unsigned short num=0, letters=0;
            for (size_t i = 0; i != auxVec.size();i++) {
                if (strIsNumber(auxVec[i])) {
                    if (stoi(auxVec[i]) < 100 && stoi(auxVec[i])>0) {
                        num++;
                    }
                    else {
                        cout << "WRONG FORMAT!!!!\nMust be in XX-YY-ZZ without any other character before or after. 2 pairs of numbers and 1 pair of capital letters\n";
                        cout << "Your input: " << license << endl;
                        enter_to_exit();
                        return false;
                    }
                }
                else {
                    if (isupper(auxVec[i][0]) && isupper(auxVec[i][1])) {
                        letters++;
                    }
                    else {
                        cout << "WRONG FORMAT!!!!\nMust be in XX-YY-ZZ without any other character before or after. 2 pairs of numbers and 1 pair of capital letters\n";
                        cout << "Your input: " << license << endl;
                        enter_to_exit();
                        return false;
                    }
                }
            }
            if (num == 2 && letters == 1) {
                for (auto it : *trucks) {
                    if (it->getlicense() == license) {
                        cout << "The truck with license " << license << " already exists in our database\n";
                        enter_to_exit();
                        return false;
                    }
                }
                return true;
            }
        }
    }
    cout << "WRONG FORMAT!!!!\nMust be in XX-YY-ZZ without any other character before or after. 2 pairs of numbers and 1 pair of capital letters\n";
    cout << "Your input: " << license << endl;
    enter_to_exit();
    return false;
}

bool checkLicenseV2(string license) {
    vector<string> auxVec;
    if (license.size() == 8) {
        auxVec = vectorString(license, "-");
        if (auxVec.size() == 3) {
            unsigned short num = 0, letters = 0;
            for (size_t i = 0; i != auxVec.size(); i++) {
                if (strIsNumber(auxVec[i])) {
                    if (stoi(auxVec[i]) < 100 && stoi(auxVec[i]) > 0) {
                        num++;
                    }
                    else {
                        cout << "WRONG FORMAT!!!!\nMust be in XX-YY-ZZ without any other character before or after. 2 pairs of numbers and 1 pair of capital letters\n";
                        cout << "Your input: " << license << endl;
                        enter_to_exit();
                        return false;
                    }
                }
                else {
                    if (isupper(auxVec[i][0]) && isupper(auxVec[i][1])) {
                        letters++;
                    }
                    else {
                        cout << "WRONG FORMAT!!!!\nMust be in XX-YY-ZZ without any other character before or after. 2 pairs of numbers and 1 pair of capital letters\n";
                        cout << "Your input: " << license << endl;
                        enter_to_exit();
                        return false;
                    }
                }
            }
            if (num == 2 && letters == 1) {
                return true;
            }
        }
    }
    cout << "WRONG FORMAT!!!!\nMust be in XX-YY-ZZ without any other character before or after. 2 pairs of numbers and 1 pair of capital letters\n";
    cout << "Your input: " << license << endl;
    enter_to_exit();
    return false;
}

long askForId(string classToAsk,string what_to_do, string identifier){
    string id;
    cout<<"Which "+classToAsk+" you want to "+what_to_do+" ( write "+classToAsk+"'s "+identifier+" ):"<<endl;
    if(cin>>id){
        if(strIsNumber(id) && stoi(id)>=0){
            long t_id=stol(id);
            return t_id;
        }
    }

    if(id=="!q"){
        clearScreen();
        return  -1;
    }
    clearScreen();
    cout<<identifier+" not acceptable"<<endl;
    return -2;

}



bool cmpOnQueue(Service *a,Service *b){
    return *a->getIDate() <*b->getIDate();
}

bool cmpOnTransit(Service *a,Service *b){
    return *b->getIDate() <*a->getIDate();
}

bool overAYear(Date date) {
    Date aux;
    aux.setYear(aux.getYear() - 1);
    return !(aux < date);
}