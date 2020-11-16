#include "tree_map.h"

tree_map *init_tree_map(size_t pair_size,
                        int (*cmp_func)(void *a, void *b),
                        key_type *(*get_key)(pair_type *pair),
                        value_type *(*get_value)(pair_type *pair))
{
    tree_map *tmap = (tree_map *)malloc(sizeof(tree_map));
    tmap->pair_size = pair_size;
    tmap->length = 0;
    tmap->get_key = get_key;
    tmap->get_value = get_value;
    tmap->cmp_func = cmp_func;
    tmap->rbt = init_red_black_tree(pair_size, cmp_func, get_key);
    return tmap;
}

size_t tree_map_get_length(tree_map *tmap)
{
    return tmap->length;
}

int tree_map_is_empty(tree_map *tmap)
{
    return tmap->length == 0;
}

void tree_map_put(tree_map *tmap, pair_type *pair)
{
    rbt_insert(tmap->rbt, pair);
    tmap->length = tmap->rbt->node_count;
    return;
}

int tree_map_has_key(tree_map *tmap, key_type *key)
{
    pair_type *pair = rbt_search(tmap->rbt, key);
    return pair != NULL;
}

pair_type *tree_map_get_pair(tree_map *tmap, key_type *key)
{
    return rbt_search(tmap->rbt, key);
}

value_type *tree_map_get_value(tree_map *tmap, key_type *key)
{
    pair_type *pair = rbt_search(tmap->rbt, key);
    return pair == NULL ? NULL : tmap->get_value(pair);
}

void tree_map_delete_pair(tree_map *tmap, key_type *key)
{
    rbt_delete(tmap->rbt, key);
    tmap->length = tmap->rbt->node_count;
    return;
}

void destory_tree_map(tree_map **tmap_ptr)
{
    tree_map *tmap = *tmap_ptr;
    destory_red_black_tree(&tmap->rbt);
    *tmap_ptr = NULL;
    return;
}
