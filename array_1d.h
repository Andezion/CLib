#pragma once

#include <stdlib.h>

void destroy_array_1d(signed long long int **ptr, size_t size);

int create_array_1d(signed long long int **ptr, size_t size);
int create_array_1d_init(signed long long int **ptr, size_t size, signed long long int value);

void display_array_1d(signed long long int *ptr, size_t size);
