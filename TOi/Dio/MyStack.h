//
// Created by dio on 28/03/2023.
//

#ifndef ENGINE_MYSTACK_H
#define ENGINE_MYSTACK_H
#include <vector>
#include <iostream>
#include <tuple>
#include <cassert>
#include "StateSetDio.h"

using namespace std;

class MyStack {
public:
    MyStack();

private:
    vector <StateDio*> stack;
    int stack_pointer=0;
    int max_size=0;

public:
    bool push(StateDio* item);
    StateDio* pop();
    void grow_stack();
    StateDio* getTop();
    int size();
    bool isEmpty();

};


#endif //ENGINE_MYSTACK_H
