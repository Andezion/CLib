#pragma once

#include <stdio.h>
#include <stdlib.h>

void destroy_array_2d(signed long long int ***ptr, size_t height);

int create_array_2d(signed long long int ***ptr, size_t width, size_t height);
int create_array_2d_init(signed long long int ***ptr, size_t width, size_t height, signed long long int value);
int create_array_2d(signed long long int ***ptr, size_t size);
int create_array_2d_init(signed long long int ***ptr, size_t size, signed long long int value);

void display_array_2d(signed long long int **ptr, size_t width, size_t height);