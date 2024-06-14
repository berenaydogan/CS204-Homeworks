//
//  DynStuQueue.cpp
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Implemented from DynIntQueue.cpp of Week 4 Lecture
//

#include <iostream>
#include "DynStuQueue.h"

using namespace std;

// Constructor to generate an empty queue
DynStuQueue::DynStuQueue()
{
    front = nullptr;
    rear = nullptr;
}

// Member function to create a new academic according to given parameters and insert it at the rear of the queue
void DynStuQueue::enqueue(string name, int ID, int totalPayment, service request) {
    if (isEmpty()) {  // If the queue is empty create a new academic and make it the first element of the queue
        front = new academic(name, ID, totalPayment, request);
        rear = front;
    }
    else {  //If the queue is not empty create a new academic and add it after rear
        rear->next = new academic(name, ID, totalPayment, request);
        rear = rear->next;
    }
}

// Member function dequeue removes the academic at the front of the queue, and copies its features into its reference parameters
void DynStuQueue::dequeue(string &name, int &ID, int &totalPayment, service &request) {   
    academic *tempStu = nullptr; 
    if (isEmpty()) // If queue is empty, let the user know by displaying a message
    {
        cout << "The students' queue is empty." << endl;
    }
    else //If the queue is not empty delete the front and replace it with the next element in the queue
    {
        name = front->name;
        ID = front->ID;
        totalPayment = front->totalPayment;
        request = front->request;
        tempStu = front;
        front = front->next;
        delete tempStu;
    }
}


// Member function to return true if the queue is empty, and false otherwise
bool DynStuQueue::isEmpty() const {
    if (front == nullptr)
        return true;
    else
        return false;
}


// Member function to clear all the elements in the queue by dequeuing them
void DynStuQueue::clear() {
    academic *tempStu = front;
    
    while(!isEmpty()){ 
        dequeue(tempStu->name, tempStu->ID, tempStu->totalPayment, tempStu->request);
    }
}
