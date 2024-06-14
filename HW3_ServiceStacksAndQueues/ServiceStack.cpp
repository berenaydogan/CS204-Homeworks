//
//  ServiceStack.cpp
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Implemented from DynIntStack.cpp of Week 4 Lecture
//

#include "ServiceStack.h"
#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;


// Constructor to generate an empty stack
ServiceStack::ServiceStack () {
    top = nullptr;
}

// Member function to create a new academic according to given parameters and push it to the top of the stack
void ServiceStack::push(string pushedCommandName) {
    
    command *newCommandToBePushed = new command(pushedCommandName, nullptr);

    if (isEmpty()) // If the list is empty equating newCommandToBePushed to top enough
    {
        top = newCommandToBePushed;
    }
    else { // Else insert NewNode before top
        newCommandToBePushed->next = top;
        top = newCommandToBePushed;
    }
}

// Member function to remove the command at the top of the stack, and copy its name into its reference parameter
void ServiceStack::pop(string &poppedCommandName)
{
    command *tempCommand;

    if (isEmpty()) { // If stack is empty, let the user know by displaying a message
        cout << "The stack is empty.\n";
    }
    else {   // Else pop the command on top of the stack (FILO)
        poppedCommandName = top->commandName; // Assgign the name to the reference parameter before deleting to keep it
        tempCommand = top->next;
        delete top; // Release dynamically allocated memory
        top = tempCommand;
    }
}

// Member function to remove the command at the top of the stack, and without copying its name to anywhere
void ServiceStack::pop()
{
    command *tempCommand;

    if (isEmpty()) { // If stack is empty, let the user know by displaying a message
        cout << "The stack is empty.\n";
    }
    else {   // Else pop the command on top of the stack (FILO)
        tempCommand = top->next;
        delete top; // Release dynamically allocated memory
        top = tempCommand;
    }
}

// Member function to return true if the stack is empty, and false otherwise
bool ServiceStack::isEmpty() {
    if (top == nullptr)
        return true;
    else
        return false;
}

// Member function to print stack trace
void ServiceStack::printStackTrace() {
    ServiceStack tempStack; // Use this temporary stack to reverse the order of printing
    command *tempCommand = top;

    // Iterate through the stack and copy its elements into another stack 
    while (tempCommand) {
        tempStack.push(tempCommand->commandName);
        tempCommand = tempCommand->next;
    }

    // Print the name of the top node and pop until the stack is empty
    while (!tempStack.isEmpty()) {
        command *tempCommand = tempStack.top;
        cout << tempCommand->commandName << endl;
        tempStack.pop(tempCommand->commandName);
    }
}

// Member function to remove commands that came to stack from same function
void ServiceStack::popSameFunc(string funcToBePopped) {
    size_t colonPos = top->commandName.find(":");

    while (top->commandName.substr(0, colonPos) == funcToBePopped && top != NULL) {
        pop();
    }
}

// Member function to clear all the elements in the stack by popping them
void ServiceStack::clear() {
    while (!isEmpty()) {
        pop();
    }
}
