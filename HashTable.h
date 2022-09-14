#pragma once
#ifndef HASH_TABLE
#define HASH_TABLE

#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Course{

    private:
    string courseId,days,time; 
    int credits,capacity,collisions; 

    public:
    Course(string newId, int newCredits, int newCapacity, string newDays, string newTime){
        courseId = newId;
        credits = newCredits;
        capacity = newCapacity;
        days = newDays;
        time = newTime;
	collisions=0; //not yet in the table and thus has no collisions yet
    }
    //copy constructor(use in HashTable: incertElement)
    Course(const Course& copy){
      courseId=copy.courseId;
      credits=copy.credits;
      capacity = copy.capacity;
      days = copy.days;
      time = copy.time;
      collisions= copy.collisions;
    }
    //Overload "<<" operator, to be used under option: B, in Assignment5.cpp
    friend ostream& operator<<(ostream& os, const Course& input){
        os << input.courseId << " found with credit(s) " << input.credits << ", capacity " << input.capacity << " in the days: " << input.days << " and the time: "<< input.time;
        return os;
    } 
   friend class HashTable; //allow HashTable to directly access private attributes
};

//hash table (open addressing with double hashing) using a size that a user enters 
class HashTable{
    private:
    Course** table;
    int size, relPrime;
    
    //Hashfunction using H1 & H2 (double hashed)
    int h(int key,int i){
      return (h1(key)+h2(key)*i)%size;
    }
    //sub-hashfunction 1. Uses same p=size
    int h1(int k){
      return k%size;
    }
    //should be relatively prime to h1 (both in p' and in value)
    int h2(int k){
      return (k%(relPrime))+1;
    }

    /*convert id to a workable integer key for hashfunction. to do this: 
    express this as if it was written in base 16 using each char's ascii values
    (oriignally intended to use base 128, but its too large to be practical for 
    this small of a scale & will easly overflow even unsigned integers)*/
     int IdToInt(string strKey){
        int key=0;
	    int len=strKey.length();
        for(int i=0; i<len; i++){
            int ascii=int(strKey.at(i));
            key+= (int)(ascii*pow(16,(len-1)-i));
        }
        return key;
    }

    public:
    //constructor
    HashTable(int newSize){
        size= newSize;
        table = new Course*[newSize];
        //in all cases but size<=3, relprime <size, & is relatively prime to size,
        // which optimizes the chosen hashfunction
        relPrime = 3;
    }
    //deconstructor
    ~HashTable(){
        delete[] table;
    }
    /*attempt to insert new course while keeping track of how many collisions occured in order to add it.
    returns false if unable to add to the table*/
    bool insertElement(Course inCourse){
        
        Course* newCourse= new Course(inCourse);//to be incerted
        int key= IdToInt(newCourse->courseId);// string to int key
        int numCol=0; //number of collisions

        //loop through the size of the table and check the hash at that index.
        for(int i=0; i<size; i++ ){
            int index =h(key,i);
            //if it hashes to an idex that already has an element in it, 
            //increase number of collisions it takes to incert the course and do NOT add it.
            if(table[index] != NULL){
                numCol++;
            }
            else{//if the index is empty, update the number of numCol and add the course
                newCourse->collisions=numCol;
                table[index]= newCourse;
                return true;
            }
        }
        //if all indexes has been checked that means that the hash table is full, 
        //thus the item cannot be incerted
        return false;
    }

    //search for a course by ID. Return course information if found, else return null
    Course* searchElement(string courseID){
        int key= IdToInt(courseID);//string to int key
        int i=0, j=h(key,0);
        //go through the indexes the id hashes too 1 by 1 and check their contents.
        //if a NULL slot is found or i>=size before the course is found, it does not exist in the table;
        while(table[j]!=NULL && i<size){
            if((table[j]->courseId).compare(courseID)==0){
	            return table[j];
            }
            i++;
	        j=h(key,i);
        }
        return NULL;
    }
    //search for the courseID and change its capacity
    //return false if unable to find course with the specified ID.
    bool changeCapacity(string courseID,int newCap){
        Course* element = searchElement(courseID);
        if(element == NULL){
            return false;
        }
        element->capacity=newCap;
        return true;
    }
    //print hashtable content
    void printTable(){
        cout <<left <<"Index  Collision   CourseId        Credits          Capacity           Days         Time";
        for(int i=0; i<size; i++){
            if(table[i]==NULL){
	      cout <<"\n"<<setw(8)<<i<<setw(11)<<"0"<<setw(16)<<"none"<<setw(17)<<"0"<<setw(19)<<"0"<<setw(13)<<"none" << "none";
            }
            else{
	      cout <<"\n"<<setw(8)<<i<< setw(11)<<table[i]->collisions<<setw(16)<<table[i]->courseId<<setw(17)<<table[i]->credits<<setw(19)<< table[i]->capacity <<setw(12)<<table[i]->days<<table[i]->time;
            } 
        } 
	    cout << "\n";
    }
};
#endif
