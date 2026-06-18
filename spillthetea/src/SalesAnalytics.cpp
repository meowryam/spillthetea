#include "SalesAnalytics.h"

SalesAnalytics::SalesAnalytics() {
	months = 24;
	monthlysales = new double [months];
	monthlycosts = new double[months];
	customercount = new int[months];

	for (int i = 0; i < months; i++) {
		monthlysales[i] = 0.0;
		monthlycosts[i] = 0.0;
		customercount[i] = 0;
	}



}
SalesAnalytics::SalesAnalytics(double* sale, double* cost, int* customer, int month) {
	months = month;
	monthlysales = new double[months];
	monthlycosts = new double[months];
	customercount = new int[months];
	for (int i = 0; i < months; i++) {
		monthlysales[i] = sale[i];
		monthlycosts[i] = cost[i];
		customercount[i] = customer[i];
	}

}
SalesAnalytics::SalesAnalytics(const SalesAnalytics& other) {
	this->months = other.months;
	monthlysales = new double[months];
	monthlycosts = new double[months];
	customercount = new int[months];

	for (int i = 0; i < months; i++) {
		monthlysales[i] = other.monthlysales[i];
		monthlycosts[i] = other.monthlycosts[i];
		customercount[i] = other.customercount[i];

}

}



void SalesAnalytics::setmonthlysales(int month, double sale) {
	if (month >= 0 && month < months)
		monthlysales[month] = sale;

}
void SalesAnalytics::setmonthlycosts(int month, double cost) {
	if (month >= 0 && month < months)
		monthlycosts[month] = cost;
}
void SalesAnalytics::setcustomercount(int month, int customer) {
	if (month >= 0 && month < months)
		customercount[month] = customer;
}
void SalesAnalytics::setmonths(int month) {
	months = month;
}



double* SalesAnalytics::getmonthlysales() {
	return monthlysales;
}
double* SalesAnalytics::getmonthlycosts() {
	return monthlycosts;
}
int* SalesAnalytics::getcustomercount() {
	return customercount;
}
int SalesAnalytics::getmonths(){
	return months;
}

double SalesAnalytics::getMonthlySales(int month) {
	if (month >= 0 && month < months)
		return monthlysales[month];
	return 0.0;
}

double SalesAnalytics::getMonthlyCosts(int month){
	if (month >= 0 && month < months)
		return monthlycosts[month];
	return 0.0;
}

int SalesAnalytics::getCustomerCount(int month) {
	if (month >= 0 && month < months)
		return customercount[month];
	return 0;
}



double SalesAnalytics::getTotalSales() {
	double totalsales = 0.0;
	for (int i = 0; i < months; i++) {
		totalsales = totalsales + monthlysales[i];
	}
	return totalsales;
}
double SalesAnalytics::getTotalCosts() {
	double totalcosts = 0.0;
	for (int i = 0; i < months; i++) {
		totalcosts = totalcosts + monthlycosts[i];
	}
	return totalcosts;
}
double SalesAnalytics::getAverageSales() {
	return getTotalSales() / months;
}
double SalesAnalytics::getTotalProfit() {
	return getTotalSales() - getTotalCosts();
}
//last 1 year
double SalesAnalytics::getGrowthRate() {
	double totalChange = 0.0;
	for (int i = 12; i < months; i++) {
		double monthlyChange = monthlysales[i] - monthlysales[i - 1];
		totalChange += monthlyChange;

	}
	return totalChange / 12.0;
}

double SalesAnalytics::getCompositeScore() {
	return (getTotalProfit() * 0.5 + getGrowthRate() * 0.3 + getTotalSales() * 0.2);
}

SalesAnalytics SalesAnalytics::operator+(SalesAnalytics other) {
	SalesAnalytics c;
	for (int i = 0; i < months; i++) {
		c.monthlysales[i] = this->monthlysales[i] + other.monthlysales[i];
		c.monthlycosts[i] = this->monthlycosts[i] + other.monthlycosts[i];
		c.customercount[i] = this->customercount[i] + other.customercount[i];
	}
	return c;
}

double SalesAnalytics::operator[](int month) {
	if (month >= 0 && month < months)
		return monthlysales[month];
	else
		return 0.0;
}
bool SalesAnalytics::operator>(SalesAnalytics other) {
	return this->getTotalProfit() > other.getTotalProfit();
}
bool SalesAnalytics::operator<(SalesAnalytics other) {
	return this->getTotalProfit() < other.getTotalProfit();
}

SalesAnalytics& SalesAnalytics::operator=(const SalesAnalytics& other) {
	if (this == &other) return *this;

	delete[] monthlysales;
	delete[] monthlycosts;
	delete[] customercount;

	months = other.months;
	monthlysales = new double[months];
	monthlycosts = new double[months];
	customercount = new int[months];

	for (int i = 0; i < months; i++) {
		monthlysales[i] = other.monthlysales[i];
		monthlycosts[i] = other.monthlycosts[i];
		customercount[i] = other.customercount[i];
	}

	return *this;
}

//preinc
SalesAnalytics& SalesAnalytics::operator++() {
	for (int i = 0; i < months - 1; i++) {
		monthlysales[i] = monthlysales[i + 1];
		monthlycosts[i] = monthlycosts[i + 1];
		customercount[i] = customercount[i + 1];
	}
	monthlysales[months - 1] = 0.0;
	monthlycosts[months - 1] = 0.0;
	customercount[months - 1] = 0;
	return *this;
}

// post inc
SalesAnalytics SalesAnalytics::operator++(int) {
	SalesAnalytics original = *this;
	++(*this);
	return original;
}

// pre-dec
SalesAnalytics& SalesAnalytics::operator--() {
	for (int i = months - 1; i > 0; i--) {
		monthlysales[i] = monthlysales[i - 1];
		monthlycosts[i] = monthlycosts[i - 1];
		customercount[i] = customercount[i - 1];
	}
	monthlysales[0] = 0.0;
	monthlycosts[0] = 0.0;
	customercount[0] = 0;
	return *this;
}

// post-dec
SalesAnalytics SalesAnalytics::operator--(int) {
	SalesAnalytics original = *this;
	--(*this);
	return original;
}

SalesAnalytics::~SalesAnalytics() {

		delete[] monthlysales;
		delete[] monthlycosts;
		delete[] customercount;
		monthlysales = nullptr;
		monthlycosts = nullptr;
		customercount = nullptr;
}