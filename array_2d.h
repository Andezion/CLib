#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef double float64_t;

void destroy_array_i_2d(int64_t ***ptr, size_t height);
void destroy_array_f_2d(float64_t ***ptr, size_t height);

int create_array_i_2d_rect(int64_t ***ptr, size_t width, size_t height);
int create_array_i_2d_init_rect(int64_t ***ptr, size_t width, size_t height, int64_t value);
int create_array_i_2d_square(int64_t ***ptr, size_t size);
int create_array_i_2d_init_square(int64_t ***ptr, size_t size, int64_t value);

int create_array_f_2d_rect(float64_t ***ptr, size_t width, size_t height);
int create_array_f_2d_init_rect(float64_t ***ptr, size_t width, size_t height, float64_t value);
int create_array_f_2d_square(float64_t ***ptr, size_t size);
int create_array_f_2d_init_square(float64_t ***ptr, size_t size, float64_t value);

void display_array_i_2d(int64_t **ptr, size_t width, size_t height);
void display_array_f_2d(float64_t **ptr, size_t width, size_t height);

int64_t sum_array_i_2d_square(const int64_t **ptr, size_t size);
int64_t sum_array_i_2d_rect(const int64_t **ptr, size_t width, size_t height);

float64_t sum_array_f_2d_square(const float64_t **ptr, size_t size);
float64_t sum_array_f_2d_rect(const float64_t **ptr, size_t width, size_t height);