#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <queue>
#include <vector>
#include "parser.h"

class Graph {
public:
    int graphSize = 0;
    int endJobID = 0;
    std::vector<std::vector<int>> adjacency;

    Graph(int size) {
        graphSize = size;
        adjacency.resize(size);
    }
    void addNode(int startNode, int endNode) {
        adjacency[startNode].push_back(endNode);
    }

    int getSize() {
        return graphSize;
    }

    int isEmpty() {
        return graphSize == 0;
    }

    void print() { 
        for (int startNode = 1; startNode < graphSize; ++startNode) {
            for (int vertex: adjacency[startNode]) {
                std::cout << startNode << ' ' << vertex << "\n";
            }
        }
    }
};

Graph CreateGraph(std::vector<Configuration>);
std::vector<int> BFS(int, Graph &, std::vector<int> &);
int IsCycle(int, Graph &, std::vector<int> &, int);

#endif