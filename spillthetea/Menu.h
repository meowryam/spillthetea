#pragma once
#include <iostream>
#include <string>
#include "CafeBranch.h"
#include "Cluster.h"
#include "Report.h"
#include "ForeCast.h"
#include "ASCII.h"
using namespace std;

class Menu {
private:
	int choice;
	int numbranches;
	CafeBranch* Branches;
	void displayMenu();
	void showOptions();
	void handleGenerate();
	void handleLoad();
	CafeBranch generateOneBranch(int index);
	void saveAllToFile();
	void loadAllFromFile();
	void runClustering();
	void runRanking();
	void runForecasting();
	void runVisualizations();
	void runMainMenu();
	void runBranchViewer();
public:
	Menu();
	void run();


	~Menu();
};