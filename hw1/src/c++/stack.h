#ifndef __STACK_H__
#define __STACK_H__
#include <stack>

class Stack
{
    std::stack<int> myStack;

public:
    Stack() {}
    ~Stack() {}
    void push(int x);
    int pop();
};

#endif