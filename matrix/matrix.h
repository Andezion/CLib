#pragma once
#include <stdlib.h>
#include <inttypes.h>

typedef double float64_t;

struct float_matrix
{
    float64_t **data;
    size_t rows;
    size_t cols;
};

struct int_matrix
{
    int64_t **data;
    size_t rows;
    size_t cols;
};

void free_int_matrix(struct int_matrix **matrix_to_delete);
void free_float_matrix(struct float_matrix **matrix_to_delete);

struct int_matrix *create_int_matrix(size_t rows, size_t cols);
struct float_matrix *create_float_matrix(size_t rows, size_t cols);

int initialization_int_matrix(struct int_matrix *matrix, int64_t value);
int initialization_float_matrix(struct float_matrix *matrix, float64_t value);

void display_int_matrix(const struct int_matrix *matrix);
void display_float_matrix(const struct float_matrix *matrix);

struct int_matrix *copy_int_matrix(const struct int_matrix *matrix);
struct float_matrix *copy_float_matrix(const struct float_matrix *matrix);

int initialization_random_int_matrix(struct int_matrix *matrix, int64_t min, int64_t max);
int initialization_random_float_matrix(struct float_matrix *matrix, float64_t min, float64_t max);
