#pragma once

#include <stdint.h>

typedef double float64_t;

inline struct int_matrix *add_int_matrices(size_t n, size_t rows, size_t cols, ...);
inline struct int_matrix *sub_int_matrices(size_t n, size_t rows, size_t cols, ...);

inline struct float_matrix *add_float_matrices(size_t n, size_t rows, size_t cols, ...);
inline struct float_matrix *sub_float_matrices(size_t n, size_t rows, size_t cols, ...);