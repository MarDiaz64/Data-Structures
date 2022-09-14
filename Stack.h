// File Description: implementation of a stack for use in the Graph.h/cpp

//header Guards:
#pragma once
#ifndef Stack_H
#define Stack_H

//edge class for usage in stack and Graph
class Edge{
    private:
    int vertex1;
    int vertex2;
    int weight;
    
    public:
    Edge(int,int,int);
    int getVert1();
    int getVert2();
    int getWeight();

    friend class Stack;
};
//stack class for use in graph (Look at: DFS() and DFS_VISIT())
class Stack{
    private:
    Edge** stk;
    int top; 
    int max;

    public:
    Stack(int);
    ~Stack();
    bool push(int,int,int);
    Edge* pop();
    void printHorizontal();
    void printVertical();
};
#endif
