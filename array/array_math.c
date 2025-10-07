#include "array_math.h"

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

struct int_array * hadamard_product_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct int_array *array = create_int_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }
    const int error = initialization_int_array(array, 1);
    if (error != 0)
    {
        free(array);

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
            array->data[i] = array->data[i] * arr->data[i];
        }
    }

    va_end(args);
    return array;
}

int64_t dot_product_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    const struct int_array *first = va_arg(args, struct int_array *);
    if (first == NULL || first->data == NULL || first->size != size)
    {
        va_end(args);
        return 0;
    }

    int64_t sum = 0;

    for (size_t i = 0; i < size; i++)
    {
        int64_t prod = first->data[i];

        for (size_t k = 1; k < n; k++)
        {
            const struct int_array *arr = va_arg(args, struct int_array *);
            if (arr == NULL || arr->data == NULL || arr->size != size)
            {
                va_end(args);
                return 0;
            }
            prod *= arr->data[i];
        }

        sum += prod;
    }

    va_end(args);
    return sum;
}

struct float_array * hadamard_product_float_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct float_array *array = create_float_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }
    const int error = initialization_float_array(array, 1);
    if (error != 0)
    {
        free(array);

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
            array->data[i] = array->data[i] * arr->data[i];
        }
    }

    va_end(args);
    return array;
}

float64_t dot_product_float_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    const struct float_array *first = va_arg(args, struct float_array *);
    if (first == NULL || first->data == NULL || first->size != size)
    {
        va_end(args);
        return 0;
    }

    float64_t sum = 0;

    for (size_t i = 0; i < size; i++)
    {
        float64_t prod = first->data[i];

        for (size_t k = 1; k < n; k++)
        {
            const struct float_array *arr = va_arg(args, struct float_array *);
            if (arr == NULL || arr->data == NULL || arr->size != size)
            {
                va_end(args);
                return 0;
            }
            prod *= arr->data[i];
        }

        sum += prod;
    }

    va_end(args);
    return sum;
}
