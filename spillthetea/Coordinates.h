#pragma once
#include <iostream>
using namespace std;

class Coordinates {
private:
	double longitude, latitude;
public:
	Coordinates();
	Coordinates(double, double);
	Coordinates(const Coordinates& other);
	void setLongitude(double);
	void setLatitude(double);
	double getLongitude();
	double getLatitude();
	double distance(const Coordinates& other);
};