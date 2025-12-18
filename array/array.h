#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "matrix/matrix.h"

typedef double float64_t;

struct float_array
{
    float64_t *data;
    size_t size;
};

struct int_array
{
    int64_t *data;
    size_t size;
};

struct int_array *create_int_array(size_t size);
struct float_array *create_float_array(size_t size);

int initialization_int_array(const struct int_array *arr, int64_t value);
int initialization_float_array(const struct float_array *arr, float64_t value);

int initialization_random_int_array(const struct int_array *arr, int64_t min, int64_t max);
int initialization_random_float_array(const struct float_array *arr, float64_t min, float64_t max);

void free_int_array(struct int_array **array);
void free_float_array(struct float_array **array);

void display_int_array(const struct int_array *array);
void display_float_array(const struct float_array *array);

struct int_array *copy_int_array(const struct int_array *arr);
struct float_array *copy_float_array(const struct float_array *arr);



