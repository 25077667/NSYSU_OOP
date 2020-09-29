#ifndef __STACK_HPP__
#define __STACK_HPP__

class Stack
{
    enum { STACK_SIZE = 100 };
    int stk[STACK_SIZE];
    int sp;
    struct stack *my_stack;

public:
    Stack();
    ~Stack();
    void push(int x);
    int pop();
};

#endif