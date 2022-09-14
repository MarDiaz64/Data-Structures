// File Description: definition of Graph.h methods

#include "Graph.h"
#include "LinkedList.h"
#include "Stack.h"
#include <iostream>
#include <iomanip>

using namespace std;

//graph contructor
Graph::Graph(int edge,int node){
  adjacencyList = new LinkedList[node];
  nodes = node;
  edges = edge;
  //DFS variables
  circuit = new Stack(edge*2);
  visitCount= new int[node];
  color = new char[node];

  //for perfect match (at most 1/2 edges)
  odd = new Edge*[edge/2];

  //floyd-warshall arrays
  int n = nodes+1;
  pi =new int*[n];
  D  =new int*[n];
  for(int i=0; i<n;i++){
    pi[i]=new int[n];
    D[i]=new int[n];
    for(int j=0;j<n;j++){
      pi[i][j]= -1;
      if(i==j){
        D[i][j]=0;
      }
      else{
        D[i][j]=inf;
      }
    }
  }
}
//destructor to deal with dynamitcally allocated memory
Graph::~Graph(){
  delete[] adjacencyList;
  delete[] visitCount;
  delete circuit;
}

//inserting edge into adjacency list
bool Graph::insertEdge(int vert, int adjVertex, int weight){
  if(vert <1 || vert > nodes){
      return false;
  }
  //every time a vertex is added, update the D^(0) and pi^(0) array
  D[vert][adjVertex]=weight; 
  pi[vert][adjVertex]=vert; 
  return (adjacencyList[vert-1]).insertEdge(vert,adjVertex,weight,false);
}
//use a modified depth first search to create a circuit for the graph
Stack* Graph::DFS(){
  //create new temp stack
  Stack* tempStack = new Stack(edges);
  //counter, functions similar to color[u]
  for(int i=0;i<nodes;i++){
    color[i]='w';
  }
  //visit each vertex in the graph so long as it is not black
  // Black: degree = visitCount, aka all adj nodes visited
  for(int i=0; i<nodes; i++){
    if(color[i]!='b'){
      DFS_VISIT(i+1,tempStack);
    }
  }
  //return the completed circuit
  return circuit;
}
//search all the unused/touched edges adjacent to the specified vertex
//add them to the tempStack and once all have been cheked for a specifc node,
//pop the top one off and push it onto the circuit stack
void Graph::DFS_VISIT(int u,Stack* tempStack){
  //for vertex U, visit all adjacent nodes:
  for(Edge*current=adjacencyList[u-1].getHead(); current !=NULL; current = current->getNext()){
    int i=  current->getVert2()-1;
    int v = current->getVert2();
    
    //if an edge has not been used:
    if(!(current->isUsed())){

      //mark it and its inverse(ex: (1,2) AND (2,1)) USED
      current->markUsed();
      (adjacencyList[i].findEdge(u,current->getWeight(),current->isVirtual()))->markUsed(); 
      
      //grey for both vertexes
      color[u-1] ='g';
      color[v-1]='g';
      //push it onto the tempstack 
      tempStack->push(u,v,current->getWeight(),current->isVirtual());  

      //once completed, go to v's next edge (ex: for ) (3,1)(1,2), go to v=2)
      DFS_VISIT(v,tempStack);
    }
  }

  color[u-1]='b';//finished thus black

  //once all of the nodes have been checked, if the tempStack isn't empty,
  //pop the top node off 
  Edge* temp = tempStack->pop();
  
  if(temp != NULL){
    if(!temp->isVirtual()){//if its not virtual, add it normally to the circuit
      circuit->push(temp->getVert2(),temp->getVert1(),temp->getWeight(),false); 
    }
    //if its virtual, find the path between the two vertexes and add all of those edges to the circuit
    else{
      findPath(temp->getVert2(),temp->getVert1());
    }
  }
}

//private helper method for use in DFS_VISIT to find paths of virtual edges 
//using the pi array
void Graph::findPath(int i,int j){
  if(pi[i][j]!=i){
    findPath(i,pi[i][j]);
  }
  circuit->push(pi[i][j],j,1,true);
}


//find the shortest paths for all pairs of vertices on the graph. 
//In the Floyd-Warshall function, you need to compute the two 
//dimensional D (distance) array and piTemp array.  
void Graph::Floyd_Warshall(){
  int n = nodes+1;
  /*for(int k=1; k<n;k++){
    for(int i=1;i<n;i++){
      for(int j=1;j<n;j++){
        int direct = D[i][j];
        int withK;
        if(D[i][k] == inf || D[k][j]==inf){
          withK=inf;
        }
        else{
          withK = D[i][k] + D[k][j];
        }
        if(direct>withK){
          D[i][j]=withK;
          pi[i][j]=pi[k][j];
        }
        else{
          D[i][j]=direct;
          pi[i][j]=pi[i][j];
        }
      }
    }
  }
  for(int i =1; i<nodes+1;i++){
    cout <<i<< "| ";
    for(int j=1;j<nodes+1;j++){
      cout << pi[i][j]<<" ";
    }
    cout<<"\n";
  }*/

  //create temp matrixes
  int*** piTemp = new int**[n];
  int*** DTemp= new int**[n];
  for(int i=0; i<n;i++){
    piTemp[i]= new int*[n];
    DTemp[i]= new int*[n];
     for(int j=0; j<n;j++){
      piTemp[i][j]= new int[n];
      DTemp[i][j]= new int[n];
      for(int k=0; k<n;k++){
	DTemp[i][j][k]=-1111;
      }
    }
  }
  //temp list of edges:
  DTemp[0]=D;
  piTemp[0]=pi;

  for(int k=1; k<n;k++){
    for(int i=1;i<n;i++){
      for(int j=1;j<n;j++){
        int direct = DTemp[k-1][i][j];
        int withK;
        if(DTemp[k-1][i][k] == inf || DTemp[k-1][k][j]==inf){
          withK=inf;
        }
        else{
          withK = DTemp[k-1][i][k] + DTemp[k-1][k][j];
        }
        if(direct>withK){
          DTemp[k][i][j]=withK;
          piTemp[k][i][j]=piTemp[k-1][k][j];
        }
        else{
          DTemp[k][i][j]=direct;
          piTemp[k][i][j]=piTemp[k-1][i][j];
        }
      }
    }
  }
  D=DTemp[nodes];
  pi=piTemp[nodes];
} 

//print warhsall results
void Graph::printDistance(bool printOdd){
  int n=0;
  if(!printOdd){
    n=nodes+1;
  }
  else{
    n=ovSize;
  }
  int num = 1;
  if(printOdd){
      num=oddVert[1];
  }
  cout << setw(7)<<"|"<<setw(6)<<num;
  for(int i=2; i<n;i++){
    num = i;
    if(printOdd){
      num=oddVert[i];
    }
    cout<<setw(5)<<num;
  }
  cout<<"\n";
  cout <<"---  -+-";
  for(int i=1; i<n;i++){
    cout<<setw(5)<<"---";
  }
  cout << "\n";
  for(int i=1; i<n;i++){
    num = i;
    int num2 = 1;
    if(printOdd){
      num=oddVert[i];
      num2=oddVert[1];
    }
    cout<< setw(3)<<num<<setw(4)<<"|";
    if(D[num][num2]==inf){
      cout <<setw(6)<<"INF";
    }
    else{
      cout<<setw(6)<<D[num][num2];
    }
    for(int j=2; j<n;j++){
      num2 = j;
      if(printOdd){
        num2=oddVert[j];
      }
      if(D[num][num2] ==inf){
	      cout<<setw(5)<<"INF";
      }
      else{
        cout<<setw(5)<<D[num][num2];
      }
	  }
    cout << "\n";
  }
  cout<< "\n";
}

//print graph throuh its nodes and the adjacency table
void Graph::printGraph(){
  cout << "The Graph contains:\n-------------------\n";
  for(int i=0; i<nodes; i++){
      cout << "From: " << i+1 << " with its degree " << adjacencyList[i].getSize() << endl;
      adjacencyList[i].printList();
      cout << "\n"; //add space between adjacency list
  }
}
//prind the vertcies with an odd degreee and build the oddVert array for future use
void Graph::printOdd(){
  cout << "The odd-degree vertices in G: O = { ";
  int temp[nodes];
  temp[0]=0;
  int j=1;
  for(int i=0; i<nodes;i++){
    if(adjacencyList[i].getSize()%2!=0){
      temp[j]=i+1;
      j++;
      cout<<i+1<<" ";
    }
  }
  cout<<"}\n\n";
  oddVert = new int[j];
  ovSize=j;
  for(int i=0; i<ovSize;i++){
    oddVert[i]=temp[i];
  }
}

//get a set of perfect matching edges (they do not share any vertexes)
void Graph::perfectMatching(){
  //collect the edges in the result of floyd-warshall on odds
  int k=0;
  for(int i=1;i<ovSize;i++){
    int v1= oddVert[i];
    for(int j=i;j<ovSize;j++){
      int v2=oddVert[j];
      if(v1<v2){
	      odd[k] = new Edge(v1,v2,D[v1][v2],false);
      	k++;
      }
    }
  }
  //sort the edges
  sortEdges(k);


  //M is the set of perfect matching vertices.
  //add the first one and add its vertices to the foundVertex list
  Edge** M = new Edge*[k];
  M[0]=odd[0];
  int found=0;
  int foundVert[k*2];
  foundVert[found]=M[0]->getVert1();
  foundVert[found+1]=M[0]->getVert2();
  found +=2;

  //compare the edges' vertices with each new found vertex so that
  //no edges are added to the set M where two edges share a vertex
  int i=0;
  for(int j=0; j<k;j++){
    bool sameVert=false;
    for(int g=0; g<found; g++){
      //if one vertex matches, no need to do more comparisons, it cannot be added to M
      if(odd[j]->getVert1()==foundVert[g] || odd[j]->getVert2()==foundVert[g]){
        sameVert=true;
        break;
      }
    }
    //if it shares no common vertices with the already inserted edges, add it to M
    if(!sameVert){
      M[i+1]=odd[j];
      foundVert[found]=M[i+1]->getVert1();
      foundVert[found+1]=M[i+1]->getVert2();
      found +=2;
      i++;
    }
  }
  //print the edges and add them to the adjacencylist
  cout <<"\nThe greedy perfect matching in O: M = {";
  if(M[0]!=NULL){
    for(int j=0; j<=i;j++){
      int v1 =M[j]->getVert1();
      int v2 =M[j]->getVert2();
      int w = M[j]->getWeight();
      (adjacencyList[v1-1]).insertEdge(v1,v2,w,true);
      (adjacencyList[v2-1]).insertEdge(v2,v1,w,true);
      edges+=2;
      cout << " ("<< v1<<","<<v2<<")";
    }
  }
  cout<< " }\n";
}
//Sort the odd degree vertices by weight then vertex1 then vertex2.
//this is implmeneted using insertion sort
void Graph::sortEdges(int k){
  for(int j = 1;j<k;j++){
    Edge* key = odd[j];
    int i=j-1;
    while(i>=0 && odd[i]->compareWeightFirst(key)==1){
      odd[i+1]=odd[i];
      i=i-1;
    }
    odd[i+1]=key;
  }
  //print the result
  cout << "The sorted edges of odd-degree vertices from Floyd-Warshall:"<<endl;
  for(int j=0;j<k;j++){
    cout <<"("<<odd[j]->getVert1()<<","<<odd[j]->getVert2()<<") with its weight "<<odd[j]->getWeight()<<endl;
  }
}
