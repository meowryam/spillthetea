#pragma once
#include "Employee.h"
using namespace std;
class Manager : public Employee {
private:
	double bonus;
	int staffunderit;
public:
	Manager();
	Manager(double bonus, int staffunderit, string id, string name, int age, string role, int yearsofexperience, double salary);
	Manager(const Manager& other);

	void setbonus(double);
	void setstaffunderit(int);

	double getbonus();
	int getstaffunderit();
};











