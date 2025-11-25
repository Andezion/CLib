#pragma once
#include "array.h"

struct int_array *add_int_arrays(size_t n, size_t size, ...);
struct int_array *sub_int_arrays(size_t n, size_t size, ...);

struct int_array *add_value_to_int_arrays(size_t n, size_t size, int64_t value, ...);
struct int_array *sub_value_from_int_arrays(size_t n, size_t size, int64_t value, ...);

struct float_array *add_float_arrays(size_t n, size_t size, ...);
struct float_array *sub_float_arrays(size_t n, size_t size, ...);

int64_t sum_int_array(const struct int_array *arr);
float64_t sum_float_array(const struct float_array *arr);

int64_t dot_product_int_arrays(size_t n, size_t size, ...);
struct int_array *hadamard_product_int_arrays(size_t n, size_t size, ...);

float64_t dot_product_float_arrays(size_t n, size_t size, ...);
struct float_array *hadamard_product_float_arrays(size_t n, size_t size, ...);

struct int_array *div_int_arrays(size_t n, size_t size, ...);
struct float_array *div_float_arrays(size_t n, size_t size, ...);

struct int_array *mul_int_arrays(size_t n, size_t size, ...);
struct float_array *mul_float_arrays(size_t n, size_t size, ...);