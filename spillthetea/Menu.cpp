#include "Menu.h"
#include <ctime>
#include <cstdlib>
Menu::Menu() {
	choice = 0;
	numbranches = 0;
	Branches = nullptr;
}
void Menu::displayMenu() {
	cout << "\n\n";
	//cout << "======================================\n";
	cout << "   S P I L L    T H E     T E A\n\n";
	cout << "       (tea of all kinds)\n\n";
	//cout << "======================================\n";
}
void Menu::showOptions() {
	cout << "  The cup is empty. Fill it how?\n\n ";
	cout << " [1] Spill the old tea (load from files)\n ";
	cout << " [2] Brew new tea rn (generate a new datasheet)\n";
	cin >> choice;
	cout << "\n\n";
	switch (choice) {
	case 1:{
		handleLoad();
		break;
	}
	case 2: {
		handleGenerate();
		break;
	}
	default: {
		cout << "  That's not even a cup man!\n";
		cout << "  try again, only from cup 1 and 2\n\n";
		showOptions();
		break;
	}
	}
}
void Menu::handleGenerate() {
	cout << "How many spill the tea locations are we tracking?\n\n";
	cout << "Minimun 100, since we dont do smol\n";
	cin >> numbranches;
	while (numbranches < 100) {
		cout << "Hey, dont underestimate the tea, we've got more than 100 locations to spill it from";
		cout << "try again, think big this time\n\n";
		cin >> numbranches;
	}
    srand((unsigned int)time(0));

    delete[] Branches;
    Branches = new CafeBranch[numbranches];

    cout << "\nGenerating " << numbranches << " branches...\n";

    for (int i = 0; i < numbranches; i++) {
        Branches[i] = generateOneBranch(i);
    }

    cout << numbranches << " branches generated!\n";

    saveAllToFile();
    cout << "\n=== FIRST 10 BRANCHES PREVIEW ===\n";
    for (int i = 0; i < 10; i++) {
        cout << Branches[i];
    }
    runMainMenu();
}

void Menu::handleLoad() {
    loadAllFromFile();
    runMainMenu();
}

void Menu::run() {
	displayMenu();
	showOptions();
}


void Menu::runMainMenu() {
    int option = 0;
    do {
        displayMenu();
        cout << "  What would you like to explore?\n\n";
        cout << "   [1]  Geographic clustering\n";
        cout << "   [2]  Performance ranking (top 10 / bottom 5)\n";
        cout << "   [3]  Sales forecasting\n";
        cout << "   [4]  ASCII visualizations\n";
        cout << "   [5]  Search / view a specific branch\n";
        cout << "   [0]  Exit\n\n";
        cout << "  Your choice: ";
        cin >> option;
        cout << "\n";

        switch (option) {
        case 1: runClustering();     break;
        case 2: runRanking();        break;
        case 3: runForecasting();    break;
        case 4: runVisualizations(); break;
       case 5: runBranchViewer();   break;
        case 0: cout << "  Goodbye!\n"; break;
        default: cout << "  Not a valid option, try again.\n"; break;
        }

        if (option != 0) {
            cout << "\n  Press ENTER to return to menu...";
            cin.ignore(); cin.get();
        }
    } while (option != 0);
}

CafeBranch Menu::generateOneBranch(int index) {

    string areas[] = { "Drama District", "Rumour Roundabout", "Sip City", "Spill Street", "Kettle Colony", "Hot Takes Heights", "Brew Bazaar", "Chai Chowk", "Gossip Gali" };
    string cities[] = { "Chaistan", "Kettleabad","SpillPur", "Brewabad" };
    int areaCount = 9;
    int cityCount = 4;
    string area = areas[rand() % areaCount];
    string city = cities[rand() % cityCount];
    string name = "Spill The Tea, "+ area + ", " + city;

       
        string id = "STT"; //stt=spill the tea
        int num = index + 1;
        if (num < 10)   id = id + "00" + (char)('0' + num);
        else if (num < 100) id = id + "0" + to_string(num);
        else id = id + to_string(num);


        // lat: 23 -37, lon: 60-77
        double lat = 23.0 + (rand() % 1400) / 100.0;
        double lon = 60.0 + (rand() % 1700) / 100.0;
        Coordinates coord(lat, lon);

      
        double sales[24], costs[24];
        int customers[24];

        for (int i = 0; i < 24; i++) {
            sales[i] = 50000 + rand() % 450000;   // Rs 50k - 500k
            costs[i] = 30000 + rand() % 200000;   // Rs 30k - 230k
            customers[i] = 100 + rand() % 900;       // 100 - 1000
        }
        SalesAnalytics sa(sales, costs, customers, 24);

        
        string mNames[] = { "Afeerah", "Wareesha", "Maryam", "Rawish", "Maham", "Aniqa", "Minahil", "Eshal", "Aimen", "Malaika" };

        string mName = mNames[rand() % 10];
        int mAge = 28 + rand() % 20;
        string mID = "MGR" + to_string(index + 1);
        double mSalary = 50000 + rand() % 100000;
        int mYears = 1 + rand() % 15;
        double mBonus = 5000 + rand() % 30000;
        int mStaff = 3 + rand() % 8;
        Manager mgr(mBonus, mStaff, mID, mName, mAge, "Cafe Manager", mYears, mSalary);

        
        string eNames[] = { "Huria", "Farah", "Sehrish", "Mahnoor", "Zainab", "Maira", "Raazia", "Bushra" };
        int staffCount = 3 + rand() % 5;
        Employee* staff = new Employee[staffCount];
        for (int i = 0; i < staffCount; i++) {
            string eName = eNames[rand() % 8];
            int eAge = 18 + rand() % 15;
            string eID = "EMP" + to_string(index * 10 + i);
            double eSalary = 20000 + rand() % 30000;
            int eYears = rand() % 8;
            staff[i] = Employee(eID, eName, eAge, "Barista", eYears, eSalary);
        }

        CafeBranch branch(name, id, coord, sa, mgr, staff, staffCount);
        delete[] staff;
        return branch;

}
void Menu::saveAllToFile() {
    ofstream file("spillthetea.txt");
    if (!file) {
        cout << "Could not open file for saving!\n";
        return;
    }

    file << numbranches << endl;   // first line = total count

    for (int i = 0; i < numbranches; i++) {
       Branches[i].saveToFile(file);
    }

    file.close();
    cout << "\nData saved to spillthetea.txt\n";
}
void Menu::loadAllFromFile() {
    ifstream file("spillthetea.txt");
    if (!file) {
        cout << "\nNo saved data found! Switching to generate mode.\n\n";
        handleGenerate();
        return;
    }

    file >> numbranches;
    file.ignore();

    delete[] Branches;
    Branches = new CafeBranch[numbranches];

    for (int i = 0; i < numbranches; i++) {
        Branches[i].loadFromFile(file);
    }

    file.close();
    cout << "\n" << numbranches << " branches loaded from spillthetea.txt\n";
}



void Menu::runClustering() {
    int K = 5;
    Cluster* clusters = kmean(Branches, numbranches, K);
    cout << "\n=== CLUSTERING REPORT ===\n";
    for (int i = 0; i < K; i++) {
        cout << clusters[i];
    }
    delete[] clusters;
}

void Menu::runRanking() {
    CafeBranch** ptrs = new CafeBranch * [numbranches];
    for (int i = 0; i < numbranches; i++) ptrs[i] = &Branches[i];
    Report report(ptrs, numbranches);
    report.sortByScore();
    cout << report;
    delete[] ptrs;
}

void Menu::runForecasting() {
    cout << "\n=== FORECASTING ===\n";
    cout << "  [1] Forecast a specific branch\n";
    cout << "  [2] Forecast all branches (summary only)\n";
    cout << "  Your choice: ";
    int sub; cin >> sub;

    if (sub == 1) {
        cout << "  Branch number (1 to " << numbranches << "): ";
        int idx; cin >> idx;
        if (idx < 1 || idx > numbranches) { cout << "Invalid.\n"; return; }
        cout << "\nBranch: " << Branches[idx - 1].getName() << "\n";
        Forecast f = Branches[idx - 1].getForecast();
        cout << f;
    }
    else {
        int warnCount = 0;
        for (int i = 0; i < numbranches; i++) {
            Forecast f = Branches[i].getForecast();
            if (f.getWarningFlag()) warnCount++;
        }
        cout << "\n  Total branches with decline warning: " << warnCount
            << " / " << numbranches << "\n";
    }
}
void Menu::runBranchViewer() {
    cout << "\n  Enter branch number (1 to " << numbranches << "): ";
    int idx; cin >> idx;
    if (idx < 1 || idx > numbranches) { cout << "  Invalid number.\n"; return; }
    cout << Branches[idx - 1];
    Forecast f = Branches[idx - 1].getForecast();
    cout << f;
}


void Menu::runVisualizations() {
    int option = 0;
    do {
        displayMenu();
        cout << "  ASCII VISUALIZATIONS\n\n";
        cout << "    [1]  Sales trend for a branch\n";
        cout << "    [2]  Profit comparison (top 10)\n";
        cout << "    [3]  Cluster revenue distribution\n";
        cout << "    [0]  Back\n\n";
        cout << "  Your choice: ";
        cin >> option;

        if (option == 0) break;

        CafeBranch** ptrs = new CafeBranch * [numbranches];
        for (int i = 0; i < numbranches; i++) ptrs[i] = &Branches[i];
        VisualReport vr(ptrs, numbranches, 80);

        if (option == 1) {
            cout << "  Branch number (1 to " << numbranches << "): ";
            int idx;
            cin >> idx;
            vr.showSalesTrend(idx - 1);
        }
        else if (option == 2) {
            int topCount = min(10, numbranches);
            int* indices = new int[topCount];
            for (int i = 0; i < topCount; i++) indices[i] = i;
            vr.showProfitComparison(indices, topCount);
            delete[] indices;
        }
        else if (option == 3) {
            cout << "  How many clusters? (2-10): ";
            int K; cin >> K;
            Cluster* clusters = kmean(Branches, numbranches, K);
            vr.showClusterDistribution(clusters, K);
            delete[] clusters;
        }

        delete[] ptrs;
        cout << "\n  Press ENTER to continue...";
        cin.ignore(); cin.get();

    } while (option != 0);
}




	Menu::~Menu() {
		delete[] Branches;
		Branches = nullptr;
	}

