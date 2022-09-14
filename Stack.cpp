#include "Stack.h"
#include <cstdlib>
#include <iostream>

using namespace std;

//edge constructor
Edge::Edge(int vert1, int vert2, int newWeight){
    vertex1=vert1;
    vertex2=vert2;
    weight=newWeight;
}

//getters of edge attributes
int Edge::getVert1(){
    return vertex1;
}
int Edge::getVert2(){
    return vertex2;
}
int Edge::getWeight(){
    return weight;
}

//stack constructor
Stack::Stack(int edges){
    stk = new Edge*[edges];
    max = edges;
    top =-1;
}
//destructor for managing dynamically allocated attributes
Stack::~Stack(){
    delete[] stk;
}
//push an element onto the stack
bool Stack::push(int vert1, int vert2, int weight){  
  if(top>=max-1){
        return false;
    }
  top++;
    stk[top]= new Edge(vert1,vert2,weight);
    return true;
}
//pop an element from the stack
Edge* Stack::pop(){
    if(top==-1){
        return NULL;
    }
    top--;
    return stk[top+1];
}
//print stack values in horizontal format: (1,2) (3,4) (5,6) ...
void Stack::printHorizontal(){
    if(top==-1){
        cout <<"Empty";
    }
    else{
        for(int i=0; i<=top; i++){
            cout << "(" << stk[i]->vertex1 << "," << stk[i]->vertex2 << ") ";
        }
    }
}
/*print stack in vertical format:
(1,2)
(3,4)
(5,6)*/
void Stack::printVertical(){
    if(top==-1){
        cout <<"Empty";
    }
    else{
        for(int i=0; i<=top; i++){
            cout << "(" << stk[i]->vertex1 << "," << stk[i]->vertex2 << ")\n";
        }
    }
}
