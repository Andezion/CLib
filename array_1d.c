#include "array_1d.h"

void destroy_array_i_1d(int64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }

    free(*ptr);
    *ptr = NULL;
}
void destroy_array_f_1d(float64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }

    free(*ptr);
    *ptr = NULL;
}

int create_array_i_1d(int64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    int64_t *array = malloc(sizeof(int64_t) * size);
    if (array == NULL)
    {
        return 2;
    }
    *ptr = array;

    return 0;
}
int create_array_i_1d_init(int64_t **ptr, const size_t size, const int64_t value)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    const int error = create_array_i_1d(ptr, size);
    if (error != 0)
    {
        return error;
    }

    int64_t *array = *ptr;
    for (size_t i = 0; i < size; i++)
    {
        *(array + i) = value;
    }

    return 0;
}
int create_array_f_1d(float64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    float64_t *array = malloc(sizeof(float64_t) * size);
    if (array == NULL)
    {
        return 2;
    }
    *ptr = array;

    return 0;
}
int create_array_f_1d_init(float64_t **ptr, const size_t size, const float64_t value)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    const int error = create_array_f_1d(ptr, size);
    if (error != 0)
    {
        return error;
    }

    float64_t *array = *ptr;
    for (size_t i = 0; i < size; i++)
    {
        *(array + i) = value;
    }

    return 0;
}

void display_array_i_1d(const int64_t *ptr, const size_t size)
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
void display_array_f_1d(const float64_t *ptr, const size_t size)
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

int64_t sum_array_i_1d(const int64_t *ptr, const size_t size)
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

float64_t sum_array_f_1d(const float64_t *ptr, const size_t size)
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

void add_to_array_i_1d_i(int64_t *ptr, const size_t size, const int64_t value)
{
    if (ptr == NULL || size == 0 || value == 0)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        *(ptr + i) = *(ptr + i) + value;
    }
}

void add_to_array_i_1d_f(int64_t *ptr, const size_t size, const float64_t value)
{
    if (ptr == NULL || size == 0 || value == 0)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        *(ptr + i) = *(ptr + i) + (int64_t) value;
    }
}

void add_to_array_f_1d_i(float64_t *ptr, const size_t size, const int64_t value)
{
    if (ptr == NULL || size == 0 || value == 0)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        *(ptr + i) = *(ptr + i) + (float64_t) value;
    }
}

void add_to_array_f_1d_f(float64_t *ptr, const size_t size, const float64_t value)
{
    if (ptr == NULL || size == 0 || value == 0)
    {
        return;
    }

    for (size_t i = 0; i < size; i++)
    {
        *(ptr + i) = *(ptr + i) + value;
    }
}
