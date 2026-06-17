#include "Cluster.h"

Cluster::Cluster() {
    name = "Default";
	branches=nullptr;
	 branchcount = 0;
	 centroidlat = 0.0;
	 centroidlan = 0.0;
}
Cluster::Cluster(string n, CafeBranch** b, int count, double lat, double lan) {
	this->name = n;
	this->branchcount = count;
	this->centroidlat = lat;
	this->centroidlan = lan;
	this->branches = new CafeBranch*[count];
	for (int i = 0; i < count; i++) {this->branches[i] = b[i];}
}
Cluster::Cluster(const Cluster& other) {
	this->name = other.name;
	this->branchcount = other.branchcount;
	this->centroidlat = other.centroidlat;
	this->centroidlan = other.centroidlan;
	this->branches = new CafeBranch*[other.branchcount];
	for (int i = 0; i < branchcount; i++)  this->branches[i] = other.branches[i];
}
void Cluster::setName(string n) {
	name = n;
}
void Cluster::setBranchCount(int c) {
	branchcount = c;
}
void Cluster::setCentroid(double lat, double lan) {
	centroidlan = lan;
	centroidlat = lat;
}
void Cluster::setBranches(CafeBranch** b, int count) {
	delete[] branches;
	branchcount = count;
	branches = new CafeBranch*[count];
	for (int i = 0; i < count; i++) branches[i] = b[i];
	
}
string Cluster::getName() {
	return name;
}
int Cluster::getBranchCount() {
	return branchcount;
}
double Cluster::getCentroidLat() {
	return centroidlat;
}
double Cluster::getCentroidLan() {
	return centroidlan;
}

double Cluster::gettotalrevenue() {
	double total = 0.0;
	for (int i = 0; i < branchcount; i++) total += branches[i]->getSalesAnalytics().getTotalSales();
	return total;
}


Cluster Cluster::operator+(const Cluster& other) {

	int newCount = this->branchcount + other.branchcount;

	CafeBranch** combined = new CafeBranch * [newCount];

	for (int i = 0; i < this->branchcount; i++) {
		combined[i] = this->branches[i];
	}
	for (int i = 0; i < other.branchcount; i++) {
		combined[this->branchcount + i] = other.branches[i];
	}

	double newLat = (this->centroidlat + other.centroidlat) / 2.0;
	double newLon = (this->centroidlan + other.centroidlan) / 2.0;

	string newName = this->name + " + " + other.name;

	Cluster merged(newName, combined, newCount, newLat, newLon);

	delete[] combined;  
	return merged;
}

ostream& operator<<(ostream& out, Cluster& c) {
	out << "================================\n";
	out << "Cluster  : " << c.getName() << "\n";
	out << "Branches : " << c.getBranchCount() << "\n";
	out << "Revenue  : Rs. " << c.gettotalrevenue() << "\n";
	out << "Centroid : (" << c.getCentroidLat() << ", " << c.getCentroidLan() << ")\n";
	out << "================================\n";
	return out;
}


Cluster* kmean(CafeBranch* allBranches, int totalBranches, int K) {

	double* centLat = new double[K];
	double* centLon = new double[K];

	for (int k = 0; k < K; k++) {
		int idx = (k * totalBranches) / K;  
		centLat[k] = allBranches[idx].getCoordinates().getLatitude();
		centLon[k] = allBranches[idx].getCoordinates().getLongitude();
	}


	int* assignment = new int[totalBranches];
	for (int i = 0; i < totalBranches; i++) assignment[i] = 0;


	bool changed = true;
	int iterations = 0;

	while (changed && iterations < 100) {
		changed = false;
		iterations++;

		
		for (int i = 0; i < totalBranches; i++) {
			double branchLat = allBranches[i].getCoordinates().getLatitude();
			double branchLon = allBranches[i].getCoordinates().getLongitude();

			int bestCluster = 0;
			double bestDist = 1e18;

			for (int k = 0; k < K; k++) {
				double dLat = branchLat - centLat[k];
				double dLon = branchLon - centLon[k];
				double dist = sqrt(dLat * dLat + dLon * dLon);

				if (dist < bestDist) {
					bestDist = dist;
					bestCluster = k;
				}
			}

			if (assignment[i] != bestCluster) {
				assignment[i] = bestCluster;
				changed = true;
			}
		}


		double* sumLat = new double[K]();
		double* sumLon = new double[K]();
		int* count = new int[K]();

		for (int i = 0; i < totalBranches; i++) {
			int k = assignment[i];
			sumLat[k] += allBranches[i].getCoordinates().getLatitude();
			sumLon[k] += allBranches[i].getCoordinates().getLongitude();
			count[k]++;
		}

		for (int k = 0; k < K; k++) {
			if (count[k] > 0) {
				centLat[k] = sumLat[k] / count[k];
				centLon[k] = sumLon[k] / count[k];
			}
		}

		delete[] sumLat;
		delete[] sumLon;
		delete[] count;
	}

	Cluster* result = new Cluster[K];

	for (int k = 0; k < K; k++) {

		int memberCount = 0;
		for (int i = 0; i < totalBranches; i++) {
			if (assignment[i] == k) memberCount++;
		}

		CafeBranch** members = new CafeBranch * [memberCount];
		int idx = 0;
		for (int i = 0; i < totalBranches; i++) {
			if (assignment[i] == k) {
				members[idx++] = &allBranches[i];
			}
		}

		result[k].setName("Cluster " + to_string(k + 1));
		result[k].setCentroid(centLat[k], centLon[k]);
		result[k].setBranches(members, memberCount);

		delete[] members;   
	}

	delete[] centLat;
	delete[] centLon;
	delete[] assignment;

	return result;  
}


Cluster::~Cluster() {
	delete[] branches;
	branches = nullptr;
}