#include"my_string.h"

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

void my_string_write(my_string *s, FILE *stream, char *fmt){
    char *str = my_string_to_char_array(s);
    fprintf(stream, fmt, str);
    free(str);
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