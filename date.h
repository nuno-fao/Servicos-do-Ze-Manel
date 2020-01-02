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
	/**
* @brief Constructor with all data necessary
*
* Receives all the data it needs to construct an invalid Date properly
*
* @param error - string describing error
* @param year - year of the Date
* @param month - month of the Date
* @param day - day of the Date
* @param hour - hour of the Date
* @param minute - minutes of the Date
*/
    DateInvalid(string error, unsigned year,unsigned short month,unsigned short day,unsigned short hour,unsigned short minute):error(error),year(year), month(month), day(day) ,hour(hour),minute(minute){}
    string error; /*!< String describing error*/
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
/**
* Default constructor
*/
	Date();
/**
* Default destructor
*/
	~Date();
	/**
* @brief Constructor with data
*
* Constructs the object by receiving all the necessary information
* 
* @param year - year of the Date
* @param month - mpnth of the Date
* @param day - day of the Date
* @param hour - hour of the Date
* @param minute - minute of the Date
*/
    Date(unsigned year, unsigned short month, unsigned short day, unsigned short hour, unsigned short minute);
	/**
* @brief Constructor with string
*
* Constructs the object by parsing the received string
*
* @param date - string containing all the informatio in the format "yyyy/mm/dd/hh/mm"
*/
	Date(string date); // date must be in format "yyyy/mm/dd/hh/mm"

	// GET METHODS

/**
* @brief Gets year
*
* Returns the year of the Date
*
* @return Returns the year of the Date
*/
	unsigned int getYear() const;
	/**
* @brief Gets month
*
* Returns the month of the Date
*
* @return Returns the month of the Date
*/
	unsigned short getMonth() const;
	/**
* @brief Gets day
*
* Returns the day of the Date
*
* @return Returns the day of the Date
*/
	unsigned short getDay() const;
	/**
* @brief Gets hour
*
* Returns the hour of the Date
*
* @return Returns the hour of the Date
*/
    unsigned short getHour() const;
	/**
* @brief Gets minutes
*
* Returns the minutes of the Date
*
* @return Returns the minutes of the Date
*
*/
    void setHour(int hour);
    unsigned short getMinute() const;
	/**
* @brief Gets date as a string
*
* Returns the date as a string in the format "yyyy/mm/dd/hh/mm" for file-writing purposes
*
* @return the date as a string in the format "yyyy/mm/dd/hh/mm"
*/
    string getDate() const;
	/**
* @brief Gets date as a string
*
* Returns the date as a string in the format "yyyy/mm/dd/hh/mm" for printing purposes
*
* @return the date as a string in the format "yyyy/mm/dd/hh/mm"
*/
    string getDateWHour() const;

	// SET METHODS

/**
* @brief Sets year
*
* Sets the Date's year
*
* @param year - year to be set
* @return Returns nothing
*/
	void setYear(unsigned year);
	/**
* @brief Sets month
*
* Sets the Date's month
*
* @param month - month to be set
* @return Returns nothing
*/
	void setMonth(unsigned short month);
/**
* @brief Sets day
*
* Sets the Date's day
*
* @param day - day to be set
* @return Returns nothing
*/
	void setDay(unsigned short day);
/**
* @brief Sets date
*
* Sets the date by receiving all the data necessary
*
* @param year - year to be set
* @param month - month to be set
* @param day - day to be set
* @return Returns nothing
*/
	void setDate(unsigned year, unsigned short month, unsigned short day);

	// OTHER METHODS

/**
* @brief Verifies Date
*
* Verifies if the Date is valid
*
* @return Returns true if the Date is valid
*/
	bool isValid();

	/**
* @brief Prints Date
*
* Prints the Date by outputting to the screen in the format "yyyy/mm/dd"
*
* @return Returns nothing
*/
	void show() const;

};

/**
* @brief Operator < overloading
*
* Overload of < operator for comparisons. A Date is < if it is prior
*
* @param date1 - Date Object to be compared
* @param date2 - Date Object to be compared
* @return Returns true if the date1 is prior to date2 
*/
bool operator < (Date const& date1, Date const& data2);

/**
* @brief Operator - overloading
*
* Overload of - operator to enable calculations with Dates
*
* @param date1 - Date Object to be compared
* @param date2 - Date Object to be compared
* @return Returns a float that represents the difference between the two dates in minutes
*/
float operator - (Date &date1, Date &data2);
/**
* @brief Returns number of days
*
* Calculates and returns the number of days the month of that year has
*
* @param year - year of the date
* @param month - month of the date
* @return Returns the total number of days the month of the given year contains
*/
unsigned total_days(unsigned year, unsigned short month);

Date operator + (Date &date1, int hours);
