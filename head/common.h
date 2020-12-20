#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

// #define DBG

#ifdef DBG
#define log(fmt, args...) printf(fmt, ##args)
#else
#define log(fmt, args...)
#endif

#define MAX_CAPACITY (~(size_t)0)

#define MIN_CAPACITY ((size_t)0xf)

typedef void data_type;

typedef void key_type;

typedef void value_type;

void shift_data(data_type *src_data, data_type *dst_data, size_t data_size);

void expand_capacity(void **arr_ptr, size_t *src_capacity, size_t elem_size);

char *read_string(size_t len);

#endif
