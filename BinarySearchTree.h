// Assignment #6
// Description: This file contains a club class, to create club objects to act as nodes 
// in a BST(BinarySearchTree) as well as an implementation of a binary search tree itself.

#include <iostream> //to use cout
#include <string> //to use strings
#include <cstdlib> //to use atoi

using namespace std;

//Club represents some club information
class Club
 {
  private: 
    string clubName;
    string universityName;
    Club * left, * right, * parent;


  public:
    //The following two functions are constructors
    Club()
     { 
      clubName = "?";
      universityName = "?";
      parent = NULL;
      left = NULL;
      right = NULL;
     }


    Club(string clubName1, string universityName1)
     {
      clubName = clubName1;
      universityName = universityName1;
     
      parent = NULL;
      left = NULL;
      right = NULL;
     }

    //The following functions are accessor functions
    Club * getLeft()
     {
      return left;
     }

    Club * getRight()
     {
      return right;
     }

    Club * getParent()
     {
      return parent;
     }
     
    string getClubName()
     {
         return clubName;
     }
     string getUniversityName()
     {
         return universityName;
     }
     

    //The following functions are mutator functions
    void setLeft(Club * other)
     {
       left = other;
     }

    void setRight(Club * other)
     {
       right = other;
     }

    void setParent(Club * other)
     {
       parent = other;
     }

    //The print method prints the clubName and universityName
    void print()
     {
         cout << "Club Name: " << clubName << endl;
         cout << "University Name: " << universityName << endl << endl;
     }

   //you can add more functions
 };

//class BinarySearchTree will contains clubs
class BinarySearchTree
 {
  private:
     Club * root;
     int size;
     void deletionHelper(Club* );//private helper method for deconstructor

  public:
     BinarySearchTree();
     ~BinarySearchTree();
     int postOrderTreeDelete(Club *);
     bool isEmpty();
     void inOrderTreePrint();
     void preOrderTreePrint();
     void postOrderTreePrint();
     void inOrderTreeWalk(Club *);
     void preOrderTreeWalk(Club *);
     void postOrderTreeWalk(Club *);
     Club * treeSearchNode(Club *, string, string);
     Club * treeSearch(string, string);
     Club * treeMinimum();
     Club * treeMaximum();
     Club * treeMinimumNode(Club *);
     Club * treeMaximumNode(Club *);
     Club * treeSuccessor(string,string);
     Club * treePredecessor(string,string);
     bool treeInsert(string,string);
     bool rightRotate(string, string);
     bool leftRotate(string, string);
};

//The constructor initialize the root to be NULL
BinarySearchTree::BinarySearchTree()
 {
  root = NULL;
 }


//private helper method for the deconstructor
void BinarySearchTree::deletionHelper(Club* node){
  if(node!=NULL){
    if(node->getLeft()!= NULL){
      deletionHelper(node->getLeft());
    }
    if(node->getRight() != NULL){
      deletionHelper(node->getRight());
    }
    else{
      delete node;
    }
  }
}
//Delete all nodes in the tree and perform garbage collections 
//starting from leaves (bottom-up order)-> 
// Also: print “The number of nodes deleted: X” 
//where X is the number of nodes deleted
BinarySearchTree::~BinarySearchTree(){
  deletionHelper(root);
  cout << "The number of nodes deleted: " << size << endl;
  size=0;
}

//Checks if the tree is empty
bool BinarySearchTree::isEmpty()
 {
   if (root == NULL)
    return true;
   else
    return false; 
 }

//prints all nodes using in-order
void BinarySearchTree::inOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    inOrderTreeWalk(root);
    cout << "\n";
   }
 }

//prints all nodes using pre-order
void BinarySearchTree::preOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    preOrderTreeWalk(root);
    cout << "\n";
   }
 }

//prints all nodes using post-order
void BinarySearchTree::postOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    postOrderTreeWalk(root);
    cout << "\n";
   }
 }
//prints tree in inorder
void BinarySearchTree::inOrderTreeWalk(Club * obj){
  if( obj != NULL){
    inOrderTreeWalk(obj->getLeft());
    obj->print();
    inOrderTreeWalk(obj->getRight());
  }
}
//prints tree in pre order
void BinarySearchTree::preOrderTreeWalk(Club * obj){
  if( obj != NULL){
    obj->print();
    preOrderTreeWalk(obj->getLeft());
    preOrderTreeWalk(obj->getRight());
  }
}
//prints tree in post order
void BinarySearchTree::postOrderTreeWalk(Club * obj){
  if( obj != NULL){
    postOrderTreeWalk(obj->getLeft());
    postOrderTreeWalk(obj->getRight());
    obj->print();
  }
}
//searches the tree rooted at obj for the node with the 
// specified key. returns NULL if a node is not found.
//compares univeristy names first and if they are equal 
//then club names are compared
Club * BinarySearchTree::treeSearchNode(Club * obj, string clubName, string uniName)
{
  //return if not found(obj==NULL) OR found: obj->UniName=UniName && obj->ClubName=CubName
  if(obj == NULL || (obj->getUniversityName().compare(uniName)==0 && obj->getClubName().compare(clubName)==0)){
    return obj;
  }
  else
  {
    //compare uni first
    if(obj->getUniversityName().compare(uniName)>0){ //k1<x->key1
      return treeSearchNode(obj->getLeft(),clubName,uniName);
    }
    else if(obj->getUniversityName().compare(uniName)<0){//k1>x->key1
      return treeSearchNode(obj->getRight(),clubName,uniName);
    }
    //if they are the same, then compare the club names
    else{//k1==x->key1
      if(obj->getClubName().compare(clubName)>0){//k2<x->key2
        return treeSearchNode(obj->getLeft(),clubName,uniName);
      }
      else{
        return treeSearchNode(obj->getRight(),clubName,uniName);
      }
    }
  }
}
//searches the entire tree for the node with the specified key 
//returns NULL if a node is not found.
//compares univeristy names first and if they are equal 
//then club names are compared
Club * BinarySearchTree::treeSearch(string clubName, string uniName){
  Club* current= root;
  //return if not found(obj==NULL) OR found: obj->UniName=UniName && obj->ClubName=CubName
  while(!(current == NULL || (current->getUniversityName().compare(uniName)==0 && current->getClubName().compare(clubName)==0))){
    //compare uni first
    if((current->getUniversityName()).compare(uniName)>0){ //k1<x->key1
      current=current->getLeft();
    }
    else if((current->getUniversityName()).compare(uniName)<0){//k1>x->key1
      current=current->getRight();
    }
    //if they are the same, then compare the club names
    else{//k1==x->key1
      if(current->getClubName().compare(clubName)>0){//k2<x->key2
        current=current->getLeft();
      }
      else{
        current=current->getRight();
      }
    }
  }
  return current;                                                                        
}
//returns the minium of the whole tree
Club * BinarySearchTree::treeMinimum(){
  if(isEmpty()){ //if empty tree
    return NULL;
  }
  Club* current = root;
  while(current->getLeft() != NULL){//get leftmost
    current = current->getLeft();
  }
  return current;
}
//returns the maximum of the whole tree
Club * BinarySearchTree::treeMaximum(){
  if(isEmpty()){//if empty tree
    return NULL;
  }
  Club* current = root;
  while(current->getRight() != NULL){//get rightmost
    current = current->getRight();
  }
  return current;
}
//calculate the minimum of the tree rooted at obj
Club * BinarySearchTree::treeMinimumNode(Club * obj){
  if(obj == NULL){//if empty subtree
    return NULL;
  }
  Club* current=obj;
  while(current->getLeft() != NULL){//get leftmost
    current = current->getLeft();
  }
  return current;
}
//calculate the maximum of the tree rooted at obj
Club * BinarySearchTree::treeMaximumNode(Club * obj){
  if(obj == NULL){//if empty subtree
    return NULL;
  }
  Club* current = obj;
  while(current->getRight() != NULL){//get rightmost
    current = current->getRight();
  }
  return current;
}
//return the node with the smallest key greater than the inputed key
//returns NULL if no such node exists.
Club * BinarySearchTree::treeSuccessor(string clubName, string uniName){
  Club* obj= treeSearch(clubName,uniName);  //find the element with the clubname & uniname
  if(obj==NULL){//if it doesn't exist, return null
    return NULL;
  }
  if(obj->getRight() != NULL){ //smallest element greater than obj (to the right of it)
    return treeMinimumNode(obj->getRight());
  }
  else{//if obj.right is null, get the parent until obj != obj.parent.right or parent ==null(above root)
    Club* parent= obj->getParent(); 
    while(parent != NULL && obj==parent->getRight()){
      obj= parent;
      parent= parent->getParent();
    }
    return parent;
  }
}
//return the node with the greatest key smaller than the inputed one
//returns NULL if no such node exists.
Club * BinarySearchTree::treePredecessor(string clubName,string uniName){
  Club* obj= treeSearch(clubName,uniName); //find the element with the clubname & uniname
  if(obj==NULL){//if it doesn't exist, return null
    return NULL;
  }
  if(obj->getLeft() != NULL){//largest element less than obj (to the left of it)
    return treeMaximumNode(obj->getLeft());
  }
  else{//if obj.left is null, get the parent until obj != obj.parent.right or parent == null(above root)
    Club* parent= obj->getParent();
    while(parent != NULL && obj==parent->getLeft()){
      obj= parent;
      parent= parent->getParent();
    }
    return parent;
  }
}
//incert a new node with the specified key at the correct location
//returns true if the node is successfully incerted.
bool BinarySearchTree::treeInsert(string clubName,string uniName ){
  Club* obj= new Club(clubName, uniName); //z
  Club* parent= NULL; //y
  Club* current = root; //x
  while(current != NULL){ //get the parent of the new node
    parent= current;
    //compare uni first
    if(uniName.compare(parent->getUniversityName())<0){ // z.key1 < y.key1
      current = current->getLeft();
    }
    else if (uniName.compare(parent->getUniversityName())>0){  // z.key1 > y.key1
      current=current->getRight();
    }
    //if unis are the same, compare club names
    else{ // z.key1 == y.key1
      if(clubName.compare(parent->getClubName())<0){  // z.key2 < y.key2
        current = current->getLeft();
      }
      else if(clubName.compare(parent->getClubName())>0){// z.key2 <y.key2
        current=current->getRight();
      }
      else{//if uni and club names are the same,
	// the element is already incerted and cannot be reinserted
	return false;
      }
    }
  }
  obj->setParent(parent);
  if (parent == NULL){//if the parent is null, the tree is empty, so obj is the root
      root = obj;
  }
  else{//if the parent is not null, determine if the new node is the left or right child
    //compare uni name first
    if(uniName.compare(parent->getUniversityName())<0){ // z.key1 < y.key1
      parent->setLeft(obj);
    }
    else if (uniName.compare(parent->getUniversityName())>0){  // z.key1 > y.key1
      parent->setRight(obj);
    }
    //if the unis are the same, compare the club names
    else{ // z.key1 == y.key1
      if(clubName.compare(parent->getClubName())<0){  // z.key2 < y.key2
        parent->setLeft(obj);
      }
      else{
        parent->setRight(obj);
      }
    }
  }
  size++;//increase size once item incerted
  return true;
}
//returns true if successfully right rotated the subtree 
//rooted at the node with the specified key
bool BinarySearchTree::rightRotate(string clubName, string uniName){
  Club* current= treeSearch(clubName,uniName);//x
  if(current == NULL||current->getLeft()==NULL){//cannot rotate if root or left child is null
    return false;
  }
  Club* next =current->getLeft();//y
  current->setLeft(next->getRight());
  if(next->getRight() != NULL){
    (next->getRight())->setParent(current);
  }
  next->setParent(current->getParent());
  if(current->getParent() == NULL){//if the roots parent==null(at the root of the tree), update root
    root= next;
  }
  else{
    if(current==(current->getParent())->getRight()){
      (current->getParent())->setRight(next);
    }
    else{
      (current->getParent())->setLeft(next);
    }
    next->setRight(current);
    current->setParent(next);
  }
  return true;
}
//returns true if successfully left rotated the subtree 
//rooted at the node with the specified key
bool BinarySearchTree::leftRotate(string clubName, string uniName){
  Club* current= treeSearch(clubName,uniName);//x
  if(current == NULL ||current->getRight()==NULL){//cannot rotate if root or right child is null
    return false;
  }
  Club* next =current->getRight();//y
  current->setRight(next->getLeft());
  if(next->getLeft() != NULL){
    (next->getLeft())->setParent(current);
  }
  next->setParent(current->getParent());
  if(current->getParent() == NULL){//if the roots parent==null(at the root of the tree), update root
    root= next;
  }
  else{
    if(current==(current->getParent())->getLeft()){
      (current->getParent())->setLeft(next);
    }
    else{
      (current->getParent())->setRight(next);
    }
    next->setLeft(current);
    current->setParent(next);
  }
  return true;
}
