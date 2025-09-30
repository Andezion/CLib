#include "array_1d.h"
#include <inttypes.h>
#include <stdio.h>

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

