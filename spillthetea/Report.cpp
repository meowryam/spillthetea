#include "Report.h"
using namespace std;
Report::Report() {
	branches = nullptr;
	count = 0;
}

Report::Report(CafeBranch** b, int c) {
	count = c;
	branches = new CafeBranch * [count];
	for (int i = 0; i < count; i++) {
		branches[i] = b[i];
	}
}

Report::Report(const Report& other) {
	count = other.count;
	branches = new CafeBranch * [count];
	for (int i = 0; i < count; i++) {
		branches[i] = other.branches[i];
	}
}
Report::~Report() {
	delete[] branches;
	branches = nullptr;
}
void Report::sortByScore() {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			double scoreJ = branches[j]->getSalesAnalytics().getCompositeScore();
			double scoreJNext = branches[j + 1]->getSalesAnalytics().getCompositeScore();
			if (scoreJNext > scoreJ) {
				CafeBranch* temp = branches[j];
				branches[j] = branches[j + 1];
				branches[j + 1] = temp;
			}
		}
	}
}
ostream& operator<<(ostream& out, Report& r) {

	out << "\n========================================\n";
	out << "       STORE PERFORMANCE REPORT\n";
	out << "========================================\n";
	out << "\n--- TOP 10 BRANCHES ---\n";
	int rank = 0;
	int top = (r.count < 10) ? r.count : 10;  
	while (rank < top) {
		++rank; 
		out << "\nRank #" << rank << "\n";
		out << *r.branches[rank - 1]; 
	}
	out << "\n--- BOTTOM 5 BRANCHES ---\n";
	int bottom = (r.count < 5) ? r.count : 5;
	rank = 0;

	while (rank < bottom) {
		++rank;
		out << "\nBottom #" << rank << "\n";
		out << *r.branches[r.count - rank];  
	}

	out << "\n========================================\n";
	return out;
}