#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <ctime>


using namespace std;

int count_ID = 0;
int airline_ID = 0;

struct flight{
    string from;
    string to;
    int hour;
    int min;
    int price;
    int ID;
  
    flight *next;
    flight *prev;
  
    flight() {
        
    }
    
    flight(flight *new_flight)
        : from(new_flight->from), to(new_flight->to), hour(new_flight->hour), min(new_flight->min), price(new_flight->price), next(new_flight->next), prev(new_flight->prev), ID(new_flight->ID) {
    }
    
    flight(string input_from, string input_to, int input_hour, int input_min, int input_price)
        : from(input_from), to(input_to), hour(input_hour), min(input_min), price(input_price), next(nullptr), prev(nullptr) {
            
    }
    
    flight(string input_from, string input_to, int input_hour, int input_min, int input_price, int input_ID)
        : from(input_from), to(input_to), hour(input_hour), min(input_min), price(input_price), next(nullptr), prev(nullptr), ID(input_ID) {
            
    }
    
};

struct airline{
    string name;
    int ID;
    airline *next;
    flight *flights;

    airline() {
        
    }
    
    airline(string input_name, int input_ID, airline *input_next, flight *input_flights)
        : name(input_name),ID(input_ID), next(input_next), flights(input_flights) {
            
    }
};

// Function to use while sorting flights according to their times
bool compare_flights(const flight &flight_one, const flight &flight_two) {
    if (flight_one.hour == flight_two.hour) {
        return flight_one.min < flight_two.min;
    }
    return flight_one.hour < flight_two.hour;
}

// Function to modify the flights by adding their IDs and sorting the vectors
void modify_inputs(vector<string> &airlines, vector<vector<flight> > &flights) {
    
    // Adding the ID of the flights by looping through the matrix flights
    for (int i = 0; i < flights.size(); i++) {
        for (int j = 0; j < flights[i].size(); j++) {
            flights[i][j].ID = count_ID;
            count_ID++; // Increase the count_ID as we go through the flights as it is a global variable that counts the flights that we've added into the structure
        }
    }
    count_ID--; // Decrease the count_ID as it was increased an excess time in the loop
        
    // Sort flights
    for (int i = 0; i < flights.size(); i++) {
        sort(flights[i].begin(), flights[i].end(), compare_flights);
    }
}


pair<vector<string>, vector<vector<flight> > > read_files(bool input_done){
    ///READ FLIGHTS///
    vector<string> airlines;
    vector<vector<flight> > flights(100);
    
    while (not input_done){
        string airline_name;
        string filename;
        cout << "Enter the name of airline: ";
        cin >> airline_name;
        cout << "Enter the name of airline file: ";
        cin >> filename;
        ifstream input(filename);
        
        if(filename == "done") {
            input_done = true;
            modify_inputs(airlines, flights);
            return make_pair(airlines, flights);
        }
        
        while (input.fail() ){
            cout << "Could not open file: " << filename << endl;
            cout << "Enter the name of airline: ";
            cin >> airline_name;
            cout << "Enter the name of airline file: ";
            cin >> filename;
            input.open(filename);
            
            if(filename == "done"){
                input_done = true;
                modify_inputs(airlines, flights);
                return make_pair(airlines, flights);
            }
        }
        
        airlines.push_back(airline_name);
        cout << "Processing input file: " << filename <<endl;
        
        int line_no = 0;
        vector<string> lines;
        string line;
        int vector_location = airlines.size() - 1;
        while(getline(input, line)){
            lines.push_back(line);
            line_no += 1;
            if(line_no % 5 == 0) {
                flight a_flight(lines[line_no-5], lines[line_no-4], stoi(lines[line_no-3]), stoi(lines[line_no-2]), stoi(lines[line_no-1]));
                flights[vector_location].push_back(a_flight);
            }
        }
    }
    
    if(input_done){
        cout << "Input files are already read, however you can do manual changes.." << endl;
    }
        
    modify_inputs(airlines, flights); // Modifying the flights by adding their IDs and sorting the vectors
    return make_pair(airlines, flights);
}



// Function to create the structure in the required format
airline* make_linked_list_structure(vector<string> airlines, vector<vector<flight> > flights){
    airline_ID = airlines.size() - 1;

    airline *airline_head, *temp_airline, *curr_airline;
    flight *temp_flight, *curr_flight;
    
    // Creating the node for the last airline to initialize the structure by creating an airline node from the last element of airines vector
    curr_airline = new airline;
    curr_airline->name = airlines[airlines.size() - 1];
    curr_airline->ID = airlines.size() - 1;
    curr_airline->next = nullptr;
    
    curr_airline->flights = new flight(flights[airlines.size() - 1][0]);
    curr_airline->flights->prev = nullptr;
    
    
    // Creating nodes for the other airlines and their first flights by going through the airlines and flights vectors
    for(int i = airlines.size() - 2; i >= 0; i--) {
        temp_airline = new airline;
        temp_airline->name = airlines[i];
        temp_airline->ID = i;
        temp_airline->next = curr_airline;
        
        temp_airline->flights = new flight(flights[i][0]);
        temp_airline->flights->prev = nullptr;
        
        curr_airline = temp_airline;
    }

    // Setting the head of the linked list
    airline_head = curr_airline;
    
    // Creating the doubly linked list for flights
    for (int i = 0; i < airlines.size(); i++) {
        temp_flight = new flight(flights[i][1]);
        curr_airline->flights->next = temp_flight;
        temp_flight->prev = curr_airline->flights;
        curr_flight = temp_flight;
        for (int j = 2; j < flights[i].size(); j++) {
            temp_flight = new flight(flights[i][j]);
            curr_flight->next = temp_flight;
            temp_flight->prev = curr_flight;
            curr_flight = temp_flight;
        }
        curr_flight->next = nullptr;
        curr_airline = curr_airline->next;
    }
    return airline_head; // Returning head to be used in other functions
}

// Function to print the structure in the required format
void print_all(airline* head) {
    
    airline *temp_airline = head;
    
    if (head != nullptr) {
        
        // Going through the structure and printing every single flight under their respective airlines if head isn't equal to nullptr (i.e. structure isn't empty)
        while (temp_airline != nullptr) {
            flight *temp_flight = temp_airline->flights;
            cout << "###################################" << endl;
            cout << "### AIRLINE ID: " << temp_airline->ID << " ###" << endl;
            cout << "NAME:" << temp_airline->name << endl;
            cout << "FLIGHTS:" << endl;
            while (temp_flight != nullptr) {
                cout << "#[" << temp_flight->ID << "|" << temp_flight->from << "->" << temp_flight->to << "|" << temp_flight->hour << ":" << temp_flight->min << "|" << temp_flight->price << "TRY]#";
                temp_flight = temp_flight->next;
            }
            cout << endl;
            temp_airline = temp_airline->next;
        }
    }
    else {
        cout << "List is empty.." << endl;
    }
}

// Function to check if the airline of the flight that is required to be added to the structure is already available, returns true if it is (Helper function for the function "void add_flight_with_input(airline* head)")
bool isAirlineAvailable(airline *head, string input_airline) {
    airline *curr_airline = head;
    
    // Going through the airlines linked list to see if the airline already exists
    while (curr_airline != nullptr) {
        if (input_airline == curr_airline->name) {
            return true; // Return true if it is available
        }
        curr_airline = curr_airline->next;
    }
    return false; // Return false if it is not available
}

// Function to add a flight to structure according to the input given by the user, creates an airline if the airline of the flights doesn't already exist in the structure
void add_flight_with_input(airline* head) {
    string input_airline, input_from, input_to;
    int input_hour, input_min, input_price;
    airline *temp_airline = head;
    cout << "Adding manual entry:" << endl;
    cout << "AIRLINE: ";
    cin >> input_airline;
    cout << "FROM: ";
    cin >> input_from;
    cout << "TO: ";
    cin >> input_to;
    cout << "HOUR: ";
    cin >> input_hour;
    cout << "MIN: ";
    cin >> input_min;
    cout << "PRICE: ";
    cin >> input_price;
    
    count_ID++; // Increase the count_ID which is a global variable that counts the flights that we've added into the structure
    
    flight *new_flight = new flight(input_from, input_to, input_hour, input_min, input_price, count_ID); // Create a new flight for the flight to be added and initialize a pointer that points to it
    
    if (isAirlineAvailable(head, input_airline)) { // If airline is available already, add the flight under it
    
        while (temp_airline->name != input_airline) {
            temp_airline = temp_airline->next;
        }
        
        flight *temp_flight = temp_airline->flights;
        
        
        // Adding the flight to the doubly linked list while keeping it sorted
        if (new_flight->hour < temp_flight->hour || (new_flight->hour == temp_flight->hour && new_flight->min < temp_flight->min)) {
            new_flight->prev = nullptr;
            new_flight->next = temp_flight;
            temp_flight->prev = new_flight;
            temp_airline->flights = new_flight;
        }
        
        else {
            while (temp_flight->next != nullptr && (new_flight->hour > temp_flight->hour || (new_flight->hour == temp_flight->hour && new_flight->min > temp_flight->min))) {
                temp_flight = temp_flight->next;
            }
            
            if (temp_flight->next == nullptr) {
                if (!(new_flight->hour > temp_flight->hour || (new_flight->hour == temp_flight->hour && new_flight->min > temp_flight->min))) {
                    new_flight->next = temp_flight;
                    new_flight->prev = temp_flight->prev;
                    temp_flight->prev->next = new_flight;
                    temp_flight->prev = new_flight;
                }
                else {
                    new_flight->next = nullptr;
                    new_flight->prev = temp_flight;
                    temp_flight->next = new_flight;
                }
            }
            else {
                new_flight->next = temp_flight;
                new_flight->prev = temp_flight->prev;
                temp_flight->prev->next = new_flight;
                temp_flight->prev = new_flight;
            }
        }
    }
    
    else { // If airline is not available already, add it to the structure
        airline_ID++; // Increase the airline_ID which is a global variable that counts the airlines that we've added into the structure
        while (temp_airline->next != nullptr) {
            temp_airline = temp_airline->next;
        }
        temp_airline->next = new airline(input_airline, airline_ID, nullptr, new flight(input_from, input_to, input_hour, input_min, input_price, count_ID)); // Create a new airline for the airline to be added and initialize a pointer that points to it
        temp_airline->next->flights->next = nullptr;
        temp_airline->next->flights->prev = nullptr;
    }
    cout << "Flight ID " << count_ID << " is added to the list.." << endl;
}

// Function to remove an airline from the structure and delete it if there are no flights left under it (Helper function for the function "void remove_flight_with_input(airline* head) ")
void remove_airline (airline *airline_to_be_deleted, airline *&head){
    airline *temp_airline;
    if (airline_to_be_deleted == head) { // If airline to be deleted is equal to head, we can directly delete it
        head = airline_to_be_deleted->next; // Equate the next flight in the linked list to the head
        delete airline_to_be_deleted;
    }
    else { // If airline to be deleted is not equal to head, iterate through the linked list until we find the airline to be deleted
        temp_airline = head;
        while (temp_airline->next != airline_to_be_deleted) {
            temp_airline = temp_airline->next;
        }
        temp_airline->next = airline_to_be_deleted->next;
        delete airline_to_be_deleted;
    }
}

// Function to remove an flight from the structure and delete it (Helper function for the function "void remove_flight_with_input(airline* head) ")
void remove_flight(flight *flight_to_be_deleted, airline *airline_of_flight){
    flight *temp_flight;
    if (flight_to_be_deleted == airline_of_flight->flights) { // If flight to be deleted is the first flight of an airline, we should check if it is the only flight under that airline
        if (flight_to_be_deleted->next != nullptr) { // If it isn't the only flight, change airline_of_flight->flights to point to the next flight after the flight to be deleted
            airline_of_flight->flights = new flight(flight_to_be_deleted->next);
            delete flight_to_be_deleted;
        }
        else { // If it is the only flight, change airline_of_flight->flights to point to nullptr (airline will also be deleted)
            delete flight_to_be_deleted;
            airline_of_flight->flights = nullptr;
        }
    }
    else { // If airline to be deleted is not the first flight of an airline, iterate through the doubly linked list until we find the flight to be deleted
        temp_flight = airline_of_flight->flights;
        while (temp_flight->next != flight_to_be_deleted) {
            temp_flight = temp_flight->next;
        }
        temp_flight->next = flight_to_be_deleted->next;
        delete flight_to_be_deleted;
    }
}

// Function to remove an flight from the structure according to the input given by the user, deletes the airline if there are no flights left under it after the given flight is removed
void remove_flight_with_input(airline *&head) {
    
    if (head != nullptr) {
        int input_ID;
        bool breakAll = false;
        
        airline *temp_airline = head, *airline_of_flight = nullptr;;
        flight *temp_flight = temp_airline->flights, *flight_to_be_deleted = nullptr;
        
        cout << "Flight id to remove: ";
        cin >> input_ID;
        
        // Checking all the flights on the doubly linked list until we find the flight with the ID that we want to remove
        while (temp_airline != nullptr) {
            temp_flight = temp_airline->flights;
            while (temp_flight != nullptr) {
                if (temp_flight->ID == input_ID) {
                    breakAll = true;
                    break;
                }
                else {
                    temp_flight = temp_flight->next;
                }
            }
            if (breakAll) {
                break;
            }
            else {
                temp_airline = temp_airline->next;
            }
        }
        
        flight_to_be_deleted = temp_flight;
        airline_of_flight = temp_airline;
        
        if (flight_to_be_deleted == nullptr) { // If the flight with the given ID is not found on the list, print out that there is no flight with that id
            cout << "There is no flight with id " << input_ID << endl;
        }
        
        else { //  If the flight with the given ID is found on the list, delete it using the helper funtions
            remove_flight(flight_to_be_deleted, airline_of_flight);
            
            if (airline_of_flight->flights == nullptr){ // Delete the airline as well if it is emptied out
                remove_airline(airline_of_flight, head);
            }
            cout << "Flight ID " << input_ID << " is removed from the list.." << endl;
        }
    }
    
    else {
        cout << "The list is empty.." << endl;
    }
}


// Function to add a flight to the route and increasing the total price of the route (Helper function for the function "int pathfinder(airline *head, string &curr_loc, const string &destination, const int &max_trans, int &total_price, vector <flight> &route, vector <flight> &best_route, vector <airline> &route_airline, int &best_price, airline *&curr_airline, flight *&curr_flight, flight *&found_flight, airline *&found_airline)")
void addFlightToRoute(flight *&curr_flight, airline *&curr_airline, string &curr_loc, vector<flight> &route, vector<airline> &route_airline, int &total_price) {
    route.push_back(*curr_flight);
    route_airline.push_back(*curr_airline);
    total_price += curr_flight->price;
}

// Function to move to the next flight to begin searching from after popping back a flight from the route (Helper function for the function "int pathfinder(airline *head, string &curr_loc, const string &destination, const int &max_trans, int &total_price, vector <flight> &route, vector <flight> &best_route, vector <airline> &route_airline, int &best_price, airline *&curr_airline, flight *&curr_flight, flight *&found_flight, airline *&found_airline)")
void moveToNextAfterPop(flight *&curr_flight, airline *&curr_airline, flight *&found_flight, airline *&found_airline, string &curr_loc) {
    curr_loc = found_flight->from; // Change current location to where the flight we have popped back to is going to so we search for flights taking off from that location
    curr_flight = found_flight; // Set the current flight to where we had found the previous flight
    curr_airline = found_airline; // Set the current airline to where to the previous flight's airline's location
    
    if (curr_flight->next != nullptr) {
        curr_flight = curr_flight->next;
    }
    else if (curr_flight->next == nullptr && curr_airline->next != nullptr) {
        curr_airline = curr_airline->next;
        curr_flight = curr_airline->flights;
    }
}

// Function to find the cheapest path in between locations given by the user
int pathfinder(airline *head, string &curr_loc, const string &destination, const int &max_trans, int &total_price, vector <flight> &route, vector <flight> &best_route, vector <airline> &route_airline, int &best_price, airline *&curr_airline, flight *&curr_flight, flight *&found_flight, airline *&found_airline) {

    if (head != nullptr) {
        // While the size of the route is zero (i.e. we have not already found first flight) we try to find the first flight of our route whose from is equal to the curr_loc, if we can't find anything we return 0 and exit.
        while (route.size() == 0) {
            if (curr_flight->from != curr_loc) { // If current flight is not from the current location we try to find the first flight of our route whose from is equal to the curr_loc by passing through the values and recalling the function in each pass
                if (curr_flight->next != nullptr) { // If the next flight is not equal to nullptr
                    curr_flight = curr_flight->next; // Move to the next flight
                }
                else if (curr_flight->next == nullptr && curr_airline->next != nullptr) { // If the next flight is equal to nullptr and the next airline isn't equal to nullptr
                    curr_airline = curr_airline->next; // Move to the next airline
                    curr_flight = curr_airline->flights; // Move to the next flight
                }
                else {
                    return 0; // If no flight from the initial given location is found, return 0 to exit
                }
            }
            
            else { // If current flight is from the current location
                if (curr_flight->to != destination) { // If current flight is not to our destination, this means the flight could only be a substep, in this case first step
                    if ((total_price + curr_flight->price) < best_price) {
                        addFlightToRoute(curr_flight, curr_airline, curr_loc, route, route_airline, total_price); // Add flight to route
                        curr_loc = curr_flight->to; // Change current location to where the flight we are taking is going to so we search for flights taking off from that location
                        
                        // Set current airline to head and current flight to its first flight to make sure that we start searching the next flight from the beginning of our structure, not missing any steps
                        curr_airline = head;
                        curr_flight = head->flights;
                    }
                    else {
                        if (curr_flight->next != nullptr) { // If the next flight is not equal to nullptr
                            curr_flight = curr_flight->next; // Move to the next flight
                        }
                        else if (curr_flight->next == nullptr && curr_airline->next != nullptr) { // If the next flight is equal to nullptr and the next airline isn't equal to nullptr
                            curr_airline = curr_airline->next; // Move to the next airline
                            curr_flight = curr_airline->flights; // Move to the next flight
                        }
                        else {
                            return 0; // If no flight from the initial given location is found, return 0 to exit
                        }
                    }
                }
                else { // If current flight is to our destination, in this case this means that it is a direct flight
                    
                    if (curr_flight->price < best_price) {
                        best_route.clear();
                        best_route.push_back(*curr_flight);
                        best_price = curr_flight->price;
                    }
                    if (curr_flight->next != nullptr) { // If the next flight is not equal to nullptr
                        curr_flight = curr_flight->next; // Move to the next flight
                    }
                    else if (curr_flight->next == nullptr && curr_airline->next != nullptr) { // If the next flight is equal to nullptr and the next airline isn't equal to nullptr
                        curr_airline = curr_airline->next; // Move to the next airline
                        curr_flight = curr_airline->flights; // Move to the next flight
                    }
                    else {
                        return 0; // If no flight from the initial given location is found, return 0 to exit
                    }
                    
                }
            }
        }
        
        
        // While we our route size is bigger than zero but smaller then max ticket count
        while (route.size() > 0 && route.size() < max_trans + 1) {
            
            if (curr_flight->from != curr_loc) { // If current flight is not from the current location
                if (curr_flight->next != nullptr) { // If the next flight is not equal to nullptr
                    curr_flight = curr_flight->next; // Move to the next flight
                }
                else if (curr_flight->next == nullptr && curr_airline->next != nullptr) { // If the next flight is equal to nullptr and the next airline isn't equal to nullptr
                    curr_airline = curr_airline->next; // Move to the next airline
                    curr_flight = curr_airline->flights; // Move to the next flight
                }
                else { // If the element is the last element in the list, we should return to a previous entry
                    
                    // Set the found flight and its airline to where we found the previous flight which isn't the last flight in the list and its airline to keep their locations which will help us start searching from them
                    for (int i = route.size() - 1; i >= 0 ; i--) {
                        total_price -= route[i].price;
                        if (route[i].next != nullptr || route_airline[i].next != nullptr) {
                            found_flight = &route[i];
                            found_airline = &route_airline[i];
                            route.pop_back();
                            route_airline.pop_back();
                            break;
                        }
                        else if (i == 0 && (route[i].next == nullptr && route_airline[i].next == nullptr)) {
                            return 0;
                        }
                    }
                    
                    // Move to the next flight (no need for "else" check since we guaranteed "next" will be equal to some flight
                    moveToNextAfterPop(curr_flight, curr_airline, found_flight, found_airline, curr_loc);
                    
                    // If route size decreases to 0 during pop_back, recall function
                    if (route.size() == 0) {
                        pathfinder(head, curr_loc, destination, max_trans, total_price, route, best_route, route_airline, best_price, curr_airline, curr_flight, found_flight, found_airline); // Recall the function
                    }
                }
            }
            //Else (add next flight)
            else {
                if (curr_flight->to != destination) {
                    if ((total_price + curr_flight->price) < best_price) {
                        addFlightToRoute(curr_flight, curr_airline, curr_loc, route, route_airline, total_price);
                        curr_loc = curr_flight->to; // Change current location to where the flight we are taking is going to so we search for flights taking off from that location
                        
                        // Set current airline to head and current flight to its first flight to make sure that we start searching the next flight from the beginning of our structure
                        curr_airline = head;
                        curr_flight = head->flights;
                    }
                    else {
                        if (curr_flight->next != nullptr) {
                            curr_flight = curr_flight->next;
                        }
                        else if (curr_flight->next == nullptr && curr_airline->next != nullptr) {
                            curr_airline = curr_airline->next;
                            curr_flight = curr_airline->flights;
                        }
                        else {
                            // Set the found flight and its airline to where we found the previous flight which isn't the last flight in the list and its airline to keep their locations which will help us start searching from them
                            for (int i = route.size() - 1; i >= 0 ; i--) {
                                total_price -= route[i].price;
                                if (route[i].next != nullptr || route_airline[i].next != nullptr) {
                                    found_flight = &route[i];
                                    found_airline = &route_airline[i];
                                    route.pop_back();
                                    route_airline.pop_back();
                                    break;
                                }
                                else if (i == 0 && (route[i].next == nullptr && route_airline[i].next == nullptr)) {
                                    return 0;
                                }
                            }
                            
                            // Move to the next flight (no need for "else" check since we guaranteed "next" will be equal to some flight
                            moveToNextAfterPop(curr_flight, curr_airline, found_flight, found_airline, curr_loc);
                            
                            // If route size decreases to 0 during pop_back, recall function
                            if (route.size() == 0) {
                                pathfinder(head, curr_loc, destination, max_trans, total_price, route, best_route, route_airline, best_price, curr_airline, curr_flight, found_flight, found_airline); // Recall the function
                            }
                        }
                    }
                }
                else { // If current flight is to our destination, we found a route
                    
                    if ((total_price + curr_flight->price) < best_price) {
                        // Add to route
                        addFlightToRoute(curr_flight, curr_airline, curr_loc, route, route_airline, total_price);
                        best_route = route;
                        best_price = total_price;
                        
                        // Set the found flight and its airline to where we found a previous flight which isn't the last flight in the list and its airline to keep their locations which will help us start searching from them
                        for (int i = route.size() - 1; i >= 0 ; i--) {
                            total_price -= route[i].price;
                            if (route[i].next != nullptr || route_airline[i].next != nullptr) {
                                found_flight = &route[i];
                                found_airline = &route_airline[i];
                                route.pop_back();
                                route_airline.pop_back();
                                break;
                            }
                            else if (i == 0 && (route[i].next == nullptr && route_airline[i].next == nullptr)) {
                                return 0;
                            }
                        }
                        
                        // Move to the next flight (no need for "else" check since we guaranteed "next" will be equal to some flight
                        moveToNextAfterPop(curr_flight, curr_airline, found_flight, found_airline, curr_loc);
                        
                        // If route size decreases to 0 during pop_back, recall function
                        if (route.size() == 0) {
                            pathfinder(head, curr_loc, destination, max_trans, total_price, route, best_route, route_airline, best_price, curr_airline, curr_flight, found_flight, found_airline); // Recall the function
                        }
                    }
                    else {
                        if (curr_flight->next != nullptr) {
                            curr_flight = curr_flight->next;
                        }
                        else if (curr_flight->next == nullptr && curr_airline->next != nullptr) {
                            curr_airline = curr_airline->next;
                            curr_flight = curr_airline->flights;
                        }
                        else {
                            // Set the found flight and its airline to where we found the previous flight which isn't the last flight in the list and its airline to keep their locations which will help us start searching from them
                            for (int i = route.size() - 1; i >= 0 ; i--) {
                                total_price -= route[i].price;
                                if (route[i].next != nullptr || route_airline[i].next != nullptr) {
                                    found_flight = &route[i];
                                    found_airline = &route_airline[i];
                                    route.pop_back();
                                    route_airline.pop_back();
                                    break;
                                }
                                else if (i == 0 && (route[i].next == nullptr && route_airline[i].next == nullptr)) {
                                    return 0;
                                }
                            }
                            
                            // Move to the next flight (no need for "else" check since we guaranteed "next" will be equal to some flight
                            moveToNextAfterPop(curr_flight, curr_airline, found_flight, found_airline, curr_loc);
                            
                            // If route size decreases to 0 during pop_back, recall function
                            if (route.size() == 0) {
                                pathfinder(head, curr_loc, destination, max_trans, total_price, route, best_route, route_airline, best_price, curr_airline, curr_flight, found_flight, found_airline); // Recall the function
                            }
                        }
                    }
                }
            }
        }
        
        // Function will come to this for loop if route size is bigger than the max ticket number
        for (int i = route.size() - 1; i >= 0 ; i--) {
            total_price -= route[i].price;
            if (route[i].next != nullptr || route_airline[i].next != nullptr) {
                found_flight = &route[i];
                found_airline = &route_airline[i];
                route.pop_back();
                route_airline.pop_back();
                break;
            }
            else if (i == 0 &&
                     (route[i].next == nullptr && route_airline[i].next == nullptr)) {
                return 0;
            }
        }
        
        moveToNextAfterPop(curr_flight, curr_airline, found_flight, found_airline, curr_loc); // Move to the next flight (no need for "else" check since we guaranteed "next" will be equal to some flight
        pathfinder(head, curr_loc, destination, max_trans, total_price, route, best_route, route_airline, best_price, curr_airline, curr_flight, found_flight, found_airline); // Recall the function
        
    }
    
    else {
        cout << "List is empty.." << endl;
    }
    
    return 0;
}


// Function to delete the linked list structure that we have created
void delete_linked_list(airline *&head){
    
    airline *temp_airline = head, *curr_airline = temp_airline;
    flight *temp_flight = temp_airline->flights, *curr_flight = temp_flight;
    
    // Iterating through the structure to delete every element which we allocated by "new"
    while (curr_airline != nullptr) {
        while (curr_flight != nullptr) {
            curr_flight = temp_flight->next;
            delete temp_flight; // Deleting flights
            temp_flight = curr_flight;
        }
        curr_airline = temp_airline->next;
        delete temp_airline; // Deleting airlines
        temp_airline = curr_airline;
    }
    head = nullptr;
    cout << "Data is destroyed.." << endl;
}


void printMainMenu() {
  cout << endl;
  cout <<"I***********************************************I"<<endl
       <<"I               0 - DELETE DATA                 I"<<endl
       <<"I               1 - READ FILES                  I"<<endl
       <<"I               2 - PRINT ALL FLIGHTS           I"<<endl
       <<"I               3 - ADD FLIGHT                  I"<<endl
       <<"I               4 - REMOVE FLIGHT               I"<<endl
       <<"I               5 - PATH FINDER                 I"<<endl
       <<"I               6 - EXIT                        I"<<endl
       <<"I***********************************************I"<<endl
       <<">>";
  cout << endl;
}

void processMainMenu() {

  pair<vector<string>, vector<vector<flight> > > lines_flights;
    airline* head;
    bool input_done = false;
  
  char input;
  do{
    printMainMenu();
    cout << "Please enter your option " << endl;
    cin >> input;
    switch (input) {
    case '0':
      delete_linked_list(head);
      input_done = false;
      break;
    case '1':
      if(not input_done){
    lines_flights = read_files(input_done);
    head = make_linked_list_structure(lines_flights.first, lines_flights.second);
    cout << "Files have read.." << endl;
      }
      else{
    cout << "Files are already read.." << endl;
      }
      input_done = true;
      break;
    case '2':
      print_all(head);
      break;
    case '3':
      add_flight_with_input(head);
      break;
    case '4':
      remove_flight_with_input(head);
      break;
    case '5':
        {
            int max_trans, total_price = 0, best_price = INT_MAX;
            string curr_loc, destination;
            vector <flight> route, best_route;
            vector <airline> route_airline;
            airline *curr_airline = head, *found_airline = nullptr;
            flight *curr_flight = head->flights, *found_flight = nullptr;
            
            cout << "Where are you now?" << endl;
            cin >> curr_loc;
            cout << "Where do you want to go" << endl;
            cin >> destination;
            cout << "Maximum number of transfers: " << endl;
            cin >> max_trans;
            
            const string initialLoc = curr_loc;
            
            pathfinder(head, curr_loc, destination, max_trans, total_price, route, best_route, route_airline, best_price, curr_airline, curr_flight, found_flight, found_airline);
            
            if (best_price == INT_MAX) {
                cout << "No path found between " << initialLoc << " and " << destination << endl;
            }
            else {
                cout << "##Best price path##" << endl;
                for (int i = 0; i < best_route.size(); i++) {
                    cout << "[" << best_route[i].ID << "|" << best_route[i].from << "->" << best_route[i].to << "|" << best_route[i].hour << ":" << best_route[i].min << "|" << best_route[i].price << "]";
                    if (i != best_route.size() - 1) {
                        cout << "->";
                    }
                }
                cout << " $TOTAL PRICE: " << best_price << endl << "<<";
            }
            
            break;
        }
    case '6':
      cout << "Exiting.." << endl;
      exit(0);
    default:
      cout << "Invalid option: please enter again" << endl;
    }
  } while(true);
}


int main(){
  
  processMainMenu();
  
  return 0;
  
}
