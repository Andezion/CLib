#pragma once
#include "array.h"

struct int_array *add_int_arrays(size_t n, size_t size, ...);
struct int_array *sub_int_arrays(size_t n, size_t size, ...);

struct float_array *add_float_arrays(size_t n, size_t size, ...);
struct float_array *sub_float_arrays(size_t n, size_t size, ...);

int64_t sum_int_array(const int64_t *ptr, size_t size);
float64_t sum_float_array(const float64_t *ptr, size_t size);

int64_t dot_product_int_arrays(size_t n, size_t size, ...);
struct int_array *hadamard_product_int_arrays(size_t n, size_t size, ...);

float64_t dot_product_float_arrays(size_t n, size_t size, ...);
struct float_array *hadamard_product_float_arrays(size_t n, size_t size, ...);