// Description: defines a linkedlist of nodes,to be used
//as part of the adjecency list in Graph.h/cpp

//header guards
#pragma once
#ifndef LinkedList_H
#define LinkedList_H
#include <string>
using namespace std;

//class node, used in LinkedList and Graph
class Node
{
    private:
    int adjVertex;
    int weight;
    Node* next;
    bool  notUsed; 

    public:
    int compareNode(Node*); //helper method, used in linked list 
    Node(int,int);
    bool isUsed();
    void markUsed();
    int getVertex();
    int getWeight();
    Node* getNext();
    friend class LinkedList;
};

//class LinkedList will contains a linked list of nodes
class LinkedList
{
    private:
    Node * head;
    int size;

    public:
    LinkedList();
    ~LinkedList();
    bool insertEdge(int, int);
    void printList();
    int getSize();
    Node* getHead();
    Node* findEdge(int,int);
};
#endif
