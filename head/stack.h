#ifndef _STACK_H
#define _STACK_H

#define data_type void

typedef struct stack_node
{
    data_type *data;
    size_t data_size;
    struct stack_node *last;
} stack_node;

stack_node *init_stack_node(data_type *data, size_t data_size, stack_node *last);

void destory_stack_node(stack_node **node_ptr);

typedef struct stack
{
    stack_node *top;
    stack_node *head;
    int length;
} stack;

stack *init_stack();

int stack_is_empty(stack *st);

void stack_push(stack *st, data_type *data, size_t data_size);

void stack_pop(stack *st);

data_type *stack_get_peek(stack *st);

int stack_get_length(stack *st);

void destory_stack(stack **st_ptr);

#endif