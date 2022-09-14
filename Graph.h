// File Description: creates and represents a graph and manages graph data
// through an adjecency list

//header guards
#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"
#include "Stack.h"

class Graph{
    private: 
    LinkedList* adjacencyList; //adjacency list (vertexes = index +1)
    int nodes;
    int edges;
    Stack* circuit;
    int* visitCount;
    public:
    Graph(int,int);
    ~Graph();
    void printGraph();
    bool insertEdge(int vertex, int adjVertex, int weight);
    Stack* DFS();
    void DFS_VISIT(int,Stack*);
};
#endif


