#include "matrix_math.h"
#include "matrix.h"
#include <stdarg.h>

struct int_matrix *mul_int_matrices(const size_t n, ...)
{
    va_list args;
    va_start(args, n);

    struct int_matrix *current_input = va_arg(args, struct int_matrix *);
    if (!current_input || !current_input->data)
    {
        va_end(args);
        return NULL;
    }

    struct int_matrix *current = copy_int_matrix(current_input);
    if (!current || !current->data)
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

struct float_matrix * mul_float_matrices(const size_t n, ...)
{
    va_list args;
    va_start(args, n);

    struct float_matrix *current = va_arg(args, struct float_matrix *);
    if (!current || !current->data)
    {
        va_end(args);
        return NULL;
    }

    for (size_t i = 1; i < n; i++)
    {
        const struct float_matrix *next = va_arg(args, const struct float_matrix *);
        if (!next || !next->data || current->cols != next->rows)
        {
            free_float_matrix(&current);
            va_end(args);
            return NULL;
        }

        struct float_matrix *temp = create_float_matrix(current->rows, next->cols);
        if (!temp)
        {
            free_float_matrix(&current);
            va_end(args);
            return NULL;
        }

        for (size_t r = 0; r < current->rows; r++)
        {
            for (size_t c = 0; c < next->cols; c++)
            {
                float64_t sum = 0;
                for (size_t k = 0; k < current->cols; k++)
                {
                    sum += current->data[r][k] * next->data[k][c];
                }
                temp->data[r][c] = sum;
            }
        }

        free_float_matrix(&current);
        current = temp;
    }

    va_end(args);
    return current;
}
struct int_matrix *div_int_matrices(const size_t n, ...)
{
    va_list args;
    va_start(args, n);

    struct int_matrix *current = va_arg(args, struct int_matrix *);
    if (!current || !current->data)
    {
        va_end(args);
        return NULL;
    }

    for (size_t i = 1; i < n; i++)
    {
        const struct int_matrix *next = va_arg(args, const struct int_matrix *);
        if (!next || !next->data || next->rows != next->cols)
        {
            free_int_matrix(&current);

            va_end(args);
            return NULL;
        }

        const size_t size = next->rows;

        struct int_matrix *a = copy_int_matrix(next);
        struct int_matrix *inv = create_int_matrix(size, size);
        if (!a || !inv)
        {
            free_int_matrix(&current);
            free_int_matrix(&a);
            free_int_matrix(&inv);

            va_end(args);
            return NULL;
        }

        for (size_t r = 0; r < size; r++)
        {
            inv->data[r][r] = 1;
        }

        for (size_t r = 0; r < size; r++)
        {
            int64_t pivot = a->data[r][r];
            if (pivot == 0)
            {
                size_t swap = r + 1;
                while (swap < size && a->data[swap][r] == 0)
                {
                    swap++;
                }

                if (swap == size)
                {
                    free_int_matrix(&current);
                    free_int_matrix(&a);
                    free_int_matrix(&inv);

                    va_end(args);
                    return NULL;
                }

                int64_t *tmp = a->data[r];

                a->data[r] = a->data[swap];
                a->data[swap] = tmp;

                tmp = inv->data[r];

                inv->data[r] = inv->data[swap];
                inv->data[swap] = tmp;

                pivot = a->data[r][r];
            }

            for (size_t c = 0; c < size; c++)
            {
                a->data[r][c] = a->data[r][c] * 1000 / pivot;
                inv->data[r][c] = inv->data[r][c] * 1000 / pivot;
            }

            for (size_t rr = 0; rr < size; rr++)
            {
                if (rr == r)
                {
                    continue;
                }

                const int64_t factor = a->data[rr][r];
                for (size_t cc = 0; cc < size; cc++)
                {
                    a->data[rr][cc] -= (a->data[r][cc] * factor) / 1000;
                    inv->data[rr][cc] -= (inv->data[r][cc] * factor) / 1000;
                }
            }
        }

        free_int_matrix(&a);

        if (current->cols != inv->rows)
        {
            free_int_matrix(&current);
            free_int_matrix(&inv);
            va_end(args);
            return NULL;
        }

        struct int_matrix *temp = mul_int_matrices(2, current, inv);
        free_int_matrix(&current);
        free_int_matrix(&inv);
        if (!temp)
        {
            va_end(args);
            return NULL;
        }

        current = temp;
    }

    va_end(args);
    return current;
}
struct float_matrix * div_float_matrices(const size_t n, ...)
{
    va_list args;
    va_start(args, n);

    struct float_matrix *current = va_arg(args, struct float_matrix *);
    if (!current || !current->data)
    {
        va_end(args);
        return NULL;
    }

    for (size_t i = 1; i < n; i++)
    {
        const struct float_matrix *next = va_arg(args, const struct float_matrix *);
        if (!next || !next->data || next->rows != next->cols)
        {
            free_float_matrix(&current);

            va_end(args);
            return NULL;
        }

        const size_t size = next->rows;

        struct float_matrix *a = copy_float_matrix(next);
        struct float_matrix *inv = create_float_matrix(size, size);
        if (!a || !inv)
        {
            free_float_matrix(&current);
            free_float_matrix(&a);
            free_float_matrix(&inv);

            va_end(args);
            return NULL;
        }

        for (size_t r = 0; r < size; r++)
        {
            inv->data[r][r] = 1;
        }

        for (size_t r = 0; r < size; r++)
        {
            float64_t pivot = a->data[r][r];
            if (pivot == 0)
            {
                size_t swap = r + 1;
                while (swap < size && a->data[swap][r] == 0)
                {
                    swap++;
                }

                if (swap == size)
                {
                    free_float_matrix(&current);
                    free_float_matrix(&a);
                    free_float_matrix(&inv);

                    va_end(args);
                    return NULL;
                }

                float64_t *tmp = a->data[r];

                a->data[r] = a->data[swap];
                a->data[swap] = tmp;

                tmp = inv->data[r];

                inv->data[r] = inv->data[swap];
                inv->data[swap] = tmp;

                pivot = a->data[r][r];
            }

            for (size_t c = 0; c < size; c++)
            {
                a->data[r][c] = a->data[r][c] * 1000 / pivot;
                inv->data[r][c] = inv->data[r][c] * 1000 / pivot;
            }

            for (size_t rr = 0; rr < size; rr++)
            {
                if (rr == r)
                {
                    continue;
                }

                const float64_t factor = a->data[rr][r];
                for (size_t cc = 0; cc < size; cc++)
                {
                    a->data[rr][cc] -= (a->data[r][cc] * factor) / 1000;
                    inv->data[rr][cc] -= (inv->data[r][cc] * factor) / 1000;
                }
            }
        }

        free_float_matrix(&a);

        if (current->cols != inv->rows)
        {
            free_float_matrix(&current);
            free_float_matrix(&inv);
            va_end(args);
            return NULL;
        }

        struct float_matrix *temp = mul_float_matrices(2, current, inv);
        free_float_matrix(&current);
        free_float_matrix(&inv);
        if (!temp)
        {
            va_end(args);
            return NULL;
        }

        current = temp;
    }

    va_end(args);
    return current;
}

int64_t sum_int_matrix(const struct int_matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL || matrix->rows == 0 || matrix->cols == 0)
    {
        return 1;
    }

    int64_t sum = 0;
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            sum += *(*(matrix->data + i) + j);
        }
    }
    return sum;
}
float64_t sum_float_matrix(const struct float_matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL || matrix->rows == 0 || matrix->cols == 0)
    {
        return 1;
    }

    float64_t sum = 0;
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            sum += *(*(matrix->data + i) + j);
        }
    }
    return sum;
}

struct float_matrix * div_value_float_matrices(const size_t n, const size_t rows, const size_t cols, const float64_t value, ...)
{
    if (n == 0 || value == 0)
    {
        return NULL;
    }

    va_list args;
    va_start(args, value);

    struct float_matrix *current = va_arg(args, struct float_matrix *);
    if (!current || !current->data || current->rows != rows || current->cols != cols)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct float_matrix *next = va_arg(args, const struct float_matrix *);
        if (!next || !next->data || next->rows != next->cols)
        {
            free_float_matrix(&current);
            va_end(args);
            return NULL;
        }

        const size_t size = next->rows;

        struct float_matrix *a = copy_float_matrix(next);
        struct float_matrix *inv = create_float_matrix(size, size);
        if (!a || !inv)
        {
            free_float_matrix(&current);
            free_float_matrix(&a);
            free_float_matrix(&inv);

            va_end(args);
            return NULL;
        }

        for (size_t r = 0; r < size; r++)
        {
            inv->data[r][r] = 1;
        }

        for (size_t r = 0; r < size; r++)
        {
            float64_t pivot = a->data[r][r];
            if (pivot == 0)
            {
                size_t swap = r + 1;
                while (swap < size && a->data[swap][r] == 0)
                {
                    swap++;
                }

                if (swap == size)
                {
                    free_float_matrix(&current);
                    free_float_matrix(&a);
                    free_float_matrix(&inv);
                    va_end(args);
                    return NULL;
                }

                float64_t *tmp = a->data[r];
                a->data[r] = a->data[swap];
                a->data[swap] = tmp;

                tmp = inv->data[r];
                inv->data[r] = inv->data[swap];
                inv->data[swap] = tmp;

                pivot = a->data[r][r];
            }

            for (size_t c = 0; c < size; c++)
            {
                a->data[r][c] = a->data[r][c] * 1000.0 / pivot;
                inv->data[r][c] = inv->data[r][c] * 1000.0 / pivot;
            }

            for (size_t rr = 0; rr < size; rr++)
            {
                if (rr == r)
                {
                    continue;
                }

                const float64_t factor = a->data[rr][r];
                for (size_t cc = 0; cc < size; cc++)
                {
                    a->data[rr][cc] -= a->data[r][cc] * factor / 1000.0;
                    inv->data[rr][cc] -= inv->data[r][cc] * factor / 1000.0;
                }
            }
        }

        free_float_matrix(&a);

        if (current->cols != inv->rows)
        {
            free_float_matrix(&current);
            free_float_matrix(&inv);
            va_end(args);
            return NULL;
        }

        struct float_matrix *temp = mul_float_matrices(2, current, inv);
        free_float_matrix(&current);
        free_float_matrix(&inv);

        if (!temp)
        {
            va_end(args);
            return NULL;
        }

        current = temp;
    }

    for (size_t i = 0; i < current->rows; i++)
    {
        for (size_t j = 0; j < current->cols; j++)
        {
            current->data[i][j] /= value;
        }
    }

    va_end(args);
    return current;
}
struct float_matrix * mul_value_float_matrices(const size_t n, const size_t rows, const size_t cols, const float64_t value, ...)
{
    va_list args;
    va_start(args, value);

    struct float_matrix *matrix = va_arg(args, struct float_matrix *);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix->data[i][j] = 1.0;
        }
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct float_matrix *arg = va_arg(args, struct float_matrix *);
        if (!arg || !arg->data || arg->cols != cols || arg->rows != rows)
        {
            free_float_matrix(&matrix);
            va_end(args);
            return NULL;
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] *= arg->data[i][j];
            }
        }
    }

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix->data[i][j] *= value;
        }
    }

    va_end(args);
    return matrix;
}
struct float_matrix * sub_value_float_matrices(const size_t n, const size_t rows, const size_t cols, const float64_t value, ...)
{
    va_list args;
    va_start(args, value);

    struct float_matrix *matrix_input = va_arg(args, struct float_matrix *);
    if (!matrix_input)
    {
        va_end(args);
        return NULL;
    }

    struct float_matrix *matrix = copy_float_matrix(matrix_input);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct float_matrix *arg = va_arg(args, struct float_matrix *);
        if (!arg || !arg->data || arg->cols != cols || arg->rows != rows)
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

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix->data[i][j] -= value;
        }
    }

    va_end(args);
    return matrix;
}
struct float_matrix * add_value_float_matrices(const size_t n, const size_t rows, const size_t cols, const float64_t value, ...)
{
    va_list args;
    va_start(args, value);

    struct float_matrix *matrix_input = va_arg(args, struct float_matrix *);
    if (!matrix_input)
    {
        va_end(args);
        return NULL;
    }

    struct float_matrix *matrix = copy_float_matrix(matrix_input);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct float_matrix *arg = va_arg(args, struct float_matrix *);
        if (!arg || !arg->data || arg->cols != cols || arg->rows != rows)
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

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix->data[i][j] += value;
        }
    }

    va_end(args);
    return matrix;
}

struct int_matrix * div_value_int_matrices(const size_t n, const size_t rows, const size_t cols, const int64_t value, ...)
{
    if (n == 0 || value == 0)
    {
        return NULL;
    }

    va_list args;
    va_start(args, value);

    struct int_matrix *current = va_arg(args, struct int_matrix *);
    if (!current || !current->data || current->rows != rows || current->cols != cols)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct int_matrix *next = va_arg(args, const struct int_matrix *);
        if (!next || !next->data || next->rows != next->cols)
        {
            free_int_matrix(&current);
            va_end(args);
            return NULL;
        }

        const size_t size = next->rows;

        struct int_matrix *a = copy_int_matrix(next);
        struct int_matrix *inv = create_int_matrix(size, size);
        if (!a || !inv)
        {
            free_int_matrix(&current);
            free_int_matrix(&a);
            free_int_matrix(&inv);
            va_end(args);
            return NULL;
        }

        for (size_t r = 0; r < size; r++)
        {
            inv->data[r][r] = 1;
        }

        for (size_t r = 0; r < size; r++)
        {
            int64_t pivot = a->data[r][r];
            if (pivot == 0)
            {
                size_t swap = r + 1;
                while (swap < size && a->data[swap][r] == 0)
                {
                    swap++;
                }

                if (swap == size)
                {
                    free_int_matrix(&current);
                    free_int_matrix(&a);
                    free_int_matrix(&inv);
                    va_end(args);
                    return NULL;
                }

                int64_t *tmp = a->data[r];
                a->data[r] = a->data[swap];
                a->data[swap] = tmp;

                tmp = inv->data[r];
                inv->data[r] = inv->data[swap];
                inv->data[swap] = tmp;

                pivot = a->data[r][r];
            }

            for (size_t c = 0; c < size; c++)
            {
                a->data[r][c] = a->data[r][c] * 1000 / pivot;
                inv->data[r][c] = inv->data[r][c] * 1000 / pivot;
            }

            for (size_t rr = 0; rr < size; rr++)
            {
                if (rr == r)
                {
                    continue;
                }

                const int64_t factor = a->data[rr][r];
                for (size_t cc = 0; cc < size; cc++)
                {
                    a->data[rr][cc] -= a->data[r][cc] * factor / 1000;
                    inv->data[rr][cc] -= inv->data[r][cc] * factor / 1000;
                }
            }
        }

        free_int_matrix(&a);

        if (current->cols != inv->rows)
        {
            free_int_matrix(&current);
            free_int_matrix(&inv);
            va_end(args);
            return NULL;
        }

        struct int_matrix *temp = mul_int_matrices(2, current, inv);
        free_int_matrix(&current);
        free_int_matrix(&inv);

        if (!temp)
        {
            va_end(args);
            return NULL;
        }

        current = temp;
    }

    for (size_t i = 0; i < current->rows; i++)
    {
        for (size_t j = 0; j < current->cols; j++)
        {
            current->data[i][j] /= value;
        }
    }

    va_end(args);
    return current;
}
struct int_matrix * mul_value_int_matrices(const size_t n, const size_t rows, const size_t cols, const int64_t value, ...)
{
    va_list args;
    va_start(args, value);

    struct int_matrix *matrix = va_arg(args, struct int_matrix *);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (!arg || !arg->data || arg->cols != cols || arg->rows != rows)
        {
            free_int_matrix(&matrix);
            va_end(args);
            return NULL;
        }

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix->data[i][j] *= arg->data[i][j];
            }
        }
    }

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix->data[i][j] *= value;
        }
    }

    va_end(args);
    return matrix;
}
struct int_matrix *sub_value_int_matrices(const size_t n, const size_t rows, const size_t cols, const int64_t value, ...)
{
    va_list args;
    va_start(args, value);

    struct int_matrix *matrix_input = va_arg(args, struct int_matrix *);
    if (!matrix_input)
    {
        va_end(args);
        return NULL;
    }

    struct int_matrix *matrix = copy_int_matrix(matrix_input);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (!arg || !arg->data || arg->cols != cols || arg->rows != rows)
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

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix->data[i][j] -= value;
        }
    }

    va_end(args);
    return matrix;
}
struct int_matrix *add_value_int_matrices(const size_t n, const size_t rows, const size_t cols, const int64_t value, ...)
{
    va_list args;
    va_start(args, value);

    struct int_matrix *matrix_input = va_arg(args, struct int_matrix *);
    if (!matrix_input)
    {
        va_end(args);
        return NULL;
    }

    struct int_matrix *matrix = copy_int_matrix(matrix_input);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
    {
        const struct int_matrix *arg = va_arg(args, struct int_matrix *);
        if (!arg || !arg->data || arg->cols != cols || arg->rows != rows)
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

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            matrix->data[i][j] += value;
        }
    }

    va_end(args);
    return matrix;
}

struct int_matrix *add_int_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    const struct int_matrix *matrix_input = va_arg(args, struct int_matrix *);
    if (matrix_input == NULL)
    {
        va_end(args);
        return NULL;
    }

    struct int_matrix *matrix = copy_int_matrix(matrix_input);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }


    for (size_t k = 1; k < n; k++)
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
struct int_matrix *sub_int_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    const struct int_matrix *matrix_input = va_arg(args, struct int_matrix *);
    if (matrix_input == NULL || matrix_input->data == NULL || matrix_input->cols != cols || matrix_input->rows != rows)
    {
        va_end(args);
        return NULL;
    }

    struct int_matrix *matrix = copy_int_matrix(matrix_input);
    if (!matrix)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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
struct float_matrix *add_float_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    const struct float_matrix *matrix_input = va_arg(args, struct float_matrix *);
    if (matrix_input == NULL)
    {
        va_end(args);
        return NULL;
    }

    struct float_matrix *matrix = copy_float_matrix(matrix_input);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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
struct float_matrix *sub_float_matrices(const size_t n, const size_t rows, const size_t cols, ...)
{
    va_list args;
    va_start(args, cols);

    const struct float_matrix *matrix_input = va_arg(args, struct float_matrix *);
    if (matrix_input == NULL)
    {
        va_end(args);
        return NULL;
    }

    struct float_matrix *matrix = copy_float_matrix(matrix_input);
    if (matrix == NULL)
    {
        va_end(args);
        return NULL;
    }

    for (size_t k = 1; k < n; k++)
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
