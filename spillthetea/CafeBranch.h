#pragma once
#include "Coordinates.h"
#include "SalesAnalytics.h"
#include "Person.h"
#include "Manager.h"
#include "Employee.h"
#include "ForeCast.h"
#include <fstream>
using namespace std;

class CafeBranch {
private:
	string name;
	string branchID;
	int staffCount;
	Coordinates c;
	SalesAnalytics s;
	Manager m;
	Employee* staff;
	Forecast F;

public:
	CafeBranch();
	CafeBranch(string n, string ID, Coordinates c1, SalesAnalytics s1, Manager m1, Employee* staff1, int staffCount1);
	CafeBranch(const CafeBranch& other);

	void setName(string);
	void setBranchID(string);
	void setStaffCount(int);

	string getName();
	string getBranchID();
	int getStaffCount();

	Coordinates getCoordinates();
	SalesAnalytics getSalesAnalytics();
	Manager getManager();

	bool operator==(const CafeBranch& other);
	CafeBranch& operator=(const CafeBranch& other);
	friend ostream& operator<<(ostream& out, CafeBranch& b);
	Forecast& getForecast();

	void loadFromFile(ifstream& file);
	void saveToFile(ofstream& file);

	~CafeBranch();
};