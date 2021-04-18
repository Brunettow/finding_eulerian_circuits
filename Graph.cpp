#include "Graph.h"

Graph::Graph(int numbOfVertices){

    this->numbOfVertices = numbOfVertices;
    this->adjacencyList = new list<pair<int,bool>>[numbOfVertices];
    this->numbOfEdges=0;
    this->isVisited = vector<bool>(numbOfVertices);
    this->incomings = vector<int> (numbOfVertices,0);
    this->outgoings =  vector<int> (numbOfVertices,0);;
}

void Graph::addEdge(int v, int w){
    this->adjacencyList[v].push_back(make_pair(w,false));
    this->incomings[w]++;
    this->numbOfEdges++;
}

Graph::~Graph(){
    delete[] adjacencyList, incomings, outgoings, isVisited;
}
