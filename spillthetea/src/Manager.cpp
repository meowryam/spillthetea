#include "Manager.h"



Manager::Manager(): Employee("xyz123", "Default", 0, "Default",0, 0.0){
	bonus = 0.0;
	staffunderit = 0;
}
Manager::Manager(double bonus, int staffunderit, string id, string name, int age, string role, int yearsofexperience, double salary) : Employee(id, name, age, role, yearsofexperience, salary) {
	this->bonus = bonus;
	this->staffunderit = staffunderit;
}
Manager::Manager(const Manager& other) : Employee(other) {
	this->bonus = other.bonus;
	this->staffunderit = other.staffunderit;
}

void Manager::setbonus(double b) {
	bonus = b;
}
void Manager::setstaffunderit(int s) {
	staffunderit = s;
}

double Manager::getbonus() {
	return bonus;
}
int Manager::getstaffunderit() {
	return staffunderit;
}