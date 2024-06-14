//
//  ServiceStack.hpp
//  beren.aydogan_Aydogan_Beren_HW3
//
//  Created by Beren Aydogan on 6.11.2023.
//

#ifndef ServiceStack_hpp
#define ServiceStack_hpp

#include <stdio.h>
#include <string>
#include "structs.h"

using namespace std;

class ServiceStack {
private:
    command *top;
public:
    ServiceStack();
    void push(string);
    void pop(string &);
    void pop();
    void popSameFunc(string);
    bool isEmpty();
    void printStackTrace();
    void clear();
};

#endif /* ServiceStack_hpp */
