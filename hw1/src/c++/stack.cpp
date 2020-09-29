#include "stack.h"
#include "../../src/c/stack.h"

void (*push_c)(struct stack *, int) = push;
int (*pop_c)(struct stack *) = pop;

Stack::Stack()
{
    this->my_stack = new_stack();
}

Stack::~Stack()
{
    delete_stack(this->my_stack);
}

void Stack::push(int x)
{
    push_c(this->my_stack, x);
}

int Stack::pop()
{
    return pop_c(this->my_stack);
}