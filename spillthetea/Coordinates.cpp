#include"Coordinates.h"
#include<cmath>

Coordinates::Coordinates() {
	latitude = 0.0;
	longitude = 0.0;
}

Coordinates::Coordinates(double latitude, double longitude) {
	this->latitude = latitude;
	this->longitude = longitude;
}
Coordinates::Coordinates(const Coordinates& other) {
	this->latitude = other.latitude;
	this->longitude = other.longitude;
}
void Coordinates::setLongitude(double lon) {
	longitude = lon;
}
void Coordinates::setLatitude(double lat) {
	latitude = lat;
}
double Coordinates::getLongitude() {
	return longitude;
}
double Coordinates::getLatitude() {
	return latitude;
}
double Coordinates::distance(const Coordinates &other) {
	double latdiff = this->latitude - other.latitude;
	double londiff = this->longitude - other.longitude;
	return pow (pow (latdiff, 2) + pow (londiff, 2), 0.5);
}