//
//  StatInsQueue.cpp
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Implemented from IntQueue.cpp of Week 4 Lecture
//

#include "StatInsQueue.h"
#include <iostream>

using namespace std;

// Constructor to create an empty queue with its capacity given as a parameter
StatInsQueue::StatInsQueue(int size) {
    queueArray = new academic[size];
    //queueArray = new instructor[size];
    queueSize = size;
    front = -1;
    rear = -1;
    numItems = 0;
}

// Member function to create a new academic according to given parameters and insert it at the rear of the queue
void StatInsQueue::enqueue(string name, int ID, int totalPayment, service request) {
    if (isFull()) { // 
         cout << "The queue is full. " << endl; // If the queue is full, print a message informing the user
    }
    else {
        rear = (rear + 1) % queueSize; // Calculate the new rear position circularly
        // Insert new item
        queueArray[rear].name = name;
        queueArray[rear].ID = ID;
        queueArray[rear].totalPayment = totalPayment;
        queueArray[rear].request = request;
        numItems++; // Update item count
    }
}

// Member function dequeue removes the academic at the front of the queue, and copies its features into its reference parameters
void StatInsQueue::dequeue(string &name, int &ID, int &totalPayment, service &request) {
    if (isEmpty()) { // If queue is empty, let the user know by displaying a message
       cout << "The instructors' queue is empty." << endl;
       exit(1);
    }
    else {
        front = (front + 1) % queueSize; // Move front
        // Retrieve the front item
        name = queueArray[front].name;
        ID = queueArray[front].ID;
        totalPayment = queueArray[front].totalPayment;
        request =  queueArray[front].request;
        numItems--; // Update item count
    }
}

// Member function to return true if the queue is empty, and false otherwise
bool StatInsQueue::isEmpty() const {
    if (numItems > 0)
        return false;
    else
        return true;
}

// Member function to return true if the queue is full, and false otherwise
bool StatInsQueue::isFull() const {
    if (numItems < queueSize)
        return false;
    else
        return true;
}

// Member function to clear all the elements in the queue by dequeuing them and setting front and rear to -1
void StatInsQueue::clear() {
    front =  - 1;
    rear =  - 1;
    numItems = 0;
}

