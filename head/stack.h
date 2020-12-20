#ifndef __STACK_H__
#define __STACK_H__

#include "common.h"

typedef struct stack_node
{
    data_type *data;
    struct stack_node *last;
} stack_node;

stack_node *init_stack_node(data_type *data, size_t data_size, stack_node *last);

void destory_stack_node(stack_node **node_ptr);

typedef struct stack
{
    stack_node *top;
    stack_node *head;
    size_t length;
    size_t data_size;
} stack;

stack *init_stack(size_t data_size);

int stack_is_empty(stack *st);

void stack_push(stack *st, data_type *data);

void stack_pop(stack *st);

data_type *stack_get_peek(stack *st);

size_t stack_get_length(stack *st);

void destory_stack(stack **st_ptr);

#endif
