#include "airport.h"
#include <math.h>
#include <iostream>
#define radius 3956

using namespace std;

airport::airport()
{
	//intentionally blank
}

//Every useful piece of info about the airport
airport::airport(
		string airportID,
		string name,
		string latitude,
		string longitude) {

	ID_ = airportID;
	name_ = name;
	latitude_ = latitude;
	longitude_ = longitude;
}

//convert decimal to radians
double airport::rad(double dec) {
	return dec * M_PI / 180.0;
}

//haversine formula the 2 decimal inputs
double airport::hav(double a, double b) {
	return pow(sin(rad(a - b) / 2), 2);
}

//This function can only be called with well-formed airports
int airport::find_distance(airport other) {
	double longA = stof(longitude_);
	double longB = stof(other.longitude_);
	double latA  = stof(latitude_);
	double latB  = stof(other.latitude_);

	//haversine function adapted from wikipedia page
	double a =  hav(latA, latB) +
				hav(longA, longB) *
				cos(rad(latB)) * 
				cos(rad(latA));
	return (int) 2.0 * radius * asin(sqrt(a));
}