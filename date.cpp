#include "date.h"

Date::Date() {

	time_t t = time(nullptr);
	struct tm* now = localtime(&t);
    typedef unsigned short date_u_short;
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
}


Date::Date(unsigned year, unsigned short month, unsigned short day, unsigned short hour, unsigned short minute) : year(year), month(month), day(day) ,hour(hour),minute(minute){
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

	return to_string(year) + "/" + to_string(month) + "/" + to_string(day);
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
unsigned Date::total_days(unsigned year, unsigned short month) {

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
			return true;
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

