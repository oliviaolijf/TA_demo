//
// Created by dio on 28/03/2023.
//

#include "MyStack.h"

MyStack::MyStack() {
    for (int i=0; i<10 ; i++){
        this->stack.push_back(0);
        max_size++;
    }
}

bool MyStack::push(StateDio* item) {
    if (stack_pointer==max_size){
        grow_stack();
    }
    stack[stack_pointer]=item;
    stack_pointer++;
    return true;
}

StateDio* MyStack::pop() {
    assert(stack_pointer !=0);
    StateDio* item=stack[stack_pointer - 1];
    stack_pointer--;
    return item;
}

void MyStack::grow_stack() {
    for (int i=0; i<max_size;i++){
        stack.push_back(0);
    }
}

StateDio *MyStack::getTop() {
    return stack[stack_pointer-1];
    ;
}

int MyStack::size() {
    return stack_pointer;
}

bool MyStack::isEmpty() {
    return size()==0;
}

