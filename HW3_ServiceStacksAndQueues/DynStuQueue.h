//
//  DynStuQueue.h
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Implemented from DynIntQueue.h of Week 4 Lecture
//

#ifndef DynStuQueue_h
#define DynStuQueue_h

#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class DynStuQueue
{
private:
    academic *front; // Points to the front of the queue
    academic *rear; // Points to the rear of the queue

public:
    DynStuQueue(); // Constructor to generate an empty queue
    void enqueue(string, int, int, service); // Member function to create a new academic according to given parameters and insert it at the rear of the queue
    void dequeue(string &, int &, int &, service &); // Member function dequeue removes the academic at the front of the queue, and copies its features into its reference parameters
    bool isEmpty() const; // Member function to return true if the queue is empty, and false otherwise
    void clear(); // Member function to clear all the elements in the queue by dequeuing them
};

#endif 
