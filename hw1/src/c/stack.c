#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/* Every struct stack is implemented by an array to reduce the cost of malloc */

/* The lisked-list of single stack */
typedef struct ll_stack {
    struct stack *block;
    struct ll_stack *prev;
} ll_stack;

typedef struct pool {
    ll_stack *me;
    struct pool *prev;
} pool;

pool *stack_pool = NULL;

void push(struct stack *this, int x)
{
    /* The new comming element is out of range */
    if (this->sp > 98) {
        /* Get this block's ll_stack */
        pool *curr = stack_pool;
        while (curr && curr->me && curr->me->block != this)
            curr = curr->prev;

        /* Create a new block */
        ll_stack *new_ll_stack = malloc(sizeof(struct ll_stack));
        new_ll_stack->block = malloc(sizeof(struct stack));
        new_ll_stack->block->sp = -1;
        new_ll_stack->prev = curr->me;
        if (curr->me)
            curr->me = new_ll_stack;
        else {
            perror("Push to non-exist stack.");
            free(new_ll_stack->block);
            free(new_ll_stack);
        }

        this = new_ll_stack->block;
    }

    this->stk[++this->sp] = x;
}

int pop(struct stack *this)
{
    if (!this) {
        perror("Popping an empty stack");
        return __INT32_MAX__;
    }
    if (this->sp > 0)
        return this->stk[this->sp--];

    int ret_val = this->stk[0];
    pool *curr = stack_pool;
    while (curr && curr->me && curr->me->block != this)
        curr = curr->prev;

    /* Free block if it's empty */
    struct stack *next = curr->prev->me->block;
    free(this);
    this = next;
    return ret_val;
}

struct stack *new_stack()
{
    struct stack *stk = malloc(sizeof(struct stack));
    stk->sp = -1;

    pool *tmp = stack_pool;
    stack_pool = calloc(1, sizeof(pool));
    stack_pool->me = malloc(sizeof(ll_stack));
    stack_pool->prev = tmp;

    stack_pool->me->block = stk;
    stack_pool->me->prev = NULL;

    return stk;
}

void delete_stack(struct stack *stk)
{
    /*Ref: https://hackmd.io/@sysprog/c-linked-list */
    pool **curr = &stack_pool;
    while ((*curr) && (*curr)->me && (*curr)->me->block != stk)
        curr = &(*curr)->prev;

    for (ll_stack *next, *tmp = (*curr)->me; tmp; tmp = next) {
        next = tmp->prev;
        free(tmp->block);
        free(tmp);
    }

    /* Concatenate */
    *curr = (*curr)->prev;
}