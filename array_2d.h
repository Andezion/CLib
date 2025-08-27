#pragma once

#include <stdio.h>
#include <stdlib.h>

void destroy_array_2d(size_t ***ptr, size_t height);

int create_array_2d(size_t ***ptr, size_t width, size_t height);
int create_array_2d_init(size_t ***ptr, size_t width, size_t height, size_t value);
int create_array_2d(size_t ***ptr, size_t size);
int create_array_2d_init(size_t ***ptr, size_t size, size_t value);

void display_array_2d(size_t **ptr, size_t width, size_t height);