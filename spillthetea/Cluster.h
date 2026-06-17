#pragma once
#include "CafeBranch.h"
using namespace std;

class Cluster {
private:
	string name;
	CafeBranch** branches; //aggreagation
	int branchcount;
	double centroidlat, centroidlan;
public:
	Cluster();
	Cluster(string n, CafeBranch** b, int count, double lat, double lan);
	Cluster(const Cluster& other);

	void setName(string n);
	void setBranchCount(int c);
	void setCentroid(double lat, double lan);
	void setBranches(CafeBranch** b, int count);

	string getName();
	int getBranchCount();
	double getCentroidLat();
	double getCentroidLan();

	double gettotalrevenue();

	Cluster operator+(const Cluster& other);
	friend ostream& operator<<(ostream& out, Cluster& c);

	~Cluster();
};
Cluster* kmean(CafeBranch* bb, int totalbranches, int k);

