#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void destroy_array_2d(int64_t ***ptr, size_t height);

int create_array_2d(int64_t ***ptr, size_t width, size_t height);
int create_array_2d_init(int64_t ***ptr, size_t width, size_t height, int64_t value);
int create_array_2d(int64_t ***ptr, size_t size);
int create_array_2d_init(int64_t ***ptr, size_t size, int64_t value);

void display_array_2d(int64_t **ptr, size_t width, size_t height);