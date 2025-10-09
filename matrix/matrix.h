#pragma once
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <time.h>

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

inline void free_int_matrix(struct int_matrix **matrix_to_delete);
inline void free_float_matrix(struct float_matrix **matrix_to_delete);

inline struct int_matrix *create_int_matrix(size_t rows, size_t cols);
inline struct float_matrix *create_float_matrix(size_t rows, size_t cols);

inline int initialization_int_matrix(struct int_matrix *matrix, int64_t value);
inline int initialization_float_matrix(struct float_matrix *matrix, float64_t value);

void display_int_matrix(int64_t **ptr, size_t row, size_t col);
void display_float_matrix(float64_t **ptr, size_t row, size_t col);

inline struct int_matrix *copy_int_matrix(const struct int_matrix *matrix);
inline struct float_matrix *copy_float_matrix(const struct float_matrix *matrix);

inline int initialization_random_int_matrix(struct int_matrix *matrix, int64_t min, int64_t max);
inline int initialization_random_float_matrix(struct float_matrix *matrix, float64_t min, float64_t max);
