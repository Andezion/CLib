#include "array_1d.h"

void destroy_array_1d(int64_t **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }

    free(*ptr);
    ptr = NULL;
}

int create_array_1d(int64_t **ptr, const size_t size)
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

int create_array_1d_init(int64_t **ptr, const size_t size, const int64_t value)
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

    for (size_t i = 0; i < size; i++)
    {
        *(array + i) = value;
    }
    *ptr = array;

    return 0;
}

void display_array_1d(const int64_t *ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }
    for (size_t i = 0; i < size; i++)
    {
        printf("%" PRId64 " ", *(ptr + i));
    }
}

