//
//  DynStuQueue.hpp
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Created by Beren Aydogan on 6.11.2023.
//

#ifndef DynStuQueue_hpp
#define DynStuQueue_hpp

#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class DynStuQueue
{
private:
    academic *front;
    academic *rear;

public:
    // Constructor
    DynStuQueue();
    // Member functions
    void enqueue(string, int, int, service);
    void dequeue(string &, int &, int &, service &);
    bool isEmpty() const;
    void clear();
};

#endif /* DynStuQueue_hpp */
