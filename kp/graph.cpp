#include <queue>
#include "parser.h"
#include "graph.h"
#include <vector>

using namespace std;

Graph CreateGraph(vector<Configuration> configs) {
    Graph graph(configs.size() + 1);
    for (auto config: configs) {
        for (auto parent: config.parents) {
            if (parent == 0) {
                graph.endJobID = config.id;
            }
            graph.addNode(parent, config.id);
        }
    }

    if (graph.endJobID == 0) {
        cout << "Graph doesn't have End Jobs\n";
        exit(1);
    }
    return graph;
}

void IsCycle(int vertex, Graph &graph, vector<int> &visited, int parent) {
	visited[vertex] = true;
	for (auto neighbor: graph.adjacency[vertex]) {
		if (!visited[neighbor])
			IsCycle(neighbor, graph, visited, vertex);
		else if(neighbor != parent) {
			cout << "Grath has a cycle!\n";
			exit(0);
		}
	}
}

vector<int> BFS (int u, Graph &graph, vector<int> &visited) {
    vector<int> path;
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        path.push_back(u);
        for (int v : graph.adjacency[u]) {
            if (visited[v] == 0) {
                q.push(v);
                visited[v] = 1;
            }
        }
        
    }
    return path;
}

