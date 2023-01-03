#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "graph.h"

using namespace std;

map<int, string> CreateDictionary(vector<Configuration> configs) {
    map<int, string> paths_dictionary;
    for (auto config: configs) {
        paths_dictionary[config.id] = config.path;
    }
    return paths_dictionary;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Not input ini file!\n";
        exit(1); 
    }

    vector<Configuration> configs;
    configs = IniParser(argv[1]);
    // for (auto config: configs) {
    //     config.printConfiguration();
    // }
    Graph dag_jobs = CreateGraph(configs);
    if (dag_jobs.isEmpty()) {
        cout << "The graph is empty!\n";
        exit(2);
    }

    dag_jobs.print();

    vector<int> visited(dag_jobs.getSize(), 0);

    for (auto end_job: dag_jobs.end_jobs_id) {
        if (IsCycle(end_job, dag_jobs, visited)) {
            cout << "The graph has a cycle!\n";
            exit(3);
        }
    }

    vector<int> traveled(dag_jobs.getSize(), 0);
    vector<int> path = BFS(dag_jobs, traveled);

    map<int, string> job_paths = CreateDictionary(configs);
    cout << '\n';

    for (int id = path.size() - 1; id >= 0; --id) {
        pid_t processID = fork();
        if (processID < 0) {
            printf("Error: fork\n");
            return 1;
        }

        if (processID > 0) {
            wait(NULL); 
        } else {
            execl(job_paths[path[id]].c_str(), job_paths[path[id]].c_str(), NULL);
        } 
    }
    
    return 0;
}
