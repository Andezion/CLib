#include "matrix.h"

#include <math.h>

void display_int_matrix(const struct int_matrix *matrix)
{
    if (matrix->data == NULL || matrix->rows == 0 || matrix->cols == 0 || matrix == NULL)
    {
        return;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            printf("%" PRId64 "  ", matrix->data[i][j]);
        }
        printf("\n");
    }
}
void display_float_matrix(const struct float_matrix *matrix)
{
    if (matrix->data == NULL || matrix->rows == 0 || matrix->cols == 0 || matrix == NULL)
    {
        return;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            printf("%f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

int initialization_random_int_matrix(struct int_matrix *matrix, const int64_t min, const int64_t max)
{
    if (matrix == NULL || min > max || matrix->data == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = min + rand() % (max - min + 1);
        }
    }

    return 1;
}
int initialization_random_float_matrix(struct float_matrix *matrix, const float64_t min, const float64_t max)
{
    if (matrix == NULL || min > max || matrix->data == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = min + (max - min) * ((double)rand() / RAND_MAX);
        }
    }

    return 1;
}

struct float_matrix * copy_float_matrix(const struct float_matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL ||
        matrix->rows == 0 || matrix->cols == 0)
    {
        return NULL;
    }

    struct float_matrix *new_matrix = malloc(sizeof(struct float_matrix));
    if (new_matrix == NULL)
    {
        return NULL;
    }

    new_matrix->rows = matrix->rows;
    new_matrix->cols = matrix->cols;

    new_matrix->data = malloc(new_matrix->rows * sizeof(float64_t *));
    if (new_matrix->data == NULL)
    {
        free(new_matrix);
        return NULL;
    }

    for (size_t i = 0; i < new_matrix->rows; i++)
    {
        new_matrix->data[i] = malloc(new_matrix->cols * sizeof(float64_t));
        if (new_matrix->data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(new_matrix->data[j]);
            }
            free(new_matrix->data);
            free(new_matrix);
            return NULL;
        }

        for (size_t j = 0; j < new_matrix->cols; j++)
        {
            new_matrix->data[i][j] = matrix->data[i][j];
        }
    }

    return new_matrix;
}
struct int_matrix * copy_int_matrix(const struct int_matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL ||
        matrix->rows == 0 || matrix->cols == 0)
    {
        return NULL;
    }

    struct int_matrix *new_matrix = malloc(sizeof(struct int_matrix));
    if (new_matrix == NULL)
    {
        return NULL;
    }

    new_matrix->rows = matrix->rows;
    new_matrix->cols = matrix->cols;

    new_matrix->data = malloc(new_matrix->rows * sizeof(int64_t *));
    if (new_matrix->data == NULL)
    {
        free(new_matrix);
        return NULL;
    }

    for (size_t i = 0; i < new_matrix->rows; i++)
    {
        new_matrix->data[i] = malloc(new_matrix->cols * sizeof(int64_t));
        if (new_matrix->data[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                free(new_matrix->data[j]);
            }
            free(new_matrix->data);
            free(new_matrix);
            return NULL;
        }

        for (size_t j = 0; j < new_matrix->cols; j++)
        {
            new_matrix->data[i][j] = matrix->data[i][j];
        }
    }

    return new_matrix;
}

void free_int_matrix(struct int_matrix **matrix_to_delete)
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
void free_float_matrix(struct float_matrix **matrix_to_delete)
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

struct int_matrix *create_int_matrix(const size_t rows, const size_t cols)
{
    struct int_matrix *matrix = malloc(sizeof(struct int_matrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->data = calloc(rows, sizeof(int64_t *));
    if (matrix->data == NULL)
    {
        free(matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++)
    {
        matrix->data[i] = calloc(cols, sizeof(int64_t));
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
struct float_matrix *create_float_matrix(const size_t rows, const size_t cols)
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

int initialization_int_matrix(struct int_matrix *matrix, const int64_t value)
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
int initialization_float_matrix(struct float_matrix *matrix, const float64_t value)
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

