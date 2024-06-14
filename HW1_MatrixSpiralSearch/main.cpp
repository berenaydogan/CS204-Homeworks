/*
    beren.aydogan_Aydogan_Beren_HW1, main.cpp
    Purpose: Open and read a file, check whether it is in the correct format according to the requirements, create matrices out of the given characters - one containing the characters that is required for us to conduct a search on and one containing the words that we will search - and search the words given in the file on the matrix containing the characters to conduct a search on using a spiral search method
 
    Created by Beren Aydogan on 11.10.2023.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

// Function to read and check if the file format is correct according to the requirements, return 1 if not
int checkFile(ifstream& input, int& matrixSize, int& numberOfWordsToBeSearched) {
    string line, errorOutput = "Error: Input file is not in correct format!";
    int counterMatrix = 0, counterSearch = 0;
    
    getline(input, line);
    
    // Check if the matrix size (which is the number and length of the words that will be put in the matrix since we're creating a square matrix) is given in the first line of the file and whether if it is in integer format, return 1 if not
    for (char ch : line) {
        if (!isdigit(ch)) {
            cout << errorOutput << endl;
            return 1;
        }
    }
    
    matrixSize = stoi(line); // Store matrix size in a variable that is given as a reference integer parameter to the function to be able to use it in the main function
    
    // Get line from the input file until the counterMatrix variable is equal to the matrixSize given in the file
    while(counterMatrix != matrixSize) {
        getline(input, line);
        
        // If the length of the line given is not equal to the matrixSize given in the file, return 1 as this means the given matrixSize in the file is wrong and there is a problem with the format of the file
        if (line.length() != matrixSize) {
            cout << errorOutput << endl;
            return 1;
        }
        
        // For all characters in the line read check if they are uppercase letters, return 1 if not
        for (char ch : line) {
            if (!isupper(ch)) {
                cout << errorOutput << endl;
                return 1;
            }
        }
        counterMatrix++;
    }
    
    
    getline(input, line);
    
    // Check if the number of words to be searched is given in the place it is supposed to be (after number of lines equal to matrixSize) and whether if it is in integer format, return 1 if not
    for (char ch : line) {
        if (!isdigit(ch)) {
            cout << errorOutput << endl;
            return 1;
        }
    }
    
    numberOfWordsToBeSearched = stoi(line); // Store the number of the words given to be searched in a variable that is given as a reference integer parameter to the function to be able to use it in the main function
    
    // Get line from the input file until the counterSearch variable is equal to the numberOfWordsToBeSearched given in the file
    while (counterSearch != numberOfWordsToBeSearched) {
        getline(input, line);
        
        // If getLine function reaches the end of the file before counterSearch becomes equal to numberOfWordsToBeSearched, return 1 as this means the given numberOfWordsToBeSearched in the file is wrong and there is a problem with the format of the file
        if (input.eof()) {
            cout << errorOutput << endl;
            return 1;
        }
        
        // For all characters in the line read, check if they are uppercase letters, return 1 if not
        for (char ch : line) {
            if (!isupper(ch)) {
                cout << errorOutput << endl;
                return 1;
            }
        }
        counterSearch++;
    }
    
    // Check if the given number of words is larger than the given number of words to be searched, return 1 if not
    getline(input, line);
    if (!input.eof()) {
        cout << errorOutput << endl;
        return 1;
    }
    
    // Return 0 if the file passes all checks
    return 0;
}

// Function to create matrices from the file
void createMatrixFromFile(ifstream& input, int& matrixSize, vector<vector<char> >& matrix) {
    char ch = '\0';
    
    //Move to the next line by getting the characters on the first line to get rid of the line containing the number
    while (ch != '\n') {
        input.get(ch);
    }

    // Go through the characters and add them to the matrix
    for (int i = 0; i < matrixSize; i++) {
        input.get(ch);
        while (ch != '\n') {
            matrix[i].push_back(ch);
            input.get(ch);
        }
    }
}



// Function to check if the position we reached during the search is valid
bool isPositionValid(int row, int col, unsigned long matrixSize) {
    return (row >= 0 && col >= 0 && row < matrixSize && col < matrixSize);
}

// Function to conduct spiral search steps which will be repeated during the spiral search steps in different directions by conducting additions and substractions in the main spiral search function
void  spiralSearchSteps(vector<vector<char> >& matrixToBeSearched, int& elemToBeChanged, int toBeAdded, string& search, int& row, int& col, int& searchSize, bool& breakAll, int& numberOfStepsToBeTaken) {
        
    // Counting the number of steps taken and making sure steps taken doesn't exceed the number of steps to be taken
    for (int stepsTaken = 0; stepsTaken < numberOfStepsToBeTaken; stepsTaken++) {
        
        // If number of steps to be taken during the movement is not even, we add the toBeAdded that is given as a parameter to the function, to the elemToBeChanged to change it
        if (numberOfStepsToBeTaken % 2 == 1) {
            elemToBeChanged += toBeAdded;
            
            // If the position found after the addition is valid (exists on the matrix), we add it to our search and increase the variable that counts the size of our search string by one
            if (isPositionValid(row, col, matrixToBeSearched.size())) {
                search += matrixToBeSearched[row][col];
                searchSize++;
            }
            
            // If the position found after the addition is invalid (doesn't exist on the matrix), we break from the loop and set the breakAll variable to "true" which we will need as a flag during the main spiral search function implementation to break from other loops
            else {
                breakAll = true;
                break;
            }
        }
        
        // If number of steps to be taken during the movement is even, we substract the toBeAdded variable that is given as a parameter to the function, to the elemToBeChanged to change it
        else {
            elemToBeChanged -= toBeAdded;
            if (isPositionValid(row, col, matrixToBeSearched.size())) {
                search += matrixToBeSearched[row][col];
                searchSize++;
            }
            // If the position found after the substraction is invalid (doesn't exist on the matrix), we break from the loop and set the breakAll variable to "true" which we will need as a flag during the main spiral search function implementation to break from other loops
            else {
                breakAll = true;
                break;
            }
        }
    }
}

// Function to perform spiral search on a matrix in a specific directions
void  spiralSearchInDirection(vector<vector<char> >& matrixToBeSearched, vector<vector<char> >& matrixOfTheWordsToBeSearched, vector <string>& foundWords, int initialRowAddition, int initialColAddition, string order) {
    string search = "", searchedWord = "";
    int row = 0, col = 0, searchSize = 1;
    bool breakAll = false;
    
    // Loop through the words to be searched
    for (int i = 0; i < matrixOfTheWordsToBeSearched.size(); i++) {
        
        // Loop through the matrix to be searched
        for (int j = 0; j < matrixToBeSearched.size(); j++) {
            for (int k = 0; k < matrixToBeSearched[i].size(); k++) {
                
                // Check if the first letter of the word matches the letter the loop is on the matrix to be searched
                if (matrixToBeSearched[j][k] == matrixOfTheWordsToBeSearched[i][0]) {
                    
                    // Setting row and column variables according to the loops
                    row = j;
                    col = k;
                    
                    // Setting search, searchedWord and breakAll variables to their beginning position to start a new search
                    search = "";
                    searchedWord = "";
                    breakAll = false;
                    
                    // Build the word we are searching for
                    for (int l = 0; l < matrixOfTheWordsToBeSearched[i].size(); l++) {
                        searchedWord += matrixOfTheWordsToBeSearched[i][l];
                    }
                    
                    search += matrixToBeSearched[row][col];
                    searchSize = 1;
                    
                    // Perform a row-first search using the parameters of the function
                    if (order == "rowFirst") {
                        
                        // Increasing the number of steps to be taken during each movement to ensure a spiral movement and making sure the number of steps to be taken doesn't exceed the size of the matrix we are searching
                        for (int numberOfStepsToBeTaken = 1; numberOfStepsToBeTaken < matrixToBeSearched.size(); numberOfStepsToBeTaken++) {
                            
                            spiralSearchSteps(matrixToBeSearched, row, initialRowAddition, search, row, col, searchSize, breakAll,  numberOfStepsToBeTaken);
                            
                            // Apply the addition or substraction operations depending on the initialColAddition parameter given to the function to col variable to make sure we're drawing a spiral
                            spiralSearchSteps(matrixToBeSearched, col, initialColAddition, search, row, col, searchSize, breakAll,  numberOfStepsToBeTaken);
                            if (breakAll) {
                                break;
                            }
                        }
                    }
                    
                     
                    // If order parameter of the function is given as "colFirst" perform a column-first search, repeating the same things that would have been done if order parameter of the function is given as "rowFirst", only performing addition or subtraction actions starting from the col variable instead of row
                    if (order == "colFirst") {
                        for (int numberOfStepsToBeTaken = 1; numberOfStepsToBeTaken < matrixToBeSearched.size(); numberOfStepsToBeTaken++) {
                            
                            spiralSearchSteps(matrixToBeSearched, col, initialColAddition, search, row, col, searchSize, breakAll,  numberOfStepsToBeTaken);
                            
                            spiralSearchSteps(matrixToBeSearched, row, initialRowAddition, search, row, col, searchSize, breakAll,  numberOfStepsToBeTaken);
                            
                            if (breakAll) {
                                break;
                            }
                        }
                    }
                    
                    // Check if the found string matches the searched string and add it to the list of found words if it does match and if it doesn't already exist
                    if (search.substr(0, matrixOfTheWordsToBeSearched[i].size()) == searchedWord && find(foundWords.begin(), foundWords.end(), searchedWord) == foundWords.end()) {
                        foundWords.push_back(searchedWord);
                    }
                }
            }
        }
    }
}

// Function to perform spiral search on a matrix in all possible directions
void spiralSearchInAllDirections(vector<vector<char> >& matrixToBeSearched, vector<vector<char> >& matrixOfTheWordsToBeSearched, vector <string>& foundWords) {
    vector<string> possibleOrders;
    possibleOrders.push_back("rowFirst");
    possibleOrders.push_back("colFirst");

    
    for (int i = 1; i >= -1; i -= 2) {
        for (int j = 1; j >= -1; j -= 2) {
            for (string order : possibleOrders) {
                spiralSearchInDirection(matrixToBeSearched, matrixOfTheWordsToBeSearched, foundWords, i, j, order);
            }
        }
    }
}
    
    
    
int main() {
    
    string line, inFileName;
    int matrixSize, numberOfWordsToBeSearched, checkFileReturn;
    vector<string> foundWords;
    ifstream input;
    
    // Get the name of the file to be opened from the user and attempt to open it
    cout << "Enter the name of the file ";
    cin >> inFileName;
    input.open(inFileName.c_str());
    
    // While the fails to open print an error message and prompt the user for a file name
    while (input.fail()) {
        cout << "Could not open the file " << inFileName << endl;
        cout << "Enter the name of the file ";
        cin >> inFileName;
        input.open(inFileName.c_str());
    }
    
    // Check the file to see if the format is correct, terminate if it isn't
    checkFileReturn = checkFile(input, matrixSize, numberOfWordsToBeSearched);
    if (checkFileReturn != 0)
        return 0;
    
    // Clear any flags that could be generated during the execution of checkFile function and reset the get pointer to the beginning of the file
    input.clear();
    input.seekg(0);
    
    // Create the matrix that contains the given elements to create the matrix that needs to be searched
    vector<vector<char> > matrixToBeSearched(matrixSize, vector<char>());
    createMatrixFromFile(input, matrixSize, matrixToBeSearched);
    
    
    // Create a matrix containing the words that need to be searched
    vector<vector<char> > matrixOfTheWordsToBeSearched(numberOfWordsToBeSearched, vector<char>());
    createMatrixFromFile(input, numberOfWordsToBeSearched, matrixOfTheWordsToBeSearched);
    
    // Close the input file
    input.close();
    
    // Perform spiral search in every possible way
    spiralSearchInAllDirections(matrixToBeSearched, matrixOfTheWordsToBeSearched, foundWords);
    
    // Print the words we found from the matrix we gathered them into
    cout << foundWords.size() << " Words are Found:  ";
    for (int i = 0; i < foundWords.size(); i++) {
        cout << foundWords[i] << " ";
    }
    
    cout << endl;
    
    return 0;
}
