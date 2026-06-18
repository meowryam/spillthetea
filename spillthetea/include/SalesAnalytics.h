#pragma once
#include<iostream>
using namespace std;

class SalesAnalytics {
private:
	double* monthlysales;
	double* monthlycosts;
	int* customercount;
	int months;
public:
	SalesAnalytics();
	SalesAnalytics(double*, double*, int*, int);
	SalesAnalytics(const SalesAnalytics& other);



	void setmonthlysales(int, double);
	void setmonthlycosts(int, double);
	void setcustomercount(int, int);
	void setmonths(int);

	double* getmonthlysales();
	double* getmonthlycosts();
	int* getcustomercount();
	int getmonths();

	double getMonthlySales(int month);
	double getMonthlyCosts(int month);
	int getCustomerCount(int month);

	double getTotalSales();
	double getTotalCosts();
	double getAverageSales();
	double getTotalProfit();
	double getGrowthRate();
	double getCompositeScore();


	SalesAnalytics operator+(SalesAnalytics other);
	double operator[](int month);
	bool operator>(SalesAnalytics other);
	bool operator<(SalesAnalytics other);
	SalesAnalytics& operator=(const SalesAnalytics& other);

	SalesAnalytics& operator++();    
	SalesAnalytics operator++(int);  
	SalesAnalytics& operator--();    
	SalesAnalytics operator--(int); 

	~SalesAnalytics();
};