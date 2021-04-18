#include <iostream>
#include <fstream>
#include "Graph.h"
#include <iomanip>
#include <iterator>
#include <vector>
#include <cstddef> 
using namespace std;
     
int mergeItData = 0;

bool isEulerian(Graph* g){

    int numbOfVertices=g->numbOfVertices;

    for (int k = 0; k < numbOfVertices; k++) {   //checking whether the graph is eulerian circuit
           
           int incomings = g->incomings[k];
           int outgoings = g->outgoings[k];
               
           if(incomings>outgoings){  //if it's not
                return false;
           }
       }

    return true;
}

list<int> merge (list<int> circuit, list<int> tour, int src){ //checked
   
    list<int>::iterator i = circuit.begin();
    if (mergeItData!=0) {
        i=next(i,mergeItData);
   }

   for (; i!=circuit.end(); ++i) {
       mergeItData++;
       if (*i==src) {
           break;
       }
   }

    auto itPos = next(circuit.begin(),mergeItData);
    auto iter = circuit.insert(itPos,tour.begin(),tour.end());

    return circuit; 
}

int findNextVertex(Graph* g, list<int> circuit){

     for(auto i : circuit ){
        if (g->isVisited[i]) {
            for (auto j : g->adjacencyList[i]) {
                if (!j.second) {
                    return i;
                }   
            }
        }
    }
}

list<int> hierholzer (Graph* graph, int src){

    list<int> eulerianCircuit;  //main circuit
    eulerianCircuit.push_back(src);  //push src to circuit
    int tourSrc = src;  //the vertex that next tour will start

    while(eulerianCircuit.size() <= graph->numbOfEdges ){  //until circuit length equals to numb of edges 
    
        list<int> tour;  //new circuit that will be added
        list<pair<int,bool>>::iterator itr = graph->adjacencyList[src].begin();
            for (; itr!= graph->adjacencyList[src].end();){ //bir ihtimal sıkıntı çıkabilir
                pair<int,bool>* p = &*itr; 
                itr++;
                
                if (itr==graph->adjacencyList[src].end()) {
                    graph->isVisited[src]=false;
                }
                
                if(!p->second){
                    p->second=true; //mark as checked
                    src = p->first;
                    tour.push_back(src);
                    itr = graph->adjacencyList[src].begin();
                }
            }

        if(tour.size()>0) {
        eulerianCircuit = merge(eulerianCircuit, tour, tourSrc);
        }   

        src = findNextVertex(graph,eulerianCircuit);
        tourSrc = src;
    }
    return eulerianCircuit;
}

int main(int argc, char const *argv[]) {
    
    string infile_name = argv[1];  //file input
    string outfile_name = argv[2]; //file output
    ifstream infile;
    infile.open(infile_name);

    ofstream outfile;
    outfile.open(outfile_name);

    int numbOfVertices, vertexID, numbOfAdjacency, adjacencyID, src;

    infile >> numbOfVertices;
    Graph graph(numbOfVertices);

    for (int i = 0; i < numbOfVertices; ++i) {
        
        infile >> vertexID;
        infile >> numbOfAdjacency;
        if (numbOfAdjacency>0) {
            graph.isVisited[vertexID]=true;
        }
        
        graph.outgoings[vertexID] = numbOfAdjacency;

        for (int j = 0; j < numbOfAdjacency; ++j) {
            
            infile >> adjacencyID;
            graph.addEdge(vertexID,adjacencyID);
        }
    }

    bool eulerian = isEulerian(&graph);  //whether the input is eulerian circuit

    if(!eulerian){

        outfile << "no path" <<endl;
        return 0; 
    }

    infile >> src;
    list<int> eulerianCircuit = hierholzer(&graph, src);  //değişebilir belki
    
    for (list<int>::const_iterator i = eulerianCircuit.begin(); i != eulerianCircuit.end(); ++i){
        outfile << *i << ' ';
    }

    infile.close();
    outfile.close();
 
    return 0; 

} 
