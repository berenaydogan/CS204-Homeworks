//
//  ServiceStack.h
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Implemented from DynIntStack.h of Week 4 Lecture
//

#ifndef ServiceStack_h
#define ServiceStack_h

#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class ServiceStack {
private:
    command *top; // Last added element of the stack
public:
    ServiceStack(); // Constructor to generate an empty stack
    void push(string); // Member function to create a new academic according to given parameters and push it to the top of the stack
    void pop(string &); // Member function to remove the command at the top of the stack, and copy its name into its reference parameter
    void pop(); // Member function to remove the command at the top of the stack, and without copying its name to anywhere
    void popSameFunc(string); // Member function to return true if the stack is empty, and false otherwise
    bool isEmpty(); // Member function to print stack trace
    void printStackTrace(); // Member function to remove commands that came to stack from same function
    void clear(); // Member function to clear all the elements in the stack by popping them
};

#endif 
