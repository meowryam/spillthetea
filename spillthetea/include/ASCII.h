#pragma once
#include "CafeBranch.h"
#include "Cluster.h"
using namespace std;

class VisualReport {
private:
    CafeBranch** branches;  // aggregation 
    int count;
    int consoleWidth;

    double getMax(double* arr, int size);
    void printLine(int width);

public:
    VisualReport();
    VisualReport(CafeBranch** b, int c, int width = 80);
    VisualReport(const VisualReport& other);
    ~VisualReport();
    void setConsoleWidth(int w);
    void showSalesTrend(int branchIndex);
    void showProfitComparison(int* indices, int indexCount);
    void showClusterDistribution(Cluster* clusters, int clusterCount);
    friend ostream& operator<<(ostream& out, VisualReport& vr);
};