#include "matrix_math.h"
#include "matrix.h"
#include <stdarg.h>

inline struct int_matrix *add_int_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    struct int_matrix *matrix = create_int_matrix(rows, cols);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (arg == NULL || arg->data == NULL || arg->cols != cols || arg->rows != rows)
        {
            free_int_matrix(&matrix);

            va_end(args);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] += arg->data[i][j];
            }
        }
    }

    va_end(args);
    return matrix;
}
inline struct int_matrix *sub_int_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    struct int_matrix *matrix = create_int_matrix(rows, cols);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (arg == NULL || arg->data == NULL || arg->cols != cols || arg->rows != rows)
        {
            free_int_matrix(&matrix);

            va_end(args);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] -= arg->data[i][j];
            }
        }
    }

    va_end(args);
    return matrix;
}

inline struct float_matrix *add_float_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    struct float_matrix *matrix = create_float_matrix(rows, cols);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct float_matrix *arg = va_arg(args, struct float_matrix *);
        if (arg == NULL || arg->data == NULL || arg->cols != cols || arg->rows != rows)
        {
            free_float_matrix(&matrix);

            va_end(args);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] += arg->data[i][j];
            }
        }
    }

    va_end(args);
    return matrix;
}
inline struct float_matrix *sub_float_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    struct float_matrix *matrix = create_float_matrix(rows, cols);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 0; k < n; k++)
    {
        const struct float_matrix *arg = va_arg(args, struct float_matrix *);
        if (arg == NULL || arg->data == NULL || arg->cols != cols || arg->rows != rows)
        {
            free_float_matrix(&matrix);

            va_end(args);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] -= arg->data[i][j];
            }
        }
    }

    va_end(args);
    return matrix;
}
