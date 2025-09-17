#pragma once

#include <stdint.h>
#include <stdlib.h>

typedef double float64_t;

struct float_array
{
    float64_t *data;
    size_t size;
};

struct int_array
{
    int32_t *data;
    size_t size;
};

inline struct int_array *create_int_array(const size_t size)
{
    struct int_array *arr = malloc(sizeof(struct int_array));
    if (arr == NULL)
    {
        return NULL;
    }

    arr->size = size;
    arr->data = malloc(sizeof(int64_t) * size);
    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

inline struct float_array *create_float_array(const size_t size)
{
    struct float_array *arr = malloc(sizeof(struct float_array));
    if (arr == NULL)
    {
        return NULL;
    }

    arr->size = size;
    malloc(size * sizeof(float64_t));
    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

inline int initialization_int_array(const struct int_array *arr, const int64_t value)
{
    if (arr == NULL || arr->data == NULL || arr->size <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] = value;
    }
    return 0;
}

inline int initialization_float_array(const struct int_array *arr, const float64_t value)
{
    if (arr == NULL || arr->data == NULL || arr->size <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] = value;
    }
    return 0;
}

void destroy_array_i_1d(int64_t **ptr, size_t size);
void destroy_array_f_1d(float64_t **ptr, size_t size);

int create_array_i_1d(int64_t **ptr, size_t size);
int create_array_f_1d_init(int64_t **ptr, size_t size, int64_t value);

int create_array_f_1d(float64_t **ptr, size_t size);
int create_array_f_1d_init(float64_t **ptr, size_t size, float64_t value);

void display_array_i_1d(const int64_t *ptr, size_t size);
void display_array_f_1d(const float64_t *ptr, size_t size);

int64_t sum_array_i_1d(const int64_t *ptr, size_t size);
float64_t sum_array_f_1d(const float64_t *ptr, size_t size);

void add_to_array_i_1d_i(int64_t *ptr, size_t size, int64_t value);
void add_to_array_i_1d_f(int64_t *ptr, size_t size, float64_t value);
void add_to_array_f_1d_i(float64_t *ptr, size_t size, int64_t value);
void add_to_array_f_1d_f(float64_t *ptr, size_t size, float64_t value);

void mul_to_array_i_1d_i(int64_t *ptr, size_t size, int64_t value);
void mul_to_array_i_1d_f(int64_t *ptr, size_t size, float64_t value);
void mul_to_array_f_1d_i(float64_t *ptr, size_t size, int64_t value);
void mul_to_array_f_1d_f(float64_t *ptr, size_t size, float64_t value);

void sub_to_array_i_1d_i(int64_t *ptr, size_t size, int64_t value);
void sub_to_array_i_1d_f(int64_t *ptr, size_t size, float64_t value);
void sub_to_array_f_1d_i(float64_t *ptr, size_t size, int64_t value);
void sub_to_array_f_1d_f(float64_t *ptr, size_t size, float64_t value);

void div_to_array_i_1d_i(int64_t *ptr, size_t size, int64_t value);
void div_to_array_i_1d_f(int64_t *ptr, size_t size, float64_t value);
void div_to_array_f_1d_i(float64_t *ptr, size_t size, int64_t value);
void div_to_array_f_1d_f(float64_t *ptr, size_t size, float64_t value);
