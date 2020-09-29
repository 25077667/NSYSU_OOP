#ifndef __STACK_H__
#define __STACK_H__

#define STACK_SIZE 100

struct stack {
    int sp;
    int stk[STACK_SIZE];
};

#ifdef __cplusplus
extern "C" {
#endif

extern void push(struct stack *_this, int x);
extern int pop(struct stack *_this);
extern struct stack *new_stack();
extern void delete_stack(struct stack *stk);

#ifdef __cplusplus
}
#endif

#endif