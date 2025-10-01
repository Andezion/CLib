#include "array_1d.h"
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

int64_t sum_int_array(const int64_t *ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    int64_t sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += *(ptr + i);
    }
    return sum;
}
float64_t sum_float_array(const float64_t *ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    float64_t sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += *(ptr + i);
    }
    return sum;
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