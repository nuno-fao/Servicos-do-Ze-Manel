#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>


#include "misc.h"

using namespace std;

typedef unsigned short date_u_short;

class DateInvalid{
public:
    DateInvalid(string error,unsigned year,unsigned short month,unsigned short day,unsigned short hour,unsigned short minute):error(error),year(year), month(month), day(day) ,hour(hour),minute(minute){}
    string error;
    unsigned year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
};

class Date {
private:
	unsigned year;
	unsigned short month;
	unsigned short day;
    unsigned short hour;
    unsigned short minute;

public:
	Date();
	~Date();
    Date(unsigned year, unsigned short month, unsigned short day,unsigned short hour,unsigned short minute);
	Date(string date); // date must be in format "yyyy/mm/dd"

// GET methods

	unsigned int getYear() const;
	unsigned short getMonth() const;
	unsigned short getDay() const;
    unsigned short getHour() const;
    unsigned short getMinute() const;
    string getDate() const; // returns the date in format "yyyy/mm/dd/hh/mm"
    string getDateWHour() const;

// SET methods

	void setYear(unsigned year);
	void setMonth(unsigned short month);
	void setDay(unsigned short day);
	void setDate(unsigned year, unsigned short month, unsigned short day);


	//other methods

	bool isValid();
	// out methods */
	void show() const;
	// shows the date on the screen in format "yyyy/mm/dd"

};
bool operator < (Date const& date1, Date const& data2);
bool operator > (Date const& date1, Date const& data2);
bool operator >= (Date const& date1, Date const& data2);
bool operator <= (Date const& date1, Date const& data2);
bool operator == (Date const& date1, Date const& data2);
float operator - (Date &date1, Date &data2);
unsigned total_days(unsigned year, unsigned short month);
