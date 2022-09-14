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
    int* visitCount; //functions similar to color[u], see: DFS() for more information
    int**pi;
    int**D;
    int inf = 2000000000; //close to max int value 
    void findPath(int,int);
    Edge** odd;
    int* oddVert;
    int ovSize;
    char* color;

    public:
    Graph(int,int);
    ~Graph();
    void printGraph();
    void printOdd();
    bool insertEdge(int vertex, int adjVertex, int weight);
    Stack* DFS();
    void DFS_VISIT(int,Stack*);
    void Floyd_Warshall();
    void perfectMatching();
    void sortEdges(int);
    void printDistance(bool);
};
#endif


