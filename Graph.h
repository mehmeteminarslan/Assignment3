//
// Created by student on 14.12.2018.
//

#ifndef PROJECT4_GRAPH_H
#define PROJECT4_GRAPH_H

#include <list>
using namespace std;

class Graph {
    int V;    // No. of vertices

    // Pointer to an array containing adjacency
    // lists

public:
    list<int> *adj;
    Graph(int V);  // Constructor
    ~Graph();

    // function to add an edge to graph
    void addEdge(int v, int w);
    void removeEdge (int v,int w);

    // prints BFS traversal from a given source s
    bool BFS(int s,int end);
};


#endif //PROJECT4_GRAPH_H
