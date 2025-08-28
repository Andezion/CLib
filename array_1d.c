#include "array_1d.h"

void destroy_array_1d(signed long long int **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return;
    }

    free(*ptr);
    ptr = NULL;
}

int create_array_1d(signed long long int **ptr, const size_t size)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    signed long long int *array = malloc(sizeof(signed long long int) * size);
    if (array == NULL)
    {
        return 2;
    }
    *ptr = array;

    return 0;
}

int create_array_1d_init(signed long long int **ptr, const size_t size, const signed long long int value)
{
    if (ptr == NULL || size == 0)
    {
        return 1;
    }

    signed long long int *array = malloc(sizeof(signed long long int) * size);
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

