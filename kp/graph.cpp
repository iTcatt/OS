#include <queue>
#include "parser.h"
#include "graph.h"

using namespace std;

vector<int> BFS(int graphSize, vector<int> adj[]) {
    vector<int> bfs_traversal;
    vector<int> visited(graphSize, 0);
    for (int i = 0; i < graphSize; ++i) {
        if (!visited[i]) {
            queue<int> q;
            visited[i] = 1;
            q.push(i);
            
            while (!q.empty()) {
                int g_node = q.front();
                q.pop();
                bfs_traversal.push_back(g_node);
                for (auto it : adj[g_node]) {
                    if (!visited[it]) {
                        visited[it] = 1;
                        q.push(it);
                    }
                }
            }
        }
    }
    return bfs_traversal;
}

Graph createGraph(vector<Configuration> configs) {
    Graph graph(configs.size() + 1);
    int endJob = 0; // хранит конечную job'у
    for (auto config: configs) {
        if (endJob != 0) {
            cout << "Error: Wrong configuration! Too many finish jobs.\n";
            exit(2);
        }
        if (config.parent == 0) {
            endJob  =config.id;
        }
        graph.addNode(config.parent, config.id);
    }
    cout << "End job is " << endJob << '\n';
    return graph;
}