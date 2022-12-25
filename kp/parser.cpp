#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "parser.h"

using namespace std;

vector<Configuration> iniParser(string nameFile) {
    ifstream iniFile;
    vector<Configuration> configs;

    iniFile.open(nameFile);
    if (!iniFile.is_open()) {
        cout << "The file was not open" << '\n';
    }
    string line;
    Configuration currentConfig;
    while (getline(iniFile, line)) {
        if (line[0] == '[') {
            continue;
        } else if (line.substr(0, 2) == "id") {
            currentConfig.id = stoi(line.substr(5, line.size() - 5));
        } else if (line.substr(0, 4) == "name") {
            currentConfig.name = line.substr(8, line.size() - 9);
        } else if (line.substr(0, 4) == "path") {
            currentConfig.path = line.substr(8, line.size() - 9);
        } else {
            configs.push_back(currentConfig);
        }
    }
    configs.push_back(currentConfig);
    iniFile.close();
    return configs;
}