//  Fall 2023 CS204 HW#5 -- myVector.h
//  Beren Aydoğan

#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Template struct to represent a pair of values
template <typename T1, typename T2>
struct vecPair{
    T1 value;
    T2 key;

    // Default constructor
    vecPair()
    {}

    // Constructor with initial values
    vecPair(T1 inpVal, T2 inpKey) 
        : value(inpVal), key(inpKey)
    {}
};

// Template class called "myVector" that modifies a std::vector that contains pairs 
template <typename T1, typename T2>
class myVector {
public:
    
    myVector(); // Default constructor
    myVector(const myVector &); // Copy constructor
    
    // Iterator class for iterating through the vector
    class Iterator {
    public:
        // Constructor of Iterator class
        Iterator(myVector & vec)
        : vectorToBeIterated(vec)
        {}

        // Member function to reset the iterator to the beginning of the vector in myVector class object
        void Reset() {
            iter = vectorToBeIterated.data.begin();
        }

        // Member function to check if there are any elements left to iterate in the vector in myVector class object
        bool HasMore() const {   
            return (iter != vectorToBeIterated.data.end());
        }
        
        // Member function to get the index of the vector in myVector class object the iterator is at
        int CurrentIndex() {  
            return (iter - (vectorToBeIterated.data.begin()));
        }

        // Member function to get the element of the vector in myVector class object the iterator is at
        vecPair<T1, T2> CurrentElem() {  
            return *iter;
        }
        
        // Move to the next element of the vector in myVector class object by increasing current index
        void Next() {
            if (iter != vectorToBeIterated.data.end()) {
                iter++;
            }
            else {
                cout << "End of vector is reached." << endl;
            }
        }

        // Member function to find a specific key in the vector in myVector class object, returns true if found, false if not found
        bool find(T2 key, const myVector & vec) {

            // Iterate through the vector until key is found
            for (Reset(); HasMore(); Next()) {
                if ((*iter).key == key) { // If key is found, return true
                    return true;
                }
            }
            // If key is not found reset iterator to the beginning and return false
            Reset(); 
            return false; 
        }

        // Member function to replace the key of the current element of the vector in myVector class object
        void replaceKey(T2 newKey) {
            (*iter).key = newKey;
            Reset();
        }

        // Member function to print the elements of the vector in myVector class object
        void printVector() {
            for (Reset(); HasMore(); Next()) {
                cout << "Value: " << (*iter).value << ", "
                    << "Key: " << (*iter).key << endl;
            }

            Reset(); 
        }

    private:
        myVector& vectorToBeIterated; // myVector object the instance of Iterator class will iterate
        typename vector<vecPair<T1, T2> >::iterator iter = vectorToBeIterated.data.begin(); // std::vector::iterator instance for data std::vector in myVector instance vectorToBeIterated
    };

    typename myVector<T1, T2>::Iterator begin(); // Member function to get an iterator pointing to the beginning of the vector
    void setName(string);  // Member function to set the name of the myVector object
    void push_back(T1, T2); // Member function to add a pair of values to the vector 
    void slideVector(int); // Member function to slide the vector to the removed element's position
    void remove(T2); // Member function to remove an element from the vector by key
    void process_data(); // Member function to process the data in the vector according to instructions
    bool isEmpty(); // Member function to check if the vector is empty
    string getName(); // Member function to get the name of the myVector object
    
    T1* operator[](T2); // Overloaded subscript operator to access elements by key
    myVector & operator=(const myVector &); // Overloaded assignment operator to copy a vector into another vector
    bool operator==(const myVector &) const; // Overloaded equality operator to check whether two vectors are equal or not
    
private:
    string name; // Name of the myVector object
    vector<vecPair<T1, T2> > data; // A std::vector that contains elements of the template struct which stores pairs of values
};

#endif

/*******************************************************************************************************/