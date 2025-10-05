#pragma once
#include "matrix.h"

inline struct int_matrix *add_int_matrices(size_t n, size_t rows, size_t cols, ...);
inline struct int_matrix *sub_int_matrices(size_t n, size_t rows, size_t cols, ...);
inline struct int_matrix *mul_int_matrices(size_t n, ...);

inline struct float_matrix *add_float_matrices(size_t n, size_t rows, size_t cols, ...);
inline struct float_matrix *sub_float_matrices(size_t n, size_t rows, size_t cols, ...);

int64_t sum_int_matrix(const int64_t **ptr, size_t row, size_t col);
float64_t sum_float_matrix(const float64_t **ptr, size_t row, size_t col);