#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

void destroy_array_1d(int64_t **ptr, size_t size);

int create_array_1d(int64_t **ptr, size_t size);
int create_array_1d_init(int64_t **ptr, size_t size, int64_t value);



void display_array_1d(const int64_t *ptr, size_t size);
