#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Every struct stack is implemented by an array to reduce the cost of malloc */

/* The lisked-list of single stack */
typedef struct ll_stack {
    struct stack *block;
    struct ll_stack *next;
} ll_stack_t;

typedef struct pool {
    ll_stack_t *me;
    struct pool *prev;
} pool_t;

pool_t *stack_pool = NULL;

void push(struct stack *this, int x)
{
    /* The new comming element is out of range */
    if (this->sp > 98) {
        /* Get this block's ll_stack_t */
        pool_t *curr = stack_pool;
        while (curr && curr->me && curr->me->block != this)
            curr = curr->prev;

        /* Create a new block */
        ll_stack_t *new_ll_stack = malloc(sizeof(ll_stack_t));
        new_ll_stack->block = malloc(sizeof(struct stack));
        new_ll_stack->next = curr->me->next;

        /* Put the final element in the `stack` */
        this->stk[99] = x;

        /* Copy old stack to new allocated */
        memcpy(new_ll_stack->block, this, sizeof(struct stack));
        curr->me->next = new_ll_stack;

        /* Initialize old stack */
        memset(this->stk, 0, 100 * sizeof(int));
        this->sp = -1;
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

    /* Reach the bottom of `stack` */
    int ret_val = this->stk[0];
    pool_t *curr = stack_pool;
    while (curr && curr->me && curr->me->block != this)
        curr = curr->prev;

    if (!curr || !curr->me->next)
        return ret_val;

    /* Copy next block to `this` */
    struct stack *stack_next = curr->me->next->block;
    ll_stack_t *tmp = curr->me->next;
    memcpy(this, stack_next, sizeof(struct stack));
    memcpy(curr->me->block, curr->me->next->block, sizeof(struct stack));
    curr->me->next = curr->me->next->next;
    this->sp = 99;
    free(stack_next);
    free(tmp);

    return ret_val;
}

struct stack *new_stack()
{
    struct stack *stk = malloc(sizeof(struct stack));
    stk->sp = -1;

    pool_t *tmp = stack_pool;
    stack_pool = calloc(1, sizeof(pool_t));
    stack_pool->me = malloc(sizeof(ll_stack_t));
    stack_pool->prev = tmp;

    stack_pool->me->block = stk;
    stack_pool->me->next = NULL;

    return stk;
}

void delete_stack(struct stack *stk)
{
    /*Ref: https://hackmd.io/@sysprog/c-linked-list */
    pool_t **curr = &stack_pool;
    while ((*curr) && (*curr)->me && (*curr)->me->block != stk)
        curr = &(*curr)->prev;

    for (ll_stack_t *next, *tmp = (*curr)->me; tmp; tmp = next) {
        next = tmp->next;
        free(tmp->block);
        free(tmp);
    }

    /* Concatenate */
    pool_t *prev = (*curr)->prev;
    free(*curr);
    *curr = prev;
}