#include "math_arrays.h"

void * add_arrays_i_i(int64_t *array1, const int64_t *array2)
{
    for (size_t i = 0; i < sizeof(array1); i++)
    {
        array1[i] = array1[i] + array2[i];
    }
    return array1;
}

void * add_arrays_i_f(int64_t *array1, const float64_t *array2)
{
    for (size_t i = 0; i < sizeof(array1); i++)
    {
        array1[i] = array1[i] + (int64_t) array2[i];
    }
    return array1;
}

void * add_arrays_f_i(float64_t *array1, const int64_t *array2)
{
    for (size_t i = 0; i < sizeof(array1); i++)
    {
        array1[i] = array1[i] + (float64_t) array2[i];
    }
    return array1;
}

void * add_arrays_f_f(float64_t *array1, const float64_t *array2)
{
    for (size_t i = 0; i < sizeof(array1); i++)
    {
        array1[i] = array1[i] + array2[i];
    }
    return array1;
}

