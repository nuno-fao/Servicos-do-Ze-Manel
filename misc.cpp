#include "misc.h"
#include <cmath>


#ifdef _WIN32
void clearScreen() {
    system("cls"); system("cls");
}
#endif

#ifdef linux
void clearScreen() {
    system("clear"); system("clear");
}
#endif

vector<string> vectorString(string stringToVectorize, string separador) {
    vector<string> ret;
    size_t startPos = 0, endPos = 0;
    while (endPos < stringToVectorize.length()) {
        endPos = stringToVectorize.find(separador, startPos);
        if (endPos == stringToVectorize.npos) {
            ret.push_back(stringToVectorize.substr(startPos));
            break;
        }
        else {
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
        if (!isdigit(str[i])) {
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

unsigned chooseOptionNumber(unsigned minimum, unsigned maximum, string Message, unsigned maxPerPage){
    clearScreen();
    unsigned option;
    unsigned i=0;
    while (true) {
        cout<<Message<<endl;
        unsigned last_i=i;
        stringstream out;
        for(;i+minimum<maximum && unsigned(abs(signed(i-last_i)))<maxPerPage;i++){
            out<<"["+to_string(unsigned(abs(signed(i-last_i)))%maxPerPage)+"] "+to_string(i+minimum)<<endl;
        }
        if(i+minimum<maximum){
            out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+1)+"] Go Next Page"<<endl;
            if(signed(i-maxPerPage)>=0)
                out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+2)+"] Go Last Page"<<endl;
        }
        else
            out<<"["+to_string((unsigned(abs(signed(i-last_i)))-1)%maxPerPage+2)+"] Go Last Page"<<endl;
        cout<<out.str();
        bool error=true;
        while (error) {
            if(cin>>option && signed(option-1)<=signed(unsigned(abs(signed(i-last_i))))){
                if(option<unsigned(abs(signed(i-last_i)))){
                    return option+minimum+i-unsigned(abs(signed(i-last_i)));
                }
                else if(signed(i-(maxPerPage+unsigned(abs(signed(i-last_i)))))>=0 && option-1==unsigned(abs(signed(i-last_i))))
                    i-=maxPerPage+unsigned(abs(signed(i-last_i)));
                else if(signed(i-(maxPerPage+unsigned(abs(signed(i-last_i)))))<0 && option-1==unsigned(abs(signed(i-last_i))))
                    i=0;
                else if(option==unsigned(abs(signed(i-last_i))))
                    i=min(maximum-maxPerPage+1,i+minimum)-minimum;
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
