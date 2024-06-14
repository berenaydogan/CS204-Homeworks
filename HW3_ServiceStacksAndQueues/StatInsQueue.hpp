//
//  StatInsQueue.hpp
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Created by Beren Aydogan on 6.11.2023.
//

#ifndef StatInsQueue_hpp
#define StatInsQueue_hpp

#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class StatInsQueue {
private:
    //instructor *queueArray;
    academic *queueArray;
    int queueSize;  //capacity of queue
    int front;
    int rear;
    int numItems;  //# of elements currently in the queue
public:
    StatInsQueue(int);  //constructor, parameter is capacity
    void enqueue(string, int, int, service);
    void dequeue(string &, int &, int &, service &);
    bool isEmpty() const;
    bool isFull() const;
    void clear();  //removes all elements
};

#endif /* StatInsQueue_hpp */
