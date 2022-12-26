#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Not input ini file!\n";
        exit(1); 
    }
    vector<Configuration> config;
    config = iniParser(argv[1]);
    Graph dagJobs = createGraph(config);
    if (dagJobs.isEmpty()) {
        exit(2);
    }
    // for (int i = 0; i < config.size(); ++i) {
    //     pid_t processID  =  fork();
    //     if (processID < 0) {
    //         printf("Error: fork\n");
    //         return 1;
    //     }

    //     if (processID > 0) {
    //         // config[1].printConfiguration();
    //         wait(NULL); 
    //     } else {
    //         execl(config[i].path.c_str(), config[i].path.c_str(), NULL);
    //     }

    // }
    // for (int i = 0; i < config.size(); ++i) {
    //     config[i].printConfiguration();
    // }
    return 0;
}