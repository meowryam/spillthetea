#pragma once
#include "Person.h"
using namespace std;
class Employee : public Person {
private:
	string role;
	int yearsofexperience;
	double salary;
public:
	Employee();
	Employee(string id, string name, int age, string role, int yearsofexperience, double salary);
	Employee(const Employee& other);

	void setrole(string);
	void setyearsofexperience(int);
	void setsalaray(double);

	string getrole();
	int getyearsofexperience();
	double getsalaray();

};