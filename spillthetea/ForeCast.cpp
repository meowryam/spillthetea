#include "ForeCast.h"
#include <cmath>
using namespace std;
Forecast::Forecast() {
	predictedSales = 0.0;
	confidence = 0.0;
	warningFlag = false;
}

Forecast::Forecast(double predicted, double conf, bool warning) {
	this->predictedSales = predicted;
	this->confidence = conf;
	this->warningFlag = warning;
}

Forecast::Forecast(const Forecast& other) {
	this->predictedSales = other.predictedSales;
	this->confidence = other.confidence;
	this->warningFlag = other.warningFlag;
}
void Forecast::setPredictedSales(double p) { predictedSales = p; }
void Forecast::setConfidence(double c) { confidence = c; }
void Forecast::setWarningFlag(bool w) { warningFlag = w; }
double Forecast::getPredictedSales() { return predictedSales; }
double Forecast::getConfidence() { return confidence; }
bool   Forecast::getWarningFlag() { return warningFlag; }
void Forecast::calculate(double* monthlySales, int months) {

	int window = 6;
	int start = months - window;   // index 18 for 24 months
	double sum = 0.0;
	for (int i = start; i < months; i++) {
		sum += monthlySales[i];
	}
	double average = sum / window;
	predictedSales = average;
	double varianceSum = 0.0;
	for (int i = start; i < months; i++) {
		double diff = monthlySales[i] - average;
		varianceSum += diff * diff;
	}
	double stdDev = sqrt(varianceSum / window);
	if (average > 0) {
		confidence = 100.0 - (stdDev / average * 100.0);
	}
	else {
		confidence = 0.0;
	}
	if (confidence < 0.0)   confidence = 0.0;
	if (confidence > 100.0) confidence = 100.0;
	warningFlag = (monthlySales[months - 1] < predictedSales);
}
Forecast Forecast::operator+(const Forecast& other) {
	double newPredicted = this->predictedSales + other.predictedSales;
	double newConfidence = (this->confidence + other.confidence) / 2.0;
	bool   newWarning = this->warningFlag || other.warningFlag;
	return Forecast(newPredicted, newConfidence, newWarning);
}
Forecast Forecast::operator++(int) {
	Forecast original = *this;          
	predictedSales = predictedSales * 1.02;  
	return original;                    
}
Forecast& Forecast::operator++() {
	predictedSales = predictedSales * 1.02;
	return *this;
}
Forecast& Forecast::operator--() {
	predictedSales = predictedSales * 0.98;
	return *this;
}
Forecast Forecast::operator--(int) {
	Forecast original = *this;
	--(*this);
	return original;
}






// operator<< prints the full forecast report for one branch
ostream& operator<<(ostream& out, Forecast& f) {
	out << "  Predicted Sales : Rs. " << f.getPredictedSales() << "\n";
	out << "  Confidence      : " << f.getConfidence() << "%\n";
	out << "  Warning         : " << (f.getWarningFlag() ? "YES — sales decline predicted" : "No") << "\n";
	return out;
}