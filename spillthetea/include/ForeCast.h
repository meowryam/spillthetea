#pragma once
#include <iostream>
using namespace std;

class Forecast {
private:
	double predictedSales;  
	double confidence;     
	bool warningFlag;        
public:
	Forecast();
	Forecast(double predicted, double conf, bool warning);
	Forecast(const Forecast& other);
	void setPredictedSales(double p);
	void setConfidence(double c);
	void setWarningFlag(bool w);
	double getPredictedSales();
	double getConfidence();
	bool getWarningFlag();
	void calculate(double* monthlySales, int months);
	Forecast operator+(const Forecast& other);
	Forecast operator++(int);
	Forecast& operator++();    
	Forecast& operator--();    
	Forecast operator--(int);  
	friend ostream& operator<<(ostream& out, Forecast& f);
};