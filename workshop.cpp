#include "workshop.h"

Workshop::Workshop(string n = "unknown", car_brand b = car_brand::None, unsigned ua = 0, wait_queue wl)
{
	name = n;
	brand = b;
	unavailability = ua;
	waiting_line = wl;
}

Workshop::Workshop(string n)
{
	name = n;
	brand = car_brand::None;
	unavailability = 0;

	Truck* default_truck = NULL;
	Date default_date;
	pair<Truck*, Date> default_pair (default_truck, default_date);
	waiting_line.push(default_pair);
}

string Workshop::getName() const
{
	return name;
}

car_brand Workshop::getBrand() const
{
	return brand;
}

unsigned int Workshop::getUnavailability() const
{
	return unavailability;
}

queue<pair<Truck*, Date>> Workshop::getWaitingLine() const
{
	return waiting_line;
}

void Workshop::setName(string n)
{
	name = n;
}

void Workshop::setBrand(car_brand b)
{
	brand = b;
}

void Workshop::setUnavailability(unsigned int ua)
{
	unavailability = ua;
}

void Workshop::setWaitingLine(wait_queue wl)
{
	waiting_line = wl;
}
