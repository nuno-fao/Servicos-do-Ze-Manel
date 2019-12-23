#include "workshop.h"

Workshop::Workshop(string n, car_brand b, unsigned ua)
{
	name = n;
	brand = b;
	unavailability = ua;
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
