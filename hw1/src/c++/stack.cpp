#include "stack.h"
#include <stack>
using namespace std;

void Stack::push(int x)
{
    this->myStack.push(x);
}

int Stack::pop()
{
    int result = this->myStack.top();
    this->myStack.pop();
    return result;
}