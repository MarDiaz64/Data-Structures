// File Description: implementation of a stack for use in the Graph.h/cpp

//header Guards:
#pragma once
#ifndef Stack_H
#define Stack_H

#include "LinkedList.h"
using namespace std;

//stack class for use in graph (Look at: DFS() and DFS_VISIT())
class Stack{
    private:
    Edge** stk;
    int top; 
    int max;

    public:
    Stack(int);
    ~Stack();
    bool push(int,int,int,bool);
    Edge* pop();
    void printHorizontal();
    void printVertical();
};
#endif
