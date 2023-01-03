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

int IsCycle(int vertex, Graph &graph, vector<int> &visited, int parent) {
	visited[vertex] = 1;
    int result = 0;
	for (auto neighbor: graph.adjacency[vertex]) {
		if (visited[neighbor] == 0) {
			result = IsCycle(neighbor, graph, visited, vertex);
            if (result) {
                break;
            }
        }
		else if (visited[neighbor] == 1) {
			result = 1;
            break;
		}
	}
    visited[vertex] = 2;
    return result;
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

