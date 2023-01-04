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

    // for (auto id: path) {
    //     cout << id << ' ';
    // }
    // cout << '\n';
    int number = 1;
    for (int id = path.size() - 1; id >= 0; --id) {
        int pipe_parent[2];
        int pipe_child[2];
        if (pipe(pipe_parent) == -1) {
            fprintf(stderr, "Pipe Failed");
            exit(1);
        }

        if (pipe(pipe_child) == -1) {
            fprintf(stderr, "Pipe Failed");
            exit(1);
        }
        cout << "Ha " << path[id] << '\n';
        pid_t process_id = fork();
        
        if (process_id < 0) {
            printf("Error: Fork\n");
            exit(1);
        }

        if (process_id > 0) {
            close(pipe_parent[0]);
            write(pipe_parent[1], &number, sizeof(int));
            close(pipe_parent[1]);
            wait(NULL);
            
            close(pipe_child[1]);
            read(pipe_child[0], &number, sizeof(int));
            close(pipe_child[0]);
            
        } else {
            close(pipe_parent[1]);

            if (dup2(pipe_child[1], 2) == -1) {
                printf("Error: Dup2\n");
                exit(2);
            }

            int received;
            read(pipe_parent[0], &received, sizeof(int));
            close(pipe_parent[0]);
            
            close(pipe_child[0]);
            char str[2];
            sprintf(str, "%d", received);
            execl(job_paths[path[id]].c_str(), job_paths[path[id]].c_str(), str, NULL);
        }
        cout << number << '\n';
    }
    return 0;
}
