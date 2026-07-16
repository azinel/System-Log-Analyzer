#include <bits/stdc++.h>
using namespace std;

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

string getLogType(const string &line) {
    if (line.find("ERROR") != string::npos) return "ERROR";
    if (line.find("WARNING") != string::npos) return "WARNING";
    return "INFO";
}

int main() {
    string filename;
    cout << "Enter log file name: ";
    cin >> filename;

    ifstream fin(filename);    
    if (!fin.is_open()) {
        cerr << "Error opening file.\n";
        return 1;
    }

    unordered_map<string, int> logCount;         
    unordered_map<string, int> errorFrequency;    

    string line;
    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty()) continue;

        string type = getLogType(line);
        logCount[type]++;

        if (type == "ERROR") {
            errorFrequency[line]++;
        }
    }

    fin.close();

    cout << "\n--- Log Summary Report ---\n";
    cout << "INFO count: " << logCount["INFO"] << "\n";
    cout << "WARNING count: " << logCount["WARNING"] << "\n";
    cout << "ERROR count: " << logCount["ERROR"] << "\n";

    cout << "\nMost frequent ERRORs:\n";
    vector<pair<int, string>> freqList;
    for (auto &p : errorFrequency)
        freqList.push_back({p.second, p.first});

    sort(freqList.rbegin(), freqList.rend());

    for (int i = 0; i < min(5, (int)freqList.size()); i++) {
        cout << freqList[i].first << " occurrences: " << freqList[i].second << "\n";
    }

    cout << "\nAnalysis complete.\n";

    return 0;
}
