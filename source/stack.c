#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * stack_node
*/

stack_node *init_stack_node(data_type *data, stack_node *last)
{
    stack_node *sn = (stack_node *)malloc(sizeof(stack_node));
    sn->data = data;
    sn->last = last;
    return sn;
}

void destory_stack_node(stack_node **node_ptr)
{
    free(*node_ptr);
    *node_ptr = NULL;
}

/**
 * stack
*/

stack *init_stack()
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->head = init_stack_node(NULL, NULL);
    st->top = st->head;
    return st;
}

int stack_is_empty(stack *st)
{
    return st->head == st->top;
}

void stack_push(stack *st, data_type *data)
{
    stack_node *node = init_stack_node(data, st->top);
    st->top = node;
    return;
}

data_type *stack_pop(stack *st)
{
    if (stack_is_empty(st))
    {
        printf("stack pop error: stack is empty!\n");
        exit(1);
    }
    stack_node *tmp = st->top;
    st->top = st->top->last;
    destory_stack_node(&tmp);
    return tmp->data;
}

data_type *stack_get_peek(stack *st)
{
    return st->top->data;
}

void destory_stack(stack **st_ptr)
{
    stack *st = *st_ptr;
    while (!stack_is_empty(st))
    {
        stack_pop(st);
    }
    destory_stack_node(&st->head);
    free(st);
    *st_ptr = NULL;
    return;
}
