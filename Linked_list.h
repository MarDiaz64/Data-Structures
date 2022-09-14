/*Date: 5 July 2021
Description: Template for Linked list and Node class
*/
#pragma once
#ifndef LIST_H
#define LIST_H
#include <cstddef>//defining NULL
#include <iostream>

//Node template
template <class T> class Node{

    private:
    T* data; //pointer to information stored in the node
    Node<T>* next; //pointer to the next Node
    
    public:
    //Constructors
    Node();
    Node(T* newData);
    Node(T* newData, Node<T>* newNext);
    //Destructor
    ~Node<T>();
    //getters
    T* getData();
    Node<T>* getNext();
    //setters:
    void setData(T* newData);
    void setNext(Node<T>* newNext);
};
//linkedList template
template <class T> class LinkedList{

    private:
    Node<T> *head, *tail; //pointers to first and last nodes in the list
    int len; //length of linkedList

    public:
    //default constructor
    LinkedList();
    
    //destructor
    ~LinkedList();
   
    //ADDING:
    void addToFront(T* data);
    void addToEnd(T* data);
    bool addAtIndex(T* data, int index);
    
    //REMOVING:
    T* removeFromFront();
    T* removeFromEnd();
    void removeTheFirst(T* data);
    void removeAllOf(T* data);
    
    //FINDING ELEMENTS:
    bool elementExists(T* data); 
    Node<T>* find(T* data);
    int indexOf(T* data);
    
    //RETREIVING:
    T* retrieveFront();
    T* retrieveEnd();
    T* retrieve(int index);
    
    //other methods:
    void printList();
    void empty();
    int length();
};

//~~~~~~~~~  NODE METHODS ~~~~~~~~~//
//Default Constructor
template <class T> 
Node<T>::Node(){
    data= NULL;
    next=NULL;
}
//alt constructor with 1 perameter
template <class T> 
Node<T>::Node(T* newData){
        data= newData;
        next= NULL;
    }    
//alt Constructor with 2 perameters
template <class T> 
Node<T>::Node(T* newData, Node<T>* newNext){
    data= newData;
    next= newNext;
}
//Destructor
template <class T> 
Node<T>::~Node(){
    delete data;
    delete next;
}
//get Data
template <class T> 
T* Node<T>::getData(){
    return data;
}
//get the nextNode
template <class T> 
Node<T>* Node<T>::getNext(){
    return next;
}
//Set data
template <class T> 
void Node<T>::setData(T* newData){
    data=newData;
}
template <class T> 
//set the next Node
void Node<T>::setNext(Node<T>* newNext){
    next= newNext;
}


//~~~~~~~~~  LINKEDLIST METHODS ~~~~~~~~~//

//default constructor
template <class T> 
LinkedList<T>::LinkedList(){
    head= NULL;
    tail= NULL;
    len=0;

}
//destructor
template <class T> 
LinkedList<T>::~LinkedList(){
    empty();
    delete head;
    delete tail;
}
//create a Node containing T data and add it to the front of the list
template <class T> 
void LinkedList<T>::addToFront(T* data){
    Node<T>* newNode= new Node<T>(data);
    newNode->setNext(head);//set next node to head
    head = newNode;// and change the head pointer to point at newNode(new 1st element in the list)
    len++;//increment length now that a new node is added
} 
//create a Node containing T data and add it to the end of the list
template <class T> 
void LinkedList<T>::addToEnd(T* data){
    if(head == NULL){//if the list is empty, just add it to the front
        addToFront(data);
        tail = head;//set tail to head since the list will only be 1 element long
    }
    else{//any other clase: create a new node with the data
        Node<T>* newNode = new Node<T>(data);
        Node<T>* current=head;
        while(current->getNext()!=NULL){
            current= current->getNext();
        }
        //then traverse the list until reaching the end.
        current->setNext(newNode);
        tail = newNode;
        len++;
    }
}
//create a Node containing T data and add it to the list at index.
//The new Node containing the data will be the #index Node in the list. 
//Return boolean for success or failure 
template <class T> 
bool LinkedList<T>::addAtIndex(T* data, int index){
    Node<T>* newNode = new Node<T>(data);
    //if setting the head 
    if(index==0){
        addToFront(data);
        return true;
    }
    //if adding to the end
    else if(index ==len){
        addToEnd(data);
        return true;
    }
    //if index out of bounds
    if(index > len || index<0){
        return false;
    }
    //else traverse the list until current= node before index
    Node<T>* current = head;
    for(int i=0; i<(index-1); i++){
        current = current->getNext();
    }
    //get the node afterward
    Node<T>* temp= current->getNext();
    //set the next node for the current node (index-1) to be the new Node
    current->setNext(newNode);
    //then set the next node of the newNode to be the temp node;
    newNode->setNext(temp);
    //increment the length now that the new node is added;
    len++;
    return true;
}
//Delete first item and return its contents
//must return a pointer because it can potentially return null
template <class T> 
T* LinkedList<T>::removeFromFront(){
    //if empty list
    if(head==NULL){
        return NULL;
    }
    //else, store the head in temp
    Node<T>* temp = head;
    //replace head with the next value in the list
    head = head->getNext();
    len--;//decrease length
    return temp->getData();//return the contents of the node
}
//Delete last item and return its contents
//must return a pointer because it can potentially return null
template <class T> 
T* LinkedList<T>::removeFromEnd(){
    if(head==NULL || tail==NULL){//if empty list
        return NULL;
    }
    //store the data in the tail and create a current pointer
    Node<T>* temp = tail; 
    Node<T>* current= head;
    //traverse the array till the node before the tail
    while(current->getNext() != tail){
        current = current->getNext();
    }
    //change that next node at the point to null
    current->setNext(NULL);
    tail = current;//set teh tail to current
    len--;//decrease length
    return temp->getData();//return contents of node
}
//find first instance of T data and remove it
template <class T> 
void LinkedList<T>::removeTheFirst(T* data) {
    if(head!=NULL){//if not an empty list
    
        //if the head's data is matching, remove the front
        if(head->getData()==data){
            removeFromFront();
        }
        else{//create 2 pointers, before at head, 
        ///and current at head.next()(since head has already been checked)
            Node<T>* current= head->getNext();
            Node<T>* before = head;
            //while not at the end of list
            while(current != NULL){
                //if the data matches set the node at before to the current.next,
                // reduce the length and stop looping
                if(*(current->getData())==*(data)){
                    before->setNext(current->getNext());
                    len--;
                    break;
                }
                //increment before and current each time
                before = current;
                current= current->getNext();
            }
        }        
    }  
}
//find each instance of T data and remove it
template <class T> 
void LinkedList<T>::removeAllOf(T* data){
    if(head!=NULL){//if non-empty list
        if(*(head->getData())==*(data)){//if data is head, remove from front
            removeFromFront();
        }
        else{//else create current node starting a head->next() and a node before that at head
            Node<T>* current= head->getNext();
            Node<T>* before = head;
            //while not at the end of the list
            while(current != NULL){
                //if the data matches
                if(*(current->getData())==*(data)){
                    //if at the end: detach the node,set tail to before and decrease length
                    if(current->getNext() == NULL){
                        before->setNext(NULL);
                        tail=before;
                        len--; 
                        break;//break since the end of the list has been reached
                    }
                    else{//in any other case, increment current and cut out the matching node
                        current = current->getNext();
                        before->setNext(current); 
                        len--;
                    }
                }
                else{//if data doesn't match:
                    before= current;
                    current=current->getNext();
                }
            }
        }
    }
}
//Returns a T/F if element exists in list
template <class T> 
bool LinkedList<T>::elementExists(T* data) {
    Node<T>* current=head;
    //traverse the list,
    while(current != NULL){
        //return true at the first match
        if(*(current->getData())==*(data)){
            return true;
        }
        current= current->getNext();
    }//if no matches found, return false:
    return false;
}
//Look for data in the list, return a pointer to its Node
template <class T> 
Node<T>* LinkedList<T>::find(T* data) {
    Node<T>* current=head;
    //traverse the list
    while(current != NULL){
        //return the node with the first matching data
        if(*(current->getData())==*(data)){
            return current;
        }
        current= current->getNext();
    }//if none found, return NULL:
    return NULL;
}
//returns an index of the item in the list (zero-based)
template <class T> 
int LinkedList<T>::indexOf(T* data) {
    if(head ==NULL){//if empty list, return -1
        return -1;
    }
    int index=0;
    Node<T>* current=head;
    //traverse the linkedList
    while(current != NULL){
        //if the data matches, return that index
        if(*(current->getData())==*(data)){
            return index;
        }
        current= current->getNext();
        index++;
    }
    //if item isn't found
    return -1;
} 
//returns the data contained in the first Node, does not delete it   
//because it could potentially return null, return a pointer
template <class T> 
T* LinkedList<T>::retrieveFront (){
    //if the end is null (typically if the list itself is empty)
    if(head ==NULL){
        return NULL;
    }
    //else return the head
    return head->getData();
}
//returns the data contained in the last Node, does not delete it
//because it could potentially return null, return a pointer
template <class T> 
T* LinkedList<T>::retrieveEnd(){
    //if the end is null (typically if the list itself is empty)
    if(tail ==NULL){
        return NULL;
    }
    //else just return the tail
    return tail->getData();
}
//returns the data contained in Node # index, does not delete it, 
//returns NULL if index is out of bounds or data does not exist
template <class T> 
T* LinkedList<T>::retrieve(int index) {
    if(index<0 || index>=len){//if out of bounds index, return null
        return NULL;
    }
    else if(head==NULL){//if empty list, return null
        return NULL;
    }
    Node<T>* current=head;
    int counter =0;
    //traverse the linkedList
    while (current!=NULL && counter<index){
        current= current->getNext();
        counter++;
    }
    //if current is null at this index, return null
    if(current == NULL){
        return NULL;
    }
    //else return the data at current:
    return current->getData();
}

//Loop through each Node and print the contents of the Node
template <class T> 
void LinkedList<T>::printList(){
    Node<T>* current = head;
    //traverse the list printing out each object
    while(current !=NULL){
        std::cout<<*(current->getData())<< " ";
        current = current->getNext();
    }
}
//empty out the list, node by node
template <class T> 
void LinkedList<T>::empty(){
    Node<T> *current = head, *next=NULL;
    //while there are still nodes left
    while(current != NULL){
        next= current;//set next to current
        delete current;//free memory at current
        current = next;//set current to next
    }
    //reset all other variables to defaults
    head = NULL;
    tail= NULL;
    len =0;
}
//return how many elements are in the list
template <class T> 
int LinkedList<T>::length(){
    return len;
} 
#endif
