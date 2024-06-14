//
//  structs.h
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Beren Aydoğan
//  Contains the structs used in the project
//

#ifndef structs_h
#define structs_h

#include <iostream>
#include <string>

using namespace std;

struct command {
    string commandName;
    command *next;
    
    // Default constructor
    command() {
        commandName = "";
        next = nullptr;
    }
    
    command(string inpCommandName, command *inpNext)
        : commandName(inpCommandName), next(inpNext) {
        
    }
};

struct service 
{
    string servName;
    service *next;
    command *commands;
    
    // Default constructor
    service() {
        servName = "";
        next = nullptr;
        commands = nullptr;
    }
    
    service(string inpServName, service *inpNext, command *inpCommands)
        : servName(inpServName), next(inpNext), commands(inpCommands) {
        
    }
};

struct academic
{
    string name;
    int ID;
    int totalPayment;
    service request;
    academic *next;
    
    academic() {
        name = "";
        ID = 0;
        totalPayment = 0;
        next = nullptr;
    }
    
    academic(string academicName, int academicID, int payment, service requestFunc, academic *academicNext = nullptr)
        : name(academicName), ID(academicID), totalPayment(payment), request(requestFunc), next(academicNext) {
    }
};

#endif
