//
//  StatInsQueue.h
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Implemented from IntQueue.h of Week 4 Lecture
//

#ifndef StatInsQueue_h
#define StatInsQueue_h

#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class StatInsQueue {
private:
    academic *queueArray;
    int queueSize;  // Capacity of queue
    int front; // Points to the front of the queue 
    int rear; // Points to the rear of the queue
    int numItems;  //Number of elements currently in the queue
public:
    StatInsQueue(int);  // Constructor to create an empty queue with its capacity given as a parameter
    void enqueue(string, int, int, service); // Member function to create a new academic according to given parameters and insert it at the rear of the queue
    void dequeue(string &, int &, int &, service &); // Member function dequeue removes the academic at the front of the queue, and copies its features into its reference parameters
    bool isEmpty() const; // Member function to return true if the queue is empty, and false otherwise
    bool isFull() const; // Member function to return true if the queue is full, and false otherwise
    void clear();  // Member function to clear all the elements in the queue by dequeuing them and setting front and rear to -1
};

#endif
