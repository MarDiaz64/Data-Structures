// Description: implements methods in the LinkedList.h file

#include "LinkedList.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

//constructor for node
Node::Node(int vertex, int newWeight){
    adjVertex= vertex;
    weight = newWeight;
    next = NULL;
    notUsed = true;
}
//returns 1 if this>second, 0 if this==second, and -1 if this<second
int Node::compareNode(Node* second){
    if(second == NULL){
        return -1; //-1 for use in line 53(makes edge.compareNode(next) easier to check)
    }
    //if (first >second)
    if(this->adjVertex > second->adjVertex){
        return 1;
    }
    //if(second >first)
    else if(this->adjVertex < second->adjVertex){
        return -1;
    }
    else{//if first == second:
        if(this->weight > second->weight){
            return 1;
        }
        else if(this->weight < second->weight){
            return -1;
        }
        else{
            return 0;
        }
    }
}
bool Node::isUsed(){
  return !(notUsed);
}
void Node::markUsed(){
  notUsed=false;
}
int Node::getVertex(){
    return adjVertex;
}
int Node::getWeight(){
    return weight;
}
Node* Node::getNext(){
  return next;
}
//insert new edge into adjacency/linked list
//return true if added successfully
bool LinkedList::insertEdge(int vertex, int weight){
    Node* edge = new Node(vertex,weight);
    if(head == NULL){//if list is empty, add at the head
        head = edge;
        size++;
        return true;
    }
    else if(edge->compareNode(head) == -1){
      edge->next = head;
      head = edge;
      size++;
      return true;
    }
    else{//otherwise, add at the next acceptable node
        Node* current = head;
        Node* next = head->next;
        while(current !=NULL){
            //do not insert duplicate nodes (same vertex & weight)
            if(edge->compareNode(current)==0){
                return false;
            }
            //if current<edge<next, insert the node edge <next when next= NULL
            else if(edge->compareNode(current) == 1  && edge->compareNode(next) == -1 ){
                current->next=edge;
                edge->next=next;
                size++;
                return true;
            }
            current = current->next;
            next = current->next;
        }
    }
    return false;//shouldn't get to this point
}

//Constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = NULL;
    size = 0;
}

//Destructor
LinkedList::~LinkedList()
{
    //traverse the list starting at the head
    Node* current = head;
    while(current != NULL){
        //temporarily store the address of node
        Node* temp =current;
        current = current->next;
        delete temp;//free memory of specified node 
    }
}

void LinkedList::printList(){
    if(head != NULL){
        Node* current = head;
        while(current != NULL){
            cout << "To: "<< current->adjVertex << " with weight "<< current->weight << endl;
            current = current->next;
        }
    }
}
int LinkedList::getSize(){
    return size;
}
Node* LinkedList::findEdge(int vertex, int weight){
    Node* edge = new Node(vertex,weight);
    Node* current =head;
    while(current != NULL){
        if(current->compareNode(edge)==0){
            return current;
        }
	current= current->next;
    }
    return NULL;
}
Node* LinkedList::getHead(){
  return head;
}
