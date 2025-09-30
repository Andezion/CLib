#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "array_2d.h"

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
inline struct int_array *add_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct int_array *array = create_int_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct int_array *arr = va_arg(args, struct int_array *);
        if (arr == NULL || arr->data == NULL || arr->size != size)
        {
            free(array);

            va_end(args);
            return NULL;
        }

        for (size_t i = 0; i < size; i++)
        {
            array->data[i] = array->data[i] + arr->data[i];
        }
    }

    va_end(args);
    return array;
}
inline struct int_array *sub_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct int_array *array = create_int_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct int_array *arr = va_arg(args, struct int_array *);
        if (arr == NULL || arr->data == NULL || arr->size != size)
        {
            free(array);

            va_end(args);
            return NULL;
        }

        for (size_t i = 0; i < size; i++)
        {
            array->data[i] = array->data[i] - arr->data[i];
        }
    }

    va_end(args);
    return array;
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
inline struct float_array *add_float_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct float_array *array = create_float_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct float_array *arr = va_arg(args, struct float_array *);
        if (arr == NULL || arr->data == NULL || arr->size != size)
        {
            free(array);

            va_end(args);
            return NULL;
        }

        for (size_t i = 0; i < size; i++)
        {
            array->data[i] = array->data[i] + arr->data[i];
        }
    }

    va_end(args);
    return array;
}
inline struct float_array *sub_float_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct float_array *array = create_float_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct float_array *arr = va_arg(args, struct float_array *);
        if (arr == NULL || arr->data == NULL || arr->size != size)
        {
            free(array);

            va_end(args);
            return NULL;
        }

        for (size_t i = 0; i < size; i++)
        {
            array->data[i] = array->data[i] - arr->data[i];
        }
    }

    va_end(args);
    return array;
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

void display_array_i_1d(const int64_t *ptr, size_t size);
void display_array_f_1d(const float64_t *ptr, size_t size);

int64_t sum_array_i_1d(const int64_t *ptr, size_t size);
float64_t sum_array_f_1d(const float64_t *ptr, size_t size);


