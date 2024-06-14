//  Fall 2023 CS204 HW#5 -- main.cpp
//  Beren Aydoğan

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "beren.aydogan_Aydoğan_Beren_HW5_myVector.h"

using namespace std;

// Default constructor
template <typename T1, typename T2>
myVector<T1, T2>::myVector() {
}

// Copy constructor
template <typename T1, typename T2>
myVector<T1, T2>::myVector(const myVector & copy) {
    this->name = copy.name; // Assign the name of myVector object copy to the newly constructed myVector object's name
    this->data = copy.data; /// Assign the data vector of myVector object copy to the newly constructed myVector object's data vector
}

template <typename T1, typename T2>
typename myVector<T1, T2>::Iterator myVector<T1, T2>::begin() {
    return Iterator(*this);
}

// Member function to set the name of the myVector object
template <typename T1, typename T2>
void myVector<T1, T2>::setName(string vectorName) {
    name = vectorName; // Set the private member of myVector class, name, to the given vectorName
}

// Member function to add a pair of values to the vector 
template <typename T1, typename T2>
void myVector<T1, T2>::push_back(T1 value, T2 key) {
    vecPair<T1, T2> newPair(value, key); // Create a new instance of vecPair struct (a value, key pair) according to parameters
    data.push_back(newPair); // Push newPair into the vector of the myVector object
}

// Member function to slide the rest of the vector to the position of the element to be removed (Helper function to "void remove(T2 key)")
template <typename T1, typename T2>
void myVector<T1, T2>::slideVector(int removedPos) {
    for (size_t i = removedPos; i < data.size(); i++) {
        data[i] = data[i + 1]; // Move elements to the front
    }

    data.resize(data.size() - 1); // Resize the vector to the new size
}

// Member function to remove an element from the vector by key
template <typename T1, typename T2>
void myVector<T1, T2>::remove(T2 key) {
    Iterator iter(*this); // Instantiate an Iterator object 
    iter.find(key, *this); // Find the index of the element to be removed using Iterator object
    slideVector(iter.CurrentIndex()); // Slide the rest of the vector to the position of the element to be removed
}

// Free template function to sort a vector using bubble sort algorithm (Helper function to "void process_data()")
template <typename T>
void bubbleSort(vector<T>& vec) {
    T temp;

    // Outer for loop iterates through the entire vector
    for (int i = 0; i < vec.size() - 1; ++i) {
        // Inner loop compares adjacent elements
        for (int j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) { // Swap elements if they are in the wrong order
                temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}

// Member function to process the data in the vector according to instructions:
// * If the value is string: calculate most frequent word and character for all values of the vector.
// * If the value is arithmetic: calculate the mean, median, standard deviation, max and mode values.
// This function also checks whether the vector is empty or the type isn't compatible and 
// lets the user know by printing out messages accordingly if either of the cases occur
template <typename T1, typename T2>
void myVector<T1, T2>::process_data(){

    if (data.empty()) { // If vector is empty, let the user know
        cout << "Vector is empty. Cannot process data." << endl;
       
    }

    else if constexpr (is_same<T1, string>::value) { // If the values in pairs in the vector are of type string
    
        Iterator iter(*this); // Iterator for the vector

        vector<char> chars; // An instance of std::vector containing characters to put all the characters the values contain 
        myVector<int, char> countChars; // An instance of myVector class containing pairs of integers and characters which will be used to store the characters the values contain and their counts
        myVector<int, char>::Iterator iterCC(countChars.begin()); // Iterator for countChars vector

        myVector<int, string> countWords; // An instance of myVector class containing pairs of integers and strings which will be used to store the values (words) and their counts
        myVector<int, string>::Iterator iterCW(countWords.begin()); // Iterator for countWords vector

        // Iterate through the vector and collect characters from each value into the vector "chars"
        for (iter.Reset(); iter.HasMore(); iter.Next()) {
            // Iterate through the string
            for (int i = 0; i < data[iter.CurrentIndex()].value.size(); i++) { 
                chars.push_back(data[iter.CurrentIndex()].value[i]); // Push each character of the string into the vector "chars"
            }
        }

        // Count the occurrences of each character by iterating through the vector "chars"
        for (int i = 0; i < chars.size(); i++) {
            if (!countChars[chars[i]]) { // If the character doesn't exist in countChars
                countChars.push_back(1, chars[i]); // Push the count, character pair into countChars
            }
            else { // If the character does exist in countChars
                *countChars[chars[i]] += 1; // Increment its count by 1
            }
        }

        iterCC.Reset();  //  Reset iterCC since countChars vector is modified
        char mostFreqChar = (iterCC.CurrentElem()).key; // Initialize mostFreqChar to the first element of countChars to start the comparison
    
        // Find the most frequent character by iterating through countChars
        for (iterCC.Reset(); iterCC.HasMore(); iterCC.Next()) {
            if (*countChars[mostFreqChar] < iterCC.CurrentElem().value || (mostFreqChar > iterCC.CurrentElem().key && *countChars[mostFreqChar] == iterCC.CurrentElem().value)) { // If a more frequent or an alphabetically more significant character with the same count is found
                mostFreqChar = iterCC.CurrentElem().key; // Update mostFreqChar 
            }
        }

        // Count the occurrences of each word by iterating through the vector
        for (iter.Reset(); iter.HasMore(); iter.Next()) {
            if (!countWords[data[iter.CurrentIndex()].value]) { // If the word doesn't exist in countWords
                countWords.push_back(1, data[iter.CurrentIndex()].value); // Push the count, word pair into countWords
            }
            else { // If the word does exist in countWords
                *countWords[data[iter.CurrentIndex()].value] += 1; // Increment its count by 1
            }
        }

        iterCW.Reset(); //  Reset iterCW since countChars vector is modified
        string mostFreqWord = iterCW.CurrentElem().key; // Initialize mostFreqWord to the first element of countWords to start the comparison

        // Find the most frequent word by iterating through countWords
        for (iterCW.Reset(); iterCW.HasMore(); iterCW.Next()) { 
            if (*countWords[mostFreqWord] < iterCW.CurrentElem().value || (mostFreqWord > iterCW.CurrentElem().key && *countWords[mostFreqWord] == iterCW.CurrentElem().value)) { // If a more frequent or an alphabetically more significant word with the same count is found
                mostFreqWord = iterCW.CurrentElem().key; // Update mostFreqWord
            }
        }

        // Display the results according to the given format
        cout << "Most Frequent Character: \'" << mostFreqChar << "\' (Frequency: " << *countChars[mostFreqChar]  << ")" << endl;
        cout << "Most Frequent Word: \"" << mostFreqWord << "\" (Frequency: " << *countWords[mostFreqWord]  << ")" << endl;

    } 
    
    else if constexpr (is_arithmetic<T1>::value) { // If the values in pairs in the vector are of an arithmetic type
        Iterator iter(*this); // Iterator for the vector
        vector<T1> values; // An instance of std::vector containing all values in the vector
        double mean, median, standardDeviation, maxValue, mode; // The values we need to calculate

        // Transfer values from myVector to values vector
        for (iter.Reset(); iter.HasMore(); iter.Next()) {
            values.push_back(iter.CurrentElem().value);
        }

        // Sort the vector "values"
        bubbleSort(values); 

        // Calculate mean by iterating through the vector "values", computing the sum of all values and dividing by size of the vector
        double sum = 0;
        for (int i = 0; i < values.size(); i++) {
            sum += values[i]; // Add all elements of values into sum
        }
        mean = sum / values.size(); // Divide sum by the size of the vector "values" (number of values available) to compute the mean

        // Calculate median considering whether the size of the vector "values" is even or odd
        if (values.size() % 2 == 0) { // If the size of the vector "values" is even, median equals to the average of the two middle elements
            T1 firstMiddle = values[values.size()/2 - 1];
            T1 secondMiddle = values[values.size()/2];
            median = (firstMiddle + secondMiddle) / 2.0;
        } 
        else { // If the size of the vector "values" is odd, median equals to the middle element
            median = values[values.size()/2];
        }

        // Calculate standard deviation
        double sumSquaredDiff = 0;
        // Iterate through the vector "values" to compute the squared difference from the mean of each value
        for (int i = 0; i < values.size(); ++i) {
            sumSquaredDiff += (values[i] - mean) * (values[i] - mean); // Calculate the sum of squared differences from the mean
        }
        standardDeviation = sqrt(sumSquaredDiff / values.size()); // Compute standard deviation by taking the squareroot of the sum of squared differences divided by the size of the vector "values"

        // Set max value as the last element of "values" since it is already sorted
        maxValue = values[values.size() - 1];

        // Calculate mode
        int maxCount = 0;
        for (int i = 0; i < values.size(); ++i) {
            int count = 0;
            for (int j = 0; j < values.size(); ++j) {
                if (values[j] == values[i]) {
                    ++count;
                }
            }
            if (count > maxCount || (count == maxCount && values[i] < mode)) {
                maxCount = count;
                mode = values[i];
            }
        }

        // Display the results according to the given format
        cout << "Mean: " << mean << endl;
        cout << "Median: " << median << endl;
        cout << "Standard Deviation: " << standardDeviation << endl;
        cout << "Max: " << maxValue << endl;
        cout << "Mode: " << mode << endl;
    }

    else { // If the type of values that the vectors story isn't string or an arithmetic value, let the user know
        cout << "Unsupported type for processing data." << endl; 
    }
}

// Member function to check if the vector is empty, return true if it is, false otherwise
template <typename T1, typename T2>
bool myVector<T1, T2>::isEmpty() {
    if (data.size() != 0) { // If size of the vector of myVector object is not 0
        return false; 
    }
    else {
        return true;
    }
}

// Member function to get the name of the myVector object
template <typename T1, typename T2>
string myVector<T1, T2>::getName(){
    return name;
}

// Overloaded subscript operator to access elements by key
template <typename T1, typename T2>
T1* myVector<T1, T2>::operator[](T2 key) {
    Iterator iter(*this); // Iterator for the vector    

    if (iter.find(key, *this)) { // If the given key is found in the vector
        int foundIndex = iter.CurrentIndex(); // Store the index where key is found
        T1* ptr = &data[foundIndex].value; // Store the value of the key in a pointer 
        return ptr; // Return the pointer
    }
    else { // If the given key is not found in the vector
        return nullptr;
    }
}

// Overloaded assignment operator to copy a vector into another vector
template <typename T1, typename T2>
myVector<T1, T2> & myVector<T1, T2>::operator=(const myVector & rhs) {
    if (this != &rhs) { // If rhs is not equal to lhs
        name = rhs.name; // Copy name
        data = rhs.data; // Copy data in the vector "data"
    }
    return *this; // Return a reference to the myVector object, *this
}

// Overloaded equality operator to check whether two vectors are equal or not, returns true if they are, false if they are not
template <typename T1, typename T2>
bool myVector<T1, T2>::operator==(const myVector& rhs) const {
    if (data.size() != rhs.data.size()) { // If the sizes of rhs and lhs are not equal
        return false; 
    }

    // Iterate through the vector to check each element for equality
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].value != rhs.data[i].value || data[i].key != rhs.data[i].key) { // If any element is not equal
            return false;
        }
    }
    return true;
}

/*******************************************************************************************************
    DO NOT CHANGE THE MAIN FUNCTION BELOW
    YOU WILL NOT GET ANY POINTS FROM THIS HOMEWORK IF YOU CHANGE IT
*******************************************************************************************************/
int main()
{
    //Vector and iterator declarations
    myVector<std::string, int> vecStringInt;
    vecStringInt.setName("vecStringInt");
    myVector<std::string, int>::Iterator itrStringInt(vecStringInt.begin());

    myVector<double, double> vecDoubleDouble;
    vecDoubleDouble.setName("vecDoubleDouble");
    myVector<double, double>::Iterator itrDoubleDouble(vecDoubleDouble.begin());

    myVector<int, std::string> vecIntString;
    vecIntString.setName("vecIntString");
    myVector<int, std::string>::Iterator itrIntString(vecIntString.begin());

    myVector<double, std::string> vecDoubleString;
    vecDoubleString.setName("vecDoubleString");
    myVector<double, std::string>::Iterator itrDoubleString(vecDoubleString.begin());

    myVector<std::string, int> vecStringInt2;
    vecStringInt2.setName("vecStringInt2");
    myVector<std::string, int>::Iterator itrStringInt2(vecStringInt2.begin());

    myVector<double, double> vecDoubleDouble2;
    vecDoubleDouble2.setName("vecDoubleDouble2");
    myVector<double, double>::Iterator itrDoubleDouble2(vecDoubleDouble2.begin());

    myVector<int, std::string> vecIntString2;
    vecIntString2.setName("vecIntString2");
    myVector<int, std::string>::Iterator itrIntString2(vecIntString2.begin());

    myVector<double, std::string> vecDoubleString2;
    vecDoubleString2.setName("vecDoubleString2");
    myVector<double, std::string>::Iterator itrDoubleString2(vecDoubleString2.begin());

    //File reading
    std::string filename;
    std::cout << "Enter the filename: ";
    std::getline(std::cin, filename);
    std::ifstream inFile(filename);

    if (!inFile.is_open() || inFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Error: Input file is empty or cannot be opened." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string command, vecName, key;
        iss >> command;

        if (command.empty()) {
            continue; // Skip empty lines or lines with only spaces
        }

        if (command == "push") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                std::string stringValue;
                iss >> intKey >> stringValue;
                vecStringInt.push_back(stringValue, intKey);
            } else if (vecName == "vecDoubleDouble") {
                double doubleValue;
                iss >> doubleKey >> doubleValue;
                vecDoubleDouble.push_back(doubleValue, doubleKey);
            } else if (vecName == "vecIntString") {
                int intValue;
                std::string stringValue;
                iss >> stringKey >> intValue;
                vecIntString.push_back(intValue, stringKey);
            } else if (vecName == "vecDoubleString") {
                double doubleValue;
                iss >> stringKey >> doubleValue;
                vecDoubleString.push_back(doubleValue, stringKey);
            }
        }
        else if (command == "remove") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;

            if (vecName == "vecStringInt") {
                iss >> intKey;
                vecStringInt.remove(intKey);
            } else if (vecName == "vecDoubleDouble") {
                iss >> doubleKey;
                vecDoubleDouble.remove(doubleKey);
            } else if (vecName == "vecIntString") {
                iss >> stringKey;;
                vecIntString.remove(stringKey);
            } else if (vecName == "vecDoubleString") {
                iss >> stringKey;
                vecDoubleString.remove(stringKey);
            }
        }
        else if (command == "find") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                iss >> intKey;
                std::string* foundValue = vecStringInt[intKey];
                if (foundValue) std::cout << "Found: Key = " << intKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << intKey << std::endl;
            } 
            else if (vecName == "vecDoubleDouble") {
                iss >> doubleKey;
                double* foundValue = vecDoubleDouble[doubleKey];
                if (foundValue) std::cout << "Found: Key = " << doubleKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << doubleKey << std::endl;
            }
            else if (vecName == "vecIntString") {
                iss >> stringKey;
                int* foundValue = vecIntString[stringKey];
                if (foundValue) std::cout << "Found: Key = " << stringKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << stringKey << std::endl;
            }
            else if (vecName == "vecDoubleString") {
                iss >> stringKey;
                double* foundValue = vecDoubleString[stringKey];
                if (foundValue) std::cout << "Found: Key = " << stringKey << ", Value = " << *foundValue << std::endl;
                else std::cout << "Key not found: " << stringKey << std::endl;
            }
        }

        else if (command == "replace_value") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                std::string stringValue;
                iss >> intKey >> stringValue;
                std::string* foundValue = vecStringInt[intKey];
                if (foundValue) *foundValue = stringValue;
                else std::cout << "Key not found for replacement: " << intKey << std::endl;
            } 
            else if (vecName == "vecDoubleDouble") {
                double doubleValue;
                iss >> doubleKey >> doubleValue;
                double* foundValue = vecDoubleDouble[doubleKey];
                if (foundValue) *foundValue = doubleValue;
                else std::cout << "Key not found for replacement: " << doubleKey << std::endl;
            }
            else if (vecName == "vecIntString") {
                int intValue;
                iss >> stringKey >> intValue;
                int* foundValue = vecIntString[stringKey];
                if (foundValue) *foundValue = intValue;
                else std::cout << "Key not found for replacement: " << stringKey << std::endl;
            }
            else if (vecName == "vecDoubleString") {
                double doubleValue;
                iss >> stringKey >> doubleValue;
                double* foundValue = vecDoubleString[stringKey];
                if (foundValue) *foundValue = doubleValue;
                else std::cout << "Key not found for replacement: " << stringKey << std::endl;
            }
        }

        if (command == "replace_key") {
            std::string oldKeyStr, newKeyStr;
            int oldKeyInt, newKeyInt;
            double oldKeyDouble, newKeyDouble;
            
            iss >> vecName;
            if (vecName == "vecStringInt") {
                iss >> oldKeyInt >> newKeyInt;
                if (itrStringInt.find(oldKeyInt, vecStringInt)) {
                    itrStringInt.replaceKey(newKeyInt);
                } else {
                    std::cout << "Key not found: " << oldKeyInt << std::endl;
                }
            } else if (vecName == "vecDoubleDouble") {
                iss >> oldKeyDouble >> newKeyDouble;
                if (itrDoubleDouble.find(oldKeyDouble, vecDoubleDouble)) {
                    itrDoubleDouble.replaceKey(newKeyDouble);
                } else {
                    std::cout << "Key not found: " << oldKeyDouble << std::endl;
                }
            } else if (vecName == "vecIntString") {
                iss >> oldKeyStr >> newKeyStr;
                if (itrIntString.find(oldKeyStr, vecIntString)) {
                    itrIntString.replaceKey(newKeyStr);
                } else {
                    std::cout << "Key not found: " << oldKeyStr << std::endl;
                }
            } else if (vecName == "vecDoubleString") {
                iss >> oldKeyStr >> newKeyStr;
                if (itrDoubleString.find(oldKeyStr, vecDoubleString)) {
                    itrDoubleString.replaceKey(newKeyStr);
                } else {
                    std::cout << "Key not found: " << oldKeyStr << std::endl;
                }
            } else {
                std::cout << "Unknown vector name: " << vecName << std::endl;
            }
        }

        else if (command == "print") {
            std::string stringKey;
            int intKey;
            double doubleKey;
            iss >> vecName;
            if (vecName == "vecStringInt") {
                iss >> intKey;
                std::string* value = vecStringInt[intKey];
                if (value) {
                    std::cout << "Key: " << intKey << ", Value: " << *value << std::endl;
                } else {
                    std::cout << "Error: Key not found: " << intKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
            else if (vecName == "vecDoubleDouble")
            {
                iss >> doubleKey;
                double* value = vecDoubleDouble[doubleKey];
                if (value) {
                    std::cout << "Key: " << doubleKey << ", Value: " << *value << std::endl;
                } else {
                    std::cout << "Error: Key not found: " << doubleKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
            else if (vecName == "vecIntString")
            {
                iss >> stringKey;
                int* value = vecIntString[stringKey];
                if (value) {
                    std::cout << "Key: " << stringKey << ", Value: " << *value << std::endl;
                } else {
                    std::cout << "Error: Key not found: " << stringKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
            else if (vecName == "vecDoubleString")
            {
                iss >> stringKey;
                double* value = vecDoubleString[stringKey];
                if (value) {
                    std::cout << "Key: " << stringKey << ", Value: " << *value << std::endl;
                } else {
                    std::cout << "Error: Key not found: " << stringKey << " in vector '" << vecName << "'" << std::endl;
                }
            }
        }

        else if (command == "print_vector") {
            iss >> vecName;
            if (vecName == "vecStringInt") {
                if (vecStringInt.isEmpty()) {
                    std::cout << "Error: vecStringInt is empty." << std::endl;
                } else {
                    std::cout << "\nPrinting vecStringInt:" << std::endl;
                    itrStringInt.printVector();
                }
            } else if (vecName == "vecDoubleDouble") {
                if (vecDoubleDouble.isEmpty()) {
                    std::cout << "Error: vecDoubleDouble is empty." << std::endl;
                } else {
                    std::cout << "\nPrinting vecDoubleDouble:" << std::endl;
                    itrDoubleDouble.printVector();
                }
            } else if (vecName == "vecIntString") {
                if (vecIntString.isEmpty()) {
                    std::cout << "Error: vecIntString is empty." << std::endl;
                } else {
                    std::cout << "\nPrinting vecIntString:" << std::endl;
                    itrIntString.printVector();
                }
            } else if (vecName == "vecDoubleString") {
                if (vecDoubleString.isEmpty()) {
                    std::cout << "Error: vecDoubleString is empty." << std::endl;
                } else {
                    std::cout << "\nPrinting vecDoubleString:" << std::endl;
                    itrDoubleString.printVector();
                }
            } else {
                std::cout << "Error: Unknown vector name '" << vecName << "'" << std::endl;
            }
        }

        else if (command == "copy") {
            std::string targetVecName;
            iss >> vecName >> targetVecName;

            if (vecName == "vecStringInt" && targetVecName == "vecStringInt2") {
                vecStringInt2 = vecStringInt;
                std::cout << "\nPrinting vecStringInt2:" << std::endl;
                itrStringInt2.printVector();
            } 
            else if (vecName == "vecDoubleDouble" && targetVecName == "vecDoubleDouble2") {
                vecDoubleDouble2 = vecDoubleDouble;
                std::cout << "\nPrinting vecDoubleDouble2:" << std::endl;
                itrDoubleDouble2.printVector();
            } 
            else if (vecName == "vecIntString" && targetVecName == "vecIntString2") {
                vecIntString2 = vecIntString;
                std::cout << "\nPrinting vecIntString2:" << std::endl;
                itrIntString2.printVector();
            } 
            else if (vecName == "vecDoubleString" && targetVecName == "vecDoubleString2") {
                vecDoubleString2 = vecDoubleString;
                std::cout << "\nPrinting vecDoubleString2:" << std::endl;
                itrDoubleString2.printVector();
            } 
            else {
                std::cout << "Error: Incompatible vector types or unknown vector names for copy." << std::endl;
            }
        }

        else if (command == "check_equal") {
            std::string targetVecName;
            iss >> vecName >> targetVecName;

            if (vecName == "vecStringInt" && targetVecName == "vecStringInt2") {
                if (vecStringInt == vecStringInt2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                } else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            } else if (vecName == "vecDoubleDouble" && targetVecName == "vecDoubleDouble2") {
                if (vecDoubleDouble == vecDoubleDouble2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                } else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            } else if (vecName == "vecIntString" && targetVecName == "vecIntString2") {
                if (vecIntString == vecIntString2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                } else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            } else if (vecName == "vecDoubleString" && targetVecName == "vecDoubleString2") {
                if (vecDoubleString == vecDoubleString2) {
                    std::cout << vecName << " and " << targetVecName << " are equal." << std::endl;
                } else {
                    std::cout << vecName << " and " << targetVecName << " are not equal." << std::endl;
                }
            } else {
                std::cout << "Error: Incompatible vector types or unknown vector names for comparison." << std::endl;
            }
        }

        if (command == "process_data") {
            iss >> vecName;
            if (vecName == "vecStringInt") {
                std::cout << "Processing data of vector " << vecStringInt.getName() << ":" << std::endl;
                vecStringInt.process_data();
            } else if (vecName == "vecDoubleDouble") {
                std::cout << "Processing data of vector " << vecDoubleDouble.getName() << ":" << std::endl;
                vecDoubleDouble.process_data();
            } else if (vecName == "vecIntString") {
                std::cout << "Processing data of vector " << vecIntString.getName() << ":" << std::endl;
                vecIntString.process_data();
            } else if (vecName == "vecDoubleString") {
                std::cout << "Processing data of vector " << vecDoubleString.getName() << ":" << std::endl;
                vecDoubleString.process_data();
            } else {
                std::cout << "Error: Unknown vector name '" << vecName << "'" << std::endl;
            }
        }
    }


    inFile.close();
    return 0;
}
/*******************************************************************************************************/
