//  CS204 Fall 2023 - HW4
//
//  beren.aydogan.cpp
//
//  Beren Aydoğan
//

#include <iostream>

using namespace std;

// Implementation of Node struct
struct Node {
    int val; // Value of node
    Node *next; // Pointer to the next node of the structure the node is going to be used in
    Node(int num, Node *ptr = nullptr) 
        : val(num), next(ptr) // Node constructor with initializer list to initialize the variables val and next with given parameters, sets next to nullptr if no parameter is given
    {}
};

// Implementation of LinkedListSet class
class LinkedListSet {
private:
    Node *head; // Pointer to the head of the linked list
    Node *tail; // Pointer to the tail of the linked list
public:
    LinkedListSet(); // Default constructor
    LinkedListSet(const LinkedListSet &copy); // Copy constructor
    ~LinkedListSet(); // Destructor
    Node *createClone () const; // Function to create a copy of the linked list
    void display(); // Function to display all elements in a given set in the required format
    bool isAvailable(int target) const; // Function to check if a value is in the linked list
    LinkedListSet &operator+(int num); // Insertion operator, adds a value to the set, returns inserted set
    LinkedListSet &operator-(int num); // Deletion operator, removes a value from the set, returns the deducted set
    const LinkedListSet &operator+=(const LinkedListSet & rhs); // Union operator, returns returns the set of all elements that exist in lhs, or in rhs, or in both
    const LinkedListSet &operator-=(const LinkedListSet & rhs); // Difference operator, returns the set of all elements that exist in lhs but not rhs
    const LinkedListSet &operator&=(const LinkedListSet & rhs); // Intersection operator, the set of all elements that are in both lhs and rhs
};

// Default constructor to create an empty list
LinkedListSet::LinkedListSet() {
    head = nullptr; // Set head to nullptr
    tail = head; // Set tail to head to make sure they point to same location
}

// Copy constructor
LinkedListSet::LinkedListSet(const LinkedListSet &copy) {
    head = copy.createClone(); // Create a clone of the given linked list
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head to iterate through the list

    // Go to the last element of the list to set it as tail
    while (tempLhs->next) {
        tempLhs = tempLhs->next; 
    }
    tail = tempLhs; // Make tail point to the last element in the list
}

LinkedListSet::~LinkedListSet() {
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head to iterate through the list
    Node *tempLhsPrev; // Define a tempPrev pointer to a node to follow tempLhs pointer from one element behind to delete elements

    // While tempLhs pointer hasn't reached end of the list
    while (tempLhs) {
        tempLhsPrev = tempLhs; // Set tempPrev to tempLhs
        tempLhs = tempLhs->next; // Move tempLhs to the next element of the list
        delete tempLhsPrev; // Delete tempPrev
    }
}

 // Function to create a copy of the linked list, returns a pointer to the head of the clone of the linked list
Node *LinkedListSet::createClone() const {

    // If the list is empty, return nullptr
    if (head == nullptr) {
        return nullptr;
    }

    Node *headClone = new Node(head->val); // Create the first clone node, set it as headClone
    Node *tempLhs = head->next; // Define a tempLhs pointer to a node and set it to point to head->next (as we have already copied head) to iterate through the list
    Node *tempClone = headClone; // Define a tempClone pointer to a node and set it to point to headClone to iterate through the clone list

    // While tempLhs pointer hasn't reached end of the list
    while (tempLhs) {
        // Create a new node for the clone list containing the value of the corresponding node on the original list
        tempClone->next = new Node(tempLhs->val); 

        // Move to the next node in both the original and clone lists
        tempLhs = tempLhs->next;
        tempClone = tempClone->next;
    }

    return headClone; // Return the head of the cloned list
}

// Function to display all elements in a given set in the required format
void LinkedListSet::display() {
    Node *tempLhs = head; // Define a pointer to a tempLhs node and set it to point to head to iterate through the list
    cout << "LinkedListSet{";

    // While tempLhs pointer hasn't reached end of the list
    while (tempLhs) {
      cout << tempLhs->val << ", "; // Print the value of the reached node
      tempLhs = tempLhs->next; // Move to the next element
    }

    cout << "}" << endl;
}

// Function to check if a value is in the linked list, returns true if it exists, false if it doesn't
bool LinkedListSet::isAvailable(int target) const {
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head to iterate through the list

    // Iterate through the linked list
    while (tempLhs) {
        // Check if the current node's val matches the target value
        if (tempLhs->val == target) { 
            return true; // Value is found
        }
        // Move to the next node in the list
        tempLhs = tempLhs->next;
    }
    
    // Value is not found
    return false;
}

// Union operator, returns returns the set of all elements that exist in lhs, or in rhs, or in both
LinkedListSet &LinkedListSet::operator+(int num) {
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head to iterate through the list
    Node *tempLhsPrev; // Define a tempLhsPrev pointer to a node to follow tempLhs pointer from one element behind to keep the previous element
    Node *newNode; // Define a newNode pointer to a node to point to the newly created node

    if (head) { // If the list is not empty
        if (!isAvailable(num)) { // If a node containing the given value isn't available
            newNode = new Node(num); // Create a new node containing the given value

            // To maintain a sorted list, iterate through the list until tempLhs is larger than the value of the new node
            while (tempLhs && tempLhs->val < newNode->val) {
                tempLhsPrev = tempLhs; // Set tempLhsPrev to tempLhs to keep the previous node
                tempLhs = tempLhs->next; // Move to the next element in the lhs list
            }

            if(tempLhs == head) { // If tempLhs is equal to head (i.e. new node will be the smallest in the list)
                newNode->next = head; // Make the next of the new node point to the head of the new list
                head = newNode; // Change head to the new node
            }
            else if(!tempLhs) { // If tempLhs is equal to nullptr (i.e. new node will be the largest in the list)
                tail->next = newNode; // Make the next of tail point to the new node
                tail = newNode; // Change tail to the new node
            }
            else {
                tempLhsPrev->next = newNode; // Make the next of tempLhsPrev point to the new node
                newNode->next = tempLhs; // Make the next of new node point to the tempLhs
            }
        }
    }
    else { // If the list is empty
        newNode = new Node(num); // Create a new node containing the given value
        head = newNode; // Set new node as head
        tail = head; // Set tail to head to make sure they point to same location
    }
    return *this; // Return the pointer to the lhs list
}

// Deletion operator, removes a value from the set, returns the deducted set
LinkedListSet &LinkedListSet::operator-(int num) {
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head to iterate through the list
    Node *tempLhsPrev; // Define a tempPrev pointer to a node to follow tempLhs pointer from one element behind to keep the previous element
    
    if (head) {// If the list is not empty

        // While tempLhs hasn't reach the end of the list
        while (tempLhs) {
            if (tempLhs->val == num) { // If the value of tempLhs is equal to the number that wanted to be deleted

                // Perform deletion according to the place of the node to be deleted
                if(tempLhs == head) { // If the node to be deleted is equal to head
                    head = tempLhs->next; // Change head to the next element of the list
                }
                else if (tempLhs == tail) { // If the node to be deleted is equal to tail
                    tail = tempLhsPrev; // Change tail to the previous element of the list
                }
                else {
                    tempLhsPrev->next = tempLhs->next; // Change previous element's next to the next of the element to be deleted of the list
                }
            }
            tempLhsPrev = tempLhs; // Set tempLhsPrev to tempLhs to keep the previous node
            tempLhs = tempLhs->next; // Move to the next element in the lhs list
        }
    }
    return *this; // Return the pointer to the lhs list
}

// Union operator, returns returns the set of all elements that exist in lhs, or in rhs, or in both
const LinkedListSet &LinkedListSet::operator+=(const LinkedListSet &rhs) {
    Node *tempRhs = rhs.head; // Define a tempRhs pointer to a node and set it to point to head of rhs to iterate through the rhs list
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head of lhs to iterate through the lhs list
    Node *tempLhsPrev; // Define a tempLhsPrev pointer to a node to follow tempLhs pointer from one element behind to keep the previous element
    Node *newNode; // Define a newNode pointer to a node to point to the newly created node

    if (head) { // If the list is not empty

        // While tempRhs hasn't reach the end of the list
        while (tempRhs) {
            if (!isAvailable(tempRhs->val)) {  // If the value in rhs list isn't available in the lhs list
                newNode = new Node(tempRhs->val);  // Create a new node containing the value of the current node in the rhs list

                // To maintain a sorted list, iterate through the list until tempLhs is larger than the value of the new node
                while (tempLhs && tempLhs->val < newNode->val) {
                    tempLhsPrev = tempLhs; // Set tempLhsPrev to tempLhs to keep the previous node
                    tempLhs = tempLhs->next; // Move to the next element in the lhs list
                }

                if(tempLhs == head) { // If tempLhs is equal to head (i.e. new node will be the smallest in the list)
                    newNode->next = head; // Make the next of the new node point to the head of the new list
                    head = newNode; // Change head to the new node
                }
                else if(!tempLhs) { // If tempLhs is equal to nullptr (i.e. new node will be the largest in the list)
                    tail->next = newNode; // Make the next of tail point to the new node
                    tail = newNode; // Change tail to the new node
                }
                else {
                    tempLhsPrev->next = newNode; // Make the next of tempLhsPrev point to the new node
                    newNode->next = tempLhs; // Make the next of new node point to the tempLhs
                }
            }
            tempLhs = head; // Point tempLhs back to head
            tempRhs = tempRhs->next; // Move tempRhs to the next element in the rhs list
        }
    }
    else { // If the lhs list is empty
        LinkedListSet newLhs(rhs); // Use copy constructor to make a copy of the rhs list
        *this = newLhs; // Make "this" point to the copy of the rhs list 
    }
    return *this; // Return the pointer to the lhs list
}

// Difference operator, returns the set of all elements that exist in lhs but not in rhs
const LinkedListSet &LinkedListSet::operator-=(const LinkedListSet &rhs) {
    Node *tempRhs = rhs.head; // Define a tempRhs pointer to a node and set it to point to head of rhs to iterate through the rhs list
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head of lhs to iterate through the lhs list
    Node *tempLhsPrev; // Define a tempLhsPrev pointer to a node to follow tempLhs pointer from one element behind to keep the previous element

    if (head) { // If the list is not empty

        // While tempRhs hasn't reach the end of the list
        while (tempRhs) { 
            if (isAvailable(tempRhs->val)) { // If the value in rhs list is available in the lhs list
                
                // Until the node to be deleted is found on lhs, iterate through the list
                while (tempLhs->val != tempRhs->val) {
                    tempLhsPrev = tempLhs; // Set tempLhsPrev to tempLhs to keep the previous node
                    tempLhs = tempLhs->next; // Move to the next element in the lhs list
                }

                // Perform deletion according to the place of the node to be deleted
                if(tempLhs == head) { // If the node to be deleted is equal to head
                    head = tempLhs->next; // Change head to the next element of the list
                }
                else if (tempLhs == tail) { // If the node to be deleted is equal to tail
                    tail = tempLhsPrev; // Change tail to the previous element of the list
                }
                else {
                    tempLhsPrev->next = tempLhs->next; // Change previous element's next to the next of the element to be deleted of the list
                }

                delete tempLhs; // Delete the node that was meant to be deleted
                tempLhs = head; // Point tempLhs back to head
            }
            tempRhs = tempRhs->next; // Move to the next element in the rhs list
        }
    }
    return *this; // Return the pointer to the lhs list
}

// Intersection operator, the set of all elements that are in both lhs and rhs
const LinkedListSet &LinkedListSet::operator&=(const LinkedListSet &rhs) {
    Node *tempLhs = head; // Define a tempLhs pointer to a node and set it to point to head to iterate through the list
    Node *tempLhsHolder = head; // Define a tempLhsHolder pointer to a node and set it to point to head to iterate through the list
    Node *tempLhsPrev; // Define a tempPrev pointer to a node to follow tempLhs pointer from one element behind to keep the previous element
    Node *tempNext = tempLhsHolder->next; // Define a tempNext pointer to keep the next element of tempLhsHolder in case current element gets deleted

    if (head) { // If the list is not empty
        // While tempLhsHolder hasn't reach the end of the list
        while (tempLhsHolder) { 
            tempNext = tempLhsHolder->next; // Keep the next element of tempLhsHolder
            if (!rhs.isAvailable(tempLhsHolder->val)) {  // If the value in lhs list isn't available in the rhs list
                
                // Until the node to be deleted is found on lhs, iterate through the list
                while (tempLhs && tempLhs->val != tempLhsHolder->val) {
                    tempLhsPrev = tempLhs; // Set tempLhsPrev to tempLhs to keep the previous node
                    tempLhs = tempLhs->next; // Move to the next element in the lhs list
                } 

                // Perform deletion according to the place of the node to be deleted
                if(tempLhs == head) { // If the node to be deleted is equal to head
                    head = tempLhs->next; // Change head to the next element of the list
                }
                else if (tempLhs == tail) { // If the node to be deleted is equal to tail
                    tail = tempLhsPrev; // Change tail to the previous element of the list
                }
                else {
                    tempLhsPrev->next = tempLhs->next; // Change previous element's next to the next of the element to be deleted of the list
                }

                delete tempLhs; // Delete the node that was meant to be deleted
                tempLhs = head; // Point tempLhs back to head
            }
            tempLhsHolder = tempNext; // Set tempLhsHolder to tempNext to move to the next available element
        }
    }
    return *this; // Return the pointer to the lhs list
}


int main() {

  // Example usage
  LinkedListSet set1;
  set1 + 1 + 2 + 3 + 17; // Insertion
  set1.display();   
  
  set1 - 2; // Deletion
  set1.display(); 
  
  LinkedListSet set2;
  set2 + 3 + 4 + 5; 
  set2.display();   
  
  set2 += set1 + 7 + 3 + 19; //Insertion with multiple right-hand values
  set2.display();
  
  LinkedListSet set3;
  set3 + 3 + 4 + 7 + 17 + 41;
  set3.display();
  
  LinkedListSet set4;
  set4 + 41 + 37+ 7 + 19 + 41;
  set4.display();
  
  // Set Union
  set1 += set2;
  set1.display(); 
  
  // Set Difference
  set1 -= set3;
  set1.display(); 
  
  // Set Intersection
  set1 &= set4;
  set1.display(); 
  
  return 0;
}


