#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <vector>
using namespace std;

class Graph {

public:

    int numbOfVertices, numbOfEdges;
    vector<int> incomings;
    vector<int> outgoings;
    vector<bool> isVisited;
    list <pair<int,bool>> * adjacencyList;
    Graph (int numbOfVertices);
    void addEdge (int v, int w);
    ~Graph();

};




#endif //GRAPH_H
