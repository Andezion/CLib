#include "matrix.h"
#include <stdio.h>

void display_int_matrix(int64_t **ptr, const size_t row, const size_t col)
{
    if (ptr == NULL || row == 0 || col == 0)
    {
        return;
    }

    for (size_t i = 0; i < col; i++)
    {
        for (size_t j = 0; j < row; j++)
        {
            printf("%" PRId64 "  ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
}
void display_float_matrix(float64_t **ptr, const size_t row, const size_t col)
{
    if (ptr == NULL || row == 0 || col == 0)
    {
        return;
    }

    for (size_t i = 0; i < col; i++)
    {
        for (size_t j = 0; j < row; j++)
        {
            printf("%f ", *(*(ptr + i) + j));
        }
        printf("\n");
    }
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

inline void free_int_matrix(struct int_matrix **matrix_to_delete)
{
    if (matrix_to_delete == NULL || *matrix_to_delete == NULL)
    {
        return;
    }

    struct int_matrix *matrix = *matrix_to_delete;

    if (matrix->data != NULL)
    {
        for (size_t i = 0; i < matrix->rows; i++)
        {
            free(matrix->data[i]);
        }
        free(matrix->data);
    }

    free(matrix);
    *matrix_to_delete = NULL;
}
inline void free_float_matrix(struct float_matrix **matrix_to_delete)
{
    if (matrix_to_delete == NULL || *matrix_to_delete == NULL)
    {
        return;
    }

    struct float_matrix *matrix = *matrix_to_delete;

    if (matrix->data != NULL)
    {
        for (size_t i = 0; i < matrix->rows; i++)
        {
            free(matrix->data[i]);
        }
        free(matrix->data);
    }

    free(matrix);
    *matrix_to_delete = NULL;
}

inline struct int_matrix *create_int_matrix(const size_t rows, const size_t cols)
{
    struct int_matrix *matrix = malloc(sizeof(struct int_matrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->data = calloc(rows, sizeof(int32_t *));
    if (matrix->data == NULL)
    {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix->data[i] = calloc(cols, sizeof(int32_t));
        if (matrix->data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}
inline struct float_matrix *create_float_matrix(const size_t rows, const size_t cols)
{
    struct float_matrix *matrix = malloc(sizeof(struct float_matrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->data = calloc(rows, sizeof(float64_t *));
    if (matrix->data == NULL)
    {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix->data[i] = calloc(cols, sizeof(float64_t));
        if (matrix->data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(matrix->data[j]);
            }
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

inline int initialization_int_matrix(const struct int_matrix *matrix, const int64_t value)
{
    if (matrix == NULL || matrix->data == NULL || matrix->cols <= 0 || matrix->rows <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = value;
        }
    }
    return 0;
}
inline int initialization_float_matrix(const struct float_matrix *matrix, const float64_t value)
{
    if (matrix == NULL || matrix->data == NULL || matrix->cols <= 0 || matrix->rows <= 0)
    {
        return -1;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = value;
        }
    }
    return 0;
}

