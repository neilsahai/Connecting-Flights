#pragma once
#include <string>

using namespace std;

class airport {
public:
	string ID_;
	string name_;
	string latitude_;
	string longitude_;


    airport();

    airport(
    	string ID,
		string name,
		string latitude,
		string longitude);


	double rad(double dec);

	double hav(double a, double b);

    //find distance from this airport to other airport
    int find_distance(airport other);
};