#ifndef __TREE_SET_H__
#define __TREE_SET_H__

#include "rb_tree.h"
#include "array_list.h"

typedef struct tree_set
{
    size_t data_size;
    size_t length;
    int (*cmp_func)(void *a, void *b);
    red_black_tree *rbt;
} tree_set;

key_type *tree_set_get_key(data_type *data);

tree_set *init_tree_set(size_t data_size,
                        int (*cmp_func)(void *a, void *b));

size_t tree_set_get_length(tree_set *tset);

int tree_set_is_empty(tree_set *tset);

void tree_set_put(tree_set *tset, data_type *data);

int tree_set_has_data(tree_set *tset, data_type *data);

void _tree_set_to_array(tree_set *tset, rbt_node *root, array_list *arr);

array_list *tree_set_to_array(tree_set *tset);

void tree_set_delete(tree_set *tset, data_type *data);

void destory_tree_set(tree_set **tset_ptr);

#endif
