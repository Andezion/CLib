#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

typedef double float64_t;

void destroy_array_i_1d(int64_t **ptr, size_t size);
void destroy_array_f_1d(float64_t **ptr, size_t size);

int create_array_i_1d(int64_t **ptr, size_t size);
int create_array_f_1d_init(int64_t **ptr, size_t size, int64_t value);

int create_array_f_1d(float64_t **ptr, size_t size);
int create_array_f_1d_init(float64_t **ptr, size_t size, float64_t value);

void display_array_i_1d(const int64_t *ptr, size_t size);
void display_array_f_1d(const float64_t *ptr, size_t size);
