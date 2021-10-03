#include "stack.h"
#include "../../src/c/stack.h"

Stack::Stack()
{
    this->my_stack = ::new_stack();
}

Stack::~Stack()
{
    ::delete_stack(this->my_stack);
}

void Stack::push(int x)
{
    ::push(this->my_stack, x);
}

int Stack::pop()
{
    return ::pop(this->my_stack);
}
