#include "myutil.h"

/**
 * queue_node
*/

queue_node *init_queue_node(data_type *data,
                            size_t data_size,
                            queue_node *last)
{
    queue_node *node = (queue_node *)malloc(sizeof(queue_node));
    //node->data = data
    node->data = (data_type *)malloc(data_size);
    shift_data(data, node->data, data_size);
    //
    node->last = last;
    return node;
}

void destory_queue_node(queue_node **node_ptr)
{
    queue_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
    return;
}

/**
 * queue
*/

queue *init_queue(size_t data_size)
{
    queue *qu = (queue *)malloc(sizeof(queue));
    qu->tail = init_queue_node(NULL, 0, NULL);
    qu->p_head = qu->tail;
    qu->length = 0;
    qu->data_size = data_size;
    return qu;
}

int queue_is_empty(queue *qu)
{
    return qu->length == 0;
}

void queue_push_front(queue *qu, data_type *data)
{
    queue_node *node = init_queue_node(data, qu->data_size, NULL);
    qu->p_head->last = node;
    qu->p_head = node;
    qu->length++;
    return;
}

void queue_pop_back(queue *qu)
{
    if (queue_is_empty(qu))
    {
        printf("queue pop back error: queue is empty!\n");
        exit(1);
    }
    queue_node *node = qu->tail->last;
    qu->tail->last = node->last;
    destory_queue_node(&node);
    qu->length--;
    if (queue_get_length(qu) == 0)
    {
        qu->p_head = qu->tail;
    }
    return;
}

size_t queue_get_length(queue *qu)
{
    return qu->length;
}

data_type *queue_get_back(queue *qu)
{
    if (queue_is_empty(qu))
    {
        printf("queue get back error: queue is empty!\n");
        exit(1);
    }
    return qu->tail->last->data;
}

void destory_queue(queue **qu_ptr)
{
    queue *qu = *qu_ptr;
    while (!queue_is_empty(qu))
    {
        queue_pop_back(qu);
    }
    destory_queue_node(&qu->tail);
    free(qu);
    *qu_ptr = NULL;
    return;
}


/*a < b, 小根堆*/
heap *init_heap(size_t data_size, int (*cmp_func)(void *a, void *b))
{
    heap *hp = (heap *)malloc(sizeof(heap));
    hp->length = 0;
    hp->capacity = MIN_CAPACITY;
    hp->data_size = data_size;
    hp->cmp_func = cmp_func;
    hp->array = (heap_node *)calloc(hp->capacity, sizeof(heap_node));
    return hp;
}

int heap_is_empty(heap *hp)
{
    return hp->length == 0;
}

void heap_add(heap *hp, data_type *data)
{
    if (hp->capacity <= hp->length)
    {
        expand_capacity((void **)&hp->array, &hp->capacity, sizeof(heap_node));
    }
    size_t data_size = hp->data_size;
    size_t i = hp->length;
    while (i > 0)
    {
        size_t parent_i = (i - 1) / 2;
        if (hp->cmp_func(hp->array[parent_i].data, data) <= 0)
        {
            break;
        }
        hp->array[i].data = hp->array[parent_i].data;
        i = parent_i;
    }
    hp->array[i].data = (data_type *)malloc(data_size);
    shift_data(data, hp->array[i].data, data_size);
    hp->length++;
    return;
}

data_type *heap_get_peek(heap *hp)
{
    if (heap_is_empty(hp))
    {
        printf("heap get peek error: heap is empty!\n");
        exit(1);
    }
    return hp->array[0].data;
}

size_t heap_get_length(heap *hp)
{
    return hp->length;
}

void heap_pop(heap *hp)
{
    if (heap_is_empty(hp))
    {
        printf("heap pop error: heap is empty!\n");
        exit(1);
    }
    size_t size = hp->data_size;
    free(hp->array[0].data);
    hp->array[0].data = NULL;
    data_type *x = hp->array[hp->length - 1].data;
    // shift_data(hp->array[hp->length - 1].data, x, size);
    size_t i = 0;
    if(hp->length >= 2){
        while (i <= (hp->length - 2) / 2)
        {
            size_t left = i * 2 + 1;
            size_t right = i * 2 + 2;
            size_t min = left;
            if (right <= hp->length - 1 && hp->cmp_func(hp->array[right].data, hp->array[min].data) < 0)
            {
                min = right;
            }
            if (hp->cmp_func(hp->array[min].data, x) >= 0)
            {
                break;
            }
            hp->array[i].data = hp->array[min].data;
            i = min;
        }
    }
    hp->array[i].data = x;
    hp->length--;
    return;
}

void destory_heap(heap **hp_ptr)
{
    heap *hp = *hp_ptr;
    for (size_t i = 0; i < hp->length; i++)
    {
        free(hp->array[i].data);
    }
    free(hp->array);
    free(hp);
    *hp_ptr = NULL;
    return;
}


key_type *tree_set_get_key(data_type *data)
{
    return data;
}

tree_set *init_tree_set(size_t data_size,
                        int (*cmp_func)(void *a, void *b))
{
    tree_set *tset = (tree_set *)malloc(sizeof(tree_set));
    tset->data_size = data_size;
    tset->length = 0;
    tset->cmp_func = cmp_func;
    tset->rbt = init_red_black_tree(data_size, cmp_func, tree_set_get_key);
    return tset;
}
size_t tree_set_get_length(tree_set *tset)
{
    return tset->length;
}

int tree_set_is_empty(tree_set *tset)
{
    return tset->length == 0;
}

void tree_set_put(tree_set *tset, data_type *data)
{
    rbt_insert(tset->rbt, data);
    tset->length = tset->rbt->node_count;
    return;
}

int tree_set_has_data(tree_set *tset, data_type *data)
{
    data_type *p = rbt_search(tset->rbt, data);
    return p != NULL;
}

void _tree_set_to_array(tree_set *tset, rbt_node *root, array_list *arr)
{
    if (root == NULL || root->is_null_leaf)
    {
        return;
    }
    _tree_set_to_array(tset, root->left, arr);
    array_list_push_back(arr, root->data);
    _tree_set_to_array(tset, root->right, arr);
}

array_list *tree_set_to_array(tree_set *tset)
{
    array_list *arr = init_array_list(tset->data_size);
    _tree_set_to_array(tset, tset->rbt->root, arr);
    return arr;
}

void tree_set_delete(tree_set *tset, data_type *data)
{
    rbt_delete(tset->rbt, data);
    tset->length = tset->rbt->node_count;
    return;
}

void destory_tree_set(tree_set **tset_ptr)
{
    tree_set *tset = *tset_ptr;
    destory_red_black_tree(&tset->rbt);
    free(tset);
    *tset_ptr = NULL;
    return;
}

rbt_node *init_black_node(data_type *data, size_t data_size)
{
    rbt_node *node = (rbt_node *)malloc(sizeof(rbt_node));
    node->is_null_leaf = 0;
    node->data = (void *)malloc(data_size);
    shift_data(data, node->data, data_size);
    node->color = RBT_BLACK;
    //TODO:
    node->parent = NULL;
    //
    node->left = init_null_leaf_node(node);
    node->right = init_null_leaf_node(node);
    return node;
}

rbt_node *init_red_node(data_type *data, size_t data_size, rbt_node *parent)
{
    rbt_node *node = (rbt_node *)malloc(sizeof(rbt_node));
    node->is_null_leaf = 0;
    node->data = (void *)malloc(data_size);
    shift_data(data, node->data, data_size);
    node->color = RBT_RED;
    node->parent = parent;
    node->left = init_null_leaf_node(node);
    node->right = init_null_leaf_node(node);
    return node;
}

rbt_node *init_null_leaf_node(rbt_node *parent)
{
    rbt_node *leaf = (rbt_node *)malloc(sizeof(rbt_node));
    leaf->is_null_leaf = 1;
    leaf->data = NULL;
    leaf->color = RBT_BLACK;
    leaf->left = NULL;
    leaf->right = NULL;
    return leaf;
}

void destory_rbt_node(rbt_node **node_ptr)
{
    rbt_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
    return;
}

red_black_tree *init_red_black_tree(size_t data_size,
                                    int (*cmp_func)(void *a, void *b),
                                    key_type *(*get_key)(data_type *data))
{
    red_black_tree *rbt = (red_black_tree *)malloc(sizeof(red_black_tree));
    rbt->data_size = data_size;
    rbt->node_count = 0;
    rbt->root = NULL;
    rbt->cmp_func = cmp_func;
    rbt->get_key = get_key;
    return rbt;
}

int rbt_is_empty(red_black_tree *rbt)
{
    return rbt->node_count == 0;
}

void rbt_insert(red_black_tree *rbt, data_type *data)
{
    rbt->root = _rbt_insert(rbt, rbt->root, NULL, data);
    log("insert success..\n\n");
    rbt->node_count++;
    return;
}

rbt_node *_rbt_insert(red_black_tree *rbt,
                      rbt_node *root, rbt_node *parent,
                      data_type *data)
{
    log("start insert.\n");
    if (root == NULL || root->is_null_leaf)
    {
        log("root is null or leaf.\n");
        if (parent != NULL)
        {
            log("root is leaf. end insert.\n");
            return init_red_node(data, rbt->data_size, parent);
        }
        else
        {
            log("root is null. end insert.\n");
            return init_black_node(data, rbt->data_size);
        }
    }
    key_type *root_key = rbt->get_key(root->data);
    key_type *key = rbt->get_key(data);
    if (rbt->cmp_func(root_key, key) == 0)
    {
        //printf("warning: duplicate happened!\n");
        shift_data(data, root->data, rbt->data_size);
        rbt->node_count--;
        return root;
    }
    int is_left = 0;
    if (rbt->cmp_func(root_key, key) > 0)
    {
        rbt_node *left = _rbt_insert(rbt, root->left, root, data);
        if (left == root->parent)
        {
            return left;
        }
        root->left = left;
        is_left = 1;
    }
    else
    {
        rbt_node *right = _rbt_insert(rbt, root->right, root, data);
        if (right == root->parent)
        {
            return right;
        }
        root->right = right;
        is_left = 0;
    }
    if (is_left)
    {
        log("inserted node is left.\n");
        if (root->color == RBT_RED && root->left->color == RBT_RED)
        {
            rbt_node *sibling = rbt_find_sibling(rbt, root);
            if (sibling == NULL || sibling->color == RBT_BLACK)
            {
                if (root->parent->left == root)
                {
                    rbt_right_rotate(rbt, root, 1);
                }
                else
                {
                    rbt_right_rotate(rbt, root->left, 0);
                    root = root->parent;
                    rbt_left_rotate(rbt, root, 1);
                }
            }
            else
            {
                root->color = RBT_BLACK;
                sibling->color = RBT_BLACK;
                if (root->parent->parent != NULL)
                {
                    root->parent->color = RBT_RED;
                }
            }
        }
    }
    else
    {
        log("inserted node is right.\n");
        if (root->color == RBT_RED && root->right->color == RBT_RED)
        {
            rbt_node *sibling = rbt_find_sibling(rbt, root);
            if (sibling == NULL || sibling->color == RBT_BLACK)
            {
                if (root->parent->right == root)
                {
                    rbt_left_rotate(rbt, root, 1);
                }
                else
                {
                    rbt_left_rotate(rbt, root->right, 0);
                    root = root->parent;
                    rbt_right_rotate(rbt, root, 1);
                }
            }
            else
            {
                root->color = RBT_BLACK;
                sibling->color = RBT_BLACK;
                if (root->parent->parent != NULL)
                {
                    root->parent->color = RBT_RED;
                }
            }
        }
    }
    log("end insert.\n");
    return root;
}

data_type *rbt_search(red_black_tree *rbt,
                      key_type *key)
{
    return _rbt_search(rbt, rbt->root, key);
}

data_type *_rbt_search(red_black_tree *rbt,
                       rbt_node *root,
                       key_type *key)
{
    if (root == NULL || root->is_null_leaf)
    {
        return NULL;
    }
    key_type *data_key = rbt->get_key(root->data);
    if (rbt->cmp_func(data_key, key) == 0)
    {
        return root->data;
    }
    if (rbt->cmp_func(data_key, key) < 0)
    {
        return _rbt_search(rbt, root->right, key);
    }
    else
    {
        return _rbt_search(rbt, root->left, key);
    }
}

void rbt_delete(red_black_tree *rbt, key_type *key)
{
    _rbt_delete(rbt, rbt->root, key);
    rbt->node_count--;
    if (rbt->root == NULL)
    {
        return;
    }
    if (rbt->root->is_null_leaf)
    {
        free(rbt->root);
        rbt->root = NULL;
    }
    return;
}

void _rbt_delete(red_black_tree *rbt, rbt_node *root, key_type *key)
{
    if (root == NULL || root->is_null_leaf)
    {
        rbt->node_count++;
        return;
    }
    key_type *root_key = rbt->get_key(root->data);
    if (rbt->cmp_func(root_key, key) == 0)
    {
        if (root->right->is_null_leaf || root->left->is_null_leaf)
        {
            rbt_delete_one_child(rbt, root);
        }
        else
        {
            rbt_node *inorder_successor = rbt_find_smallest(rbt, root->right);
            shift_data(inorder_successor->data, root->data, rbt->data_size);
            _rbt_delete(rbt, root->right,
                        rbt->get_key(inorder_successor->data));
        }
    }
    else if (rbt->cmp_func(root_key, key) < 0)
    {
        _rbt_delete(rbt, root->right, key);
    }
    else
    {
        _rbt_delete(rbt, root->left, key);
    }
    return;
}

rbt_node *rbt_find_smallest(red_black_tree *rbt, rbt_node *root)
{
    rbt_node *prev = NULL;
    while (root != NULL && !root->is_null_leaf)
    {
        prev = root;
        root = root->left;
    }
    return prev != NULL ? prev : root;
}

void rbt_delete_one_child(red_black_tree *rbt,
                          rbt_node *node_to_be_deleted)
{
    rbt_node *child =
        node_to_be_deleted->right->is_null_leaf ? node_to_be_deleted->left : node_to_be_deleted->right;

    rbt_color del_color = node_to_be_deleted->color;
    rbt_replace_node(rbt, &node_to_be_deleted, child);

    if (del_color == RBT_BLACK)
    {
        if (child->color == RBT_RED)
        {
            child->color = RBT_BLACK;
        }
        else
        {
            rbt_delete_case1(rbt, child);
        }
    }
    return;
}

/*double black node becomes root then we are done. Turning it into single black*/
void rbt_delete_case1(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    if (double_black_node->parent == NULL)
    {
        rbt->root = double_black_node;
        return;
    }
    rbt_delete_case2(rbt, double_black_node);
    return;
}

/*sibling is red and parent and sibling's children are black then rotate it
 so that sibling becomes black. double black node is still double black so need further 
 processing.*/
void rbt_delete_case2(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (sibling_node->color == RBT_RED)
    {
        if (sibling_node == sibling_node->parent->left)
        {
            rbt_right_rotate(rbt, sibling_node, 1);
        }
        else
        {
            rbt_left_rotate(rbt, sibling_node, 1);
        }
        if (sibling_node->parent == NULL)
        {
            rbt->root = sibling_node;
        }
    }
    rbt_delete_case3(rbt, double_black_node);
    return;
}

/**
* If sibling, sibling's children and parent are all black then turn sibling
* into red. This reduces black node for both the paths from parent. Now parent
* is new double black node which needs further processing by going back to
* case1.
*/
void rbt_delete_case3(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (double_black_node->parent->color == RBT_BLACK && sibling_node->color == RBT_BLACK && sibling_node->left->color == RBT_BLACK && sibling_node->right->color == RBT_BLACK)
    {
        sibling_node->color = RBT_RED;
        rbt_delete_case1(rbt, double_black_node->parent);
    }
    else
    {
        rbt_delete_case4(rbt, double_black_node);
    }
}

/**
* If sibling color is black, parent color is red and sibling's children color
* is black then swap color b/w sibling and parent. This increases one black
* node on double black node path but does not affect black node count on
* sibling path. We are done if we hit this situation.
*/
void rbt_delete_case4(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (double_black_node->parent->color == RBT_RED && sibling_node->color == RBT_BLACK && sibling_node->left->color == RBT_BLACK && sibling_node->right->color == RBT_BLACK)
    {
        sibling_node->color = RBT_RED;
        double_black_node->parent->color = RBT_BLACK;
        return;
    }
    else
    {
        rbt_delete_case5(rbt, double_black_node);
    }
}

/**
* If sibling is black, double black node is left child of its parent, siblings
* right child is black and sibling's left child is red then do a right rotation
* at siblings left child and swap colors. This converts it to delete case6. It
* will also have a mirror case.
*/
void rbt_delete_case5(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    if (sibling_node->color == RBT_BLACK)
    {
        if (double_black_node->parent->left == double_black_node && sibling_node->right->color == RBT_BLACK && sibling_node->left->color == RBT_RED)
        {
            rbt_right_rotate(rbt, sibling_node->left, 1);
        }
        else if (double_black_node->parent->left != double_black_node && sibling_node->left->color == RBT_BLACK && sibling_node->right->color == RBT_RED)
        {
            rbt_left_rotate(rbt, sibling_node->right, 1);
        }
    }
    rbt_delete_case6(rbt, double_black_node);
}

/**
* If sibling is black, double black node is left child of its parent, sibling
* left child is black and sibling's right child is red, sibling takes its
* parent color, parent color becomes black, sibling's right child becomes black
* and then do left rotation at sibling without any further change in color.
* This removes double black and we are done. This also has a mirror condition.
*/
void rbt_delete_case6(red_black_tree *rbt,
                      rbt_node *double_black_node)
{
    rbt_node *sibling_node = rbt_find_sibling(rbt, double_black_node);
    sibling_node->color = sibling_node->parent->color;
    sibling_node->parent->color = RBT_BLACK;
    if (double_black_node->parent->left == double_black_node)
    {
        sibling_node->right->color = RBT_BLACK;
        rbt_left_rotate(rbt, sibling_node, 0);
    }
    else
    {
        sibling_node->left->color = RBT_BLACK;
        rbt_right_rotate(rbt, sibling_node, 0);
    }
    if (sibling_node->parent == NULL)
    {
        rbt->root = sibling_node;
    }
    return;
}

void rbt_replace_node(red_black_tree *rbt, rbt_node **root_ptr, rbt_node *child)
{
    rbt_node *root = *root_ptr;
    child->parent = root->parent;
    if (root->parent == NULL)
    {
        rbt->root = child;
    }
    else
    {
        if (root->parent->left == root)
        {
            root->parent->left = child;
        }
        else
        {
            root->parent->right = child;
        }
    }
    free(root->data);
    free(root);
    *root_ptr = NULL;
    return;
}

rbt_node *rbt_find_sibling(red_black_tree *rbt, rbt_node *root)
{
    rbt_node *parent = root->parent;
    if (parent->left == root)
    {
        if (parent->right->is_null_leaf)
        {
            return NULL;
        }
        else
        {
            return parent->right;
        }
    }
    else
    {
        if (parent->left->is_null_leaf)
        {
            return NULL;
        }
        else
        {
            return parent->left;
        }
    }
}

void rbt_right_rotate(red_black_tree *rbt, rbt_node *root, int change_color)
{
    rbt_node *parent = root->parent;
    root->parent = parent->parent;
    if (parent->parent != NULL)
    {
        if (parent->parent->right == parent)
        {
            parent->parent->right = root;
        }
        else
        {
            parent->parent->left = root;
        }
    }
    rbt_node *right = root->right;
    root->right = parent;
    parent->parent = root;
    parent->left = right;
    if (right != NULL)
    {
        right->parent = parent;
    }
    if (change_color)
    {
        root->color = RBT_BLACK;
        parent->color = RBT_RED;
    }
    return;
}

void rbt_left_rotate(red_black_tree *rbt, rbt_node *root, int change_color)
{
    rbt_node *parent = root->parent;
    root->parent = parent->parent;
    if (parent->parent != NULL)
    {
        if (parent->parent->right == parent)
        {
            parent->parent->right = root;
        }
        else
        {
            parent->parent->left = root;
        }
    }
    rbt_node *left = root->left;
    root->left = parent;
    parent->parent = root;
    parent->right = left;
    if (left != NULL)
    {
        left->parent = parent;
    }
    if (change_color)
    {
        root->color = RBT_BLACK;
        parent->color = RBT_RED;
    }
    return;
}

void _destory_red_black_tree(red_black_tree *rbt, rbt_node **root_ptr)
{
    rbt_node *root = *root_ptr;
    if (root == NULL)
    {
        return;
    }
    if (root->is_null_leaf)
    {
        free(root);
        *root_ptr = NULL;
        return;
    }
    _destory_red_black_tree(rbt, &root->left);
    _destory_red_black_tree(rbt, &root->right);
    free(root);
    *root_ptr = NULL;
    return;
}

void destory_red_black_tree(red_black_tree **rbt_ptr)
{
    red_black_tree *rbt = *rbt_ptr;
    _destory_red_black_tree(rbt, &rbt->root);
    *rbt_ptr = NULL;
    return;
}

int rbt_is_validate(red_black_tree *rbt)
{
    rbt_node *root = rbt->root;
    if (root == NULL)
    {
        return 1;
    }
    if (root->color != RBT_BLACK)
    {
        printf("root is not black!\n");
        return 0;
    }
    size_t b = 0;
    if (!black_nodes_count_is_same(root, &b, 0))
    {
        printf("nodes count not same!\n");
        return 0;
    }
    if (!no_red_red_parent_child(root, RBT_BLACK))
    {
        printf("has red red child!\n");
        return 0;
    }
    return 1;
    //return black_nodes_count_is_same(root, &b, 0) && no_red_red_parent_child(root, RBT_BLACK);
}

int black_nodes_count_is_same(rbt_node *root, size_t *black_count, size_t cur_count)
{
    if (root->color == RBT_BLACK)
    {
        cur_count++;
    }
    if (root->left == NULL && root->right == NULL)
    {
        if (*black_count == 0)
        {
            *black_count = cur_count;
            return 1;
        }
        else
        {
            return cur_count == *black_count;
        }
    }
    return black_nodes_count_is_same(root->left, black_count, cur_count) && black_nodes_count_is_same(root->right, black_count, cur_count);
}

int no_red_red_parent_child(rbt_node *root, rbt_color parent_color)
{
    if (root == NULL)
    {
        return 1;
    }
    if (root->color == RBT_RED && parent_color == RBT_RED)
    {
        return 0;
    }
    return no_red_red_parent_child(root->left, root->color) && no_red_red_parent_child(root->right, root->color);
}


my_string *init_my_string(){
    my_string *s = (my_string *)malloc(sizeof(my_string));
    s->length = 0;
    s->str = init_array_list(sizeof(char));
    return s;
}

void my_string_read(my_string *s, FILE *stream){
    FILE *fp = stream;
    if(fp == NULL){
        printf("stream open error: can't open stream!\n");
        exit(1);
    }
    char ch;
    while((ch = getc(fp)) != '\n'){
        array_list_push_back(s->str, &ch);
    }
    ch = '\0';
    array_list_push_back(s->str, &ch);
    s->length = s->str->length;
    return;
}

size_t my_string_get_length(my_string *s){
    return s->length;
}

char my_string_index_of(my_string *s, size_t index){
    char ch = *(char *)array_list_get_data(s->str, index);
    return ch;
}

int my_string_is_empty(my_string *s){
    return s->length == 0;
}

int my_string_compare(my_string *s1, my_string *s2){
    array_list_node *p1 = s1->str->array;
    array_list_node *p2 = s2->str->array;
    char ch1 = *(char *)p1->data;
    char ch2 = *(char *)p2->data;
    while(ch1 != '\0' && ch2 != '\0'){
        if(ch1 > ch2){
            return 1;
        } else if(ch1 < ch2){
            return -1;
        } else {
            p1++;
            p2++;
            ch1 = *(char *)p1->data;
            ch2 = *(char *)p2->data;
        }
    }
    if(ch1 == '\0' && ch2 != '\0'){
        return -1;
    } else if(ch1 != '\0' && ch2 == '\0'){
        return 1;
    } else {
        return 0;
    }
}

void my_string_replace(my_string *s, char ch, size_t index){
    array_list_set_data(s->str, &ch, index);
    return;
}

void my_string_insert(my_string *s, char ch, size_t index){
    array_list_insert(s->str, &ch, index);
    s->length = s->str->length;
    return;
}

void my_string_push(my_string *s, char ch){
    my_string_insert(s, ch, s->length);
    return;
}

void my_string_delete(my_string *s, size_t index){
    array_list_delete(s->str, index);
    s->length = s->str->length;
    return;
}

char *my_string_to_char_array(my_string *s){
    size_t len = s->length;
    char *str = (char *)calloc(s->length, sizeof(char));
    array_list_node *p = s->str->array;
    for(size_t i = 0; i < len; i++){
        str[i] = *((char *)p->data);
        p++;
    }
    return str;
}

void destory_my_string(my_string **s_ptr){
    my_string *s = *s_ptr;
    destory_array_list(&s->str);
    free(s);
    *s_ptr = NULL;
    return;
}

/**
 * stack_node
*/

stack_node *init_stack_node(data_type *data, size_t data_size, stack_node *last)
{
    stack_node *sn = (stack_node *)malloc(sizeof(stack_node));
    sn->data = (data_type *)malloc(data_size);
    shift_data(data, sn->data, data_size);
    sn->last = last;
    return sn;
}

void destory_stack_node(stack_node **node_ptr)
{
    stack_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
}

/**
 * stack
*/

stack *init_stack(size_t data_size)
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->head = init_stack_node(NULL, 0, NULL);
    st->top = st->head;
    st->length = 0;
    st->data_size = data_size;
    return st;
}

int stack_is_empty(stack *st)
{
    return st->length == 0;
}

void stack_push(stack *st, data_type *data)
{
    stack_node *node = init_stack_node(data, st->data_size, st->top);
    st->top = node;
    st->length++;
    return;
}

void stack_pop(stack *st)
{
    if (stack_is_empty(st))
    {
        printf("stack pop error: stack is empty!\n");
        exit(1);
    }
    stack_node *tmp = st->top;
    st->top = st->top->last;
    destory_stack_node(&tmp);
    st->length--;
    return;
}

data_type *stack_get_peek(stack *st)
{
    if (stack_is_empty(st))
    {
        printf("stack get peek error: stack is empty!\n");
        exit(1);
    }
    return st->top->data;
}

size_t stack_get_length(stack *st)
{
    return st->length;
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

void _tree_map_to_array(tree_map *tmap, rbt_node *root, array_list *arr)
{
    if (root == NULL || root->is_null_leaf)
    {
        return;
    }
    _tree_map_to_array(tmap, root->left, arr);
    array_list_push_back(arr, root->data);
    _tree_map_to_array(tmap, root->right, arr);
}

array_list *tree_map_to_array(tree_map *tmap)
{
    array_list *arr = init_array_list(tmap->pair_size);
    _tree_map_to_array(tmap, tmap->rbt->root, arr);
    return arr;
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


array_list *init_array_list(size_t data_size)
{
    array_list *arr = (array_list *)malloc(sizeof(array_list));
    arr->capacity = MIN_CAPACITY;
    arr->array = (array_list_node *)calloc(arr->capacity, sizeof(array_list_node));
    arr->length = 0;
    arr->data_size = data_size;
    return arr;
}

int array_list_is_empty(array_list *arr)
{
    return arr->length == 0;
}

size_t array_list_get_length(array_list *arr)
{
    return arr->length;
}

void array_list_push_back(array_list *arr, data_type *data)
{
    size_t data_size = arr->data_size;
    if (arr->capacity <= arr->length)
    {
        expand_capacity((void **)&arr->array, &arr->capacity, sizeof(array_list_node));
    }
    array_list_node *node = &arr->array[arr->length];
    node->data = (data_type *)malloc(data_size);
    shift_data(data, node->data, data_size);
    arr->length++;
    return;
}

void array_list_pop_back(array_list *arr)
{
    if (array_list_is_empty(arr))
    {
        printf("array_list pop_back error: array_list is empty!\n");
        exit(1);
    }
    array_list_node *node = &arr->array[arr->length - 1];
    node->data = NULL;
    arr->length--;
    return;
}

data_type *array_list_get_data(array_list *arr, size_t index)
{
    if (index >= arr->length)
    {
        printf("array_list get data error: index >= length!\n");
        exit(1);
    }
    array_list_node *node = &arr->array[index];
    return node->data;
}

void array_list_set_data(array_list *arr, data_type *data, size_t index)
{
    if (index >= arr->length)
    {
        printf("array_list set data error: index >= length!\n");
        exit(1);
    }
    shift_data(data, arr->array[index].data, arr->data_size);
    return;
}

void array_list_insert(array_list *arr, data_type *data, size_t index)
{
    if (index > arr->length)
    {
        printf("array_list insert error: index > length!\n");
        exit(1);
    }

    size_t data_size = arr->data_size;
    if (arr->capacity <= arr->length)
    {
        expand_capacity((void **)&arr->array, &arr->capacity, sizeof(array_list_node));
    }
    if (index == arr->length)
    {
        array_list_push_back(arr, data);
        return;
    }
    size_t i = arr->length - 1;
    array_list_node *p = &arr->array[i];
    array_list_node *post = &arr->array[i + 1];
    while (i >= index)
    {
        post->data = p->data;
        i--;
        p = &arr->array[i];
        post = &arr->array[i + 1];
    }
    array_list_node *node = &arr->array[index];
    //new data
    node->data = (data_type *)malloc(data_size);
    shift_data(data, node->data, data_size);
    arr->length++;
    return;
}

void array_list_delete(array_list *arr, size_t index)
{
    if (index >= arr->length)
    {
        printf("array_list delete error: index >= length!\n");
        exit(1);
    }
    size_t i = index + 1;
    array_list_node *pre = &arr->array[i - 1];
    array_list_node *post = &arr->array[i];
    free(pre->data);
    while (i <= arr->length - 1)
    {
        pre->data = post->data;
        i++;
        pre = &arr->array[i - 1];
        post = &arr->array[i];
    }
    pre->data = NULL;
    arr->length--;
    return;
}

void destory_array_list(array_list **arr_ptr)
{
    array_list *arr = *arr_ptr;
    for (size_t i = 0; i < arr->length; i++)
    {
        array_list_node *node = &arr->array[i];
        free(node->data);
    }
    free(arr->array);
    free(arr);
    *arr_ptr = NULL;
    return;
}


void shift_data(data_type *src_data, data_type *dst_data, size_t data_size)
{
    size_t tail_size = data_size;
    size_t *dst_ptr = dst_data;
    size_t *src_ptr = src_data;
    while (tail_size / 8 != 0)
    {
        *dst_ptr = *src_ptr;
        dst_ptr++;
        src_ptr++;
        tail_size -= 8;
    }
    char *_dst_ptr = (char *)dst_ptr;
    char *_src_ptr = (char *)src_ptr;
    while (tail_size != 0)
    {
        *_dst_ptr = *_src_ptr;
        _dst_ptr++;
        _src_ptr++;
        tail_size--;
    }
    return;
}

void expand_capacity(void **arr_ptr, size_t *src_capacity, size_t elem_size)
{
    if (*src_capacity == MAX_CAPACITY)
    {
        printf("add capacity error: capacity over INT_MAX!\n");
        exit(1);
    }
    void *arr = *arr_ptr;
    size_t length = *src_capacity;
    *src_capacity = ((*src_capacity) << 1) | 0x1;
    void *tmp = (void *)calloc(*src_capacity, elem_size);
    char *p = tmp;
    char *q = arr;
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < elem_size; j++)
        {
            *p = *q;
            p++;
            q++;
        }
    }
    free(arr);
    *arr_ptr = tmp;
    tmp = NULL;
    return;
}

char *read_string(size_t len)
{
    char *str = (char *)calloc(len + 1, sizeof(char));
    char ch = '\0';
    size_t i = 0;
    while ((ch = getchar()) != '\n' && i < len)
    {
        str[i] = ch;
        ++i;
    }
    str[len] = '\0';
    return str;
}


/**
 * linked_list_node
*/
linked_list_node *init_linked_list_node(data_type *data,
                                        size_t data_size,
                                        linked_list_node *next,
                                        linked_list_node *last)
{
    linked_list_node *node = (linked_list_node *)malloc(sizeof(linked_list_node));
    //node->data = data
    node->data = (data_type *)malloc(data_size);
    shift_data(data, node->data, data_size);
    //
    node->next = next;
    node->last = last;
    return node;
}

void destory_linked_list_node(linked_list_node **node_ptr)
{
    linked_list_node *node = *node_ptr;
    free(node->data);
    free(node);
    *node_ptr = NULL;
    return;
}

/**
 * linked_list
*/
linked_list *init_linked_list(size_t data_size)
{
    linked_list *ls = (linked_list *)malloc(sizeof(linked_list));
    ls->head = init_linked_list_node(NULL, 0, NULL, NULL);
    ls->tail = init_linked_list_node(NULL, 0, ls->head, ls->head);
    ls->head->next = ls->tail;
    ls->head->last = ls->tail;
    ls->length = 0;
    ls->data_size = data_size;
    return ls;
}

int linked_list_is_empty(linked_list *ls)
{
    return ls->length == 0;
}

void linked_list_insert(linked_list *ls, data_type *data, size_t index)
{
    if (index > ls->length)
    {
        printf("linked_list insert error: index > length!\n");
        exit(1);
    }
    size_t data_size = ls->data_size;
    linked_list_node *p = ls->head; //-1
    if (index != 0)
    {
        p = ls->head->next;
        size_t i = 0;
        while (i < index - 1)
        {
            p = p->next;
            i++;
        }
    }
    //p pointers to the pre node of inserting node
    linked_list_node *post = p->next;
    //new node
    linked_list_node *node = init_linked_list_node(data, data_size, post, p);
    p->next = node;
    post->last = node;
    //length++
    ls->length++;
    return;
}

void linked_list_push_back(linked_list *ls, data_type *data)
{
    linked_list_insert(ls, data, ls->length);
}

void linked_list_delete(linked_list *ls, size_t index)
{
    if (index >= ls->length)
    {
        printf("linked_list delete error: index >= length!\n");
        exit(1);
    }
    linked_list_node *p = ls->head; //-1
    if (index != 0)
    {
        p = ls->head->next;
        size_t i = 0;
        while (i < index - 1)
        {
            p = p->next;
            i++;
        }
    }
    linked_list_node *node = p->next;
    linked_list_node *post = node->next;
    p->next = post;
    post->last = p;
    destory_linked_list_node(&node);
    ls->length--;
    return;
}

void linked_list_pop_back(linked_list *ls)
{
    linked_list_delete(ls, ls->length - 1);
}

data_type *linked_list_get_data(linked_list *ls, size_t index)
{
    if (index >= ls->length)
    {
        printf("linked_list get data error: index >= length!\n");
        exit(1);
    }
    linked_list_node *p = ls->head->next;
    size_t i = 0;
    while (i < index)
    {
        p = p->next;
        i++;
    }
    return p->data;
}

void linked_list_set_data(linked_list *ls, data_type *data, size_t index)
{
    if (index > ls->length)
    {
        printf("linked_list set data error: index > length!\n");
        exit(1);
    }
    linked_list_node *p = ls->head->next;
    size_t i = 0;
    while (i < index)
    {
        p = p->next;
        ++i;
    }
    shift_data(data, p->data, ls->data_size);
    return;
}

size_t linked_list_get_length(linked_list *ls)
{
    return ls->length;
}

void destory_linked_list(linked_list **ls_ptr)
{
    linked_list *ls = *ls_ptr;
    while (!linked_list_is_empty(ls))
    {
        linked_list_delete(ls, 0);
    }
    destory_linked_list_node(&ls->head);
    destory_linked_list_node(&ls->tail);
    free(*ls_ptr);
    *ls_ptr = NULL;
    return;
}

