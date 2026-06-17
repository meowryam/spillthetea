#pragma once
#include "CafeBranch.h"
#include <ostream>
using namespace std;

class Report {
private:
	CafeBranch** branches;//aggregation
	int count;

public:
	Report();
	Report(CafeBranch** b, int c);
	Report(const Report& other);
	~Report();
	void sortByScore();
	friend ostream& operator<<(ostream& out, Report& r);
};