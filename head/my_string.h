#ifndef MY_STRING_H
#define MY_STRING_H

#include"array_list.h"

typedef struct my_string{
    size_t length;
    array_list *str;
}my_string;

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

#endif