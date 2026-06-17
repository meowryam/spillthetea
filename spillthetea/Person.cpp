#include "Person.h"

Person::Person() {
	id = "xyz123";
	name = "Default";
	age = 0;
}

Person::Person(string id, string name, int age) {
	this->id = id;
	this->name = name;
	this->age = age;
}
Person::Person(const Person& other) {
	this->id = other.id;
	this->name = other.name;
	this->age = other.age;
}

void Person::setName(string n) {
	name = n;
}
void Person::setAge(int a) {
	age = a;
}
void Person::setID(string i) {
	id = i;
}

string Person::getID() {
	return id;
}
int Person::getAge() {
	return age;
}
string Person::getName() {
	return name;
}