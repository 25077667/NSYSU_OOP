#ifndef __STACK_HPP__
#define __STACK_HPP__

class Stack
{
    struct stack *my_stack;

public:
    Stack();
    ~Stack();
    void push(int x);
    int pop();
};

#endif