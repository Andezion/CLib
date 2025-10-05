#include "matrix_math.h"
#include "matrix.h"
#include <stdarg.h>

struct int_matrix *mul_int_matrices(const size_t n, ...)
{
    va_list args;
    va_start(args, n);

    struct int_matrix *result = va_arg(args, struct int_matrix *);
    if (!result || !result->data)
    {
        va_end(args);
        return NULL;
    }

    struct int_matrix *current = copy_int_matrix(result);
    if (!current)
    {
        va_end(args);
        return NULL;
    }

    for (size_t i = 1; i < n; i++)
    {
        const struct int_matrix *next = va_arg(args, const struct int_matrix *);
        if (!next || !next->data || current->cols != next->rows)
        {
            free_int_matrix(&current);
            va_end(args);
            return NULL;
        }

        struct int_matrix *temp = create_int_matrix(current->rows, next->cols);
        if (!temp)
        {
            free_int_matrix(&current);
            va_end(args);
            return NULL;
        }

        for (size_t r = 0; r < current->rows; r++)
        {
            for (size_t c = 0; c < next->cols; c++)
            {
                int64_t sum = 0;
                for (size_t k = 0; k < current->cols; k++)
                {
                    sum += current->data[r][k] * next->data[k][c];
                }
                temp->data[r][c] = sum;
            }
        }

        free_int_matrix(&current);
        current = temp;
    }

    va_end(args);
    return current;
}


int64_t sum_int_matrix(const int64_t **ptr, const size_t row, const size_t col)
{
    if (ptr == NULL || row == 0 || col == 0)
    {
        return 1;
    }

    int64_t sum = 0;
    for (size_t i = 0; i < col; i++)
    {
        for (size_t j = 0; j < row; j++)
        {
            sum += *(*(ptr + i) + j);
        }
    }
    return sum;
}
float64_t sum_float_matrix(const float64_t **ptr, const size_t row, const size_t col)
{
    if (ptr == NULL || row == 0 || col == 0)
    {
        return 1;
    }

    float64_t sum = 0;
    for (size_t i = 0; i < col; i++)
    {
        for (size_t j = 0; j < row; j++)
        {
            sum += *(*(ptr + i) + j);
        }
    }
    return sum;
}

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
