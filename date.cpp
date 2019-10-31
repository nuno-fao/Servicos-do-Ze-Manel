#include "date.h"


Date::Date() {

    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    day = date_u_short((now->tm_mday));
    month = date_u_short(now->tm_mon + 1);
    year = date_u_short(now->tm_year + 1900);
}

Date::Date(string date) {
    typedef unsigned short date_u_short;
    vector<string> dateVector;
    dateVector = vectorString(date, "/");
    year = date_u_short(stoi(dateVector.at(0)));
    month = date_u_short(stoi(dateVector.at(1)));
    day = date_u_short(stoi(dateVector.at(2)));
    hour = date_u_short(stoi(dateVector.at(3)));
    minute = date_u_short(stoi(dateVector.at(4)));
}


Date::Date(unsigned year, unsigned short month, unsigned short day, unsigned short hour, unsigned short minute) : month(month), day(day) ,hour(hour),minute(minute){
    if(to_string(year).size()<=2)
        this->year=year+2000;
    isValid();
}
Date::~Date() {

}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const {

    return day;
}


unsigned short Date::getMonth() const {

    return month;
}

unsigned Date::getYear() const {

    return year;
}

unsigned short Date::getHour() const{

    return hour;
}
unsigned short Date::getMinute() const{

    return minute;
}

string Date::getDate() const {

    return to_string(year) + "/" + to_string(month) + "/" + to_string(day)+"/"+to_string(hour)+"/"+to_string(minute);
}

string Date::getDateWHour() const{
    string t="0";
    string tempMinute=to_string(minute);
    if(tempMinute.size()==1)
        t+=to_string(minute);
    else {
        t=to_string(minute);
    }
    return to_string(year) + "/" + to_string(month) + "/" + to_string(day)+",  "+to_string(hour)+":"+t;
}
/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short day) {

    this->day = day;
}

void Date::setMonth(unsigned short month) {

    this->month = month;
}

void Date::setYear(unsigned year) {

    this->year = year;
}

void Date::setDate(unsigned year, unsigned short month, unsigned short day) {

    this->year = year; this->month = month; this->day = day;
}

/*********************************
 * Other methods
 ********************************/

//function to calculate total amount of days of a given month
unsigned total_days(unsigned year, unsigned short month) {

    if (month == 2) {
        return (year % 400 == 0 || year % 100 != 0) && (year % 4 == 0) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

//check if instance date is valid
bool Date::isValid() {

    if (month > 0 && month <= 12) {
        if (day > 0 && day <= total_days(year, month)) {
            if(hour>=0 && hour<=23){
                if(minute>=0 && minute<=59)
                    return true;
                else
                    throw DateInvalid("Invalid minutes: "+to_string(minute),year,month,day,hour,minute);
            }
            else
                throw DateInvalid("Invalid Hour: "+to_string(hour),year,month,day,hour,minute);
        }
        else
            throw DateInvalid("Invalid Day: "+to_string(day),year,month,day,hour,minute);
    }
    else
        throw DateInvalid("Invalid Month: "+to_string(month),year,month,day,hour,minute);
}


/*********************************
 * Show Date
 ********************************/

//prints date year/month/day
void Date::show() const {
    cout << to_string(year) + "/" + to_string(month) + "/" + to_string(day) << endl;
}

bool operator < (Date const& date1, Date const& data2) {

    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() < data2.getDay()) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (date1.getMonth() < data2.getMonth()) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (date1.getYear() < data2.getYear()) {
        return true;
    }
    return false;
}

bool operator > (Date const& date1, Date const& data2) {

    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() > data2.getDay()) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (date1.getMonth() > data2.getMonth()) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (date1.getYear() > data2.getYear()) {
        return true;
    }
    return false;
}
bool operator >= (Date const& date1, Date const& data2) {

    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() < data2.getDay()) {
                return false;
            }
            else {
                return true;
            }
        }
        else if (date1.getMonth() < data2.getMonth()) {
            return false;
        }
        else {
            return true;
        }
    }
    else if (date1.getYear() < data2.getYear()) {
        return false;
    }
    return true;
}
bool operator <= (Date const& date1, Date const& data2) {
    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() > data2.getDay()) {
                return false;
            }
        }
        else if (date1.getMonth() > data2.getMonth()) {
            return false;
        }
    }
    else if (date1.getYear() > data2.getYear()) {
        return false;
    }
    return true;
}
bool operator == (Date const& date1, Date const& data2) {

    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() == data2.getDay()) {
                return true;
            }
        }
    }
    return false;
}
bool operator != (Date const& date1, Date const& data2) {

    if (date1.getYear() == data2.getYear()) {
        if (date1.getMonth() == data2.getMonth()) {
            if (date1.getDay() == data2.getDay()) {
                return false;
            }
        }
    }
    return true;
}



const int monthDays[12] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};


int countLeapYears(Date d)
{
    unsigned years = d.getYear();
    if (d.getMonth() <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2)
{

    long int n1 = dt1.getYear()*365 + dt1.getDay();
    for (int i=0; i<dt1.getMonth() - 1; i++)
        n1 += monthDays[i];
    n1 += countLeapYears(dt1);

    long int n2 = dt2.getYear()*365 + dt2.getDay();
    for (int i=0; i<dt2.getMonth() - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    return int(n2 - n1);
}

double operator - (Date  &dt1, Date  &dt2){

    float n1 = dt1.getYear()*365 + dt1.getDay();

    for (int i=0; i<dt1.getMonth() - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(dt1);

    float n2 = dt2.getYear()*365 + dt2.getDay();
    for (int i=0; i<dt2.getMonth() - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    double t=double((n2*24+dt2.getHour()+double(dt2.getMinute()/60.0)) - (n1*24+dt1.getHour()+double(dt1.getMinute()/60.0)));
    return  t;
}
