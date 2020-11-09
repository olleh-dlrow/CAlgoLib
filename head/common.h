#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>

typedef void data_type;

#define MAX_CAPACITY (~(size_t)0)

#define MIN_CAPACITY ((size_t)0xf)

void shift_data(data_type *src_data, data_type *dst_data, size_t data_size);

void expand_capacity(void **arr_ptr, size_t *src_capacity, size_t elem_size);

#endif