//  CS204 Fall 2023 - HW3: Stacks & Queues and SU services
//
//  beren.aydogan_Aydogan_Beren_HW3.cpp
//  beren.aydogan_Aydogan_Beren_HW3
//
// Beren Aydoğan
//

#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>        
#include <string>
#include <vector>
#include <sstream>      // std::stringstream
#include "DynStuQueue.cpp"
#include "StatInsQueue.cpp"
#include "ServiceStack.cpp"

using namespace std;

vector <academic*> allAcademics; // Global vector to store both instructors and students who make a request and their total payments
int instructorCount = 0; // Global integer to count the number of fulfilled instructor requests to implement the logic for 10 requests for instructors and 1 request for students

// Function to delete the linked list which we had dynamically allocated by "new"
void deleteLinkedList(service* servicesHead) {
    
    service *tempServ = servicesHead;
    command *tempCommand = nullptr;
    
    if (servicesHead != nullptr) {
        // Iterate through the linked list of services
        while (tempServ) {
            tempCommand = tempServ->commands;
            // Iterate through the commands of the current service
            while (tempCommand) {
                tempServ->commands = tempCommand->next;
                delete tempCommand; // Delete the memory allocated to the command
                tempCommand = tempServ->commands;
            }
            servicesHead = tempServ->next;
            delete tempServ; // Delete the memory allocated to the service
            tempServ = servicesHead;
        }
    }
}

// Function which reads the input files, creates the required 2D linked list structure out of the files containing the functions and their respective commands and returns the head if it successful in opening every file with input name, else exits
service *readFiles(){

    string answer, line;
    service *tempServ = nullptr; // holds the last service we have read
    service *servicesHead = nullptr; // holds the head of our structure
    command *tempCommand = nullptr;
    
    cout << "Check if you want to open a service (function) defining file, \nthen press (Y/y) for 'yes', otherwise press any single key" << endl;
    cin >> answer;
    
    // While the user inputs "y" or "Y" continue taking file names as inputs to try and open
    while (answer == "y" || answer == "Y"){
        string filename;
        cout << "Enter the input file name: "; // Prompt the user for an input file name
        cin >> filename;
        ifstream input(filename); 
        
        if (input.fail() ){ // Check if input fails, print an error message and exit
            cout << "Could not open the file " << filename << endl;
            deleteLinkedList(servicesHead);
            exit(0);
        }
        
        else { 
            // Get the first line of the file which corresponds to the service/function name
            getline(input, line);
            line.pop_back(); // Removing the '\n' character from the end of the line before inserting to the linked list
            line.pop_back(); // Removing the ':' character from the end of the line before inserting to the linked list

            // Check if it is the first service on the list set it as the head of our structure, else set the next element of tempServ as the new service
            if (tempServ == nullptr) {
                tempServ = new service(line, nullptr, nullptr);
                servicesHead = tempServ; 
            }
            else {
                tempServ->next = new service(line, nullptr, nullptr);
                tempServ = tempServ->next;
            }

            // Get the lines that corresponds to commands 
            getline(input, line); 
            line.pop_back(); // Removing the '\n' character from the end of the lines before inserting them to the linked list
            tempCommand = new command(line, nullptr); 
            tempServ->commands = tempCommand; // Set the first command of the service
            
            // Create command objects using the lines we get from the file and add them to the linked list structure under their respective service until the end of file is reached
            while (!input.eof()) {
                getline(input, line);
                line.pop_back();
                tempCommand->next = new command(line, nullptr);
                tempCommand = tempCommand->next;
            }

            input.clear();
            input.close();

            cout << "Do you want to open another service defining file? \nPress (Y/y) for 'yes', otherwise press anykey" << endl; 
            cin >> answer;
        }
    }
    return servicesHead; // Return the head of the structure if no wrong input was given
}


// Function to print the structure in the required format
void printServices(service* servicesHead) {
    
    service *tempServ = servicesHead; // Pointer to iterate through the linked list containing services
    command *tempCommand = nullptr; // Pointer to iterate through the linked list of commands of services
    
    if (servicesHead != nullptr) {
        
        cout << "------------------------------------------------------------------" << endl;
        cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl;
        cout << "------------------------------------------------------------------" << endl << endl;
        
        // Going through the structure and printing according to the given format
        while (tempServ) { // Outside loop travels through the linked list which contains the services
            tempCommand = tempServ->commands;
            cout << "\n" << tempServ->servName << ":"<< endl; // Prints service name followed by a ":"
            while (tempCommand->next) { // Inside loop goes through the linked list of commands of services
                cout << tempCommand->commandName << ", "; // Prints command name followed by a ","
                tempCommand = tempCommand->next;
            }
            cout << tempCommand->commandName; // Check if it is the last command, print with a "."
            cout << "." << endl;
            tempServ = tempServ->next;
        }
    }
    else {
        cout << "List is empty.." << endl; // Check if list has no services, print "List is empty.."
    }
}

// Function which checks if a service/function available by checking the structure containing services and their respective commands, return true if found, else returns false
bool isFuncAvailable(service* servicesHead, service &request, string funcName) {
    service *tempServ = servicesHead;

    // Iterate through the linked list which contains the services
    while (tempServ) {
        // Return true if found
        if (funcName == tempServ->servName) { 
            request = *tempServ; // Return the found service using the reference parameter "request"
            return true;
        }
        tempServ = tempServ->next;
    }
    return false; // Else return false
}

// Function which checks if an academic already exists in the global vector of allAcademics, return true if it was already added, else returns false
bool isAlreadyAdded (academic *toAdd) {
    // Iterate through the allAcademics vector
    for (int i = 0; i < allAcademics.size(); i++) {
        if (allAcademics[i]->name == toAdd->name && allAcademics[i]->ID == toAdd->ID) { // Check if the unique academic (based on his/her name and ID) exists
            return true;
        }
    }
    return false;
}

// Function to enqueue instructor request to the static instuctor queue by prompting the user for its properties
void addInstructorWorkload(service* servicesHead, StatInsQueue &instructorsQueue) {
    string funcName, name;
    int ID;
    service request;
    
    cout << "Add a service (function) that the instructor wants to use: " << endl;
    cin >> funcName;
    
    if (isFuncAvailable(servicesHead, request, funcName)) { // Check if the service/function provided by the user is available
        cout << "Give instructor's name: ";  // Prompt for the name of the instructor
        cin >> name;
        
        cout << "Give instructor's ID (an int): "; // Prompt for the ID of the instructor
        cin >> ID;
        
        instructorsQueue.enqueue(name, ID, 0, request); // Enqueue instructor's request to the instuctors' queue 
        
        // Print out a message confirming the request was sucessfully added
        cout << "Prof. " << name << "'s service request of " << funcName << endl;
        cout << "has been put in the instructor's queue." << endl;
        cout << "Waiting to be served..." << endl;

        // Check if the academic whose request was added wasn't added before to the global allAcademics' vector, add it, else don't
        academic *toAdd = new academic(name, ID, 0, request);
        if (!isAlreadyAdded(toAdd)) {
            allAcademics.push_back(toAdd);
        }
        else {
            delete toAdd;
        }
    }
    else { // If the function doesn't exist print a message informing the user
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO MAIN MENU" << endl; 
    }
}

// Function to enqueue student request to the dyanmic instuctor queue by prompting the user for its properties
void addStudentWorkload(service* servicesHead, DynStuQueue &studentsQueue) {
    string funcName, name;
    int ID;
    service request;
    
    cout << "Add a service (function) that the student wants to use: " << endl;
    cin >> funcName;
    
    if (isFuncAvailable(servicesHead, request, funcName)) { // Check if the service/function provided by the user is available
        cout << "Give student's name: "; // Prompt for the name of the student
        cin >> name;
        
        cout << "Give student's ID (an int): "; // Prompt for ID name of the student
        cin >> ID;
        
        studentsQueue.enqueue(name, ID, 0, request); // Enqueue student's request to the students' queue 
        
        // Print out a message confirming the request was sucessfully added
        cout << name << "'s service request of " << funcName << " has been put in the student's queue." << endl;
        cout << "Waiting to be served..." << endl;

        // Check if the academic whose request was added wasn't added before to the global allAcademics' vector, add it if it wasn't, else don't
        academic *toAdd = new academic(name, ID, 0, request);
        if (!isAlreadyAdded(toAdd)) {
            allAcademics.push_back(toAdd);
        }
        else { 
            delete toAdd;
        }
    }
    else { // If the function doesn't exist print a message informing the user
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO MAIN MENU" << endl; 
    }
}

// Function to extract the function called within a function from the command in which it was called from whose syntax is "call function;" and return it
string extractCalledFunc(string fullCommand) {
    size_t callPos = fullCommand.find("call "); // Find the position of "call "
    size_t semicolonPos = fullCommand.find(";"); // Find the position of ";"
    
    string functionName = fullCommand.substr(callPos + 5, semicolonPos - callPos - 5); // Take the substring between the two positions we found which is equal to the name of the function

    return functionName; 
}

// Recursive function to process workload 
void processWorkload(service* servicesHead, string name, int ID, int &totalPayment, service request, ServiceStack &workloadStack) {
    service *tempServ = servicesHead;   // Pointer to iterate through the linked list containing services
    string initFuncName = request.servName; // Store the initial function name for later use

    // Iterate through the list of services
    while (tempServ) {
        if (request.servName == tempServ->servName) { // Check if the current service matches the requested service
            command *tempCommand = tempServ->commands;
            // Iterate through the commands of the current service
            while (tempCommand) {
                if (tempCommand->commandName.substr(0, 6) == "define") { // Check if the command is a "define" command
                    string toBePushed = tempServ->servName + ": " + tempCommand->commandName; // Construct the string to be pushed onto the workload stack 
                    workloadStack.push(toBePushed); 
                    totalPayment += 1; // Increment the total payment of the function by the cost of the "define" command"
                }
                else if (tempCommand->commandName.substr(0, 11) == "print stack") { // Check if the command is a "print stack" command

                    // Display a message indicating the execution of the print stack command and execute the command by printing the stack trace
                    cout << "Executing print stack; command from " << tempServ->servName << endl; 
                    cout << "PRINTING THE STACK TRACE:" << endl;
                    if (workloadStack.isEmpty()) {
                        cout << "The stack is empty" << endl;
                    }
                    else {
                        workloadStack.printStackTrace();
                    }

                    totalPayment += 2; // Increment the total payment of the function by the cost of the "print stack" command"
                }
                else if (tempCommand->commandName.substr(0, 4) == "call") { // Check if the command is a "call" command
                    string calledFunc = extractCalledFunc(tempCommand->commandName); // Extracted the name of the called function from the command
                    cout << "Calling " << calledFunc << " from " << tempServ->servName << endl; // Display a message indicating the function call
                    if (isFuncAvailable(servicesHead, request, calledFunc)) { // Check if the called function is available in the list of services
                        processWorkload(servicesHead, name, ID, totalPayment, request, workloadStack); // Call the recursive function to go through the called function
                        workloadStack.popSameFunc(calledFunc); // Remove the elements placed on the workload stack by the recursively called function
                    }
                    totalPayment += 5; // Increment the total payment of the function by the cost of the "call" command"
                }
                tempCommand = tempCommand->next;
            }
            break; // Break from the outer loop if tempCommand reaches nullptr
        }
        else {
            tempServ = tempServ->next; // If the current service doesn't match the requested service iterate through the list of services
        }
    }
    cout << initFuncName << " is finished. Clearing the stack from it's data..." << endl; // At the end of each function call display a message to inform user
}

// Function to process instructor and student requests implementing the logic of 10 requests for instructors and 1 request for students
void processWorkload(service *servicesHead, StatInsQueue &instructorsQueue, DynStuQueue &studentsQueue, ServiceStack &workloadStack) {
    
    if (!instructorsQueue.isEmpty() && instructorCount < 10) { // Check if the instructor queue is not empty and the instructor count is less than 10
        instructorCount++; // Increment the counter variable which counts the fulfilled instructor requests
        cout << "Processing instructors queue..." << endl; // Display a message to inform the user that we are processing the instructors queue
        
        string name;
        int ID, totalPayment;
        service request;
        instructorsQueue.dequeue(name, ID, totalPayment, request);
        
        cout << "Processing prof."<< name <<"'s request (with ID " << ID << ") of service (function):\n" << request.servName << endl;
        cout << "-------------------------------------------------------" << endl;
        
        processWorkload(servicesHead, name, ID, totalPayment, request, workloadStack);

        // Update the total payment for the instructor in the global vector allAcademics by iterating through it 
        for (int i = 0; i < allAcademics.size(); i++) {
            if (allAcademics[i]->name == name && allAcademics[i]->ID == ID) {
                allAcademics[i]->totalPayment += totalPayment;
                break;
            }
        }
        cout<<"GOING BACK TO MAIN MENU"<<endl;
    }
    else if (!studentsQueue.isEmpty())
    {
        if (instructorCount == 10 && !instructorsQueue.isEmpty()) { // Check if the instructor count is equal to 10
            cout<<"10 instructors are served. Taking 1 student from the queue..."<<endl; 
        }
        
        else {
            cout<< "Instructors queue is empty. Proceeding with students queue..." << endl; 
        }
        
        string name;
        int ID, totalPayment;
        service request;
        studentsQueue.dequeue(name, ID, totalPayment, request);
        
        cout << "Processing " << name << "'s request (with ID " << ID << ") of service (function):\n" << request.servName << endl;
        cout << "-------------------------------------------------------" << endl;
        
        processWorkload(servicesHead, name, ID, totalPayment, request, workloadStack);

        // Update the total payment for the student in the global vector allAcademics by iterating through it 
        for (int i = 0; i < allAcademics.size(); i++) {
            if (allAcademics[i]->name == name && allAcademics[i]->ID == ID) {
                allAcademics[i]->totalPayment += totalPayment;
                break;
            }
        }

        instructorCount = 0;
        cout<<"GOING BACK TO MAIN MENU"<<endl;
    }
    else
    {
        cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
    }
}

// Function to print users who had made a request with their names, IDs and total payments using the global allAcademic vector which is the vector where we had stored them
void displayUsers() {
    if (allAcademics.size() > 0) { // Check if allAcademic isn't empty (Valid request/requests was made)
        // Iterate through the allAcademics vector to print users' infos
        for (int i = 0; i < allAcademics.size(); i++) { 
            cout << "Name: " << allAcademics[i]->name << " ID: " << allAcademics[i]->ID << " " <<  allAcademics[i]->totalPayment << " TRY" << endl;
        }
    }
    else { // Else print a message informing the user 
        cout << "No payments defined." << endl;
    }
}

int main()
{
    StatInsQueue instructorsQueue(500);
    DynStuQueue studentsQueue;
    ServiceStack workloadStack;
    
    service *servicesHead = readFiles();
    
    printServices(servicesHead);
    
    while (true){
        cout << endl;
        cout<<"**********************************************************************"<<endl
        <<"**************** 0 - EXIT PROGRAM                        *************"<<endl
        <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
        <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl    
        <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl
        <<"**************** 4 - DISPLAY USER PAYMENTS               *************"<<endl
        <<"**********************************************************************"<<endl;
        cout << endl;
        int option;
        cout << "Pick an option from above (int number from 0 to 3): ";
        cin>>option;
        switch (option)
        {
            case 0:
                cout<<"PROGRAM EXITING ... "<<endl;
                deleteLinkedList(servicesHead);
                instructorsQueue.clear();
                studentsQueue.clear();
                workloadStack.clear();
                exit(0);
            case 1:
                addInstructorWorkload(servicesHead, instructorsQueue);
                break;
            case 2:
                addStudentWorkload(servicesHead, studentsQueue);
                break;
            case 3:
                processWorkload(servicesHead, instructorsQueue, studentsQueue, workloadStack);
                workloadStack.clear();
                break;
            case 4:
                displayUsers();
                break;
            default:
                deleteLinkedList(servicesHead);
                instructorsQueue.clear();
                studentsQueue.clear();
                workloadStack.clear();
                exit(0);
        }
    }
    return 0;
}


