#include "ASCII.h"
#include <iomanip>
#include <cmath>
using namespace std;

VisualReport::VisualReport() {
    branches = nullptr; count = 0; consoleWidth = 80;
}
VisualReport::VisualReport(CafeBranch** b, int c, int width) {
    count = c; consoleWidth = width;
    branches = new CafeBranch * [count];
    for (int i = 0; i < count; i++) branches[i] = b[i];
}
VisualReport::VisualReport(const VisualReport& other) {
    count = other.count; consoleWidth = other.consoleWidth;
    branches = new CafeBranch * [count];
    for (int i = 0; i < count; i++) branches[i] = other.branches[i];
}
VisualReport::~VisualReport() { delete[] branches; branches = nullptr; }

void VisualReport::setConsoleWidth(int w) { consoleWidth = (w > 20) ? w : 20; }

double VisualReport::getMax(double* arr, int size) {
    double mx = arr[0];
    for (int i = 1; i < size; i++) if (arr[i] > mx) mx = arr[i];
    return mx;
}
void VisualReport::printLine(int width) {
    for (int i = 0; i < width; i++) cout << "-";
    cout << "\n";
}

//Chart 1
void VisualReport::showSalesTrend(int branchIndex) {
    if (branchIndex < 0 || branchIndex >= count) return;

    SalesAnalytics sa = branches[branchIndex]->getSalesAnalytics();
    double sales[24];
    for (int i = 0; i < 24; i++) sales[i] = sa.getMonthlySales(i);
    double maxVal = getMax(sales, 24);

    int chartH = 12;
    int barW = max(1, (consoleWidth - 12) / 24);

    cout << "\n  SALES TREND — " << branches[branchIndex]->getName() << "\n";
    printLine(consoleWidth);

    for (int row = chartH; row >= 1; row--) {
        cout << setw(8) << (int)(maxVal / chartH * row / 1000) << "k |";
        for (int m = 0; m < 24; m++) {
            int barH = (int)round(sales[m] / maxVal * chartH);
            string seg(barW, row <= barH ? '#' : ' ');
            cout << seg;
        }
        cout << "\n";
    }

    cout << "         +";
    for (int i = 0; i < 24 * barW; i++) cout << "-";
    cout << "\n          ";
    for (int m = 0; m < 24; m++) cout << setw(barW) << (m + 1);
    cout << "\n          Month\n";
    printLine(consoleWidth);
}

//Chart 2
void VisualReport::showProfitComparison(int* indices, int indexCount) {
    double* profits = new double[indexCount];
    for (int i = 0; i < indexCount; i++)
        profits[i] = branches[indices[i]]->getSalesAnalytics().getTotalProfit();
    double maxP = getMax(profits, indexCount);

    int chartH = 12;
    int barW = max(2, (consoleWidth - 12) / indexCount);

    cout << "\n  PROFIT COMPARISON\n";
    printLine(consoleWidth);

    for (int row = chartH; row >= 1; row--) {
        cout << setw(8) << (int)(maxP / chartH * row / 1000) << "k |";
        for (int b = 0; b < indexCount; b++) {
            int barH = (int)round(profits[b] / maxP * chartH);
            string seg(barW - 1, row <= barH ? '|' : ' ');
            cout << seg << " ";
        }
        cout << "\n";
    }

    cout << "         +";
    for (int i = 0; i < indexCount * barW; i++) cout << "-";
    cout << "\n          ";
    for (int b = 0; b < indexCount; b++)
        cout << setw(barW) << ("B" + to_string(indices[b] + 1));
    cout << "\n";
    printLine(consoleWidth);
    delete[] profits;
}

//Chart3
void VisualReport::showClusterDistribution(Cluster* clusters, int clusterCount) {
    double maxRev = 0;
    for (int i = 0; i < clusterCount; i++) {
        double r = clusters[i].gettotalrevenue();
        if (r > maxRev) maxRev = r;
    }

    int maxBarLen = consoleWidth - 32;
    if (maxBarLen < 5) maxBarLen = 5;

    cout << "\n  CLUSTER REVENUE DISTRIBUTION\n";
    printLine(consoleWidth);

    for (int i = 0; i < clusterCount; i++) {
        double rev = clusters[i].gettotalrevenue();
        int barLen = (maxRev > 0) ? (int)(rev / maxRev * maxBarLen) : 0;
        string label = clusters[i].getName();
        if ((int)label.size() > 12) label = label.substr(0, 12);
        cout << "  " << left << setw(13) << label << "| ";
        for (int b = 0; b < barLen; b++) cout << "=";
        cout << "  Rs." << right << setw(12) << (long long)rev << "\n";
    }
    printLine(consoleWidth);
}
ostream& operator<<(ostream& out, VisualReport& vr) {
    out << "\n  VisualReport: " << vr.count << " branches, width=" << vr.consoleWidth << "\n";
    return out;
}