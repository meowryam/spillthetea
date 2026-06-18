#include "CafeBranch.h"
using namespace std;

CafeBranch::CafeBranch() {
    name = "Default";
    branchID = "XYZ123";
    staffCount = 0;
	staff = nullptr;
	//c, s, m alr initillizaed in their own files.
}
CafeBranch::CafeBranch(string n, string ID, Coordinates c1, SalesAnalytics s1, Manager m1, Employee* staff1, int staffCount1) {
	 this->name = n;
	 this->branchID = ID;
	 this->staffCount = staffCount1;
	 this->c = c1;
	 this->s = s1;
	 this->m = m1;
	 this->staff = new Employee[staffCount];
	 for (int i = 0; i < staffCount; i++) {
		 this->staff[i] = staff1[i];
	 }
}

CafeBranch::CafeBranch(const CafeBranch& other) {
	this->name = other.name;
	this->branchID = other.branchID;
	this->staffCount = other.staffCount;
	this->c = other.c;
	this->s = other.s;
	this->m = other.m;
	this->staff = new Employee[staffCount];
	for (int i = 0; i < staffCount; i++) {
		this->staff[i] = other.staff[i];
	}


}





Coordinates CafeBranch::getCoordinates() {
	return c;
}
SalesAnalytics CafeBranch::getSalesAnalytics() {
	return s;
}
Manager CafeBranch::getManager() {
	return m;
}







void CafeBranch::setName(string n) {
	name = n;
}
void CafeBranch::setBranchID(string i) {
	branchID = i;
}
void CafeBranch::setStaffCount(int c) {
	staffCount = c;
}

string CafeBranch::getName() {
	return name;
}
string CafeBranch::getBranchID() {
	return branchID;
}
int CafeBranch::getStaffCount() {
	return staffCount;
}


bool CafeBranch::operator==(const CafeBranch& other) {
	return this->branchID == other.branchID;
	}

void CafeBranch::saveToFile(ofstream& file) {

	file << name << endl << branchID << endl << staffCount << endl; 
	file << c.getLatitude() << endl << c.getLongitude() << endl;
	for (int i = 0; i < 24; i++) file << s.getMonthlySales(i) << endl;
	for (int i = 0; i < 24; i++) file << s.getMonthlyCosts(i) << endl;
	for (int i = 0; i < 24; i++) file << s.getCustomerCount(i) << endl;
	file << m.getName() << endl << m.getAge() << endl << m.getID() << endl << m.getrole() << endl << m.getsalaray() << endl << m.getyearsofexperience() << endl << m.getbonus() << endl << m.getstaffunderit() << endl;
	for (int i = 0; i < staffCount; i++) { file << staff[i].getName() << endl << staff[i].getAge() << endl << staff[i].getID() << endl << staff[i].getrole() << endl << staff[i].getsalaray() << endl << staff[i].getyearsofexperience() << endl; }

}



void CafeBranch::loadFromFile(ifstream& file) {

	getline(file, name);
	getline(file, branchID);
	file >> staffCount;
	file.ignore();


	double lat, lon;
	file >> lat >> lon;
	file.ignore();
	c.setLatitude(lat);
	c.setLongitude(lon);


	double sale, cost;
	int cust;
	for (int i = 0; i < 24; i++) { file >> sale; s.setmonthlysales(i, sale); }
	for (int i = 0; i < 24; i++) { file >> cost; s.setmonthlycosts(i, cost); }
	for (int i = 0; i < 24; i++) { file >> cust; s.setcustomercount(i, cust); }
	file.ignore();


	string mName, mID, mRole;
	int mAge, mYears, mStaff;
	double mSalary, mBonus;

	getline(file, mName);
	file >> mAge; file.ignore();
	getline(file, mID);
	getline(file, mRole);
	file >> mSalary >> mYears >> mBonus >> mStaff;
	file.ignore();
	m = Manager(mBonus, mStaff, mID, mName, mAge, mRole, mYears, mSalary);

	delete[] staff;
	staff = new Employee[staffCount];

	for (int i = 0; i < staffCount; i++) {
		string eName, eID, eRole;
		int eAge, eYears;
		double eSalary;

		getline(file, eName);
		file >> eAge; file.ignore();
		getline(file, eID);
		getline(file, eRole);
		file >> eSalary >> eYears;
		file.ignore();
		staff[i] = Employee(eID, eName, eAge, eRole, eYears, eSalary);
	}
}

CafeBranch& CafeBranch::operator=(const CafeBranch& other) {
	if (this == &other) return *this;  // self assignment check

	// delete old memory first
	delete[] staff;

	// copy everything
	name = other.name;
	branchID = other.branchID;
	staffCount = other.staffCount;
	c = other.c;
	s = other.s;
	m = other.m;

	// deep copy staff
	if (staffCount > 0) {
		staff = new Employee[staffCount];
		for (int i = 0; i < staffCount; i++) {
			staff[i] = other.staff[i];
		}
	}
	else {
		staff = nullptr;
	}

	return *this;
}

Forecast& CafeBranch::getForecast() {
	F.calculate(s.getmonthlysales(), s.getmonths());
	return F;
}

ostream& operator<<(ostream& out, CafeBranch& b) {
	out << "--------------------------------\n";
	out << "Name     : " << b.getName() << "\n";
	out << "ID       : " << b.getBranchID() << "\n";
	out << "Manager  : " << b.getManager().getName() << "\n";
	out << "Staff    : " << b.getStaffCount() << "\n";
	out << "Location : (" << b.getCoordinates().getLatitude() << ", " << b.getCoordinates().getLongitude() << ")\n";
	out << "Revenue  : Rs. " << b.getSalesAnalytics().getTotalSales() << "\n";
	out << "Profit   : Rs. " << b.getSalesAnalytics().getTotalProfit() << "\n";
	out << "Growth   : " << b.getSalesAnalytics().getGrowthRate() << " Rs/month\n";
	return out;
}



CafeBranch::~CafeBranch() {
	delete[] staff;
	staff = nullptr;
}