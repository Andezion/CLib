#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "matrix.h"

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

void destroy_int_array(int64_t **ptr, size_t size);
void destroy_float_array(float64_t **ptr, size_t size);

void display_int_array(const int64_t *ptr, size_t size);
void display_float_array(const float64_t *ptr, size_t size);



