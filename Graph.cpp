// File Description: definition of Graph.h methods

#include "Graph.h"
#include "LinkedList.h"
#include "Stack.h"
#include <iostream>
using namespace std;

//graph contructor
Graph::Graph(int edge,int node){
    adjacencyList = new LinkedList[node];
    nodes = node;
    edges = edge;
    circuit = new Stack(edge);
    visitCount= new int[node];
}
//destructor to deal with dynamitcally allocated memory
Graph::~Graph(){
    delete[] adjacencyList;
    delete[] visitCount;
    delete circuit;
}

//print graph to print the vertexes and their edges
void Graph::printGraph(){
    cout << "The Graph contains:\n-------------------\n";
    for(int i=0; i<nodes; i++){
        cout << "From: " << i+1 << " with its degree " << adjacencyList[i].getSize() << endl;
        adjacencyList[i].printList();
        cout << "\n"; //add space between adjacency list
    }
}

//inserting edge into adjacency list
bool Graph::insertEdge(int vert, int adjVertex, int weight){
    if(vert <1 || vert > nodes){
        return false;
    }
    return (adjacencyList[vert-1]).insertEdge(adjVertex,weight);
}
//use a modified depth first search to create a circuit for the graph
Stack* Graph::DFS(){
  Stack* tempStack = new Stack(edges);
  for(int i=0;i<nodes;i++){
    visitCount[i]=0;
  }
  for(int i=0; i<nodes; i++){
    if(adjacencyList[i].getSize() >visitCount[i]){
      DFS_VISIT(i+1,tempStack);
    }
  }
  return circuit;
}
//search all the unused/touched edges adjacent to the specified vertex
//add them to the tempStack and once all have been cheked for a specifc node,
//pop the top one off and push it onto the circuit stack
void Graph::DFS_VISIT(int u,Stack* tempStack){
  for(Node*current=adjacencyList[u-1].getHead(); current !=NULL; current = current->getNext()){
    int i=  current->getVertex()-1;
    int v = current->getVertex();
    if(!(current->isUsed())){
      current->markUsed();
      (adjacencyList[i].findEdge(u,current->getWeight()))->markUsed(); 
      visitCount[u-1]++;
      visitCount[i]++;
      
      tempStack->push(u,v,current->getWeight());  
      
      cout << "\nCircuit: ";
      circuit->printHorizontal();
      cout << "\nStack:   ";
      tempStack->printHorizontal();
      cout << "\n";

      DFS_VISIT(v,tempStack);
    }
  }
  Edge* temp = tempStack->pop();
  if(temp != NULL){
    circuit->push(temp->getVert2(),temp->getVert1(),temp->getWeight()); 
    cout << "\nCircuit: ";
    circuit->printHorizontal();
    cout << "\nStack:   ";
    tempStack->printHorizontal();
    cout << "\n";
  }
}
