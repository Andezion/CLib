#include "array.h"
#include <inttypes.h>
#include <stdio.h>

void destroy_int_array(int64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }

    free(*ptr);
    *ptr = NULL;
}
void destroy_float_array(float64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }

    free(*ptr);
    *ptr = NULL;
}

void display_int_array(const int64_t *ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }
    for (size_t i = 0; i < size; i++)
    {
        printf("%" PRId64 " ", *(ptr + i));
    }
    printf("\n");
}
void display_float_array(const float64_t *ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }
    for (size_t i = 0; i < size; i++)
    {
        printf("%f ", *(ptr + i));
    }
    printf("\n");
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

inline int initialization_float_array(const struct float_array *arr, const float64_t value)
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