#include "array_math.h"

struct int_array *add_int_arrays(const size_t n, const size_t size, ...)
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
struct int_array *sub_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    // struct int_array *array = create_int_array(size);
    // if (array == NULL)
    // {
    //     va_end(args);
    //     return NULL;
    // }

    const struct int_array *array_input = va_arg(args, struct int_array *);
    if (array_input == NULL || array_input->data == NULL || array_input->size != size)
    {
        va_end(args);
        return NULL;
    }

    struct int_array *array = copy_int_array(array_input);
    if (!array)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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

struct float_array *add_float_arrays(const size_t n, const size_t size, ...)
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
struct float_array *sub_float_arrays(const size_t n, const size_t size, ...)
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

struct int_array * add_value_to_int_arrays(const size_t n, const size_t size, const int64_t value, ...)
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

    for (size_t i = 0; i < size; i++)
    {
        array->data[i] += value;
    }

    va_end(args);
    return array;
}

struct int_array * sub_value_from_int_arrays(const size_t n, const size_t size, const int64_t value, ...)
{
    va_list args;
    va_start(args, size);

    struct int_array *array_input = va_arg(args, struct int_array *);
    if (!array_input)
    {
        va_end(args);
        return NULL;
    }

    struct int_array *array = copy_int_array(array_input);
    if (!array)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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

    for (size_t i = 0; i < size; i++)
    {
        array->data[i] -= value;
    }

    va_end(args);
    return array;
}

struct float_array * add_value_to_float_arrays(const size_t n, const size_t size, const float64_t value, ...)
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

    for (size_t i = 0; i < size; i++)
    {
        array->data[i] += value;
    }

    va_end(args);
    return array;
}

int scale_float_array_inplace(struct float_array *arr, const float64_t alpha)
{
    if (!arr || !arr->data || arr->size == 0)
    {
        return -1;
    }
    for (size_t i = 0; i < arr->size; i++)
    {
        arr->data[i] *= alpha;
    }
    return 0;
}

int add_float_array_inplace(struct float_array *dst, const struct float_array *src)
{
    if (!dst || !src || !dst->data || !src->data)
    {
        return -1;
    }
    if (dst->size != src->size)
    {
        return -1;
    }
    for (size_t i = 0; i < dst->size; i++)
    {
        dst->data[i] += src->data[i];
    }
    return 0;
}

int hadamard_float_array_inplace(struct float_array *dst, const struct float_array *src)
{
    if (!dst || !src || !dst->data || !src->data)
    {
        return -1;
    }
    if (dst->size != src->size)
    {
        return -1;
    }
    for (size_t i = 0; i < dst->size; i++)
    {
        dst->data[i] *= src->data[i];
    }
    return 0;
}

int axpy_float_array(const float64_t alpha, const struct float_array *x, struct float_array *y)
{
    if (!x || !y || !x->data || !y->data)
    {
        return -1;
    }
    if (x->size != y->size)
    {
        return -1;
    }
    for (size_t i = 0; i < x->size; i++)
    {
        y->data[i] += alpha * x->data[i];
    }
    return 0;
}

int scale_int_array_inplace(struct int_array *arr, int64_t alpha)
{

}

int add_int_array_inplace(struct int_array *dst, const struct int_array *src)
{

}

int hadamard_int_array_inplace(struct int_array *dst, const struct int_array *src)
{

}

int axpy_int_array(float64_t alpha, const struct int_array *x, struct int_array *y)
{

}

struct float_array * sub_value_from_float_arrays(const size_t n, const size_t size, const float64_t value, ...)
{
    va_list args;
    va_start(args, size);

    struct float_array *array_input = va_arg(args, struct float_array *);
    if (!array_input)
    {
        va_end(args);
        return NULL;
    }

    struct float_array *array = copy_float_array(array_input);
    if (!array)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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

    for (size_t i = 0; i < size; i++)
    {
        array->data[i] -= value;
    }

    va_end(args);
    return array;
}

int64_t sum_int_array(const struct int_array *arr)
{
    if (arr->data == NULL || arr->size == 0)
    {
        return 1;
    }

    int64_t sum = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        sum += *(arr->data + i);
    }
    return sum;
}
float64_t sum_float_array(const struct float_array *arr)
{
    if (arr->data == NULL || arr->size == 0)
    {
        return 1;
    }

    float64_t sum = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        sum += *(arr->data + i);
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

struct float_array * mul_float_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct float_array *array = create_float_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }

    initialization_float_array(array, 1.0);

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

struct int_array * mul_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct int_array *array = create_int_array(size);
    if (array == NULL)
    {
        va_end(args);
        return NULL;
    }

    initialization_int_array(array, 1);

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

struct float_array * div_float_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct float_array *array_input = va_arg(args, struct float_array *);
    if (!array_input)
    {
        va_end(args);
        return NULL;
    }

    struct float_array *array = copy_float_array(array_input);
    if (!array)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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
            if (arr->data[i] != 0.0)
            {
                array->data[i] = array->data[i] / arr->data[i];
            }
            else
            {
                free(array);

                va_end(args);
                return NULL;
            }
        }
    }

    va_end(args);
    return array;
}

struct int_array * div_int_arrays(const size_t n, const size_t size, ...)
{
    va_list args;
    va_start(args, size);

    struct int_array *array_input = va_arg(args, struct int_array *);
    if (!array_input)
    {
        va_end(args);
        return NULL;
    }

    struct int_array *array = copy_int_array(array_input);
    if (!array)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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
            if (arr->data[i] != 0)
            {
                array->data[i] = array->data[i] / arr->data[i];
            }
            else
            {
                free(array);

                va_end(args);
                return NULL;
            }
        }
    }

    va_end(args);
    return array;
}
