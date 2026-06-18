#include "Employee.h"

Employee::Employee() : Person("xyz123", "Default", 0) {
	role = "Default";
	yearsofexperience = 0;
	salary = 0.0;
}
Employee::Employee(string id, string name, int age, string role, int yearsofexperience, double salary) : Person(id, name, age){
	this->role = role;
	this->yearsofexperience = yearsofexperience;
	this->salary = salary;

}
Employee::Employee(const Employee& other) : Person(other) {
	this->role = other.role;
	this->yearsofexperience = other.yearsofexperience;
	this->salary = other.salary;
}

void Employee::setrole(string r) {
	role = r;
}
void Employee::setyearsofexperience(int y) {
	yearsofexperience = y;
}
void Employee::setsalaray(double s) {
	salary = s;
}

string Employee::getrole() {
	return role;
}
int Employee::getyearsofexperience() {
	return yearsofexperience;
}
double Employee::getsalaray() {
	return salary;
}