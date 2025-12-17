#pragma once
#include "matrix.h"

struct int_matrix *add_int_matrices(size_t n, size_t rows, size_t cols, ...);
struct int_matrix *sub_int_matrices(size_t n, size_t rows, size_t cols, ...);
struct int_matrix *mul_int_matrices(size_t n, ...);
struct int_matrix *div_int_matrices(size_t n, ...);

struct float_matrix *add_float_matrices(size_t n, size_t rows, size_t cols, ...);
struct float_matrix *sub_float_matrices(size_t n, size_t rows, size_t cols, ...);
struct float_matrix *mul_float_matrices(size_t n, ...);
struct float_matrix *div_float_matrices(size_t n, ...);

/* Low-level helpers for NN */
int matvec_float(const struct float_matrix *A, const struct float_array *x, struct float_array *out);
int matvec_transpose_float(const struct float_matrix *A, const struct float_array *x, struct float_array *out);

int64_t sum_int_matrix(const struct int_matrix *matrix);
float64_t sum_float_matrix(const struct float_matrix *matrix);

struct int_matrix *add_value_int_matrices(size_t n, size_t rows, size_t cols, int64_t value, ...);
struct int_matrix *sub_value_int_matrices(size_t n, size_t rows, size_t cols, int64_t value,...);
struct int_matrix *mul_value_int_matrices(size_t n, size_t rows, size_t cols, int64_t value,...);
struct int_matrix *div_value_int_matrices(size_t n, size_t rows, size_t cols, int64_t value,...);

struct float_matrix *add_value_float_matrices(size_t n, size_t rows, size_t cols, float64_t value, ...);
struct float_matrix *sub_value_float_matrices(size_t n, size_t rows, size_t cols, float64_t value, ...);
struct float_matrix *mul_value_float_matrices(size_t n, size_t rows, size_t cols, float64_t value, ...);
struct float_matrix *div_value_float_matrices(size_t n, size_t rows, size_t cols, float64_t value, ...);