#pragma once

#include <stdint.h>

typedef double float64_t;

void * add_arrays_i_i(int64_t *array1, const int64_t *array2);
void * add_arrays_i_f(int64_t *array1, float64_t *array2);
void * add_arrays_f_i(float64_t *array1, int64_t *array2);
void * add_arrays_f_f(float64_t *array1, float64_t *array2);