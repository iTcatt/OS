#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <queue>
#include <vector>
#include "parser.h"

class Graph {
public:
    int graphSize = 0;
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
        return graphSize > 0;
    }

};

Graph createGraph(std::vector<Configuration>);
std::vector<int> BFS(int, std::vector<int>);

#endif