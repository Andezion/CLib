#pragma once
#include "array.h"

inline struct int_array *add_int_arrays(size_t n, size_t size, ...);
inline struct int_array *sub_int_arrays(size_t n, size_t size, ...);

inline struct float_array *add_float_arrays(size_t n, size_t size, ...);
inline struct float_array *sub_float_arrays(size_t n, size_t size, ...);

int64_t sum_int_array(const int64_t *ptr, size_t size);
float64_t sum_float_array(const float64_t *ptr, size_t size);