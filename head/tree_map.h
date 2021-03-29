#ifndef __TREE_MAP_H__
#define __TREE_MAP_H__

#include "rb_tree.h"
#include "array_list.h"

typedef void pair_type;

typedef struct tree_map
{
    red_black_tree *rbt;
    size_t pair_size;
    size_t length;
    //get key and compare key
    key_type *(*get_key)(pair_type *pair);
    int (*cmp_func)(void *a, void *b);
    //get value
    value_type *(*get_value)(pair_type *pair);
} tree_map;

tree_map *init_tree_map(size_t pair_size,
                        int (*cmp_func)(void *a, void *b),
                        key_type *(*get_key)(pair_type *pair),
                        value_type *(*get_value)(pair_type *pair));

size_t tree_map_get_length(tree_map *tmap);

int tree_map_is_empty(tree_map *tmap);

void tree_map_put(tree_map *tmap, pair_type *pair);

int tree_map_has_key(tree_map *tmap, key_type *key);

pair_type *tree_map_get_pair(tree_map *tmap, key_type *key);

value_type *tree_map_get_value(tree_map *tmap, key_type *key);

void _tree_map_to_array(tree_map *tmap, rbt_node *root, array_list *arr);

array_list *tree_map_to_array(tree_map *tmap);

void tree_map_delete_pair(tree_map *tmap, key_type *key);

void destory_tree_map(tree_map **tmap_ptr);

#endif
