# C语言模板库——myutil

## 特点

### 伪面向对象

由于C语言编译器的限制，无法像C++或者Java一样使用class来创建类和对象的实例，但是通过巧妙地设计结构体、函数名及参数和文件的内容也能够实现面向对象的部分功能：

1. 易于维护和再开发。

    由于每一个结构体对应的功能都被封装在函数中，因此对其修改或者引用都能够在局部进行调整。同时，如果需要继承某个类的部分特性，可以把该类直接作为新类的成员变量，再将该类的成员函数进行封装，得到新的类。

    例：在my_string类中，将array_list类作为底层结构，使得该类即具有array_list的所有特性，同时大大降低了开发步骤

2. 对数据成员和功能进行抽象。

    对于每一个具体类的成员函数，将该函数的第一个参数设定为指向该对象（结构体）的指针，使得每一个明确定义的功能和操作都可被使用者当做单个的实体看待，尽管这个操作实际上可能由一系列更低级的操作来完成。这个过程本质是通过函数封装实现的。遗憾的是，无法对数据成员进行抽象，原因是C语言中没有类似private的限定词，无法限制成员变量的任意修改。

其他的功能，诸如继承和多态性，也由于编译器的限制和开发时间限制，很难直接在C语言代码层面上来实现，可能需要借助宏定义来动态生成一些代码。

### 泛型

泛型，即在使用某一个容器或者数据结构时，不必去考虑具体的数据类型是什么样的，通俗点来说就是一个篮子既能够装苹果也能够装梨子，而不必为了装梨子另外造出一个篮子出来，这样就大大提高了代码的重用度和开发效率，也就是没必要频繁地造轮子。

<hr>

在C++中，泛型是通过高级宏来实现的，当我们为某个类指定一种数据类型后，C++的编译器会为该数据类型生成新的代码。

在Java中，泛型通过类型擦除来实现，Java中一切皆是对象，所有的类都起源于一个父类Object，因此在对数据进行处理、存储时，所有的类型都退化（被擦除）为Object，这样相同的对象就能够进行直接处理。为了防止数据类型不匹配，在擦除之前会对类型进行检查。

C语言实现泛型的思想和Java很像，只不过C语言将一切的数据类型都看成二进制的数据，这样，在处理数据时，我们只需要知道该数据的大小即可对该数据进行存储、转移。具体来说，在进行赋值时，需要知道该数据的地址(void *)和该数据的字节大小，然后将主存中的该段数据以字节为单位进行转移。在``stdlib.h``中，函数``qsort,qsearch``就使用了这种思想。

## 基本结构

数据成员结构体：包含该类型所具有的所有数据类型

构造函数：为对象实例分配堆空间

功能函数：该对象具有的功能和操作

销毁（析构）函数：销毁该对象在堆中的内存

## 模板功能简介

### array_list

数据成员:

```c
typedef struct array_list_node
{
    data_type *data;
} array_list_node;

typedef struct array_list
{
    array_list_node *array;
    size_t capacity;
    size_t length;
    size_t data_size;
} array_list;
```

成员函数：

```c
array_list *init_array_list(size_t data_size);

int array_list_is_empty(array_list *arr);

size_t array_list_get_length(array_list *arr);

void array_list_push_back(array_list *arr, data_type *data);

void array_list_pop_back(array_list *arr);

data_type *array_list_get_data(array_list *arr, size_t index);

void array_list_set_data(array_list *arr, data_type *data, size_t index);

void array_list_insert(array_list *arr, data_type *data, size_t index);

void array_list_delete(array_list *arr, size_t index);

void destory_array_list(array_list **arr_ptr);
```

功能：

1. 开辟一片储存数据的连续的空间，同时能够根据当前数据长度自动进行容量扩充，最大容量为$$2^{64}$$个数据。
2. 支持基本的数组操作：任意位置插入、删除、替换、查找，获取数组的长度

### linked_list

数据成员:

```c
typedef struct linked_list_node
{
    data_type *data;
    struct linked_list_node *next;
    struct linked_list_node *last;
} linked_list_node;

typedef struct linked_list
{
    linked_list_node *head;
    linked_list_node *tail;
    size_t length;
    size_t data_size;
} linked_list;
```

成员函数:

```c
linked_list *init_linked_list(size_t data_size);

int linked_list_is_empty(linked_list *ls);

linked_list_node *linked_list_next(linked_list *ls, linked_list_node *node);

linked_list_node *linked_list_last(linked_list *ls, linked_list_node *node);

linked_list_node *linked_list_delete_node(linked_list *ls, linked_list_node *node);

void linked_list_insert_node(linked_list *ls, linked_list_node *node, data_type *data);

void linked_list_set_node_data(linked_list *ls, linked_list_node *node, data_type *data);

linked_list_node *linked_list_get_head(linked_list *ls);

linked_list_node *linked_list_get_tail(linked_list *ls);

data_type *linked_list_get_node_data(linked_list *ls, linked_list_node *node);

void linked_list_insert(linked_list *ls, data_type *data, size_t index);

void linked_list_push_back(linked_list *ls, data_type *data);

void linked_list_delete(linked_list *ls, size_t index);

void linked_list_pop_back(linked_list *ls);

data_type *linked_list_get_data(linked_list *ls, size_t index);

void linked_list_set_data(linked_list *ls, data_type *data, size_t index);

size_t linked_list_get_length(linked_list *ls);

void destory_linked_list(linked_list **ls_ptr);
```

功能：

1. 使用双向循环链表来存储数据，且能够快速访问链表的首尾结点
2. 支持使用下标的增删改查和使用迭代器的增删改查

### stack

数据成员：

```c
typedef struct stack_node
{
    data_type *data;
    struct stack_node *last;
} stack_node;

typedef struct stack
{
    stack_node *top;
    stack_node *head;
    size_t length;
    size_t data_size;
} stack;
```

成员函数：

```c
stack *init_stack(size_t data_size);

int stack_is_empty(stack *st);

void stack_push(stack *st, data_type *data);

void stack_pop(stack *st);

data_type *stack_get_peek(stack *st);

size_t stack_get_length(stack *st);

void destory_stack(stack **st_ptr);
```

功能：

先进后出的数据结构

### queue

数据成员:

```c
typedef struct queue_node
{
    data_type *data;
    struct queue_node *last;
} queue_node;

//node1(p_head) <- node2 <- node3 <- tail
typedef struct queue
{
    queue_node *p_head;
    queue_node *tail;
    size_t length;
    size_t data_size;
} queue;
```

成员函数：

```c
queue *init_queue(size_t data_size);

int queue_is_empty(queue *qu);

void queue_push_front(queue *qu, data_type *data);

void queue_pop_back(queue *qu);

size_t queue_get_length(queue *qu);

data_type *queue_get_back(queue *qu);

void destory_queue(queue **qu_ptr);
```

功能：

先进先出的数据结构

### heap

数据成员：

```c
typedef struct heap_node
{
    data_type *data;
} heap_node;

typedef struct heap
{
    heap_node *array;
    size_t length;
    size_t capacity;
    size_t data_size;
    int (*cmp_func)(void *a, void *b);
} heap;
```

成员函数：

```c
heap *init_heap(size_t data_size, int (*cmp_func)(void *a, void *b));

int heap_is_empty(heap *hp);

void heap_add(heap *hp, data_type *data);

data_type *heap_get_peek(heap *hp);

size_t heap_get_length(heap *hp);

void heap_pop(heap *hp);

void destory_heap(heap **hp_ptr);
```

功能：

在$$O(log(n))$$的时间内插入，删除数据和在$$O(1)$$时间内获得数据的极值。采用线性结构进行存储，需要传入一个比较函数作为参数，该参数的返回值决定这个堆是大根堆还是小根堆。

### my_string

成员变量：

```c
typedef struct my_string{
    size_t length;
    array_list *str;
}my_string;
```

成员函数：

```c
my_string *init_my_string();

void my_string_read(my_string *s, FILE *stream);

void my_string_write(my_string *s, FILE *stream, char *fmt);

size_t my_string_get_length(my_string *s);

char my_string_index_of(my_string *s, size_t index);

int my_string_is_empty(my_string *s);

int my_string_compare(my_string *s1, my_string *s2);

void my_string_replace(my_string *s, char ch, size_t index);

void my_string_insert(my_string *s, char ch, size_t index);

void my_string_push(my_string *s, char ch);

void my_string_delete(my_string *s, size_t index);

char *my_string_to_char_array(my_string *s);

void destory_my_string(my_string **s_ptr);
```

以array_list作为底层结构

功能：

1. 在插入字符时，动态地分配存储空间
2. 支持字符的插入、删除、替换
3. 支持从文件流中读取字符串和写入字符串
4. 可通过函数``char *my_string_to_char_array(my_string *s)``将字符串转换为字符数组

### tree_set

成员变量：

```c
typedef struct tree_set
{
    size_t data_size;
    size_t length;
    int (*cmp_func)(void *a, void *b);
    red_black_tree *rbt;
} tree_set;
```

成员函数：

```c
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
```

以红黑树作为底层实现，可以在$$O(log(n))$$时间内完成查找、插入和删除，在初始化时需要传入比较函数作为参数。

功能：

1. 将数据唯一存入集合中
2. 判断集合中是否存在某个数据
3. 将集合转换为array_list以进行遍历

### tree_map

数据成员：

```c
typedef struct tree_map
{
    red_black_tree *rbt;
    size_t pair_size;
    size_t length;
    //get key and compare key
    key_type *(*get_key)(pair_type *piar);
    int (*cmp_func)(void *a, void *b);
    //get value
    value_type *(*get_value)(pair_type *pair);
} tree_map;
```

成员函数：

```c
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
```

以红黑树作为底层实现，数据类型必须是有两个变量的pair结构体（key-value），还需要传入键的比较函数、获取键的函数和获取值的函数。

功能：

1. 可将任意数据类型作为键进行存储和查找，具有较高的增删改查效率
2. 可将map转换成array_list进行遍历

## 问题

### 安全性

由于C语言的编译器几乎没有什么高级的类型检查功能，因此在把所有数据类型看成二进制字节流的情况下，不能保证传递相同的数据类型，也因此无法对数据的边界进行检查，这些容易出现问题的细节只能通过开发者自己小心注意。

### 封装性

尽管对于对象的每一种功能都使用了一个相应的函数对齐进行封装和抽象，但是使用者依然能够轻松地访问到底层的变量，即这些成员变量不具有约束性，无法通过函数封装来保证数据成员的安全。

### 内存管理

最头疼的问题。

对于基本的数据类型，我们不希望经常为其分配堆空间，因此这些变量最好能够直接通过值传递（深拷贝）。

而对于结构体类型，由于占用的内存空间较大，使用深拷贝消耗的内存空间和时间代价都很大，因此希望使用址传递（浅拷贝）。

但是在进行浅拷贝的过程中，可能存在需要嵌套拷贝的情况，即拷贝过来的地址所指向的数据依然包含地址，这种情况下对内存管理十分复杂，很容易发生内存泄露。

在C++中使用的是智能指针来管理内存，在Java中有垃圾回收机制，而C语言中只能靠自己进行手动的内存管理。

## 后续优化与改进

1. 添加hash_set和hash_map
2. 使用宏指令来对部分类型进行检查
3. 使用函数指针实现继承和多态
