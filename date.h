#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>


#include "misc.h"

using namespace std;

class Date {
private:
	unsigned total_days(unsigned year, unsigned short month);
	unsigned year;
	unsigned short month;
	unsigned short day;

public:
	Date();
	~Date();
	Date(unsigned year, unsigned short month, unsigned short day);
	Date(string date); // date must be in format "yyyy/mm/dd"

// GET methods

	unsigned int getYear() const;
	unsigned short getMonth() const;
	unsigned short getDay() const;
	string getDate() const; // returns the date in format "yyyy/mm/dd"

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