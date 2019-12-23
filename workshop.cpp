#include "workshop.h"

Workshop::Workshop(string n = "unknown", car_brand b = car_brand::None, unsigned ua = 0)
{
	name = n;
	brand = b;
	unavailability = ua;
}

Workshop::Workshop(string n)
{
	name = n;
	brand = car_brand::None;
	unavailability = 0;
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
